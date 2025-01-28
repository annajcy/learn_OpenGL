#include "glad/glad.h"
#include "error_check/error_check.h"
#include "global/singleton.h"
#include "application/application.h"
#include "utils/string_utils.h"
#include "shader/shader_code.h"
#include "shader/shader_program.h"


#include <string>
#include <memory>

#include <iostream>

GLuint vao, program;

using App = Singleton<Application>;

void prepare_single_buffer() {
	float positions[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
	};

	float colors[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	GLuint ebo = 0;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLuint pos_vbo = 0;
	GLuint color_vbo = 0;
	GL_CALL(glGenBuffers(1, &pos_vbo));
	GL_CALL(glGenBuffers(1, &color_vbo));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, pos_vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, color_vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

	vao = 0;
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);

}

void prepare_interleaved_buffer() {
	float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	GLuint vbo = 0;

	glGenBuffers(1, &vbo);
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLuint ebo = 0;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	vao = 0;
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

	GLuint pos_vao = 0;
	GLuint color_vao = 1;

	GL_CALL(glEnableVertexAttribArray(pos_vao));
	GL_CALL(glVertexAttribPointer(pos_vao, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<const void*>(0)));

	GL_CALL(glEnableVertexAttribArray(color_vao));
	GL_CALL(glVertexAttribPointer(color_vao, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<const void*>(3 * sizeof(float))));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	GL_CALL(glBindVertexArray(0));
}

std::shared_ptr<Shader_program> shader_program = std::make_shared<Shader_program>();

void prepare_shader() {

	std::string vertex_shader_code = utils::load_from_file("assets/shaders/simple/vertex.glsl");
	std::string fragment_shader_code = utils::load_from_file("assets/shaders/simple/fragment.glsl");

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

void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	shader_program->attach_program();
	GL_CALL(glBindVertexArray(vao));
	GL_CALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
	GL_CALL(glBindVertexArray(0));
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

	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

	while (App::get_instance()->is_active()) {
		render();
		App::get_instance()->update();
	}

	Application::destroy();

	return 0;
}