#include "global/core.h"
#include "global/singleton.h"
#include "global/error_check.h"

#include "graphics/shader_code.h"
#include "graphics/shader_program.h"
#include "graphics/texture.h"

#include "application/application.h"
#include "application/image.h"

#include "utils/string_utils.h"

#include <string>
#include <memory>
#include <iostream>

GLuint vao, ebo;

using App = Singleton<Application>;

void prepare_single_buffer() {
	float positions[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			0.5f,  0.5f, 0.0f,
	};

	float colors[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.5f
	};

	float uvs[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLuint pos_vbo = 0;
	GLuint color_vbo = 0;
	GLuint uv_vbo = 0;
	GL_CALL(glGenBuffers(1, &pos_vbo));
	GL_CALL(glGenBuffers(1, &color_vbo));
	GL_CALL(glGenBuffers(1, &uv_vbo));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, pos_vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, color_vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, uv_vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint pos_vao = 0;
	glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
	glEnableVertexAttribArray(pos_vao);
	glVertexAttribPointer(pos_vao, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<const void*>(0));

	GLuint color_vao = 1;
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glEnableVertexAttribArray(color_vao);
	glVertexAttribPointer(color_vao, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<const void*>(0));

	GLuint uv_vao = 2;
	glBindBuffer(GL_ARRAY_BUFFER, uv_vbo);
	glEnableVertexAttribArray(uv_vao);
	glVertexAttribPointer(uv_vao, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<const void*>(0));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

std::shared_ptr<Shader_program> shader_program = std::make_shared<Shader_program>();

void prepare_shader() {

	std::string vertex_shader_code = utils::load_from_file("assets/shaders/mipmap/vertex.glsl");
	std::string fragment_shader_code = utils::load_from_file("assets/shaders/mipmap/fragment.glsl");

	std::shared_ptr<Shader_code> vertex_shader = std::make_shared<Shader_code>();
	vertex_shader->init(vertex_shader_code, Shader_code::Shader_type::VERTEX);
	vertex_shader->compile();
	vertex_shader->check_compile_error();

	std::shared_ptr<Shader_code> fragment_shader = std::make_shared<Shader_code>();
	fragment_shader->init(fragment_shader_code, Shader_code::Shader_type::FRAGMENT);
	fragment_shader->compile();
	fragment_shader->check_compile_error();

	shader_program->init();
	shader_program->attach_shader(vertex_shader);
	shader_program->attach_shader(fragment_shader);
	
	shader_program->link();
	shader_program->check_link_error();
}

std::shared_ptr<Image> image = std::make_shared<Image>();
std::shared_ptr<Texture> texture = std::make_shared<Texture>();

void prepare_texture() {
	image->init("assets/image/goku.jpg");
	texture->init(image, false);

	texture->attach_texture();
	texture->set_wrap(Texture::Warp::S, Texture::Wrap_type::REPEAT);
	texture->set_wrap(Texture::Warp::T, Texture::Wrap_type::REPEAT);
	texture->set_filter(Texture::Filter::MIN, Texture::Filter_type::LINEAR_MIPMAP_LINEAR);
	texture->set_filter(Texture::Filter::MAG, Texture::Filter_type::LINEAR);

	texture->detach_texture();
}

void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	shader_program->attach_program();

	shader_program->set_uniform<float>("time", static_cast<float>(glfwGetTime()));
	shader_program->set_uniform<float>("speed", 1.0f);
	shader_program->set_uniform<int>("textureSampler0", 0);
	shader_program->set_uniform_glm<glm::vec2>("resolution", glm::vec2(800.0f, 600.0f));

	texture->attach_texture();

	GL_CALL(glBindVertexArray(vao));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	GL_CALL(glBindVertexArray(0));

	texture->detach_texture();


	shader_program->detach_program();
}

int main()
{
	if (!App::get_instance()->init()) {
		std::cout << "init Failed" << std::endl;
		return -1;
	}

	prepare_shader();
	prepare_single_buffer();
	prepare_texture();

	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

	while (App::get_instance()->is_active()) {
		render();
		App::get_instance()->update();
	}

	Application::destroy();

	return 0;
}