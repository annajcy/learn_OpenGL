#pragma once

#include "global/core.h"
#include "global/singleton.h"
#include "global/action.h"

class GLFWwindow;

using Resize_action = Action<int, int>;
using Mouse_action = Action<int, int, int>;
using Keyboard_action = Action<int, int, int, int>;
using Cursor_action = Action<double, double>;
using Scroll_action = Action<double, double>;

class Application {
public:
	bool init(int width = 800, int height = 600, const std::string &name = "opengl");
	bool is_active();
	void update();
	static void destroy();
	[[nodiscard]] int width() const;
	[[nodiscard]] int height() const;
	[[nodiscard]] GLFWwindow* window() const;

	Resize_action& resize_actions();
	Keyboard_action& keyboard_actions();
	Cursor_action& cursor_actions();
	Mouse_action& mouse_actions();
	Scroll_action& scroll_actions();

	Application();
	~Application();

private:
	GLFWwindow* m_window{nullptr};

	Scroll_action m_scroll_actions{};
	Cursor_action m_cursor_actions{};
	Mouse_action m_mouse_actions{};
	Resize_action m_resize_actions{
		[](int width, int height) {
			std::cout << "glViewport resize" << std::endl;
			glViewport(0, 0, width, height);
		}
	};
	Keyboard_action m_keyboard_actions {
		[&](int key, int scan_code, int action, int mods) {
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
				std::cout << "application exit" << std::endl;
				glfwSetWindowShouldClose(m_window, true);
			}
		}
	};

	static void cursor_callback(GLFWwindow* window, double xpos, double ypos);
	static void frame_buffer_resize_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);
	static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

using App = Singleton<Application>;


