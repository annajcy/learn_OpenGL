#include "glad/glad.h"
#include "error_check/error_check.h"
#include "framework/singleton.h"
#include "application/application.h"

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
			0.0f,  0.0f, 1.0f
	};

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

	glBindVertexArray(0);

}

void prepare_interleaved_buffer() {
	float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	GLuint vbo = 0;

	glGenBuffers(1, &vbo);
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	vao = 0;
	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

	GLuint pos_vao = 0;
	GLuint color_vao = 0;

	GL_CALL(glEnableVertexAttribArray(pos_vao));
	GL_CALL(glVertexAttribPointer(pos_vao, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<const void*>(0)));

	GL_CALL(glEnableVertexAttribArray(color_vao));
	GL_CALL(glVertexAttribPointer(color_vao, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<const void*>(0)));

	GL_CALL(glBindVertexArray(0));
}

void prepare_shader() {
	const char* vertexShaderSource = R"(
#version 410 core
layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

)";

	const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

)";

	GLuint vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//3 为shader程序输入shader代码
	glShaderSource(vertex, 1, &vertexShaderSource, nullptr);
	glShaderSource(fragment, 1, &fragmentShaderSource, nullptr);

	int success = 0;
	char infoLog[1024];

	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 1024, nullptr, infoLog);
		std::cout << "Error: SHADER COMPILE ERROR --VERTEX" << "\n" << infoLog << std::endl;
	} else {
		std::cout << "SHADER COMPILE Succeeded --VERTEX" << "\n";
	}

	glCompileShader(fragment);
	//检查fragment编译结果
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 1024, nullptr, infoLog);
		std::cout << "Error: SHADER COMPILE ERROR --FRAGMENT" << "\n" << infoLog << std::endl;
	} else {
		std::cout << "SHADER COMPILE Succeeded --FRAGMENT" << "\n";
	}

	program = 0;
	program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 1024, nullptr, infoLog);
		std::cout << "Error: SHADER LINK ERROR " << "\n" << infoLog << std::endl;
	} else {
		std::cout << "SHADER Linked Succeeded --FRAGMENT" << "\n";
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{
	if (!App::get_instance()->init()) {
		std::cout << "init Failed" << std::endl;
		return -1;
	}

	prepare_shader();
	prepare_interleaved_buffer();

	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

	while (App::get_instance()->is_active()) {
		render();
		App::get_instance()->update();
	}

	Application::destroy();

	return 0;
}
