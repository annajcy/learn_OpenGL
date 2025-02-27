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
        PHONG_SPECULAR_MASK, PHONG_OPACITY_MASK, PHONG_INSTANCE ,PHONG, EDGE, DEPTH, SCREEN, CUBE_MAP, SPERICAL_MAP
    };

protected:

    std::shared_ptr<Shader_program> m_shader{};

    Material_type m_type{};
    
    Depth_test_setting m_depth_test_setting{};
    Polygon_offset_setting m_polygon_offset_setting{};
    Stencil_test_setting m_stencil_test_setting{};
    Color_blend_setting m_color_blend_setting{};
    Face_culling_setting m_face_cull_setting{};

public:
    explicit Material(Material_type type, const std::shared_ptr<Shader_program>& shader);
    virtual ~Material();

    [[nodiscard]] Material_type type() const;

    [[nodiscard]] Depth_test_setting depth_test_setting() const;
    [[nodiscard]] Polygon_offset_setting polygon_offset_setting() const;
    [[nodiscard]] Stencil_test_setting stencil_test_setting() const;
    [[nodiscard]] Color_blend_setting color_blend_setting() const;
    [[nodiscard]] std::shared_ptr<Shader_program> shader() const;
    [[nodiscard]] Face_culling_setting face_cull_setting() const;

    Depth_test_setting& depth_test_setting();
    Polygon_offset_setting& polygon_offset_setting();
    Stencil_test_setting& stencil_test_setting();
    Color_blend_setting& color_blend_setting();
    Face_culling_setting& face_cull_setting();

    std::shared_ptr<Shader_program>& shader();

    virtual void before_geometry_draw();
    virtual void after_geometry_draw();
    virtual void load_from_assimp(const aiScene* scene, const aiMaterial* assimp_material);

    virtual void update_uniform(const std::shared_ptr<Node>& node, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Light_setting>& light_setting) = 0;
};
