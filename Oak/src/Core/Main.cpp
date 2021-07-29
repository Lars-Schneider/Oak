#include "src/ECS/ECS.h"
#include "src/Scripting/Lua.h"
#include "src/Scripting/Lua_API.h"
#include "src/Scripting/ECS Lua.h"
using namespace Oak;

int main(int argc, char** argv)
{
	ECS_Manager* ecs = new ECS_Manager();
	Oak::Lua_ECS_instance = new Oak::ECS_Instace();
	Oak::Lua_ECS_instance->manager = ecs;

	Entity player = ecs->Create_Entity();
	ecs->Add_Tag(player, { "Player" });
	ecs->Add_Position(player, { 100,100 });
	ECS_Lua_Add_Script(player);

	Entity p2 = ecs->Create_Entity();
	ecs->Add_Tag(p2, { "Player 2" });
	ecs->Add_Position(p2, { 54,54 });

	//Call every frame for each entity with a script.
	Lua_Call_Function(ecs->Get_Script(player).L, "Script", "Update");

	for (;;);
	delete ecs;
}