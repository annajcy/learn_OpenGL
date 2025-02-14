// #pragma once

// #include "global/core.h" // Assumed to include OpenGL headers and any needed core types.
// #include <memory>
// #include <vector>
// #include <cmath>

// class Geometry {
// private:
//     // OpenGL handles
//     GLuint m_vao{};
//     GLuint m_ebo{}; 
    
//     GLuint m_position_location{};
//     GLuint m_uv_location{};        
//     GLuint m_normal_location{};

//     GLuint m_position_vbo{};
//     GLuint m_uv_vbo{};        
//     GLuint m_normal_vbo{};  

//     int m_indices_count{};

// public:

//     GLuint vao() const { return m_vao; }
//     GLuint ebo() const { return m_ebo; }

//     GLuint position_location() const { return m_position_location; }
//     GLuint uv_location() const { return m_uv_location; }
//     GLuint normal_location() const { return m_normal_location; }

//     GLuint position_vbo() const { return m_position_vbo; }
//     GLuint uv_vbo() const { return m_uv_vbo; }
//     GLuint normal_vbo() const { return m_normal_vbo; }

//     int indices_count() const { return m_indices_count; }

//     void attach_geometry() {
//         glBindVertexArray(m_vao);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
//     }

//     void detach_geometry() {
//         glBindVertexArray(0);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//     }

//     void draw() {
//         glDrawElements(GL_TRIANGLES, m_indices_count, GL_UNSIGNED_INT, 0);
//     }

//     Geometry() = default;

//     Geometry(
//         const std::vector<float> &positions,
//         const std::vector<float> &normals,
//         const std::vector<float> &uvs,
//         const std::vector<unsigned int> &indices
//     ) {
//         init(positions.data(), positions.size() * sizeof(float), 
//             uvs.data(), uvs.size() * sizeof(float), 
//             normals.data(), normals.size() * sizeof(float), 
//             indices.data(), indices.size() * sizeof(unsigned int), indices.size());
//     }

//     void init(
//         const float* positions, int position_size, 
//         const float* uvs, int uv_size, 
//         const float* normals, int normal_size, 
//         const unsigned int* indices, int indices_size, int indices_count
//     ) {

//         m_position_location = 0;
//         m_uv_location = 1;
//         m_normal_location = 2;
//         m_indices_count = indices_count;

//         glGenBuffers(1, &m_position_vbo);
//         glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo);
//         glBufferData(GL_ARRAY_BUFFER, position_size, positions, GL_STATIC_DRAW);

//         glGenBuffers(1, &m_uv_vbo);
//         glBindBuffer(GL_ARRAY_BUFFER, m_uv_vbo);
//         glBufferData(GL_ARRAY_BUFFER, uv_size, uvs, GL_STATIC_DRAW);

//         glGenBuffers(1, &m_normal_vbo);
//         glBindBuffer(GL_ARRAY_BUFFER, m_normal_vbo);
//         glBufferData(GL_ARRAY_BUFFER, normal_size, normals, GL_STATIC_DRAW);

//         glGenBuffers(1, &m_ebo);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

//         glGenVertexArrays(1, &m_vao);
//         glBindVertexArray(m_vao);

//         glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo);
//         glEnableVertexAttribArray(m_position_location);
//         glVertexAttribPointer(m_position_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, static_cast<const void*>(0));

//         glBindBuffer(GL_ARRAY_BUFFER, m_uv_vbo);
//         glEnableVertexAttribArray(m_uv_location);
//         glVertexAttribPointer(m_uv_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, static_cast<const void*>(0));

//         glBindBuffer(GL_ARRAY_BUFFER, m_normal_vbo);
//         glEnableVertexAttribArray(m_normal_location);
//         glVertexAttribPointer(m_normal_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, static_cast<const void*>(0));

//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

//         glBindVertexArray(0);

//     }

//     ~Geometry() {
//         if (m_ebo)   glDeleteBuffers(1, &m_ebo);
//         if (m_vao)   glDeleteVertexArrays(1, &m_vao);
//         if (m_position_vbo) glDeleteBuffers(1, &m_position_vbo);
//         if (m_normal_vbo) glDeleteBuffers(1, &m_normal_vbo);
//         if (m_uv_vbo) glDeleteBuffers(1, &m_normal_vbo);   
//     }

//     static std::shared_ptr<Geometry> create_box(float size) {
//         std::shared_ptr<Geometry> geo = std::make_shared<Geometry>();

//         auto half_size = size * 0.5f;

//         float positions[] = {
//             // Front face
//             -half_size, -half_size, half_size, half_size, -half_size, half_size, half_size, half_size, half_size, -half_size, half_size, half_size,
//             // Back face
//             -half_size, -half_size, -half_size, -half_size, half_size, -half_size, half_size, half_size, -half_size, half_size, -half_size, -half_size,
//             // Top face
//             -half_size, half_size, half_size, half_size, half_size, half_size, half_size, half_size, -half_size, -half_size, half_size, -half_size,
//             // Bottom face
//             -half_size, -half_size, -half_size, half_size, -half_size, -half_size, half_size, -half_size, half_size, -half_size, -half_size, half_size,
//             // Right face
//             half_size, -half_size, half_size, half_size, -half_size, -half_size, half_size, half_size, -half_size, half_size, half_size, half_size,
//             // Left face
//             -half_size, -half_size, -half_size, -half_size, -half_size, half_size, -half_size, half_size, half_size, -half_size, half_size, -half_size
//         };

//         float uvs[] = {
//             0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
//             0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
//             0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
//             0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
//             0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
//             0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0,
//         };

