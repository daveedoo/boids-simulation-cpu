#include <stdio.h>
#include <time.h>
#include <GL/freeglut.h>
#include "Shoal.h"

void keyboard(unsigned char key, int x, int y);
void display();
void reshape(int w, int h);
void timer(int);


int N = 1000;
Shoal shoal = Shoal(N);

const int text_len = 68;
char text[text_len];
void set_text()
{
	snprintf(text, text_len, "BOIDS [qa]Separation: %4.2f, [ws]Alignment: %4.2f, [ed]Cohesion: %4.2f", shoal.separation_lvl, shoal.alignment_lvl, shoal.cohesion_lvl);
	glutSetWindowTitle(text);
}

void glut_initialize(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(1000, 700);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Boids");
	set_text();

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);

	//glClearColor(0.05f, 0.6f, 0.73f, 1.f);

	//glShadeModel(GL_SMOOTH);
	//glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
	glut_initialize(&argc, argv);
	glutMainLoop();

	return EXIT_SUCCESS;
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		shoal.separation_lvl += 0.01f;
		set_text();
		break;
	case 'a':
		shoal.separation_lvl -= 0.01f;
		set_text();
		break;
	case 'w':
		shoal.alignment_lvl += 0.01f;
		set_text();
		break;
	case 's':
		shoal.alignment_lvl -= 0.01f;
		set_text();
		break;
	case 'e':
		shoal.cohesion_lvl += 0.01f;
		set_text();
		break;
	case 'd':
		shoal.cohesion_lvl -= 0.01f;
		set_text();
		break;
	default:
		break;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
		shoal.Draw();
	glEnd();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-MAX_XY, MAX_XY, -MAX_XY, MAX_XY);
	//gluPerspective(60, 1, 2.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	shoal.Move();

	glutPostRedisplay();
	glutTimerFunc(100 / 60, timer, 0);	// TODO: zmieniæ 100 na 1000
}