// MaterialSettings.cpp
#include "material_setting.h"

//Depth test

Depth_test_setting::Depth_test_setting() : Material_setting() {}
Depth_test_setting::~Depth_test_setting() = default;

unsigned int Depth_test_setting::setting_id{ GL_DEPTH_TEST };

void Depth_test_setting::reset_to_default() {
    glEnable(setting_id);
    glDepthFunc(depth_test_function_to_gl_enum(Depth_test_function::LEQUAL));
    glDepthMask(true);
}

void Depth_test_setting::apply() {
    if (test_enabled) {
        glEnable(setting_id);
        glDepthFunc(depth_test_function_to_gl_enum(depth_test_function));
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    if (write_enabled) {
        glDepthMask(true);
    } else {
        glDepthMask(false);
    }
}

Depth_test_setting Depth_test_setting::disable_write_setting() {
    auto setting = Depth_test_setting();
    setting.write_enabled = false;
    return setting;
}

//Polygon offset

Polygon_offset_setting::Polygon_offset_setting() : Material_setting() {}
Polygon_offset_setting::~Polygon_offset_setting() = default;

Polygon_offset_setting Polygon_offset_setting::enable_setting() {
    Polygon_offset_setting setting{};
    setting.enabled = true;
    setting.polygon_offset_type = Polygon_offset_type::FILL;
    setting.factor = 0.0f;
    setting.unit = 0.0f;
    return setting;
}

void Polygon_offset_setting::reset_to_default() {
    glDisable(polygon_offset_type_to_gl_enum(Polygon_offset_type::FILL));
    glDisable(polygon_offset_type_to_gl_enum(Polygon_offset_type::LINE));
}

void Polygon_offset_setting::apply() {
    if (enabled) {
        glEnable(polygon_offset_type_to_gl_enum(polygon_offset_type));
        glPolygonOffset(factor, unit);
    } else {
        glDisable(polygon_offset_type_to_gl_enum(Polygon_offset_type::FILL));
        glDisable(polygon_offset_type_to_gl_enum(Polygon_offset_type::LINE));
    }
}

//Stencil Test

unsigned int Stencil_test_setting::setting_id{ GL_STENCIL_TEST };

Stencil_test_setting::Stencil_test_setting() : Material_setting() {}
Stencil_test_setting::~Stencil_test_setting() = default;

// Stencil Test
Stencil_test_setting Stencil_test_setting::edge_setting() {
    Stencil_test_setting setting{};
    setting.enable = true;
    setting.stencil_fail = Stencil_op::KEEP;
    setting.depth_fail = Stencil_op::KEEP;
    setting.depth_pass = Stencil_op::KEEP;
    setting.stencil_mask = 0x00;
    setting.stencil_function = Stencil_func::NOTEQUAL;
    setting.stencil_reference = 1;
    setting.stencil_function_mask = 0xff;
    return setting;
}

void Stencil_test_setting::reset_to_default() {
    glEnable(setting_id);
    glStencilOp(
        stencil_op_to_gl_enum(Stencil_op::KEEP),
        stencil_op_to_gl_enum(Stencil_op::KEEP),
        stencil_op_to_gl_enum(Stencil_op::KEEP)
    );
    glStencilMask(0xff);
}

void Stencil_test_setting::apply() {
    if (enable) {
        glEnable(setting_id);
        glStencilOp(
            stencil_op_to_gl_enum(stencil_fail),
            stencil_op_to_gl_enum(depth_fail),
            stencil_op_to_gl_enum(depth_pass)
        );
        glStencilMask(stencil_mask);
        glStencilFunc(
            stencil_func_to_gl_enum(stencil_function),
            stencil_reference,
            stencil_function_mask
        );
    } else {
        glDisable(setting_id);
    }
}

// Color blend

unsigned int Color_blend_setting::setting_id{ GL_BLEND };
Color_blend_setting::Color_blend_setting() : Material_setting() {}
Color_blend_setting::~Color_blend_setting() = default;

Color_blend_setting Color_blend_setting::enable_setting() {
    auto setting = Color_blend_setting();
    setting.enable = true;
    return setting;
 }
void Color_blend_setting::reset_to_default() {
    glDisable(setting_id);
}

void Color_blend_setting::apply() {
    if (enable) {
        glEnable(setting_id);
        glBlendFunc(
            blend_factor_to_gl_enum(src_factor),
            blend_factor_to_gl_enum(dst_factor)
        );
    } else {
        glDisable(setting_id);
    }
}

// Face culling

unsigned int Face_culling_setting::setting_id{ GL_CULL_FACE };
Face_culling_setting::Face_culling_setting() : Material_setting() {}
Face_culling_setting::~Face_culling_setting() = default;

Face_culling_setting Face_culling_setting::enable_setting() {
    auto setting = Face_culling_setting();
    setting.enable = true;
    return setting;
}

void Face_culling_setting::reset_to_default() {
    glDisable(setting_id);
}

void Face_culling_setting::apply() {
    if (enable) {
        glEnable(setting_id);
        glFrontFace(front_face_to_gl_enum(front_face));
        glCullFace(cull_face_to_gl_enum(cull_face));
    } else {
        glDisable(setting_id);
    }
}
