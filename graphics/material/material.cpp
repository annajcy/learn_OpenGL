#include "material.h"

Material::Material(Material_type type, const std::shared_ptr<Shader_program>& shader) : m_type(type), m_shader(shader) {}
Material::~Material() = default;
Material::Material_type Material::type() const { return m_type; }

Depth_test_setting Material::depth_test_setting() const { return m_depth_test_setting; }
Depth_test_setting& Material::depth_test_setting() { return m_depth_test_setting; }

Stencil_test_setting Material::stencil_test_setting() const { return m_stencil_test_setting; }
Stencil_test_setting& Material::stencil_test_setting() { return m_stencil_test_setting; }

Polygon_offset_setting Material::polygon_offset_setting() const { return m_polygon_offset_setting; }
Polygon_offset_setting& Material::polygon_offset_setting() { return m_polygon_offset_setting; }

Color_blend_setting& Material::color_blend_setting() { return m_color_blend_setting; }
Color_blend_setting Material::color_blend_setting() const { return m_color_blend_setting; }

Face_culling_setting& Material::face_cull_setting() { return m_face_cull_setting; }
Face_culling_setting Material::face_cull_setting() const { return m_face_cull_setting; }

std::shared_ptr<Shader_program> Material::shader() const { return m_shader; }
std::shared_ptr<Shader_program>& Material::shader() { return m_shader; }

void Material::before_geometry_draw() {}
void Material::after_geometry_draw() {}

void Material::load_from_assimp(const aiScene* scene, const aiMaterial* assimp_material) { }
