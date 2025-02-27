#pragma once

#include "global/core.h"
#include "geometry.h"

class Geometry_instance : public Geometry {
private:
    int m_instance_count{};
    unsigned int m_model_matrices_vbo{};
    unsigned int m_model_matrices_location{3};

public:

    Geometry_instance(const std::shared_ptr<Geometry>& geometry, const std::vector<glm::mat4> &model_matrices) {
        m_vao = geometry->vao();
        m_ebo = geometry->ebo();
        m_indices_count = geometry->indices_count();
        m_position_location = geometry->position_location();
        m_uv_location = geometry->uv_location();
        m_normal_location = geometry->normal_location();
        m_position_vbo = geometry->position_vbo();
        m_uv_vbo = geometry->uv_vbo();
        m_normal_vbo = geometry->normal_vbo();
        init_model_matrices(model_matrices);
    }

    Geometry_instance(
        const std::vector<float> &positions,
        const std::vector<float> &normals,
        const std::vector<float> &uvs,
        const std::vector<unsigned int> &indices,
        const std::vector<glm::mat4> &model_matrices
    ) : Geometry(positions, normals, uvs, indices) {
        init_model_matrices(model_matrices);
    }

    void init_model_matrices(const std::vector<glm::mat4> &model_matrices) {
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

    void update_model_matrices(const std::vector<glm::mat4> &model_matrices) {
        m_instance_count = model_matrices.size();
        glBindBuffer(GL_ARRAY_BUFFER, m_model_matrices_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, model_matrices.size() * sizeof(glm::mat4), model_matrices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void draw() override {
        attach_geometry();
        glDrawElementsInstanced(GL_TRIANGLES, m_indices_count, GL_UNSIGNED_INT, 0, m_instance_count);
        detach_geometry();
    }

    static std::shared_ptr<Geometry_instance> create_box(float size, const std::vector<glm::mat4> &model_matrices) {
        return std::make_shared<Geometry_instance>(Geometry::create_box(size), model_matrices);
    }

    static std::shared_ptr<Geometry_instance> create_plane(float width, float height, const std::vector<glm::mat4> &model_matrices) {
        return std::make_shared<Geometry_instance>(Geometry::create_plane(width, height), model_matrices);
    }

    static std::shared_ptr<Geometry_instance> create_sphere(float radius, int lat_count, int long_count, const std::vector<glm::mat4> &model_matrices) {
        return std::make_shared<Geometry_instance>(Geometry::create_sphere(radius, lat_count, long_count), model_matrices);
    }

};