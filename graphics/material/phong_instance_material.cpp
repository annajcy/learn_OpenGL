#include "phong_instance_material.h"

Phong_instance_material::Phong_instance_material() :
    Phong_material(Material_type::PHONG_INSTANCE,
        Shader_program::create_shader_program("assets/shaders/shading/phong_instance/phong_instance.vert", 
        "assets/shaders/shading/phong_instance/phong_instance.frag")) 
{
}

Phong_instance_material::~Phong_instance_material() = default;
