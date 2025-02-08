#include "phong_material.h"

Phong_material::Phong_material() : Material(Material_type::PHONG) {}

float Phong_material::kd() const { return m_kd; }
float Phong_material::ks() const { return m_ks; }
float Phong_material::ka() const { return m_ka; }
float Phong_material::shiness() const { return m_shiness; }

float& Phong_material::kd() { return m_kd; }
float& Phong_material::ks() { return m_ks; }
float& Phong_material::ka() { return m_ka; }
float& Phong_material::shiness() { return m_shiness; }

std::shared_ptr<Texture>& Phong_material::main_texture() { return m_main_texture; }
std::shared_ptr<Texture>& Phong_material::specular_mask_texture() { return m_specular_mask_texture; }
