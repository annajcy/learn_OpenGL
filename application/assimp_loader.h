#pragma once

#include "global/core.h"

#include "graphics/node.h"
#include "graphics/mesh.h"
#include "graphics/material/phong_material.h"

#include "utils/math_utils.h"

class Assimp_loader
{
   
public:
    Assimp_loader() = default;
    ~Assimp_loader() = default;

    static std::string folder_path;

    static std::shared_ptr<Node> load(const std::string& path) {
        Assimp::Importer importer{};
        auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);
        
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "Failed to load model" << std::endl;
        }

        folder_path = path;
        while (folder_path.back() != '/') folder_path.pop_back();

        auto node = process_node(scene, scene->mRootNode);
        return node;
    }

private:

    static glm::mat4 to_glm_mat4(const aiMatrix4x4& value) {
        return glm::mat4{
            value.a1, value.a2, value.a3, value.a4,
            value.b1, value.b2, value.b3, value.b4,
            value.c1, value.c2, value.c3, value.c4,
            value.d1, value.d2, value.d3, value.d4
        };
    }

    static std::shared_ptr<Node> process_node(const aiScene* scene, aiNode* ai_node) {
        std::shared_ptr<Node> node = std::make_shared<Node>();

        glm::mat4 local_tranform = to_glm_mat4(ai_node->mTransformation);

        glm::vec3 position{}, rotation_euler{}, scale{};
        utils::decompose_transform(local_tranform, position, rotation_euler, scale);

        node->position() = position;
        node->rotation_euler() = rotation_euler;
        node->scale() = scale;

        for (int i = 0; i < ai_node->mNumMeshes; i ++) {
            int id = ai_node->mMeshes[i];
            auto ai_mesh = scene->mMeshes[id];
            auto mesh = process_mesh(scene, ai_mesh, Material::Material_type::PHONG);
            node->add_child(mesh);
        }

        for (int i = 0; i < ai_node->mNumChildren; i ++) {
            auto child = process_node(scene, ai_node->mChildren[i]);
            node->add_child(child);
        }

        return node;

    }

    static std::shared_ptr<Mesh> process_mesh(const aiScene* scene, aiMesh* ai_mesh, Material::Material_type material_type) {
        std::vector<float> positions{};
        std::vector<float> normals{};
        std::vector<float> uvs{};
        std::vector<unsigned int> indices{};

        for (int i = 0; i < ai_mesh->mNumVertices; i ++) {
            //第i个顶点的位置
            positions.push_back(ai_mesh->mVertices[i].x);
            positions.push_back(ai_mesh->mVertices[i].y);
            positions.push_back(ai_mesh->mVertices[i].z);

            //第i个顶点的法线
            normals.push_back(ai_mesh->mNormals[i].x);
            normals.push_back(ai_mesh->mNormals[i].y);
            normals.push_back(ai_mesh->mNormals[i].z);

            //第i个顶点的uv
            //关注其第0套uv，一般情况下是贴图uv
            if (ai_mesh->mTextureCoords[0]) {
                uvs.push_back(ai_mesh->mTextureCoords[0][i].x);
                uvs.push_back(ai_mesh->mTextureCoords[0][i].y);
            }
            else {
                std::cerr << "Error : Model has no uv!" << std::endl;
                uvs.push_back(0.0f);
			    uvs.push_back(0.0f);
            }
        }

        for (int i = 0; i < ai_mesh->mNumFaces; i ++) {
            auto face = ai_mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j ++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>(
            positions, normals, uvs, indices
        );

        std::shared_ptr<Material> material{};

        if (material_type == Material::Material_type::PHONG) {
            auto phong_mat = std::make_shared<Phong_material>();
            aiMaterial* ai_material = scene->mMaterials[ai_mesh->mMaterialIndex];
            auto diffuse = process_texture(scene, ai_material, aiTextureType::aiTextureType_DIFFUSE, 0);
            if (diffuse) phong_mat->main_texture() = diffuse;
            auto specular = process_texture(scene, ai_material, aiTextureType::aiTextureType_SPECULAR, 1);
            if (specular) phong_mat->specular_mask_texture() = specular; 
            material = phong_mat;
        }

        return std::make_shared<Mesh>(geometry, material);
    }

    static std::shared_ptr<Texture> process_texture(const aiScene* scene, const aiMaterial* ai_material, const aiTextureType type, unsigned int unit = 0, bool set_default_warp_filter = true) {
        std::shared_ptr<Texture> texture{};
        aiString ai_path{};
        ai_material->Get(AI_MATKEY_TEXTURE(type, 0), ai_path);
        if (!ai_path.length) return nullptr; 

        const aiTexture* ai_texture = scene->GetEmbeddedTexture(ai_path.C_Str());
        if (ai_texture) {
            unsigned char* data = reinterpret_cast<unsigned char*>(ai_texture->pcData);
            int data_size{};
            if (!ai_texture->mHeight) {
                data_size = ai_texture->mWidth;
            } else {
                data_size = ai_texture->mHeight * ai_texture->mWidth * 4;
            }
            texture = Texture::create_texture_from_memory(ai_path.C_Str(), data, data_size, unit, set_default_warp_filter);
        } else {
            texture = Texture::create_texture_from_path(folder_path + "/" + ai_path.C_Str(), ai_path.C_Str(), unit, set_default_warp_filter);
        }

        return texture;
    }
};

