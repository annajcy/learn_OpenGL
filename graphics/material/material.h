#pragma once

#include "global/core.h"

struct Depth_test_setting {
    bool test_enabled{true};
    bool write_enabled{true};
    GLenum depth_function{GL_LESS};
};

struct Polygon_offset_setting {
    bool enabled{};
    unsigned int polygon_offset_type{GL_POLYGON_OFFSET_FILL};
    float factor{};
    float unit{};
};


class Material
{
public:
    enum class Material_type {
        PHONG,
        WHITE,
        DEPTH
    };

private:

    Material_type m_type{};
    
    Depth_test_setting m_depth_test_setting{};
    Polygon_offset_setting m_polygon_offset_setting{};

public:
    explicit Material(Material_type type);
    virtual ~Material();

    [[nodiscard]] Material_type type() const;
    [[nodiscard]] Depth_test_setting depth_test_setting() const;
    [[nodiscard]] Polygon_offset_setting polygon_offset_setting() const;

    Depth_test_setting& depth_test_setting();
    Polygon_offset_setting& polygon_offset_setting();
};
