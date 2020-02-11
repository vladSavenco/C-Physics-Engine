#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#pragma comment(lib, "glew32.lib") 

// Drawing routine.
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Position the objects for viewing.
	gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(5, 0, 5);
	glVertex3f(-5, 0, 5);
	glVertex3f(-5, 0, -5);
	glVertex3f(5, 0, -5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.55, 0.27, 0.07);
	glRotatef(-45, 1, 0, 0);
	glutSolidCone(0.5, 0.75, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(-2, 0, 2);
	glTranslatef(-2, 0, 2);
	glRotatef(-90, 0, 1, 0);
	glutSolidCone(0.5, 0.75, 30, 30);
	glPushMatrix();
	glTranslatef(0, 0, -0.4);
	glColor3f(1, 1, 1);
	glutSolidCube(0.8);
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void idle()
{
	glutPostRedisplay();
}

// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(2, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Week 1 - Basic Scene");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutIdleFunc(idle);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
