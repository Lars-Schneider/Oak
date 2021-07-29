#include "src/ECS/ECS.h"
using namespace Oak;
int main(int argc, char** argv)
{
	ECS_Manager* ecs = new ECS_Manager();
	Entity player = ecs->Create_Entity();
	ecs->Add_Position(player, { 100,100 });

	delete ecs;
}