#include "global/core.h"
#include "global/singleton.h"
#include "global/error_check.h"

#include "graphics/shader/shader_code.h"
#include "graphics/shader/shader_program.h"
#include "graphics/texture.h"
#include "graphics/geometry.h"

#include "application/application.h"
#include "application/image.h"
#include "application/input.h"

#include "application/camera/control/trackball_camera_control.h"
#include "application/camera/control/game_camera_control.h"
#include "application/camera/type/orthographic_camera.h"
#include "application/camera/type/perspective_camera.h"

#include "utils/string_utils.h"

#include <string>
#include <memory>
#include <iostream>

GLuint vao, ebo;

std::shared_ptr<Geometry> geo{};

void prepare_geometry() {
	geo = Geometry::create_plane(2.0f, 2.0f);
}

void prepare_state() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

std::shared_ptr<Shader_program> shader_program{};

void prepare_shader() {

	std::string vertex_shader_code = utils::load_from_file("assets/shaders/transform/vertex.glsl");
	std::string fragment_shader_code = utils::load_from_file("assets/shaders/transform/fragment.glsl");

	std::shared_ptr<Shader_code> vertex_shader = std::make_shared<Shader_code>(vertex_shader_code, Shader_code::Shader_type::VERTEX);
	vertex_shader->compile();
	vertex_shader->check_compile_error();

	std::shared_ptr<Shader_code> fragment_shader = std::make_shared<Shader_code>(fragment_shader_code, Shader_code::Shader_type::FRAGMENT);
	fragment_shader->compile();
	fragment_shader->check_compile_error();

	shader_program = std::make_shared<Shader_program>();
	shader_program->attach_shader(vertex_shader);
	shader_program->attach_shader(fragment_shader);
	
	shader_program->link();
	shader_program->check_link_error();
}

std::shared_ptr<Image> image {};
std::shared_ptr<Texture> texture {};

void prepare_texture() {
	image = std::make_shared<Image>("assets/image/goku.jpg");
	texture = std::make_shared<Texture>(image, false);

	texture->attach_texture();
	texture->set_wrap(Texture::Warp::S, Texture::Wrap_type::REPEAT);
	texture->set_wrap(Texture::Warp::T, Texture::Wrap_type::REPEAT);
	texture->set_filter(Texture::Filter::MIN, Texture::Filter_type::LINEAR_MIPMAP_LINEAR);
	texture->set_filter(Texture::Filter::MAG, Texture::Filter_type::LINEAR);

	texture->detach_texture();
}

std::shared_ptr<Perspective_camera> camera{};
std::shared_ptr<Trackball_camera_control> camera_control{};

void prepare_camera() {

	camera = std::make_shared<Perspective_camera>(
		60.0f,
		(float) App::get_instance()->width() / (float) App::get_instance()->height(),
		0.1f, 1000.0f,
		glm::vec3(0.0f, 0.0f, -5.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)
	);

	camera_control = std::make_shared<Trackball_camera_control>(camera);

}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader_program->attach_program();

	shader_program->set_uniform<float>("time", static_cast<float>(glfwGetTime()));
	shader_program->set_uniform<int>("textureSampler0", 0);
	shader_program->set_uniform_glm<glm::vec2>("resolution", glm::vec2(App::get_instance()->width(), App::get_instance()->height()));
	shader_program->set_uniform_glm<glm::mat4>("model", glm::identity<glm::mat4>());
	shader_program->set_uniform_glm<glm::mat4>("view", camera->view_matrix());
	shader_program->set_uniform_glm<glm::mat4>("projection", camera->projection_matrix());

	texture->attach_texture();
	
	geo->attach_geometry();
	geo->draw();
	geo->detach_geometry();

	texture->detach_texture();

	shader_program->detach_program();
}

int main()
{
	if (!App::get_instance()->init()) {
		std::cout << "init Failed" << std::endl;
		return -1;
	}

	//upd io events
	App::get_instance()->keyboard_actions().add([](int key, int scancode, int action, int mods) {
		Input::get_instance()->update_key(key, scancode, action, mods);
	});

	App::get_instance()->cursor_actions().add([](double xpos, double ypos) {
		Input::get_instance()->update_cursor_position(xpos, ypos);
	});

	App::get_instance()->mouse_actions().add([](int button, int action, int mods) {
		Input::get_instance()->update_mouse_button(button, action, mods);
	});

	App::get_instance()->scroll_actions().add([](double xoffset, double yoffset) {
		Input::get_instance()->update_scroll(xoffset, yoffset);
	});

	prepare_shader();
	prepare_state();
	prepare_geometry();
	prepare_texture();
	prepare_camera();


	glViewport(0, 0, App::get_instance()->width(), App::get_instance()->height());
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	while (App::get_instance()->is_active()) {
		App::get_instance()->update();
		camera_control->update();
		render();
	}

	Application::destroy();

	return 0;
}