#include "assimp_utils.h"

std::string Assimp_utils::folder_path{};

// Static function: Converts aiMatrix4x4 to glm::mat4
glm::mat4 Assimp_utils::to_glm_mat4(const aiMatrix4x4& value) {
    return glm::mat4{
        value.a1, value.a2, value.a3, value.a4,
        value.b1, value.b2, value.b3, value.b4,
        value.c1, value.c2, value.c3, value.c4,
        value.d1, value.d2, value.d3, value.d4
    };
}

std::shared_ptr<Texture> Assimp_utils::process_texture(
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