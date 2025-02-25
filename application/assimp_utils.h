#pragma once

#include "global/core.h"
#include "graphics/texture.h"

class Assimp_utils
{

public:
    static std::string folder_path;
    static glm::mat4 to_glm_mat4(const aiMatrix4x4& value);
    static std::shared_ptr<Texture> process_texture(const aiScene* scene, const aiMaterial* ai_material, const aiTextureType type, unsigned int unit = 0);
};
