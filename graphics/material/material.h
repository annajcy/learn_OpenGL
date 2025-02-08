#pragma once

class Material
{
public:
    enum class Material_type {
        PHONG,
        WHITE,
    };

private:
    Material_type m_type;

public:
    explicit Material(Material_type type);
    virtual ~Material() = default;

    [[nodiscard]] Material_type type() const;
};
