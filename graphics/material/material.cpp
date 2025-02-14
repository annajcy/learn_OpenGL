#include "material.h"

Material::Material(Material_type type) : m_type(type) {}
Material::~Material() = default;
Material::Material_type Material::type() const { return m_type; }

bool Material::depth_test() const { return m_depth_test; }
bool Material::depth_write() const { return m_depth_write; }
GLenum Material::depth_function() const { return m_depth_function; }

bool& Material::depth_test() { return m_depth_test; }
bool& Material::depth_write() { return m_depth_write; }
GLenum& Material::depth_function() { return m_depth_function; }


