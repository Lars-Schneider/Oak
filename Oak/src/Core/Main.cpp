#include "../Scene/ECS/ECS.h"
#include "../Scene/ECS/Components/Components.h"
#include "../Scene/ECS/ECSTypes.h"

int main(int argc, char** argv)
{
	ECS ecs = ECS();

	Entity player = ecs.CreateEntity();
	Entity player2 = ecs.CreateEntity();

	ecs.AddComponent<TagComponent>(player, TagComponent{ "Player" });
	ecs.AddComponent<TagComponent>(player2, TagComponent{ "Player2" });

	ecs.Update();

	ecs.GetComponent<TagComponent>(player).tag = "1";
	ecs.GetComponent<TagComponent>(player2).tag = "2";

	ecs.Update();

	while (true);
	return 1;
}