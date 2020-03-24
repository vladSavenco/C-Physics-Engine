#include "GameEngine.h"
using namespace std;

std::vector<GameObject*> GameEngine::objects;
std::vector<ColisionData*> GameEngine::objData;
int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;

void GameEngine::UpdateGame(void)
{
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	float deltaTime = (newTimeSinceStart - oldTimeSinceStart);
	deltaTime /= 1000.f;

	glm::vec3 red(1.0, 0.0, 0.0);

	//Check for collision 
	for (int i = 0; i < objects.size() - 1; i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			else
			{
				ColisionData* colData = nullptr;
				colData = new ColisionData;

				if (objects[i]->SpC.CollideCheck(objects[j]->SpC, *colData))
				{
					/*cout << "Depth:"<<colData->depth<<",normal("<<colData->normal.x<<","<<colData->normal.y<<","<<colData->normal.z<<"), point("
						<<colData->point.x << "," << colData->point.y << "," << colData->point.z<<")           " << '\r';*/

					colData->obj1 = objects[i];
					colData->obj2 = objects[j];
					objData.push_back(colData);
					
					objects[i]->SpC.collision = true;
					objects[j]->SpC.collision = true;
				}
				else
				{
					//cout << "Not Collided" << '\r';
					objects[i]->SpC.collision = false;
					objects[j]->SpC.collision = false;
				}

				if (objects[i]->BoC.CollideCheck(objects[j]->BoC, *colData))
				{
					/*cout << "Depth:"<<colData->depth<<",normal("<<colData->normal.x<<","<<colData->normal.y<<","<<colData->normal.z<<"), point("
						<<colData->point.x << "," << colData->point.y << "," << colData->point.z<<")           " << '\r';*/

					colData->obj1 = objects[i];
					colData->obj2 = objects[j];
					objData.push_back(colData);

					objects[i]->BoC.collision = true;
					objects[j]->BoC.collision = true;
				}
				else
				{
					//cout << "Not Collided" << '\r';
					objects[i]->BoC.collision = false;
					objects[j]->BoC.collision = false;
				}

			}
		}
	}

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

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Update(deltaTime);
	}

	for (int i = objData.size() - 1; i >= 0 ; --i)
	{
		delete objData[i];
	}
	objData.clear();

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
