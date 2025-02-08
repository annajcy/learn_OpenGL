#include "light_setting.h"

// 构造函数
Light_setting::Light_setting(const std::vector<std::shared_ptr<Light>>& lights) {
    for (auto& l : lights) add(l);
}

// 获取定向光源列表
const std::vector<std::shared_ptr<Directional_light>>& Light_setting::directional_lights() {
    return m_directional_lights;
}

// 获取环境光源列表
const std::vector<std::shared_ptr<Ambient_light>> Light_setting::ambient_lights() {
    return m_ambient_lights;
}

// 获取聚光灯列表
const std::vector<std::shared_ptr<Spot_light>> Light_setting::spot_lights() {
    return m_spot_lights;
}

// 获取点光源列表
const std::vector<std::shared_ptr<Point_light>> Light_setting::point_lights() {
    return m_point_lights;
}

// 添加光源
void Light_setting::add(const std::shared_ptr<Light>& light) {
    if (auto dir_light = std::dynamic_pointer_cast<Directional_light>(light)) {
        m_directional_lights.push_back(dir_light);
    } else if (auto amb_light = std::dynamic_pointer_cast<Ambient_light>(light)) {
        m_ambient_lights.push_back(amb_light);
    } else if (auto spot_light = std::dynamic_pointer_cast<Spot_light>(light)) {
        m_spot_lights.push_back(spot_light);
    } else if (auto point_light = std::dynamic_pointer_cast<Point_light>(light)) {
        m_point_lights.push_back(point_light);
    }
}

// 移除光源
void Light_setting::erase(const std::shared_ptr<Light>& light) {
    if (auto dir_light = std::dynamic_pointer_cast<Directional_light>(light)) {
        auto it = std::find(m_directional_lights.begin(), m_directional_lights.end(), dir_light);
        if (it != m_directional_lights.end()) {
            m_directional_lights.erase(it);
            return;
        }
    }
    if (auto amb_light = std::dynamic_pointer_cast<Ambient_light>(light)) {
        auto it = std::find(m_ambient_lights.begin(), m_ambient_lights.end(), amb_light);
        if (it != m_ambient_lights.end()) {
            m_ambient_lights.erase(it);
            return;
        }
    }
    if (auto spot_light = std::dynamic_pointer_cast<Spot_light>(light)) {
        auto it = std::find(m_spot_lights.begin(), m_spot_lights.end(), spot_light);
        if (it != m_spot_lights.end()) {
            m_spot_lights.erase(it);
            return;
        }
    }
    if (auto point_light = std::dynamic_pointer_cast<Point_light>(light)) {
        auto it = std::find(m_point_lights.begin(), m_point_lights.end(), point_light);
        if (it != m_point_lights.end()) {
            m_point_lights.erase(it);
            return;
        }
    }
}