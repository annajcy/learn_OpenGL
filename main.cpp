#include "global/core.h"
#include "global/singleton.h"
#include "global/error_check.h"

#include "graphics/shader/shader_code.h"
#include "graphics/shader/shader_program.h"
#include "graphics/texture.h"
#include "graphics/geometry/geometry.h"
#include "graphics/geometry/geometry_instance.h"
#include "graphics/renderer.h"

#include "application/application.h"
#include "application/image.h"
#include "application/input.h"
#include "application/assimp_loader.h"

#include "graphics/camera/control/trackball_camera_control.h"
#include "graphics/camera/control/game_camera_control.h"
#include "graphics/camera/orthographic_camera.h"
#include "graphics/camera/perspective_camera.h"

#include "utils/string_utils.h"

#include "graphics/material/material.h"
#include "graphics/material/phong_material.h"
#include "graphics/material/phong_specular_mask_material.h"
#include "graphics/material/phong_opacity_mask_material.h"
#include "graphics/material/phong_instance_material.h"
#include "graphics/material/screen_material.h"
#include "graphics/material/cube_map_material.h"
#include "graphics/material/depth_material.h"
#include "graphics/material/edge_material.h"
#include "graphics/material/sperical_map_material.h"


#include "graphics/light/light.h"
#include "graphics/light/ambient_light.h"
#include "graphics/light/directional_light.h"
#include "graphics/light/point_light.h"
#include "graphics/light/spot_light.h"

#include "graphics/node.h"
#include "graphics/scene.h"

#include "graphics/frame_buffer.h"

std::shared_ptr<Texture> main_texture {};
std::shared_ptr<Texture> specular_mask_texture {};

std::shared_ptr<Perspective_camera> camera{};
std::shared_ptr<Trackball_camera_control> camera_control{};

std::shared_ptr<Light_setting> light_setting{};
std::shared_ptr<Renderer> renderer{};

std::shared_ptr<Scene> scene{};
std::shared_ptr<Scene> screen_scene{};

std::shared_ptr<Frame_buffer> frame_buffer{};

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

void prepare_camera() {

	camera = std::make_shared<Perspective_camera>(
		60.0f,
		(float) App::get_instance()->width() / (float) App::get_instance()->height(),
		0.1f, 
		50.0f
	);

	camera->position() = glm::vec3(0.0f, 0.0f, 5.0f);
	camera->look_at_point(glm::vec3(0.0f, 0.0f, 0.0f));
	camera_control = std::make_shared<Trackball_camera_control>(camera);
}

void prepare_lights() {
	
	auto directional_light = std::make_shared<Directional_light>(); 
	directional_light->look_at_direction(glm::vec3(1.0, -1.0, -1.0));
	directional_light->intensity() = 0.5f;

	auto ambient_light = std::make_shared<Ambient_light>();
	ambient_light->intensity() = 0.25f;
	
	auto spot_light = std::make_shared<Spot_light>();
	spot_light->position() = glm::vec3(0.0f, 0.0f, 2.0f);
	spot_light->look_at_direction(glm::vec3(0.0, 0.0f, -1.0f));
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

	light_setting = std::make_shared<Light_setting>(std::vector<std::shared_ptr<Light>> {
		ambient_light, directional_light, point_light_1, point_light_2, point_light_3, spot_light
	});

}

void prepare_model() {

	frame_buffer = std::make_shared<Frame_buffer>(App::get_instance()->width(), App::get_instance()->height());
	
	scene = std::make_shared<Scene>();
	screen_scene = std::make_shared<Scene>();

	//skybox
	if (true) {
		auto skybox_material = std::make_shared<Cube_map_material>();
		auto box = Geometry::create_box(100.0f);
		auto skybox = std::make_shared<Mesh>(box, skybox_material);
		scene->add_child(skybox);
	}

	if (false) {
		auto skybox_material = std::make_shared<Sperical_map_material>();
		auto box = Geometry::create_box(5.0f);
		auto skybox = std::make_shared<Mesh>(box, skybox_material);
		scene->add_child(skybox);
	}

	//model

	if (false) {
		Assimp_loader::default_material_type = Material::Material_type::PHONG;
		auto model = Assimp_loader::load("assets/model/mary/Marry.obj");
		model->position().y -= 1.5f;
		scene->add_child(model);

		auto plane_material = std::make_shared<Phong_material>();
		plane_material->main_texture() = Texture::create_default_texture();
		auto plane = std::make_shared<Mesh>(Geometry::create_plane(50.0f, 50.0f), plane_material);
		plane->rotate(-90.0f, plane->right());
		plane->position().y -= 1.5f;
		scene->add_child(plane);
	}

	if (false) {
		Assimp_loader::default_material_type = Material::Material_type::PHONG_OPACITY_MASK;
		auto grass = Assimp_loader::load("assets/model/grass/grass.fbx");
		grass->scale() = glm::vec3(0.005f);
		grass->position().x -= 1.5f;
		grass->position().y -= 1.3f;
		scene->add_child(grass);
	}

	if (false) {	
		Assimp_loader::default_material_type = Material::Material_type::PHONG_SPECULAR_MASK;
		auto bag = Assimp_loader::load("assets/model/backpack/backpack.obj");
		bag->position().z -= 2.0f;
		bag->position().y += 1.0f;
		scene->add_child(bag);
	}

	//instanced draw

	if (true) {
		auto material = std::make_shared<Phong_instance_material>();
		material->main_texture() = Texture::create_default_texture();

		// auto geometry = Geometry_instance::create_sphere(0.3f, 60, 60, std::vector<glm::mat4> {
		// 	glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
		// 	glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
		// 	glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		// } );

		auto geometry = Geometry_instance::create_box(0.3f, std::vector<glm::mat4> {
			glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
			glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
			glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
		} );

		auto instance = std::make_shared<Mesh>(geometry, material);
		scene->add_child(instance);
	}

	//screen

	if (true) {
		auto material = std::make_shared<Screen_material>();
		material->screen_texture() = frame_buffer->color_attachment();

		auto geometry = Geometry::create_screen();
		auto screen = std::make_shared<Mesh>(geometry, material);
		
		screen_scene->add_child(screen);
	}
}

void prepare_renderer() {
	renderer = std::make_shared<Renderer>();
	renderer->camera() = camera;
	renderer->light_setting() = light_setting;
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

void render() {
	//pass 1
	renderer->scene() = scene;
	renderer->render(frame_buffer);

	//pass 2
	renderer->scene() = screen_scene;
	renderer->render();

	render_gui();
}


int main()
{
	if (!App::get_instance()->init()) {
		std::cout << "init Failed" << std::endl;
		return -1;
	}

	prepare_imgui();
	prepare_events();
	prepare_camera();
	prepare_lights();
	prepare_model();
	prepare_renderer();

	glViewport(0, 0, App::get_instance()->width(), App::get_instance()->height());

	while (App::get_instance()->is_active()) {
		App::get_instance()->update();
		camera_control->update();
		render();
	}

	Application::destroy();

	return 0;
}


