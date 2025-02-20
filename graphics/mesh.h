#pragma once

#include "global/core.h"

#include "graphics/geometry.h"
#include "graphics/node.h"

#include "graphics/material/material.h"
#include "graphics/material/phong_material.h"
#include "graphics/material/phong_opacity_mask_material.h"
#include "graphics/material/phong_specular_mask_material.h"

#include <memory>

class Mesh : public Node
{   
private:
    std::shared_ptr<Geometry> m_geometry{};
    std::shared_ptr<Material> m_material{};

public:
    Mesh(const std::shared_ptr<Geometry>& geometry, const std::shared_ptr<Material>& material);
    ~Mesh() override = default;

    std::shared_ptr<Geometry>& geometry();
    std::shared_ptr<Material>& material();

    void draw() {
        if (m_material->type() == Material::Material_type::PHONG) {

            auto phong_mat = std::dynamic_pointer_cast<Phong_material>(m_material);

            phong_mat->main_texture()->attach_texture();

            m_geometry->attach_geometry();
            m_geometry->draw();
            m_geometry->detach_geometry();

            phong_mat->main_texture()->detach_texture();

        } else if (m_material->type() == Material::Material_type::PHONG_SPECULAR_MASK) {
            auto phong_sp_mat = std::dynamic_pointer_cast<Phong_specular_mask_material>(m_material);

            phong_sp_mat->main_texture()->attach_texture();
            phong_sp_mat->specular_mask_texture()->attach_texture();

            m_geometry->attach_geometry();
            m_geometry->draw();
            m_geometry->detach_geometry();

            phong_sp_mat->main_texture()->detach_texture();
            phong_sp_mat->specular_mask_texture()->detach_texture();

        } else if (m_material->type() == Material::Material_type::DEPTH) {

            m_geometry->attach_geometry();
            m_geometry->draw();
            m_geometry->detach_geometry();

        } else if (m_material->type() == Material::Material_type::EDGE) {

            m_geometry->attach_geometry();
            m_geometry->draw();
            m_geometry->detach_geometry();

        } else if (m_material->type() == Material::Material_type::PHONG_OPACITY_MASK) {
            
            auto phong_om_mat = std::dynamic_pointer_cast<Phong_opacity_mask_material>(m_material);

            phong_om_mat->main_texture()->attach_texture();
            phong_om_mat->opcacity_mask_texture()->attach_texture();

            m_geometry->attach_geometry();
            m_geometry->draw();
            m_geometry->detach_geometry();

            phong_om_mat->main_texture()->detach_texture();
            phong_om_mat->opcacity_mask_texture()->detach_texture();
        }
    }
};
