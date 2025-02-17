#include "assimp_loader.h"

Material::Material_type Assimp_loader::default_material_type = Material::Material_type::PHONG;
std::string Assimp_loader::folder_path{};

// Static function: Converts aiMatrix4x4 to glm::mat4
glm::mat4 Assimp_loader::to_glm_mat4(const aiMatrix4x4& value) {
    return glm::mat4{
        value.a1, value.a2, value.a3, value.a4,
        value.b1, value.b2, value.b3, value.b4,
        value.c1, value.c2, value.c3, value.c4,
        value.d1, value.d2, value.d3, value.d4
    };
}

// Static function: Processes a node in the scene
std::shared_ptr<Node> Assimp_loader::process_node(const aiScene* scene, aiNode* ai_node) {
    std::shared_ptr<Node> node = std::make_shared<Node>();

    glm::mat4 local_transform = to_glm_mat4(ai_node->mTransformation);

    utils::decompose_transform(local_transform, node->position(), node->rotation(), node->scale());

    // Process meshes attached to the node
    for (int i = 0; i < ai_node->mNumMeshes; i++) {
        int id = ai_node->mMeshes[i];
        auto ai_mesh = scene->mMeshes[id];
        auto mesh = process_mesh(scene, ai_mesh, default_material_type);
        node->add_child(mesh);
    }

    // Recursively process child nodes
    for (int i = 0; i < ai_node->mNumChildren; i++) {
        auto child = process_node(scene, ai_node->mChildren[i]);
        node->add_child(child);
    }

    return node;
}

// Static function: Processes a mesh in the scene
std::shared_ptr<Mesh> Assimp_loader::process_mesh(const aiScene* scene, aiMesh* ai_mesh, Material::Material_type material_type) {
    std::vector<float> positions{};
    std::vector<float> normals{};
    std::vector<float> uvs{};
    std::vector<unsigned int> indices{};

    // Process vertices
    for (int i = 0; i < ai_mesh->mNumVertices; i++) {
        positions.push_back(ai_mesh->mVertices[i].x);
        positions.push_back(ai_mesh->mVertices[i].y);
        positions.push_back(ai_mesh->mVertices[i].z);

        normals.push_back(ai_mesh->mNormals[i].x);
        normals.push_back(ai_mesh->mNormals[i].y);
        normals.push_back(ai_mesh->mNormals[i].z);

        if (ai_mesh->mTextureCoords[0]) {
            uvs.push_back(ai_mesh->mTextureCoords[0][i].x);
            uvs.push_back(ai_mesh->mTextureCoords[0][i].y);
        } else {
            std::cerr << "Error: Model has no UV!" << std::endl;
            uvs.push_back(0.0f);
            uvs.push_back(0.0f);
        }
    }

    // Process faces (indices)
    for (int i = 0; i < ai_mesh->mNumFaces; i++) {
        auto face = ai_mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Create geometry and material
    std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>(positions, normals, uvs, indices);
    std::shared_ptr<Material> material{};

    if (material_type == Material::Material_type::PHONG) {
        auto phong_mat = std::make_shared<Phong_material>();
        aiMaterial* ai_material = scene->mMaterials[ai_mesh->mMaterialIndex];

        auto diffuse = process_texture(scene, ai_material, aiTextureType::aiTextureType_DIFFUSE, 0);
        phong_mat->main_texture() = diffuse ? diffuse : Texture::create_default_texture(0);

        auto specular = process_texture(scene, ai_material, aiTextureType::aiTextureType_SPECULAR, 1);
        phong_mat->specular_mask_texture() = specular ? specular : Texture::create_default_texture(1);

        material = phong_mat;
    } else if (material_type == Material::Material_type::WHITE){
        material = std::make_shared<White_material>();
    } else {
        material = std::make_shared<Depth_material>();
    }

    return std::make_shared<Mesh>(geometry, material);
}

// Static function: Processes a texture for the material
std::shared_ptr<Texture> Assimp_loader::process_texture(
    const aiScene* scene, const aiMaterial* ai_material, const aiTextureType type, 
    unsigned int unit, bool set_default_warp_filter) 
{
    std::shared_ptr<Texture> texture{};
    aiString ai_path{};
    ai_material->Get(AI_MATKEY_TEXTURE(type, 0), ai_path);
    
    if (!ai_path.length) return nullptr;  // No texture

    const aiTexture* ai_texture = scene->GetEmbeddedTexture(ai_path.C_Str());
    
    if (ai_texture) {
        unsigned char* data = reinterpret_cast<unsigned char*>(ai_texture->pcData);
        int data_size = ai_texture->mHeight ? ai_texture->mHeight * ai_texture->mWidth * 4 : ai_texture->mWidth;
        texture = Texture::create_texture_from_memory(folder_path + ai_path.C_Str(), data, data_size, unit, set_default_warp_filter);
    } else {
        texture = Texture::create_texture_from_path(folder_path + ai_path.C_Str(), folder_path + ai_path.C_Str(), unit, set_default_warp_filter);
    }

    return texture;
}

// Static function: Loads a model from a path
std::shared_ptr<Node> Assimp_loader::load(const std::string& path) {
    Assimp::Importer importer{};
    auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Failed to load model" << std::endl;
        return nullptr;
    }

    folder_path = path;
    while (folder_path.back() != '/') folder_path.pop_back();

    auto node = process_node(scene, scene->mRootNode);
    return node;
}
