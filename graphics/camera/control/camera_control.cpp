#include "camera_control.h"

Camera_control::Camera_control(const std::shared_ptr<Camera> &camera) 
    : m_camera(camera) {}

std::shared_ptr<Camera> Camera_control::camera() { 
    return m_camera; 
}

float Camera_control::get_pitch_sensitivity() const { 
    return m_pitch_sensitivity; 
}

float Camera_control::get_yaw_sensitivity() const { 
    return m_yaw_sensitivity; 
}

float Camera_control::get_translate_sensitivity() const { 
    return m_tranlate_sensitivity; 
}

float Camera_control::get_scale_sensitivity() const { 
    return m_scale_sensitivity; 
}

float& Camera_control::pitch_sensitivity() { 
    return m_pitch_sensitivity; 
}

float& Camera_control::yaw_sensitivity() { 
    return m_yaw_sensitivity; 
}

float& Camera_control::translate_sensitivity() { 
    return m_tranlate_sensitivity; 
}

float& Camera_control::scale_sensitivity() { 
    return m_scale_sensitivity; 
}