//         float normals[] = {
//             //front
//             0.0f, 0.0f, 1.0f,
//             0.0f, 0.0f, 1.0f,
//             0.0f, 0.0f, 1.0f,
//             0.0f, 0.0f, 1.0f,

//             //back
//             0.0f, 0.0f, -1.0f,
//             0.0f, 0.0f, -1.0f,
//             0.0f, 0.0f, -1.0f,
//             0.0f, 0.0f, -1.0f,

//             //up
//             0.0f, 1.0f, 0.0f,
//             0.0f, 1.0f, 0.0f,
//             0.0f, 1.0f, 0.0f,
//             0.0f, 1.0f, 0.0f,

//             //down
//             0.0f, -1.0f, 0.0f,
//             0.0f, -1.0f, 0.0f,
//             0.0f, -1.0f, 0.0f,
//             0.0f, -1.0f, 0.0f,

//             //right
//             1.0f, 0.0f, 0.0f,
//             1.0f, 0.0f, 0.0f,
//             1.0f, 0.0f, 0.0f,
//             1.0f, 0.0f, 0.0f,

//             //left
//             -1.0f, 0.0f, 0.0f,
//             -1.0f, 0.0f, 0.0f,
//             -1.0f, 0.0f, 0.0f,
//             -1.0f, 0.0f, 0.0f,
//         };

//         unsigned int indices[] = {
//             0, 1, 2, 2, 3, 0,   // Front face
//             4, 5, 6, 6, 7, 4,   // Back face
//             8, 9, 10, 10, 11, 8,  // Top face
//             12, 13, 14, 14, 15, 12, // Bottom face
//             16, 17, 18, 18, 19,  16, // Right face
//             20, 21, 22, 22, 23, 20  // Left face
//         };

//         geo->init(positions, sizeof(positions), uvs, sizeof(uvs), normals, sizeof(normals), indices, sizeof(indices), sizeof(indices) / sizeof(unsigned int));

//         return geo;
//     }

//     static std::shared_ptr<Geometry> create_plane(float width, float height) {
//         std::shared_ptr<Geometry> geo = std::make_shared<Geometry>();

//         float half_width = width * 0.5f;
//         float half_height = height * 0.5f;

//         float positions[] = {
//             -half_width, -half_height, 0.0f,
//             half_width, -half_height, 0.0f,
//             half_width, half_height, 0.0f,
//             -half_width, half_height, 0.0f,
//         };

//         float uvs[] = {
//             0.0f, 0.0f,
//             1.0f, 0.0f,
//             1.0f, 1.0f,
//             0.0f, 1.0f
//         };

//         float normals[] = {
//             0.0f, 0.0f, 1.0f,
//             0.0f, 0.0f, 1.0f,
//             0.0f, 0.0f, 1.0f,
//             0.0f, 0.0f, 1.0f,
//         };

//         unsigned int indices[] = {
//             0, 1, 2,
//             2, 3, 0
//         };

//         geo->init(positions, sizeof(positions), uvs, sizeof(uvs), normals, sizeof(normals), indices, sizeof(indices), sizeof(indices) / sizeof(unsigned int));

//         return geo;

//     }

//     static std::shared_ptr<Geometry> create_sphere(float radius, int lat_count, int long_count) {
//         std::shared_ptr<Geometry> geo = std::make_shared<Geometry>();

//         std::vector<float> positions{};
//         std::vector<float> uvs{};
//         std::vector<float> normals{};
//         std::vector<unsigned int> indices{};

//         auto lat_delta = glm::pi<float>() / lat_count;
//         auto long_delta = 2.0f * glm::pi<float>() / long_count;

//         for (int i = 0; i <= lat_count; i ++) 
//             for (int j = 0; j <= long_count; j ++) {
//                 float phi = i * lat_delta;
//                 float theta = j * long_delta;

//                 float y = radius * cos(phi);
//                 float x = radius * sin(phi) * cos(theta);
//                 float z = radius * sin(phi) * sin(theta);

//                 positions.push_back(x);
//                 positions.push_back(y);
//                 positions.push_back(z);

//                 normals.push_back(x);
//                 normals.push_back(y);
//                 normals.push_back(z);

//                 float u = 1.0f - 1.0f * j / long_count;
//                 float v = 1.0f - 1.0f * i / lat_count;

//                 uvs.push_back(u);
//                 uvs.push_back(v);
//             }

    
//         for (int i = 0; i < lat_count; i ++) 
//             for (int j = 0; j < long_count; j ++) {
//                 int p1 = i * (long_count + 1) + j, p3 = p1 + 1;
//                 int p2 = p1 + long_count + 1, p4 = p2 + 1;

//                 indices.push_back(p1);
//                 indices.push_back(p2);
//                 indices.push_back(p3);
//                 indices.push_back(p3);
//                 indices.push_back(p2);
//                 indices.push_back(p4);
//             }

//         geo->init(positions.data(), positions.size() * sizeof(float), uvs.data(), uvs.size() * sizeof(float), normals.data(), normals.size() * sizeof(float), indices.data(), indices.size() * sizeof(unsigned int), indices.size());

//         return geo;
//     }
    
// };


#pragma once

#include "global/core.h" // Assumed to include OpenGL headers and any needed core types.
#include <memory>
#include <vector>
#include <cmath>

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

    static std::shared_ptr<Geometry> create_box(float size);
    static std::shared_ptr<Geometry> create_plane(float width, float height);
    static std::shared_ptr<Geometry> create_sphere(float radius, int lat_count, int long_count);
};