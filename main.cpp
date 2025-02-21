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
#include "application/assimp_loader.h"

#include "graphics/camera/control/trackball_camera_control.h"
#include "graphics/camera/control/game_camera_control.h"
#include "graphics/camera/orthographic_camera.h"
#include "graphics/camera/perspective_camera.h"

#include "utils/string_utils.h"

std::shared_ptr<Texture> main_texture {};
std::shared_ptr<Texture> specular_mask_texture {};

std::shared_ptr<Perspective_camera> camera{};
std::shared_ptr<Trackball_camera_control> camera_control{};

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

void prepare_camera() {

	camera = std::make_shared<Perspective_camera>(
		60.0f,
		(float) App::get_instance()->width() / (float) App::get_instance()->height(),
		0.1f, 
		50.0f
	);

	camera->position() = glm::vec3(0.0f, 0.0f, -5.0f);
	camera_control = std::make_shared<Trackball_camera_control>(camera);
}

void prepare_lights() {
	
	auto directional_light = std::make_shared<Directional_light>(); 

	directional_light->look_at(glm::vec3(1.0, 0.0, 0.0));
	
	auto spot_light = std::make_shared<Spot_light>();
	spot_light->position() = glm::vec3(0.0f, 0.0f, 2.0f);
	spot_light->look_at(glm::vec3(0.0, 0.0f, -1.0f));
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

void prepare_model() {

	scene = std::make_shared<Scene>();

	Assimp_loader::default_material_type = Material::Material_type::PHONG_SPECULAR_MASK;
	auto model = Assimp_loader::load("assets/model/backpack/backpack.obj");
	model->scale() = glm::vec3(0.95f);
	scene->add_child(model);

	// Assimp_loader::default_material_type = Material::Material_type::PHONG_OPACITY_MASK;
	// auto model = Assimp_loader::load("assets/model/grass/grass.fbx");
	// model->scale() = glm::vec3(0.005f);
	// scene->add_child(model);

	// Assimp_loader::default_material_type = Material::Material_type::EDGE;
	// auto model_edge = Assimp_loader::load("assets/model/backpack/backpack.obj");
	// scene->add_child(model_edge);
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

void render() {
	renderer->clear();
	renderer->render();
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
		render_gui();
	}

	Application::destroy();

	return 0;
}


