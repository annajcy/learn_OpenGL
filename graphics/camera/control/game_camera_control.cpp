#include "game_camera_control.h"


Game_camera_control::Game_camera_control(const std::shared_ptr<Camera> &camera)
    : Camera_control(camera) { }

void Game_camera_control::update()
{
    auto input = Input::get_instance();

    if (input->is_mouse_button_pressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        auto dx = input->get_mouse_dx();
        auto dy = input->get_mouse_dy();

        m_camera->yaw(dx * m_yaw_sensitivity);
        m_camera->pitch(dy * m_pitch_sensitivity);

        input->reset_mouse_dx();
        input->reset_mouse_dy();
    }

    glm::vec3 direction = glm::zero<glm::vec3>();

    if (input->is_key_pressed(GLFW_KEY_W)) {
        direction += m_camera->front();
    }

    if (input->is_key_pressed(GLFW_KEY_S)) {
        direction += m_camera->back();
    }

    if (input->is_key_pressed(GLFW_KEY_A)) {
        direction += m_camera->left();
    }

    if (input->is_key_pressed(GLFW_KEY_D)) {
        direction += m_camera->right();
    }

    if (input->is_key_pressed(GLFW_KEY_Q)) {
        direction += m_camera->up();
    }

    if (input->is_key_pressed(GLFW_KEY_E)) {
        direction += m_camera->down();
    }

    if (std::abs(glm::length(direction)) > DBL_EPSILON) {
        m_camera->translate(glm::normalize(direction), m_tranlate_sensitivity);
    }

    auto delta_scale = input->get_mouse_scroll_dy();

    if (std::abs(delta_scale) > DBL_EPSILON) {
        m_camera->adjust_zoom(delta_scale * m_scale_sensitivity);
        input->reset_scroll_dy();
    }
}


