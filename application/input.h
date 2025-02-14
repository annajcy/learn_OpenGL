#pragma once

#include "global/core.h"
#include "global/singleton.h"


class Input_system {
public:
    Input_system() = default;
    Input_system(const Input_system&) = delete;
    ~Input_system() = default;  
    
    void update_cursor_position(double x, double y);
    void update_scroll(double x, double y);
    void update_key(int key, int scan_code, int action, int mods);
    void update_mouse_button(int button, int action, int mods);

    [[nodiscard]] bool is_key_pressed(int key) const;
    [[nodiscard]] bool is_key_mods_pressed(int mods) const;
    [[nodiscard]] bool is_key_pressed_scan_code(int scan_code) const;
    [[nodiscard]] bool is_mouse_button_pressed(int button) const;
    [[nodiscard]] bool is_mouse_button_mods_pressed(int mods) const;

    [[nodiscard]] double get_mouse_x() const;
    [[nodiscard]] double get_mouse_y() const;
    [[nodiscard]] double get_mouse_dx() const;
    [[nodiscard]] double get_mouse_dy() const;
    [[nodiscard]] double get_mouse_scroll_dx() const;
    [[nodiscard]] double get_mouse_scroll_dy() const;

    void reset_scroll_dy();
    void reset_scroll_dx();

    void reset_mouse_dy();
    void reset_mouse_dx();

private:
    std::unordered_map<int, bool> m_key_scan_code{};
    std::unordered_map<int, bool> m_key_mods{};
    std::unordered_map<int, bool> m_keys{};
    std::unordered_map<int, bool> m_mouse_button_mods{};
    std::unordered_map<int, bool> m_mouse_buttons{};

    double m_mouse_x{};
    double m_mouse_y{};

    double m_mouse_dx{};
    double m_mouse_dy{};

    double m_mouse_scroll_dx{};
    double m_mouse_scroll_dy{};
};

using Input = Singleton<Input_system>;