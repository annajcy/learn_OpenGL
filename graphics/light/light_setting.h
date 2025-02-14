#pragma once

#include "light.h"
#include "directional_light.h"
#include "ambient_light.h"
#include "spot_light.h"
#include "point_light.h"

class Light_setting
{
private:
    std::vector<std::shared_ptr<Directional_light>> m_directional_lights{}; // 定向光源
    std::vector<std::shared_ptr<Ambient_light>> m_ambient_lights{};         // 环境光源
    std::vector<std::shared_ptr<Spot_light>> m_spot_lights{};               // 聚光灯
    std::vector<std::shared_ptr<Point_light>> m_point_lights{};             // 点光源

public:
    Light_setting() = default;
    Light_setting(const std::vector<std::shared_ptr<Light>>& lights);

    // 获取光源列表
    const std::vector<std::shared_ptr<Directional_light>>& directional_lights();
    const std::vector<std::shared_ptr<Ambient_light>> ambient_lights();
    const std::vector<std::shared_ptr<Spot_light>> spot_lights();
    const std::vector<std::shared_ptr<Point_light>> point_lights();

    // 添加光源
    void add(const std::shared_ptr<Light>& light);

    // 移除光源
    void erase(const std::shared_ptr<Light>& light);

    ~Light_setting() = default;
};