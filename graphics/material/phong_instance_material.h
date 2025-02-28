#pragma once

#include "material.h"
#include "phong_material.h"
#include "graphics/texture.h"

class Phong_instance_material : public Phong_material
{
public:
    Phong_instance_material();
    ~Phong_instance_material() override;
};
