#include "GameEngine.h"

std::vector<GameObject*> GameEngine::objects;
int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;

void GameEngine::UpdateGame(void)
{
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	float deltaTime = (newTimeSinceStart - oldTimeSinceStart);
	deltaTime /= 1000.f;

	glm::vec3 red(1.0, 0.0, 0.0);

	for (int i = 0; i < objects.size()-1; i++)
		for (int j = i + 1; j < objects.size(); j++)
		{
			if (objects[i]->SpC->CollideCheck(*objects[j]->SpC))
			{
				//objects[i]->Draw(glColor3f(1.0, 0.0, 0.0));
			}
		}

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Update(deltaTime);
	}

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
