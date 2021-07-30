#include "src/ECS/ECS.h"
#include "src/Scripting/Lua.h"
#include "src/Scripting/Lua_API.h"
#include "src/Scripting/ECS Lua.h"
#include <src/Renderer/SDL/SDLWindow.h>
#include <src/Renderer/SDL/SDLRenderer.h>
using namespace Oak;

int main(int argc, char** argv)
{
	//Window creation
	SDLWindow* window = new SDLWindow();
	window->Create("Oak", 100, 100, 600, 480);

	SDLRenderer* renderer = new SDLRenderer(window);
	renderer->Init();

	//Ecs initialization.
	ECS_Manager* ecs = new ECS_Manager();

	Oak::manager= ecs;

	//Main entity
	Entity player = ecs->Create_Entity();
	ecs->Add_Tag(player, { "Player" });
	ecs->Add_Position(player, { 100,100 });
	ecs->Add_Rect(player, { 100,100,100,100,45,60,75,255 });
	ECS_Lua_Add_Script(player);

	//To prove that there can be more than one entity.
	Entity p2 = ecs->Create_Entity();
	ecs->Add_Tag(p2, { "Player 2" });
	ecs->Add_Position(p2, { 54,54 });

	//Call every frame for each entity with a script.
	Lua_Call_Function(ecs->Get_Script(player).L, ecs->Get_Script(player).path, "Update");


	while (!window->Should_Close())
	{
		window->PollEvents();
		renderer->BeginFrame();

		for (Entity e = 0; e < OAK_ECS_MAX_ENTITES; e++)
		{
			if (ecs->Has_Rect(e))
			{
				f32 x = ecs->Get_Rect(e).x;
				f32 y = ecs->Get_Rect(e).y;
				f32 w = ecs->Get_Rect(e).w;
				f32 h = ecs->Get_Rect(e).h;
				i32 r = ecs->Get_Rect(e).r;
				i32 g = ecs->Get_Rect(e).g;
				i32 b = ecs->Get_Rect(e).b;
				i32 a = ecs->Get_Rect(e).a;
				renderer->DrawQuad(x, y, w, h, r, g, b, a);
			}
		}

		renderer->EndFrame();
	}
	delete ecs;
	delete window;
	delete renderer;
	return 1;
}