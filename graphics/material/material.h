#pragma once

#include "global/core.h"
#include "graphics/material/material_setting.h"
#include "graphics/shader/shader_program.h"
#include "graphics/node.h"
#include "graphics/camera/camera.h"
#include "graphics/light/light_setting.h"

class Material
{
public:
    enum class Material_type {
        PHONG, EDGE, DEPTH
    };

protected:

    std::shared_ptr<Shader_program> m_shader{};

    Material_type m_type{};
    
    Depth_test_setting m_depth_test_setting{};
    Polygon_offset_setting m_polygon_offset_setting{};
    Stencil_test_setting m_stencil_test_setting{};

public:
    explicit Material(Material_type type);
    virtual ~Material();

    [[nodiscard]] Material_type type() const;

    [[nodiscard]] Depth_test_setting depth_test_setting() const;
    [[nodiscard]] Polygon_offset_setting polygon_offset_setting() const;
    [[nodiscard]] Stencil_test_setting stencil_test_setting() const;
    [[nodiscard]] std::shared_ptr<Shader_program> shader() const;

    Depth_test_setting& depth_test_setting();
    Polygon_offset_setting& polygon_offset_setting();
    Stencil_test_setting& stencil_test_setting();
    std::shared_ptr<Shader_program>& shader();

    virtual void update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) = 0;
};
