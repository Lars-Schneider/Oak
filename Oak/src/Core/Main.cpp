#include "src/ECS/ECS.h"
#include "src/Scripting/Lua.h"
#include "src/Scripting/Lua_API.h"
#include "src/Scripting/ECS Lua.h"
using namespace Oak;
int Print(lua_State* L)
{
	std::cout << lua_tostring(L, -1) << "\n";
	return 1;
}
int main(int argc, char** argv)
{
	ECS_Manager* ecs = new ECS_Manager();
	Oak::Lua_ECS_instance = new Oak::ECS_Instace();
	Oak::Lua_ECS_instance->manager = ecs;

	Entity player = ecs->Create_Entity();
	ecs->Add_Tag(player, { "Player" });
	ecs->Add_Position(player, { 100,100 });

	Entity p2 = ecs->Create_Entity();
	ecs->Add_Tag(p2, { "Player 2" });
	ecs->Add_Position(p2, { 54,54 });

	lua_State* L = luaL_newstate();
	ECS_Lua_Push_Functions(L);
	Lua_Push_Function(L, "Print", Print);
	Lua_Call_Function(L, "Script", "Update");
	for (;;);
	delete ecs;
}