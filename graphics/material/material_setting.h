#pragma once

#include "global/core.h"

struct Material_setting {
    Material_setting() = default;
    virtual ~Material_setting() = default;
    virtual void apply() = 0;
};

struct Depth_test_setting : public Material_setting {
    bool test_enabled{true};
    bool write_enabled{true};
    GLenum depth_function{GL_LESS};

    Depth_test_setting() : Material_setting() {}
    ~Depth_test_setting() override = default;

    static void reset_to_default() {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);
    }

    void apply() override {
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

};

struct Polygon_offset_setting : public Material_setting {
    bool enabled{false};
    unsigned int polygon_offset_type{GL_POLYGON_OFFSET_FILL};
    float factor{0.0f};
    float unit{0.0f};

    Polygon_offset_setting() : Material_setting() {}
    ~Polygon_offset_setting() override = default;

    static Polygon_offset_setting enable_setting() {
        Polygon_offset_setting setting{};
        setting.enabled = true;
        setting.polygon_offset_type = GL_POLYGON_OFFSET_FILL;
        setting.factor = 0.0f;
        setting.unit = 0.0f;
        return setting;
    }

    static void reset_to_default() {
        glDisable(GL_POLYGON_OFFSET_FILL);
	    glDisable(GL_POLYGON_OFFSET_LINE);
    }

    void apply() override {
        if (enabled) {
            glEnable(polygon_offset_type);
            glPolygonOffset(factor, unit);
        } else {
            glDisable(GL_POLYGON_OFFSET_FILL);
            glDisable(GL_POLYGON_OFFSET_LINE);
        }
    }
};

struct Stencil_test_setting : public Material_setting{
    bool enable{true};

    unsigned int stencil_fail{GL_KEEP};
    unsigned int depth_fail{GL_KEEP};
    unsigned int depth_pass{GL_REPLACE};

    unsigned int stencil_mask{0xff};

    unsigned int stencil_function{GL_ALWAYS};
    unsigned int stencil_reference{1};
    unsigned int stencil_function_mask{0xff};

    Stencil_test_setting() : Material_setting() {}
    ~Stencil_test_setting() override = default;

    static Stencil_test_setting edge_setting() {
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

    static void reset_to_default() {
        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glStencilMask(0xff);
    }

    void apply() override {
        if (enable) {
            glEnable(GL_STENCIL_TEST);

            glStencilOp(stencil_fail, depth_fail, depth_pass);
            glStencilMask(stencil_mask);
            glStencilFunc(stencil_function, stencil_reference, stencil_function_mask);
        } else {
            glDisable(GL_STENCIL_TEST);
        }
    }
};