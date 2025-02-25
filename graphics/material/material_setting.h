// MaterialSettings.h
#pragma once

#include "global/core.h"

struct Material_setting {
    Material_setting() = default;
    virtual ~Material_setting() = default;
    virtual void apply() = 0;
};

struct Depth_test_setting : public Material_setting {

    static unsigned int setting_id;

    enum class Depth_test_function {
        NEVER ,
        LESS,
        EQUAL,
        LEQUAL,
        GREATER,
        NOTEQUAL,
        GEQUAL,
        ALWAYS
    };

    constexpr static unsigned int depth_test_function_to_gl_enum(Depth_test_function function) {
        switch (function) {
            case Depth_test_function::NEVER: return GL_NEVER;
            case Depth_test_function::LESS: return GL_LESS;
            case Depth_test_function::EQUAL: return GL_EQUAL;
            case Depth_test_function::LEQUAL: return GL_LEQUAL;
            case Depth_test_function::GREATER: return GL_GREATER;
            case Depth_test_function::NOTEQUAL: return GL_NOTEQUAL;
            case Depth_test_function::GEQUAL: return GL_GEQUAL;
            case Depth_test_function::ALWAYS: return GL_ALWAYS;
            default: return GL_LESS;
        }
    }

    bool test_enabled{true};
    bool write_enabled{true};
    Depth_test_function depth_test_function{Depth_test_function::LEQUAL};

    Depth_test_setting();
    ~Depth_test_setting() override;

    static Depth_test_setting disable_write_setting();
    static void reset_to_default();
    void apply() override;
};

struct Polygon_offset_setting : public Material_setting {

    enum class Polygon_offset_type {
        FILL,
        LINE
    };

    constexpr static unsigned int polygon_offset_type_to_gl_enum(Polygon_offset_type type) {
        switch (type) {
            case Polygon_offset_type::FILL: return GL_POLYGON_OFFSET_FILL;
            case Polygon_offset_type::LINE: return GL_POLYGON_OFFSET_LINE;
        }
    }

    bool enabled{false};
    Polygon_offset_type polygon_offset_type{Polygon_offset_type::FILL};
    float factor{0.0f};
    float unit{0.0f};

    Polygon_offset_setting();
    ~Polygon_offset_setting() override;

    static Polygon_offset_setting enable_setting();
    static void reset_to_default();
    void apply() override;
};

struct Stencil_test_setting : public Material_setting {

    static unsigned int setting_id;

    enum class Stencil_op {
        KEEP,
        ZERO,
        REPLACE,
        INCR,
        INCR_WRAP,
        DECR,
        DECR_WRAP,
        INVERT
    };

    constexpr static unsigned int stencil_op_to_gl_enum(Stencil_op op) {
        switch (op) {
            case Stencil_op::KEEP: return GL_KEEP;
            case Stencil_op::ZERO: return GL_ZERO;
            case Stencil_op::REPLACE: return GL_REPLACE;
            case Stencil_op::INCR: return GL_INCR;
            case Stencil_op::INCR_WRAP: return GL_INCR_WRAP;
            case Stencil_op::DECR: return GL_DECR;
            case Stencil_op::DECR_WRAP: return GL_DECR_WRAP;
            case Stencil_op::INVERT: return GL_INVERT;
            default: return GL_KEEP;
        }
    }

    enum class Stencil_func {
        NEVER,
        LESS,
        EQUAL,
        LEQUAL,
        GREATER,
        NOTEQUAL,
        GEQUAL,
        ALWAYS
    };

    constexpr static unsigned int stencil_func_to_gl_enum(Stencil_func func) {
        switch (func) {
            case Stencil_func::NEVER: return GL_NEVER;
            case Stencil_func::LESS: return GL_LESS;
            case Stencil_func::EQUAL: return GL_EQUAL;
            case Stencil_func::LEQUAL: return GL_LEQUAL;
            case Stencil_func::GREATER: return GL_GREATER;
            case Stencil_func::NOTEQUAL: return GL_NOTEQUAL;
            case Stencil_func::GEQUAL: return GL_GEQUAL;
            case Stencil_func::ALWAYS: return GL_ALWAYS;
            default: return GL_LESS;
        }
    }

    bool enable{true};
    Stencil_op stencil_fail{Stencil_op::KEEP};
    Stencil_op depth_fail{Stencil_op::KEEP};
    Stencil_op depth_pass{Stencil_op::REPLACE};
    unsigned int stencil_mask{0xff};
    Stencil_func stencil_function{Stencil_func::ALWAYS};
    unsigned int stencil_reference{1};
    unsigned int stencil_function_mask{0xff};

    Stencil_test_setting();
    ~Stencil_test_setting() override;

    static Stencil_test_setting edge_setting();
    static void reset_to_default();
    void apply() override;
};

struct Color_blend_setting : public Material_setting {

    static unsigned int setting_id;

    enum class Blend_factor {
        ZERO,
        ONE,
        SRC_COLOR,
        ONE_MINUS_SRC_COLOR,
        DST_COLOR,
        ONE_MINUS_DST_COLOR,
        SRC_ALPHA,
        ONE_MINUS_SRC_ALPHA,
        DST_ALPHA,
        ONE_MINUS_DST_ALPHA
    };

    constexpr static unsigned int blend_factor_to_gl_enum(Blend_factor factor) {
        switch (factor) {
            case Blend_factor::ZERO: return GL_ZERO;
            case Blend_factor::ONE: return GL_ONE;
            case Blend_factor::SRC_COLOR: return GL_SRC_COLOR;
            case Blend_factor::ONE_MINUS_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
            case Blend_factor::DST_COLOR: return GL_DST_COLOR;
            case Blend_factor::ONE_MINUS_DST_COLOR: return GL_ONE_MINUS_DST_COLOR;
            case Blend_factor::SRC_ALPHA: return GL_SRC_ALPHA;
            case Blend_factor::ONE_MINUS_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
            case Blend_factor::DST_ALPHA: return GL_DST_ALPHA;
            case Blend_factor::ONE_MINUS_DST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;
            default: return GL_ZERO;
        }
    }

    bool enable{false};
    Blend_factor src_factor{Blend_factor::SRC_ALPHA};
    Blend_factor dst_factor{Blend_factor::ONE_MINUS_SRC_ALPHA};

    Color_blend_setting();
    ~Color_blend_setting() override;

    static Color_blend_setting enable_setting();
    static void reset_to_default();
    void apply() override;

};

struct Face_culling_setting : public Material_setting {

    static unsigned int setting_id;

    enum class Front_face {
        CW,
        CCW
    };

    constexpr static unsigned int front_face_to_gl_enum(Front_face face) {
        switch (face) {
            case Front_face::CW: return GL_CW;
            case Front_face::CCW: return GL_CCW;
            default: return GL_CCW;
        }
    }

    enum class Cull_face {
        FRONT,
        BACK,
        FRONT_AND_BACK
    };

    constexpr static unsigned int cull_face_to_gl_enum(Cull_face face) {
        switch (face) {
            case Cull_face::FRONT: return GL_FRONT;
            case Cull_face::BACK: return GL_BACK;
            case Cull_face::FRONT_AND_BACK: return GL_FRONT_AND_BACK;
            default: return GL_BACK;
        }
    }

    bool enable{false};
    Front_face front_face{Front_face::CCW};
    Cull_face cull_face{Cull_face::BACK};

    Face_culling_setting();
    ~Face_culling_setting() override;

    static Face_culling_setting enable_setting();
    static void reset_to_default();
    void apply() override;
};