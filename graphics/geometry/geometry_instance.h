#pragma once

#include "global/core.h"
#include "geometry.h"

class Geometry_instance : public Geometry {
private:
    int m_instance_count{};
    unsigned int m_model_matrices_vbo{};
    unsigned int m_model_matrices_location{3};

public:
    Geometry_instance(
        const std::vector<float> &positions,
        const std::vector<float> &normals,
        const std::vector<float> &uvs,
        const std::vector<unsigned int> &indices,
        const std::vector<glm::mat4> &model_matrices
    );

    ~Geometry_instance();

    void init_model_matrices(const std::vector<glm::mat4> &model_matrices);
    void update_model_matrices(const std::vector<glm::mat4> &model_matrices);
    void draw() override;

    static std::shared_ptr<Geometry_instance> create_box(float size, const std::vector<glm::mat4> &model_matrices);
    static std::shared_ptr<Geometry_instance> create_plane(float width, float height, const std::vector<glm::mat4> &model_matrices);
    static std::shared_ptr<Geometry_instance> create_sphere(float radius, int lat_count, int long_count, const std::vector<glm::mat4> &model_matrices);
};