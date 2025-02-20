// MaterialSettings.h
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

    Depth_test_setting();
    ~Depth_test_setting() override;

    static Depth_test_setting disable_write_setting();
    static void reset_to_default();
    void apply() override;
};

struct Polygon_offset_setting : public Material_setting {
    bool enabled{false};
    unsigned int polygon_offset_type{GL_POLYGON_OFFSET_FILL};
    float factor{0.0f};
    float unit{0.0f};

    Polygon_offset_setting();
    ~Polygon_offset_setting() override;

    static Polygon_offset_setting enable_setting();
    static void reset_to_default();
    void apply() override;
};

struct Stencil_test_setting : public Material_setting {
    bool enable{true};
    unsigned int stencil_fail{GL_KEEP};
    unsigned int depth_fail{GL_KEEP};
    unsigned int depth_pass{GL_REPLACE};
    unsigned int stencil_mask{0xff};
    unsigned int stencil_function{GL_ALWAYS};
    unsigned int stencil_reference{1};
    unsigned int stencil_function_mask{0xff};

    Stencil_test_setting();
    ~Stencil_test_setting() override;

    static Stencil_test_setting edge_setting();
    static void reset_to_default();
    void apply() override;
};

struct Color_blend_setting : public Material_setting {
    bool enable{false};
    unsigned int src_factor{GL_SRC_ALPHA};
    unsigned int dst_factor{GL_ONE_MINUS_SRC_ALPHA};

    Color_blend_setting();
    ~Color_blend_setting() override;

    static Color_blend_setting enable_setting();
    static void reset_to_default();
    void apply() override;

};

