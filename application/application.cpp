#include "application.h"

Application::Application() = default;
Application::~Application() = default;

int Application::width() const{ 
	int width, height;
	glfwGetFramebufferSize(window(), &width, &height);
	return width;
}

int Application::height() const { 
	int width, height;
	glfwGetFramebufferSize(window(), &width, &height);
	return height;
}

bool Application::init(int width, int height, const std::string &name) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	if (m_window == nullptr) {
		std::cerr << "Failed to initialize GLFW window" << std::endl;
		return false;
	}

	glfwSetWindowUserPointer(m_window, this);
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glfwSetFramebufferSizeCallback(m_window, frame_buffer_resize_callback);
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, cursor_callback);
	glfwSetMouseButtonCallback(m_window, mouse_callback);
	glfwSetScrollCallback(m_window, scroll_callback);

	return true;
}

bool Application::is_active() {
	if (glfwWindowShouldClose(m_window)) return false;
	return true;
}

void Application::destroy() {
	glfwTerminate();
}

void Application::frame_buffer_resize_callback(GLFWwindow* window, int width, int height) {
	auto* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (self != nullptr) {
		self->m_resize_actions.execute(width, height);
	}
}

void Application::key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods) {
	auto* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (self != nullptr) {
		self->m_keyboard_actions.execute(key, scan_code, action, mods);
	}
}

void Application::cursor_callback(GLFWwindow* window, double xpos, double ypos) {
	auto* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (self != nullptr) {
		self->m_cursor_actions.execute(xpos, ypos);
	}
}

void Application::mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	auto* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (self != nullptr) {
		self->m_mouse_actions.execute(button, action, mods);
	}
}

void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	auto* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (self != nullptr) {
		self->m_scroll_actions.execute(xoffset, yoffset);
	}
}

Resize_action& Application::resize_actions() { return m_resize_actions; }
Keyboard_action& Application::keyboard_actions() { return m_keyboard_actions; }
Cursor_action& Application::cursor_actions() { return m_cursor_actions; }
Mouse_action& Application::mouse_actions() { return m_mouse_actions; }
Scroll_action& Application::scroll_actions() { return m_scroll_actions; }

void Application::update() {
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

GLFWwindow* Application::window() const {
	return m_window;
}

