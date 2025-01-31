#include "camera_control.h"

Camera_control::Camera_control() = default;

Camera_control::~Camera_control() = default;

void Camera_control::set_rotate_speed(float speed) {
    m_rotate_speed = speed;
}

void Camera_control::set_translate_speed(float speed) {
    m_tranlate_speed = speed;
}

std::shared_ptr<Camera> Camera_control::get_camera() {
    return m_camera;
}

void Camera_control::set_camera(std::shared_ptr<Camera> camera) {
    m_camera = camera;
}

float Camera_control::get_rotate_speed() {
    return m_rotate_speed;
}

float Camera_control::get_translate_speed() {
    return m_tranlate_speed;
}