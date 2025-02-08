#include "material.h"

Material::Material(Material_type type) : m_type(type) {}

Material::Material_type Material::type() const {
    return m_type;
}
