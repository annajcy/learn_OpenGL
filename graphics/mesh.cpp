#include "mesh.h"

Mesh::Mesh(const std::shared_ptr<Geometry>& geometry, const std::shared_ptr<Material>& material) 
    : Node(Node_type::MESH), m_geometry(geometry), m_material(material) {}

std::shared_ptr<Geometry>& Mesh::geometry() { return m_geometry; }
std::shared_ptr<Material>& Mesh::material() { return m_material; }

void Mesh::draw() {

    m_material->before_geometry_draw();
    m_geometry->draw();
    m_material->after_geometry_draw();
}
