#include "material.h"

Material::Material(Material_type type) : m_type(type) {}
Material::~Material() = default;
Material::Material_type Material::type() const { return m_type; }

Depth_test_setting Material::depth_test_setting() const { return m_depth_test_setting; }
Depth_test_setting& Material::depth_test_setting() { return m_depth_test_setting; }

Polygon_offset_setting Material::polygon_offset_setting() const { return m_polygon_offset_setting; }
Polygon_offset_setting& Material::polygon_offset_setting() { return m_polygon_offset_setting; }


