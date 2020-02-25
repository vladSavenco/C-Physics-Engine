#include "GameEngine.h"

//Time Global Values
float oldTimeSinceStart, newTimeSinceStart;

//Object Vector
std::vector<GameObject*> objects;
std::vector<GameObject*> particles;

//Creating Objects, cubes in this example
GameObject* cube = new Cube(glm::vec3(1, 1, 0));
GameObject* cube2 = new Cube(glm::vec3(3, 0, 1));

//Creating particles
GameObject* particle = new Particle(1.0f, glm::vec3(0, 0, 0));

//Creating the Player
GameObject* player = new Player(1.0f, glm::vec3(0, 0, 0));

//Creating a rigid body
GameObject* RigidBody = new RigidBody2D(1,1,1,glm::vec3(0, 0, 0));

GameEngine engine;

// Main routine.
int main(int argc, char** argv)
{
	engine.InitEngine(argc, argv, "GameEngine Window", 500, 500);

	engine.AddGameObject(particle);
	engine.AddGameObject(RigidBody);

	engine.AddGameObject(player);

	engine.StartEngine();

	return 0;
}