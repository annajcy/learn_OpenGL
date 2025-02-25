#pragma once

#include "global/core.h"

class Geometry {
private:
    // OpenGL handles
    GLuint m_vao{};
    GLuint m_ebo{}; 
    
    GLuint m_position_location{};
    GLuint m_uv_location{};        
    GLuint m_normal_location{};

    GLuint m_position_vbo{};
    GLuint m_uv_vbo{};        
    GLuint m_normal_vbo{};  

    int m_indices_count{};

public:
    GLuint vao() const;
    GLuint ebo() const;

    GLuint position_location() const;
    GLuint uv_location() const;
    GLuint normal_location() const;

    GLuint position_vbo() const;
    GLuint uv_vbo() const;
    GLuint normal_vbo() const;

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
    static std::shared_ptr<Geometry> create_box(float size = 1.0f);
    static std::shared_ptr<Geometry> create_plane(float width, float height);
    static std::shared_ptr<Geometry> create_sphere(float radius, int lat_count, int long_count);
};