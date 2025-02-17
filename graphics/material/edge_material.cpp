#include "edge_material.h"

Edge_material::Edge_material() : Material(Material_type::EDGE) {
    m_stencil_test_setting = Stencil_test_setting::edge_setting();
}
