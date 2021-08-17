#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include <src/Renderer/OpenGLRenderer.h>
#include <src/Renderer/Camera.h>
#include <GLFW/glfw3.h>
#include "src/ECS/ECS.h"
#include "src/Scripting/Lua.h"
#include "src/Scripting/Lua_API.h"
#include "src/Scripting/ECS Lua.h"
using namespace Oak;




auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b)
{
	return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
};

void VSTheme()
{
	auto& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	const ImVec4 bgColor = ColorFromBytes(37, 37, 38);
	const ImVec4 lightBgColor = ColorFromBytes(82, 82, 85);
	const ImVec4 veryLightBgColor = ColorFromBytes(90, 90, 95);

	const ImVec4 panelColor = ColorFromBytes(51, 51, 55);
	const ImVec4 panelHoverColor = ColorFromBytes(29, 151, 236);
	const ImVec4 panelActiveColor = ColorFromBytes(0, 119, 200);

	const ImVec4 textColor = ColorFromBytes(255, 255, 255);
	const ImVec4 textDisabledColor = ColorFromBytes(151, 151, 151);
	const ImVec4 borderColor = ColorFromBytes(78, 78, 78);
	colors[ImGuiCol_Text] = textColor;
	colors[ImGuiCol_TextDisabled] = textDisabledColor;
	colors[ImGuiCol_TextSelectedBg] = panelActiveColor;
	colors[ImGuiCol_WindowBg] = bgColor;
	colors[ImGuiCol_ChildBg] = bgColor;
	colors[ImGuiCol_PopupBg] = bgColor;
	colors[ImGuiCol_Border] = borderColor;
	colors[ImGuiCol_BorderShadow] = borderColor;
	colors[ImGuiCol_FrameBg] = panelColor;
	colors[ImGuiCol_FrameBgHovered] = panelHoverColor;
	colors[ImGuiCol_FrameBgActive] = panelActiveColor;
	colors[ImGuiCol_TitleBg] = bgColor;
	colors[ImGuiCol_TitleBgActive] = bgColor;
	colors[ImGuiCol_TitleBgCollapsed] = bgColor;
	colors[ImGuiCol_MenuBarBg] = panelColor;
	colors[ImGuiCol_ScrollbarBg] = panelColor;
	colors[ImGuiCol_ScrollbarGrab] = lightBgColor;
	colors[ImGuiCol_ScrollbarGrabHovered] = veryLightBgColor;
	colors[ImGuiCol_ScrollbarGrabActive] = veryLightBgColor;
	colors[ImGuiCol_CheckMark] = panelActiveColor;
	colors[ImGuiCol_SliderGrab] = panelHoverColor;
	colors[ImGuiCol_SliderGrabActive] = panelActiveColor;
	colors[ImGuiCol_Button] = panelColor;
	colors[ImGuiCol_ButtonHovered] = panelHoverColor;
	colors[ImGuiCol_ButtonActive] = panelHoverColor;
	colors[ImGuiCol_Header] = panelColor;
	colors[ImGuiCol_HeaderHovered] = panelHoverColor;
	colors[ImGuiCol_HeaderActive] = panelActiveColor;
	colors[ImGuiCol_Separator] = borderColor;
	colors[ImGuiCol_SeparatorHovered] = borderColor;
	colors[ImGuiCol_SeparatorActive] = borderColor;
	colors[ImGuiCol_ResizeGrip] = bgColor;
	colors[ImGuiCol_ResizeGripHovered] = panelColor;
	colors[ImGuiCol_ResizeGripActive] = lightBgColor;
	colors[ImGuiCol_PlotLines] = panelActiveColor;
	colors[ImGuiCol_PlotLinesHovered] = panelHoverColor;
	colors[ImGuiCol_PlotHistogram] = panelActiveColor;
	colors[ImGuiCol_PlotHistogramHovered] = panelHoverColor;
	//colors[ImGuiCol_ModalWindowDarkening] = bgColor;
	colors[ImGuiCol_DragDropTarget] = bgColor;
	colors[ImGuiCol_NavHighlight] = bgColor;
	//colors[ImGuiCol_DockingPreview] = panelActiveColor;
	colors[ImGuiCol_Tab] = bgColor;
	colors[ImGuiCol_TabActive] = panelActiveColor;
	colors[ImGuiCol_TabUnfocused] = bgColor;
	colors[ImGuiCol_TabUnfocusedActive] = panelActiveColor;
	colors[ImGuiCol_TabHovered] = panelHoverColor;

	style.WindowRounding = 0.0f;
	style.ChildRounding = 0.0f;
	style.FrameRounding = 0.0f;
	style.GrabRounding = 0.0f;
	style.PopupRounding = 0.0f;
	style.ScrollbarRounding = 0.0f;
	style.TabRounding = 0.0f;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	Oak::width = width;
	Oak::height = height;
}
void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
int main(int argc, char** argv)
{
	bool running = false;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 32); // Uhuh? 


	GLFWwindow* window =  glfwCreateWindow(800, 640, "Oak Game Engine", NULL, NULL); // Title now redundant..
	
	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	glfwSwapInterval(1);
	//GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL.";
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Rendering
	OpenGLRenderer* renderer = new OpenGLRenderer();
	renderer->Init();

	Camera* camera = new Camera(800, 640, glm::vec3(0.0f, 0.0f, 2.0f));
	camera->Position.z = 10;

	//Ecs initialization.
	ECS* ecs = new ECS();

	Oak::manager = ecs;
	Oak::window = window;
	Oak::camera = camera;

	//Main entity





	//Imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	VSTheme();
	bool viewing_script = false;
	char* current_script = new char[0];

	Entity selected_entity = 0;

	Entity player = ecs->CreateEntity();
	ecs->AddTag(player, { "Player" });
	ecs->AddTransform(player, { 0,2,1,1 });
	ecs->AddQuad(player, { 1,0,0,1 });
	ECS_Lua_Add_Script(player);

	Entity ground = ecs->CreateEntity();
	ecs->AddTag(ground, { "Ground" });
	ecs->AddTransform(ground, { 0,0,100,100 });
	ecs->AddQuad(ground, { 0.63,0.2789,0.1512,1 });

	f64 lastUpdateTime = 0;  // number of seconds since the last loop
	f64 lastFrameTime = 0;   // number of seconds since the last frame

	char* buf = new char[1024];

	//Game loop
	glfwMaximizeWindow(window);
	while (!glfwWindowShouldClose(window))
	{
		double now = glfwGetTime();
		double deltaTime = now - lastUpdateTime;
		double dt = now - lastFrameTime;

		glfwPollEvents();

		// update your application logic here,
		// using deltaTime if necessary (for physics, tweening, etc.)
		ProcessInput(window);

		
		glfwPollEvents();
		// This if-statement only executes once every 60th of a second
		//if ((now - lastFrameTime) >= fpsLimit)
		{
			if (running)
			{
				for (ECS_Script_c& s : ecs->Scripts())
				{
					Lua_Update(s.L, dt, s.path);
				}
			}
			if (!running)
				camera->Input(window, dt);
			// draw your frame here
			glClearColor(0.2125f, 0.4356f, 0.85f, 0.5f);
			glClear(GL_COLOR_BUFFER_BIT);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();



			renderer->BeginFrame();

			for (Entity e : ecs->WithQuads())
			{
				std::cout << 1;
				ECS_Transform_c& t = ecs->GetTransform(e);
				ECS_Quad_c& q = ecs->GetQuad(e);
				renderer->DrawQuad(t.x, t.y, t.w, t.h, q.r, q.g, q.b, q.a);
			}


			camera->Matrix(45.0f, 0.1f, 1000.0f, renderer->GetShader(), "camMatrix");
			glfwGetWindowSize(window, &camera->width, &camera->height);

			renderer->EndFrame();
	
			ImGui::Begin("FPS");
			ImGui::Text(std::to_string(1 / dt).c_str());
			ImGui::End();
			ImGui::Begin("Game");
			ImGui::Checkbox("Play", &running);
			ImGui::End();
			if (!running)
			{
				//IMGUI
				ImGui::Begin("Scene");


				if (ImGui::Button("Add Entity"))
				{
					selected_entity = ecs->CreateEntity();
					std::string tag = std::to_string(selected_entity);
					ecs->AddTag(selected_entity, { tag });
					ecs->AddTransform(selected_entity, { 0,0,1,1 });
					ecs->AddQuad(selected_entity, { 0,1,0.5f,1 });
				}
				for (Entity e = 0; e < ecs->latest_entity; e++)
				{

					if (ImGui::Button(ecs->GetTag(e).tag.c_str()))
					{
						selected_entity = e;
					}
				}
				ImGui::End();

				ImGui::Begin("Camera");
				ImGui::SliderFloat("X", &camera->Position.x, -1000, 1000);
				ImGui::SliderFloat("Y", &camera->Position.y, -1000, 1000);
				ImGui::SliderFloat("Zoom", &camera->Position.z, 2, 100);
				ImGui::SliderFloat("Speed", &camera->speed, 0, 100);
				ImGui::End();




				ImGui::Begin("Entity");
				buf = (char*)ecs->GetTag(selected_entity).tag.c_str();
				ImGui::InputText("Tag", buf, 1024 * sizeof(char));
				ImGui::SameLine();
				if (ImGui::Button("Set Tag"))
				{
					ecs->GetTag(selected_entity).tag = buf;
				}
				
				//std::cout << ecs->Get_Tag(selected_entity).tag;
				ImGui::SliderFloat("X", &ecs->GetTransform(selected_entity).x, -100, 100);

				ImGui::SliderFloat("Y", &ecs->GetTransform(selected_entity).y, -100, 100);
				ImGui::SliderFloat("W", &ecs->GetTransform(selected_entity).w, 0, 100);
				ImGui::SliderFloat("H", &ecs->GetTransform(selected_entity).h, 0, 100);
				float* color = new float[4];
				color[0] = ecs->GetQuad(selected_entity).r;
				color[1] = ecs->GetQuad(selected_entity).g;
				color[2] = ecs->GetQuad(selected_entity).b;
				color[3] = ecs->GetQuad(selected_entity).a;
				ImGui::ColorEdit4("Color", color);
				ecs->GetQuad(selected_entity).r = color[0];
				ecs->GetQuad(selected_entity).g = color[1];
				ecs->GetQuad(selected_entity).b = color[2];
				ecs->GetQuad(selected_entity).a = color[3];
				if (ImGui::Button("Add Script"))
				{
					ECS_Lua_Add_Script(selected_entity);
				}
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);

			// only set lastFrameTime when you actually draw something
			lastFrameTime = now;
		}

		// set lastUpdateTime every iteration
		lastUpdateTime = now;
		
		
		
	}
	glfwTerminate();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	delete ecs;
	delete renderer;
	delete camera;
	delete[] current_script;
	return 1;
}