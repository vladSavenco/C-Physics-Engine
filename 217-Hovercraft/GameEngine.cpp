#include "GameEngine.h"
using namespace std;

std::vector<GameObject*> GameEngine::objects;
std::vector<ColisionData*> GameEngine::objData;

//Collision Broad Phase vectors
std::vector<GameObject*> GameEngine::objectsUp;
std::vector<GameObject*> GameEngine::objectsDown;

int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;

void GameEngine::CollisionBroadphaseVectors()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->position.y + objects[i]->SpC.radius > 0 || objects[i]->position.y + objects[i]->BoC.colSide/2 > 0)
		{
			objectsUp.push_back(objects[i]);
		}

		if (objects[i]->position.y - objects[i]->SpC.radius < 0 || objects[i]->position.y - objects[i]->BoC.colSide/2 < 0)
		{
			objectsDown.push_back(objects[i]);
		}
	}
}

void GameEngine::ShowBroadphaseObjects()
{
	if (GameObject::specialKeys[GLUT_KEY_CTRL_L]==true)
	{
		std::cout << "The upper half contains: " << objectsUp.size() << " objects" <<"       "
		<< "The lower half contains: " << objectsDown.size() << " objects" << "\r";
	}
}

void GameEngine::CheckForCollision()
{
	//Check for collision 

	//UpVector
	for (int i = 0; i < objectsUp.size(); i++)
	{
		for (int j = i + 1; j < objectsUp.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			else
			{
				ColisionData* colData = nullptr;
				colData = new ColisionData;

				//sphere collisions
				if (objectsUp[i]->SpC.CollideCheck(objectsUp[j]->SpC, *colData))
				{
					colData->obj1 = objectsUp[i];
					colData->obj2 = objectsUp[j];
					objData.push_back(colData);

					//objectsUp[i]->SpC.collision = true;
					//objectsUp[j]->SpC.collision = true;
				}
				else
				{
					//cout << "Not Collided" << '\r';
					//objectsUp[i]->SpC.collision = false;
					//objectsUp[j]->SpC.collision = false;
				}

				//box collisions
				if (objectsUp[i]->BoC.CollideCheck(objectsUp[j]->BoC, *colData))
				{
					colData->obj1 = objectsUp[i];
					colData->obj2 = objectsUp[j];
					objData.push_back(colData);

					//objectsUp[i]->BoC.collision = true;
					//objectsUp[j]->BoC.collision = true;
				}
				else
				{
					//cout << "Not Collided" << '\r';
					//objectsUp[i]->BoC.collision = false;
					//objectsUp[j]->BoC.collision = false;
				}

			}
		}
	}

	//DownVector
	for (int i = 0; i < objectsDown.size(); i++)
	{
		for (int j = i + 1; j < objectsDown.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			else
			{
				ColisionData* colData = nullptr;
				colData = new ColisionData;

				//sphere collisions
				if (objectsDown[i]->SpC.CollideCheck(objectsDown[j]->SpC, *colData))
				{
					colData->obj1 = objectsDown[i];
					colData->obj2 = objectsDown[j];
					objData.push_back(colData);

					//objectsDown[i]->SpC.collision = true;
					//objectsDown[j]->SpC.collision = true;
				}
				else
				{
					//cout << "Not Collided" << '\r';
					//objectsDown[i]->SpC.collision = false;
					//objectsDown[j]->SpC.collision = false;
				}

				//box collisions
				if (objectsDown[i]->BoC.CollideCheck(objectsDown[j]->BoC, *colData))
				{
					colData->obj1 = objectsDown[i];
					colData->obj2 = objectsDown[j];
					objData.push_back(colData);

					//objectsDown[i]->BoC.collision = true;
					//objectsDown[j]->BoC.collision = true;
				}
				else
				{
					//cout << "Not Collided" << '\r';
					//objectsDown[i]->BoC.collision = false;
					//objectsDown[j]->BoC.collision = false;
				}

			}
		}
	}
}

void GameEngine::CollisionResolution()
{
	//Collision Resolution
	for (int i = objData.size() - 1; i >= 0; --i)
	{
		GameObject* obj1 = objData[i]->obj1;
		GameObject* obj2 = objData[i]->obj2;
		float val1;
		float val2;
		float impulse;

		val1 = glm::dot(-(obj1->velocity - obj2->velocity), objData[i]->normal);
		//Elasticity coeficient
		//val1 *= (1 + obj1->mass);

		val2 = glm::dot(objData[i]->normal, objData[i]->normal);
		val2 *= (1 / obj1->mass + 1 / obj2->mass);

		impulse = val1 / val2;

		obj1->velocity += (impulse / obj1->mass) * objData[i]->normal;
		obj2->velocity -= (impulse / obj1->mass) * objData[i]->normal;

		obj1->position = obj1->position + (objData[i]->depth * objData[i]->normal);
		obj2->position = obj2->position - (objData[i]->depth * objData[i]->normal);
	}

}

void GameEngine::CollisionDataCleanup()
{
	//Collision data cleanup
	for (int i = objData.size() - 1; i >= 0; --i)
	{
		delete objData[i];
	}

	objData.clear();

	objectsUp.clear();
	objectsDown.clear();
}

void GameEngine::UpdateGame(void)
{
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	float deltaTime = (newTimeSinceStart - oldTimeSinceStart);
	deltaTime /= 1000.f;

	//glm::vec3 red(1.0, 0.0, 0.0);
	
	//Assign objects to the broadphase
	CollisionBroadphaseVectors();

	//Show how many objects in each vector
	ShowBroadphaseObjects();

	CheckForCollision();

	CollisionResolution();

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Update(deltaTime);
	}

	CollisionDataCleanup();

	glutPostRedisplay();
}

//Function that draws the game engine
void GameEngine::DrawGame(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Position the objects for viewing.
	gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Draw();
	}

	glutSwapBuffers();
}

void GameEngine::CleanupEngine(void)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		delete objects[i];
	}
}

//Function to resize window
void GameEngine::ResizeWindow(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void GameEngine::InitEngine(int argc, char** argv, const char* windowTitle, int width, int height)
{
	glutInit(&argc, argv);

	glutInitContextVersion(2, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("HoverCrfaftGame");

	glewExperimental = GL_TRUE;
	glewInit();

	glutDisplayFunc(DrawGame);
	glutReshapeFunc(ResizeWindow);
	glutIdleFunc(UpdateGame);

	//Keyboard input
	glutKeyboardFunc([](unsigned char key, int x, int y)
		{
			GameObject::keys[key] = true;
			std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;
			//If we press escape, quit
			if (key == 27)
			{
				CleanupEngine(); //changed to include the GameEngine function - this function will have to be static!
				exit(0);
			}
		}
	);

	glutKeyboardUpFunc([](unsigned char key, int x, int y)
		{
			GameObject::keys[key] = false;
			//std::cout << "Key pressed: " << key << " : " << GameObject::keys[key] << std::endl;
		}
	);

	glutSpecialFunc([](int key, int x, int y)
		{

			GameObject::specialKeys[key] = true;
			//std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;
			//If we press escape, quit
			if (key == 4)
			{
				CleanupEngine();
				exit(0);
			}
		}
	);

	glutSpecialUpFunc([](int key, int x, int y)
		{
			GameObject::specialKeys[key] = false;
			//std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;
		}
	);
}

void GameEngine::AddGameObject(GameObject* object)
{
	objects.push_back(object);
}

void GameEngine::StartEngine(void)
{
	std::cout << "Press escape to exit the game." << std::endl;
	glutMainLoop();
}
