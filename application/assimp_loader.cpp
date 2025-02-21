#include "assimp_loader.h"

Material::Material_type Assimp_loader::default_material_type = Material::Material_type::PHONG;

// Static function: Processes a node in the scene
std::shared_ptr<Node> Assimp_loader::process_node(const aiScene* scene, aiNode* ai_node) {
    std::shared_ptr<Node> node = std::make_shared<Node>();

    glm::mat4 local_transform = Assimp_utils::to_glm_mat4(ai_node->mTransformation);

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

    aiMaterial* ai_material = scene->mMaterials[ai_mesh->mMaterialIndex];
    
    // Create geometry and material
    std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>(positions, normals, uvs, indices);
    std::shared_ptr<Material> material{};

    if (material_type == Material::Material_type::PHONG) {
        material = std::make_shared<Phong_material>();
    } else if (material_type == Material::Material_type::PHONG_OPACITY_MASK) {
        material = std::make_shared<Phong_opacity_mask_material>();
    } else if (material_type == Material::Material_type::PHONG_SPECULAR_MASK) {
        material = std::make_shared<Phong_specular_mask_material>();
    } else if (material_type == Material::Material_type::EDGE){
        material = std::make_shared<Edge_material>();
    } else if (material_type == Material::Material_type::DEPTH) {
        material = std::make_shared<Depth_material>();
    } else {
        material = std::make_shared<Screen_material>();
    }

    material->load_from_assimp(scene, ai_material);

    return std::make_shared<Mesh>(geometry, material);
}

// Static function: Loads a model from a path
std::shared_ptr<Node> Assimp_loader::load(const std::string& path) {
    Assimp::Importer importer{};
    auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Failed to load model" << std::endl;
        return nullptr;
    }

    Assimp_utils::folder_path = path;
    while (Assimp_utils::folder_path.back() != '/') Assimp_utils::folder_path.pop_back();

    auto node = process_node(scene, scene->mRootNode);
    return node;
}
