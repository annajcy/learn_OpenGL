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

// Process and load a texture from an Assimp material
std::shared_ptr<Texture> Assimp_utils::process_texture(
    const aiScene* scene, const aiMaterial* ai_material, const aiTextureType type, 
    unsigned int unit) 
{
    std::shared_ptr<Texture> texture{};
    aiString ai_path{};
    // Get the texture path from the material
    ai_material->Get(AI_MATKEY_TEXTURE(type, 0), ai_path);
    
    // Return nullptr if no texture path is found
    if (!ai_path.length) return nullptr;

    // Check if the texture is embedded in the scene
    const aiTexture* ai_texture = scene->GetEmbeddedTexture(ai_path.C_Str());
    
    if (ai_texture) {
        // Process embedded texture
        unsigned char* data = reinterpret_cast<unsigned char*>(ai_texture->pcData);
        // Calculate data size (compressed or uncompressed)
        int data_size = ai_texture->mHeight ? ai_texture->mHeight * ai_texture->mWidth * 4 : ai_texture->mWidth;
        // Create texture from memory
        texture = Texture::create_texture_from_memory(data, data_size, unit, folder_path + ai_path.C_Str());
    } else {
        // Load texture from external file
        texture = Texture::create_texture_from_path(folder_path + ai_path.C_Str(), unit, folder_path + ai_path.C_Str());
    }

    // Return the created texture
    return texture;
}