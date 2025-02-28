#include "geometry_instance.h"

Geometry_instance::Geometry_instance(
    const std::vector<float> &positions,
    const std::vector<float> &normals,
    const std::vector<float> &uvs,
    const std::vector<unsigned int> &indices,
    const std::vector<glm::mat4> &model_matrices
) : Geometry(positions, normals, uvs, indices) {
    init_model_matrices(model_matrices);
}

Geometry_instance::~Geometry_instance() {
    glDeleteBuffers(1, &m_model_matrices_vbo);
}

void Geometry_instance::init_model_matrices(const std::vector<glm::mat4> &model_matrices) {
    m_instance_count = model_matrices.size();

    glGenBuffers(1, &m_model_matrices_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_model_matrices_vbo);
    glBufferData(GL_ARRAY_BUFFER, model_matrices.size() * sizeof(glm::mat4), model_matrices.data(), GL_DYNAMIC_DRAW);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_model_matrices_vbo);

    for (int i = 0; i < 4; i ++) {
        glEnableVertexAttribArray(m_model_matrices_location + i);
        glVertexAttribPointer(m_model_matrices_location + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
        glVertexAttribDivisor(m_model_matrices_location + i, 1);
    }

    glBindVertexArray(0);
}

void Geometry_instance::update_model_matrices(const std::vector<glm::mat4> &model_matrices) {
    m_instance_count = model_matrices.size();
    glBindBuffer(GL_ARRAY_BUFFER, m_model_matrices_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, model_matrices.size() * sizeof(glm::mat4), model_matrices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Geometry_instance::draw() {
    attach_geometry();
    glDrawElementsInstanced(GL_TRIANGLES, m_indices_count, GL_UNSIGNED_INT, 0, m_instance_count);
    detach_geometry();
}

std::shared_ptr<Geometry_instance> Geometry_instance::create_box(float size, const std::vector<glm::mat4> &model_matrices) {
    std::vector<float> positions{};
    std::vector<float> uvs{};
    std::vector<float> normals{};
    std::vector<unsigned int> indices{};

    set_box_geometry(size, positions, normals, uvs, indices);
    return std::make_shared<Geometry_instance>(positions, normals, uvs, indices, model_matrices);
}

std::shared_ptr<Geometry_instance> Geometry_instance::create_plane(float width, float height, const std::vector<glm::mat4> &model_matrices) {
    std::vector<float> positions{};
    std::vector<float> uvs{};
    std::vector<float> normals{};
    std::vector<unsigned int> indices{};

    set_plane_geometry(width, height, positions, normals, uvs, indices);
    return std::make_shared<Geometry_instance>(positions, normals, uvs, indices, model_matrices);
}

std::shared_ptr<Geometry_instance> Geometry_instance::create_sphere(float radius, int lat_count, int long_count, const std::vector<glm::mat4> &model_matrices) {
    std::vector<float> positions{};
    std::vector<float> uvs{};
    std::vector<float> normals{};
    std::vector<unsigned int> indices{};
    set_sphere_geometry(radius, lat_count, long_count, positions, normals, uvs, indices);
    return std::make_shared<Geometry_instance>(positions, normals, uvs, indices, model_matrices);
}
