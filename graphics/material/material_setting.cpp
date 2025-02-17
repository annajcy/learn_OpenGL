// MaterialSettings.cpp
#include "material_setting.h"

//Depth test

Depth_test_setting::Depth_test_setting() : Material_setting() {}
Depth_test_setting::~Depth_test_setting() {}

void Depth_test_setting::reset_to_default() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
}

void Depth_test_setting::apply() {
    if (test_enabled) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(depth_function);
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    if (write_enabled) {
        glDepthMask(GL_TRUE);
    } else {
        glDepthMask(GL_FALSE);
    }
}

//Polygon offset

Polygon_offset_setting::Polygon_offset_setting() : Material_setting() {}
Polygon_offset_setting::~Polygon_offset_setting() {}

Polygon_offset_setting Polygon_offset_setting::enable_setting() {
    Polygon_offset_setting setting{};
    setting.enabled = true;
    setting.polygon_offset_type = GL_POLYGON_OFFSET_FILL;
    setting.factor = 0.0f;
    setting.unit = 0.0f;
    return setting;
}

void Polygon_offset_setting::reset_to_default() {
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
}

void Polygon_offset_setting::apply() {
    if (enabled) {
        glEnable(polygon_offset_type);
        glPolygonOffset(factor, unit);
    } else {
        glDisable(GL_POLYGON_OFFSET_FILL);
        glDisable(GL_POLYGON_OFFSET_LINE);
    }
}

//Stencil Test

Stencil_test_setting::Stencil_test_setting() : Material_setting() {}
Stencil_test_setting::~Stencil_test_setting() {}

Stencil_test_setting Stencil_test_setting::edge_setting() {
    Stencil_test_setting setting{};
    setting.enable = true;
    setting.stencil_fail = GL_KEEP;
    setting.depth_fail = GL_KEEP;
    setting.depth_pass = GL_KEEP;
    setting.stencil_mask = 0x00;
    setting.stencil_function = GL_NOTEQUAL;
    setting.stencil_reference = 1;
    setting.stencil_function_mask = 0xff;
    return setting;
}

void Stencil_test_setting::reset_to_default() {
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glStencilMask(0xff);
}

void Stencil_test_setting::apply() {
    if (enable) {
        glEnable(GL_STENCIL_TEST);

        glStencilOp(stencil_fail, depth_fail, depth_pass);
        glStencilMask(stencil_mask);
        glStencilFunc(stencil_function, stencil_reference, stencil_function_mask);
    } else {
        glDisable(GL_STENCIL_TEST);
    }
}
