#pragma once

#include "material.h"
#include "graphics/texture.h"
#include <memory>

class Phong_material : public Material
{
private:
    float m_kd{1.0f};
    float m_ks{1.0f};
    float m_ka{1.0f};
    float m_shiness{16.0f};

    std::shared_ptr<Texture> m_main_texture{};
    std::shared_ptr<Texture> m_specular_mask_texture{};

public:
    Phong_material();
    ~Phong_material() override = default;

    [[nodiscard]] float kd() const;
    [[nodiscard]] float ks() const;
    [[nodiscard]] float ka() const;
    [[nodiscard]] float shiness() const;

    float& kd();
    float& ks();
    float& ka();
    float& shiness();

    std::shared_ptr<Texture>& main_texture();
    std::shared_ptr<Texture>& specular_mask_texture();
};
