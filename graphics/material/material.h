#pragma once

#include "global/core.h"
#include "graphics/material/material_setting.h"


class Material
{
public:
    enum class Material_type {
        PHONG,
        EDGE,
        DEPTH
    };

protected:

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

    Depth_test_setting& depth_test_setting();
    Polygon_offset_setting& polygon_offset_setting();
    Stencil_test_setting& stencil_test_setting();
};
