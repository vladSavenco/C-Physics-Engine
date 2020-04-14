#include "GameEngine.h"

//Time Global Values
float oldTimeSinceStart, newTimeSinceStart;

//Object Vector
std::vector<GameObject*> objects;
std::vector<GameObject*> particles;

//Creating Objects, cubes in this example
//GameObject* cube = new Cube(glm::vec3(1, 1, 0));
//GameObject* cube2 = new Cube(glm::vec3(3, 0, 1));

//Creating the Player
GameObject* player = new Player(1.0f, glm::vec3(0, 3, 0), "box");

//Creating particles
GameObject* particle0 = new Particle(1.0f, glm::vec3(-3, -1, 0),"sphere");
GameObject* particle1 = new Particle(1.0f, glm::vec3(1, -2, 0),"box");
GameObject* particle2 = new Particle(1.0f, glm::vec3(3, 3, 0),"sphere");
GameObject* particle3 = new Particle(1.0f, glm::vec3(4, 3, 0), "sphere");

//Creating a rigid body
//GameObject* RigidBody = new RigidBody2D(1,1,1,glm::vec3(0, 0, 0));

GameEngine engine;

// Main routine.
int main(int argc, char** argv)
{
	engine.InitEngine(argc, argv, "GameEngine Window", 500, 500);

	engine.AddGameObject(player);

	engine.AddGameObject(particle0);
	engine.AddGameObject(particle1);
	engine.AddGameObject(particle2);
	engine.AddGameObject(particle3);

	//engine.AddGameObject(RigidBody);

	engine.StartEngine();

	return 0;
}