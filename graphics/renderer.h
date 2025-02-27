#pragma once

#include "global/core.h"

#include "graphics/camera/camera.h"
#include "graphics/mesh.h"
#include "graphics/light/light_setting.h"

#include "graphics/material/phong_material.h"
#include "graphics/material/edge_material.h"
#include "graphics/material/depth_material.h"

#include "graphics/frame_buffer.h"

#include "scene.h"

class Renderer {
private:
    std::shared_ptr<Camera> m_camera{};
    std::shared_ptr<Light_setting> m_light_settings{};
    std::shared_ptr<Scene> m_scene{};

public:
    Renderer();
    ~Renderer() = default;

    std::shared_ptr<Camera>& camera();
    std::shared_ptr<Light_setting>& light_setting();
    std::shared_ptr<Scene>& scene();

    void render_mesh(const std::shared_ptr<Mesh>& mesh);
    void set_render_list(const std::shared_ptr<Node>& node);
    void init_state();
    void clear();
    void render(std::shared_ptr<Frame_buffer> fbo = nullptr);
    void set_clear_color(const glm::vec3& color);

    static std::vector<std::shared_ptr<Mesh>> opaque_meshes;
    static std::vector<std::shared_ptr<Mesh>> albedo_meshes;

};
