#pragma once

#include "global/core.h"
#include "camera.h"

#include <memory>

class Camera_control { 
protected:

    float m_tranlate_speed {0.1f};
    float m_rotate_speed = {0.1f};

    std::shared_ptr<Camera> m_camera{};

    virtual void on_cursor(double xpos, double ypos) = 0;
    virtual void on_key(int key, int scan_code, int action, int mods) = 0;
    virtual void on_scroll(double xoffset, double yoffset) = 0;
    virtual void on_mouse(int button, int action, int mods) = 0;

public:

    Camera_control();
    ~Camera_control();

    std::shared_ptr<Camera> get_camera();
    float get_rotate_speed();
    float get_translate_speed();

    void set_rotate_speed(float speed);
    void set_translate_speed(float speed);
    void set_camera(std::shared_ptr<Camera> camera);
    
    virtual void update() = 0;
};