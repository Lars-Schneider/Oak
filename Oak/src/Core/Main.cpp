#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "src/ECS/ECS.h"
#include "src/Scripting/Lua.h"
#include "src/Scripting/Lua_API.h"
#include "src/Scripting/ECS Lua.h"
#include <src/Renderer/OpenGLRenderer.h>
#include <GLFW/glfw3.h>
#include <src/Renderer/Camera.h>
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
	//GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* glfwwindow = glfwCreateWindow(800, 640, "Oak", NULL, NULL);
	Oak::width = 800;
	Oak::height = 640;
	if (glfwwindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(glfwwindow);
	glfwSetFramebufferSizeCallback(glfwwindow, framebuffer_size_callback);

	//GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL.";
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Rendering
	OpenGLRenderer* oglrenderer = new OpenGLRenderer();
	oglrenderer->Init();

	Camera* camera = new Camera(800, 640, glm::vec3(0.0f, 0.0f, 2.0f));
	camera->Position.z = 10;

	//Ecs initialization.
	ECS_Manager* ecs = new ECS_Manager();

	Oak::manager = ecs;

	//Main entity





	//Imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(glfwwindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	VSTheme();

	Entity selected_entity = 0;


	//Game loop

	while (!glfwWindowShouldClose(glfwwindow))
	{
		ProcessInput(glfwwindow);
		glClearColor(0.2125f, 0.4356f, 0.85f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		oglrenderer->BeginFrame();

		for (Entity e = 0; e < OAK_ECS_MAX_ENTITES; e++)
		{
			if (ecs->Has_Rect(e))
			{
				f32 x = ecs->Get_Transform(e).x;
				f32 y = ecs->Get_Transform(e).y;
				f32 w = ecs->Get_Transform(e).w;
				f32 h = ecs->Get_Transform(e).h;
				f32 r = ecs->Get_Rect(e).r;
				f32 g = ecs->Get_Rect(e).g;
				f32 b = ecs->Get_Rect(e).b;
				f32 a = ecs->Get_Rect(e).a;
				oglrenderer->DrawQuad(x, y, w, h, r, g, b, a);
			}
		}


		camera->Input(glfwwindow);
		camera->Matrix(45.0f, 0.1f, 1000.0f, oglrenderer->GetShader(), "camMatrix");
		glfwGetWindowSize(glfwwindow, &camera->width, &camera->height);
		oglrenderer->EndFrame();

		ImGui::Begin("Stats");
		std::string qc("Quad Count: ");
		qc += std::to_string(oglrenderer->QuadCount());
		ImGui::Text(qc.c_str());
		std::string vc("Vertex Count: ");
		vc += std::to_string(oglrenderer->VertexCount());
		ImGui::Text(vc.c_str());
		ImGui::End();

		ImGui::Begin("Scene");


		if (ImGui::Button("Add Entity"))
		{
			selected_entity = ecs->Create_Entity();
			std::string tag = std::to_string(selected_entity);
			ecs->Add_Tag(selected_entity, { tag });
			ecs->Add_Transform(selected_entity, { 0,0,1,1 });
			ecs->Add_Rect(selected_entity, { 0,1,0.5f,1 });
		}
		for (Entity e = 0; e < ecs->latest_entity; e++)
		{
			std::cout << ecs->Get_Tag(e).tag.c_str()<<"\n";
	
			if (ImGui::Button(ecs->Get_Tag(e).tag.c_str()))
			{
				selected_entity = e;
			}
		}
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::SliderFloat("X", &camera->Position.x, -1000, 1000);
		ImGui::SliderFloat("Y", &camera->Position.y, -1000, 1000);
		ImGui::SliderFloat("Zoom", &camera->Position.z, 2, 100);
		ImGui::SliderFloat("Speed", &camera->speed, 0, 1);
		ImGui::End();
		

		ImGui::Begin(std::to_string(selected_entity).c_str());
		ImGui::SliderFloat("X", &ecs->Get_Transform(selected_entity).x, -100, 100);
		ImGui::SliderFloat("Y", &ecs->Get_Transform(selected_entity).y, -100, 100);
		ImGui::SliderFloat("W", &ecs->Get_Transform(selected_entity).w, 0, 100);
		ImGui::SliderFloat("H", &ecs->Get_Transform(selected_entity).h, 0, 100);
		float* color = new float[4];
		color[0] = ecs->Get_Rect(selected_entity).r;
		color[1] = ecs->Get_Rect(selected_entity).g;
		color[2] = ecs->Get_Rect(selected_entity).b;
		color[3] = ecs->Get_Rect(selected_entity).a;
		ImGui::ColorEdit4("Color", color);
		
		ecs->Get_Rect(selected_entity).r = color[0];
		ecs->Get_Rect(selected_entity).g = color[1];
		ecs->Get_Rect(selected_entity).b = color[2];
		ecs->Get_Rect(selected_entity).a = color[3];
		
		ImGui::End();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(glfwwindow);
		glfwPollEvents();



		/*
		
		*/
	}
	delete ecs;
	delete oglrenderer;
	return 1;
}