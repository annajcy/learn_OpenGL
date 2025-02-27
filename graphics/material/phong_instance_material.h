#pragma once

#include "material.h"
#include "phong_material.h"
#include "graphics/texture.h"

class Phong_instance_material : public Phong_material
{
public:
    Phong_instance_material() :
    Phong_material( Material_type::PHONG_INSTANCE,
        Shader_program::create_shader_program("assets/shaders/shading/phong_instance/phong_instance.vert", "assets/shaders/shading/phong_instance/phong_instance.frag")) {}
    ~Phong_instance_material() override = default;

};
