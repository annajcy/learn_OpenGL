#include "trackball_camera_control.h"
#include "application/input.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Trackball_camera_control::Trackball_camera_control(const std::shared_ptr<Camera> &camera)
    : Camera_control(camera) {}

void Trackball_camera_control::pitch(float angle) {
    auto mat = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), m_camera->right());
    m_camera->up() = glm::vec3(mat * glm::vec4(m_camera->up(), 0.0f));
    m_camera->position() = glm::vec3(mat * glm::vec4(m_camera->position(), 1.0f));
}

void Trackball_camera_control::yaw(float angle) {
    auto mat = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    m_camera->up() = glm::vec3(mat * glm::vec4(m_camera->up(), 0.0f));
    m_camera->right() = glm::vec3(mat * glm::vec4(m_camera->right(), 0.0f));
    m_camera->position() = glm::vec3(mat * glm::vec4(m_camera->position(), 1.0f));
}

void Trackball_camera_control::update() {
    auto input = Input::get_instance();
    
    if (input->is_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT)) {
        auto dx = input->get_mouse_dx();
        auto dy = input->get_mouse_dy();
        yaw(dx * m_yaw_sensitivity);
        pitch(dy * m_pitch_sensitivity);
    } 
    else if (input->is_mouse_button_pressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
        auto dx = input->get_mouse_dx();
        auto dy = input->get_mouse_dy();
        m_camera->translate(m_camera->up(), dy * m_tranlate_sensitivity);
        m_camera->translate(m_camera->right(), dx * m_tranlate_sensitivity);
    }

    auto delta_scale = input->get_mouse_scroll_dy();
    if (std::abs(delta_scale) > DBL_EPSILON) {
        m_camera->adjust_scale(delta_scale * m_scale_sensitivity);
    }
}
