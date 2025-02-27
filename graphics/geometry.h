#pragma once

#include "global/core.h"

class Geometry {
private:
    // OpenGL handles
    unsigned int m_vao{};
    unsigned int m_ebo{}; 
    
    unsigned int m_position_location{};
    unsigned int m_uv_location{};        
    unsigned int m_normal_location{};

    unsigned int m_position_vbo{};
    unsigned int m_uv_vbo{};        
    unsigned int m_normal_vbo{};  

    int m_indices_count{};

public:
    unsigned int vao() const;
    unsigned int ebo() const;

    unsigned int position_location() const;
    unsigned int uv_location() const;
    unsigned int normal_location() const;

    unsigned int position_vbo() const;
    unsigned int uv_vbo() const;
    unsigned int normal_vbo() const;

    int indices_count() const;

    void attach_geometry();
    void detach_geometry();
    void draw();

    Geometry() = default;

    Geometry(
        const std::vector<float> &positions,
        const std::vector<float> &normals,
        const std::vector<float> &uvs,
        const std::vector<unsigned int> &indices
    );

    void init(
        const float* positions, int position_size, 
        const float* uvs, int uv_size, 
        const float* normals, int normal_size, 
        const unsigned int* indices, int indices_size, int indices_count
    );

    ~Geometry();

    static std::shared_ptr<Geometry> create_screen();
    static std::shared_ptr<Geometry> create_box(float size);
    static std::shared_ptr<Geometry> create_plane(float width, float height);
    static std::shared_ptr<Geometry> create_sphere(float radius, int lat_count, int long_count);
};