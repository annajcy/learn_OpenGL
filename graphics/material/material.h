#pragma once

#include "global/core.h"

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
    bool m_depth_test{true};
    bool m_depth_write{true};
    GLenum m_depth_function{GL_LESS};

public:
    explicit Material(Material_type type);
    virtual ~Material();

    [[nodiscard]] Material_type type() const;
    [[nodiscard]] bool depth_test() const;
    [[nodiscard]] bool depth_write() const;
    [[nodiscard]] GLenum depth_function() const;

    bool& depth_test();
    bool& depth_write();
    GLenum& depth_function();
};
