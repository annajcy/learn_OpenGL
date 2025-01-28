#pragma once

#include "global/core.h"
#include <iostream>
#include <functional>

class GLFWwindow;

using Resize_callback = std::function<void(int, int)>;
using Keyboard_callback = std::function<void(int, int, int, int)>;

class Application {
public:
	bool init(int width = 800, int height = 600, const std::string &name = "opengl");
	bool is_active();
	void update();
	static void destroy();
	[[nodiscard]] int width() const;
	[[nodiscard]] int height() const;
	void set_resize_callback(const Resize_callback& callback);
	void set_keyboard_callBack(const Keyboard_callback& callback);
	Application() = default;
	~Application() = default;
private:
	int m_width{0};
	int m_height{0};
	GLFWwindow* m_window{nullptr};

	Resize_callback m_resize_callback{[](int width, int height) {
		std::cout << "new window size：" << width << " , " << height << std::endl;
	}};

	Keyboard_callback m_keyboard_callback{[](int key, int scan_code, int action, int mods) {
		std::cout << "pressed：" << key << std::endl;
		std::cout << "action：" << action << std::endl;
		std::cout << "mods：" << mods << std::endl;
	}};

	static void frame_buffer_resize_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);
};


