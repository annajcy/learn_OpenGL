#include "global/core.h"
#include "global/singleton.h"
#include "global/error_check.h"

#include "graphics/shader/shader_code.h"
#include "graphics/shader/shader_program.h"
#include "graphics/texture.h"
#include "graphics/geometry.h"
#include "graphics/renderer.h"

#include "application/application.h"
#include "application/image.h"
#include "application/input.h"

#include "application/camera/control/trackball_camera_control.h"
#include "application/camera/control/game_camera_control.h"
#include "application/camera/type/orthographic_camera.h"
#include "application/camera/type/perspective_camera.h"

#include "utils/string_utils.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "assimp/Importer.hpp"

#include <string>
#include <memory>
#include <iostream>

std::shared_ptr<Texture> main_texture {};
std::shared_ptr<Texture> specular_mask_texture {};

std::shared_ptr<Perspective_camera> camera{};
std::shared_ptr<Trackball_camera_control> camera_control{};

std::shared_ptr<Mesh> mesh1{};
std::shared_ptr<Mesh> mesh2{};

std::shared_ptr<Light_setting> light_setting{};
std::shared_ptr<Renderer> renderer{};

std::shared_ptr<Scene> scene{};

glm::vec3 clear_color{};

void prepare_imgui() {
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(App::get_instance()->window(), true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void prepare_events() {
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
}

void prepare_texture() {
	auto main_image = std::make_shared<Image>("assets/image/box.png");
	auto specular_mask_image = std::make_shared<Image>("assets/image/sp_mask.png");

	main_texture = std::make_shared<Texture>(main_image, 0, false);
	specular_mask_texture = std::make_shared<Texture>(specular_mask_image, 1, false);

	main_texture->attach_texture();
	main_texture->set_wrap(Texture::Warp::S, Texture::Wrap_type::REPEAT);
	main_texture->set_wrap(Texture::Warp::T, Texture::Wrap_type::REPEAT);
	main_texture->set_filter(Texture::Filter::MIN, Texture::Filter_type::LINEAR_MIPMAP_LINEAR);
	main_texture->set_filter(Texture::Filter::MAG, Texture::Filter_type::LINEAR);
	main_texture->detach_texture();

	specular_mask_texture->attach_texture();
	specular_mask_texture->set_wrap(Texture::Warp::S, Texture::Wrap_type::REPEAT);
	specular_mask_texture->set_wrap(Texture::Warp::T, Texture::Wrap_type::REPEAT);
	specular_mask_texture->set_filter(Texture::Filter::MIN, Texture::Filter_type::LINEAR_MIPMAP_LINEAR);
	specular_mask_texture->set_filter(Texture::Filter::MAG, Texture::Filter_type::LINEAR);
	specular_mask_texture->detach_texture();

}

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

void prepare_lights() {
	
	auto directional_light = std::make_shared<Directional_light>(); 
	directional_light->direction() = glm::vec3(0.0, 1.0, 0.0);
	
	auto spot_light = std::make_shared<Spot_light>();
	spot_light->position() = glm::vec3(0.0f, 0.0f, 2.0f);
	spot_light->direction() = glm::vec3(0.0, 0.0f, -1.0f);
	spot_light->inner_angle() = 5.0f;
	spot_light->outer_angle() = 10.0f;
	spot_light->color() = glm::vec3(1.0, 1.0, 0.0);

	auto point_light_1 = std::make_shared<Point_light>();
	point_light_1->position() = glm::vec3(1.0f, 0.0f, 0.0f);
	point_light_1->color() = glm::vec3(1.0f, 0.0f, 0.0f);

	auto point_light_2 = std::make_shared<Point_light>();
	point_light_2->position() = glm::vec3(0.0f, 1.0f, 0.0f);
	point_light_2->color() = glm::vec3(0.0f, 1.0f, 0.0f);

	auto point_light_3 = std::make_shared<Point_light>();
	point_light_3->position() = glm::vec3(0.0f, 0.0f, -1.0f);
	point_light_3->color() = glm::vec3(0.0f, 0.0f, 1.0f);

	auto ambient_light = std::make_shared<Ambient_light>();
	ambient_light->intensity() = 0.3f;

	light_setting = std::make_shared<Light_setting>(std::vector<std::shared_ptr<Light>> {
		ambient_light, directional_light, point_light_1, point_light_2, point_light_3, spot_light
	});
}

void prepare_mesh() {
	auto phong_material = std::make_shared<Phong_material>();
	phong_material->main_texture() = main_texture;
	phong_material->specular_mask_texture() = specular_mask_texture;

	auto white_material = std::make_shared<White_material>();

	auto box = Geometry::create_box(1.0f);
	auto sphere = Geometry::create_sphere(0.1f, 60, 60);

	mesh1 = std::make_shared<Mesh>(box, phong_material);
	mesh2 = std::make_shared<Mesh>(sphere, white_material);

	mesh2->position() = glm::vec3(0.0, 0.0, 2.0);

	mesh1->add_child(mesh2);

	scene = std::make_shared<Scene>();
	scene->add_child(mesh1);
}

void prepare_renderer() {
	renderer = std::make_shared<Renderer>(scene, camera, light_setting);
	renderer->init_state();
	renderer->set_clear_color(clear_color);
}

void render_gui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Hello world");
	{
		ImGui::ColorEdit3("clear color", glm::value_ptr(clear_color));

		if (ImGui::Button("change clear color", ImVec2(50, 20))) {
			renderer->set_clear_color(clear_color);
		}
	}
	ImGui::End();

	ImGui::Render();
	glViewport(0, 0, App::get_instance()->width(), App::get_instance()->height());
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
}

int main()
{
	if (!App::get_instance()->init()) {
		std::cout << "init Failed" << std::endl;
		return -1;
	}

	prepare_imgui();
	prepare_events();
	prepare_texture();
	prepare_camera();
	prepare_mesh();
	prepare_lights();
	prepare_renderer();

	glViewport(0, 0, App::get_instance()->width(), App::get_instance()->height());

	while (App::get_instance()->is_active()) {
		App::get_instance()->update();
		camera_control->update();

		mesh1->rotation_euler().x += 2.0f;

		renderer->clear();
		renderer->render();
		render_gui();
	}

	Application::destroy();

	return 0;
}


