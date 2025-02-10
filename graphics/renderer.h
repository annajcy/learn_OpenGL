#pragma once

#include "global/core.h"
#include "application/camera/type/camera.h"
#include "graphics/mesh.h"
#include "graphics/light/light_setting.h"
#include "graphics/shader/shader_program.h"
#include "graphics/material/phong_material.h"
#include "graphics/material/white_material.h"

class Renderer {
private:
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<Light_setting> m_light_settings{};
    std::vector<std::shared_ptr<Mesh>> m_mesh_list{};    

    std::shared_ptr<Shader_program> m_phong_shader{};
    std::shared_ptr<Shader_program> m_white_shader{};

public:
    Renderer(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting);
    ~Renderer() = default;

    std::shared_ptr<Camera>& camera();
    std::shared_ptr<Light_setting>& light_setting();
    std::vector<std::shared_ptr<Mesh>>& mesh_list();

    void init_state();
    void clear();
    void render();
    void set_clear_color(const glm::vec3& color);

private:
    std::shared_ptr<Shader_program> pick_shader(Material::Material_type type);
};
