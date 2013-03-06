// Solar.cpp
// OpenGL SuperBible
// Demonstrates OpenGL nested coordinate transformations
// and perspective
// Program by Richard S. Wright Jr.

#include "shared/gltools.h"	// OpenGL toolkit
#include <math.h>


void TimerFunc(int value)
{
		glutPostRedisplay();
		glutTimerFunc(100, TimerFunc, 1);
}

void ChangeSize(int w, int h)
{
		GLfloat fAspect;

		// Prevent a divide by zero
		if(h == 0)
				h = 1;

		// Set Viewport to window dimensions
		glViewport(0, 0, w, h);

		// Calculate aspect ratio of the window
		fAspect = (GLfloat)w/(GLfloat)h;

		// Set the perspective coordinate system
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// field of view of 45 degrees, near and far planes 1.0 and 425
		gluPerspective(45.0f, fAspect, 1.0, 425.0);

		// Modelview matrix reset
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}

void RenderScene()
{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
}


int main(int argc, char* argv[])
{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(800, 600);
		glutCreateWindow("Window");
		glutReshapeFunc(ChangeSize);
		glutDisplayFunc(RenderScene);
        //glutTimerFunc(250, TimerFunc, 1);

		glutMainLoop();

		return 0;
}
