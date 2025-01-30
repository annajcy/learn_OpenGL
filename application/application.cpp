#include "application.h"

int Application::width() const{ return m_width; }
int Application::height() const { return m_height; }

bool Application::init(int width, int height, const std::string &name) {
	m_width = width;
	m_height = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, name.c_str(), nullptr, nullptr);

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
		self->m_resize_callback(width, height);
	}
}

void Application::key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods) {
	auto* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (self != nullptr) {
		self->m_keyboard_callback(key, scan_code, action, mods);
	}
}

void Application::update() {
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

void Application::set_resize_callback(const Resize_callback& callback) {
	m_resize_callback = callback;
}

void Application::set_keyboard_callBack(const Keyboard_callback& callback) {
	m_keyboard_callback = callback;
}

