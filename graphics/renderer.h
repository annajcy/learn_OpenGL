#pragma once

#include "global/core.h"

#include "graphics/camera/type/camera.h"
#include "graphics/mesh.h"
#include "graphics/light/light_setting.h"
#include "graphics/shader/shader_program.h"
#include "graphics/material/phong_material.h"
#include "graphics/material/white_material.h"

#include "scene.h"

class Renderer {
private:
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<Light_setting> m_light_settings{};

    std::shared_ptr<Scene> m_scene{};

    std::shared_ptr<Shader_program> m_phong_shader{};
    std::shared_ptr<Shader_program> m_white_shader{};

public:
    Renderer(const std::shared_ptr<Scene> &scene, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting);
    ~Renderer() = default;

    std::shared_ptr<Camera>& camera();
    std::shared_ptr<Light_setting>& light_setting();
    std::shared_ptr<Scene>& scene();

    void render_mesh(const std::shared_ptr<Mesh>& mesh);
    void render_node(const std::shared_ptr<Node>& node);
    void init_state();
    void clear();
    void render();
    void set_clear_color(const glm::vec3& color);

private:
    std::shared_ptr<Shader_program> pick_shader(Material::Material_type type);

    void update_white_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::shared_ptr<Mesh> &mesh);
    void update_phong_shader_uniform(const std::shared_ptr<Shader_program>& shader, const std::shared_ptr<Mesh> &mesh);
};
