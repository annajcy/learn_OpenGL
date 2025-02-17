#pragma once

#include "global/core.h"

#include "graphics/node.h"
#include "graphics/mesh.h"
#include "graphics/material/phong_material.h"
#include "graphics/material/edge_material.h"
#include "graphics/material/depth_material.h"

#include "utils/math_utils.h"

class Assimp_loader
{
public:
    Assimp_loader() = default;
    ~Assimp_loader() = default;

    static Material::Material_type default_material_type;
    static std::string folder_path;

    static std::shared_ptr<Node> load(const std::string& path);

private:
    static glm::mat4 to_glm_mat4(const aiMatrix4x4& value);

    static std::shared_ptr<Node> process_node(const aiScene* scene, aiNode* ai_node);

    static std::shared_ptr<Mesh> process_mesh(const aiScene* scene, aiMesh* ai_mesh, Material::Material_type material_type);

    static std::shared_ptr<Texture> process_texture(const aiScene* scene, const aiMaterial* ai_material, const aiTextureType type, unsigned int unit = 0, bool set_default_warp_filter = true);
};


