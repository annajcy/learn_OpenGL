#include "light.h"

glm::vec3& Light::color() {
    return m_color;
}

float& Light::intensity() {
    return m_intensity;
}

glm::vec3 Light::color() const {
    return m_color;
}

float Light::intensity() const {
    return m_intensity;
}

std::string Light::indexed_var_name(const std::string &var_name, int index) {
    return var_name + "[" + std::to_string(index) + "]";
}
