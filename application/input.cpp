#include "input.h"

void Input_system::update_cursor_position(double x, double y) {
    
    m_mouse_dx = x - m_mouse_x;
    m_mouse_dy = y - m_mouse_y;

    m_mouse_x = x;
    m_mouse_y = y;
}

void Input_system::update_scroll(double dx, double dy) {
    m_mouse_scroll_dx = dx;
    m_mouse_scroll_dy = dy;
}

void Input_system::update_key(int key, int scan_code,  int action, int mods) {
    m_keys[key] = action != GLFW_RELEASE;
    m_key_mods[mods] = action != GLFW_RELEASE;
    m_key_scan_code[scan_code] = action != GLFW_RELEASE;
}

void Input_system::update_mouse_button(int button, int action, int mods) {
    m_mouse_buttons[button] = action != GLFW_RELEASE;
    m_mouse_button_mods[mods] = action != GLFW_RELEASE;
}

bool Input_system::is_key_pressed(int key) const {
    return m_keys.find(key) != m_keys.end() && m_keys.at(key);
}

bool Input_system::is_key_mods_pressed(int mods) const {
    return m_key_mods.find(mods) != m_key_mods.end() && m_key_mods.at(mods);
}

bool Input_system::is_key_pressed_scan_code(int scan_code) const {
    return m_key_scan_code.find(scan_code) != m_key_scan_code.end() && m_key_scan_code.at(scan_code);
}

bool Input_system::is_mouse_button_pressed(int button) const {
    return m_mouse_buttons.find(button) != m_mouse_buttons.end() && m_mouse_buttons.at(button);
}

bool Input_system::is_mouse_button_mods_pressed(int mods) const {
    return m_mouse_button_mods.find(mods) != m_mouse_button_mods.end() && m_mouse_button_mods.at(mods);
}

double Input_system::get_mouse_x() const {
    return m_mouse_x;
}

double Input_system::get_mouse_y() const {
    return m_mouse_y;
}

double Input_system::get_mouse_dx() const {
    return m_mouse_dx;
}

double Input_system::get_mouse_dy() const {
    return m_mouse_dy;
}

double Input_system::get_mouse_scroll_dx() const {
    return m_mouse_scroll_dx;
}

double Input_system::get_mouse_scroll_dy() const {
    return m_mouse_scroll_dy;
}

void Input_system::reset_mouse_dy() {
    m_mouse_dy = 0;
}

void Input_system::reset_mouse_dx() {
    m_mouse_dx = 0;
}

void Input_system::reset_scroll_dx() {
    m_mouse_scroll_dx = 0;
}

void Input_system::reset_scroll_dy() {
    m_mouse_scroll_dy = 0;
}
