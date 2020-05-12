#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <gl/gl.h>
#include <gl/glut.h>

#endif

#include <iostream>

using namespace std;

struct Point {
	float x, y;
	Point(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Point() {
	
	};
};

Point lines[2][12];

void init(void)
{
 	glClearColor (0.0, 0.0, 0.0, 0.0);
 	glShadeModel (GL_FLAT);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glColor3f(0.0, 1.0, 1.0);
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	
	lines[0][0] = Point(0.5, 0.3);
    lines[0][1] = Point(0.57, 0.35);
    lines[0][2] = Point(0.58, 0.45);
    lines[0][3] = Point(0.65, 0.4);
    lines[0][4] = Point(0.7, 0.3);
    lines[0][5] = Point(0.58, 0.45);
    lines[0][6] = Point(0.58, 0.65);
    lines[0][7] = Point(0.53, 0.45);
    lines[0][8] = Point(0.54, 0.55);
    lines[0][9] = Point(0.58, 0.6);
    lines[0][10] = Point(0.62, 0.55);
    lines[0][11] = Point(0.7, 0.5);

	lines[1][0] = Point(0.585, 0.3);
    lines[1][1] = Point(0.618, 0.38);
    lines[1][2] = Point(0.58, 0.45);
    lines[1][3] = Point(0.62, 0.385);
    lines[1][4] = Point(0.59, 0.3);
    lines[1][5] = Point(0.58, 0.45);
    lines[1][6] = Point(0.59, 0.65);
    lines[1][7] = Point(0.61, 0.47);
    lines[1][8] = Point(0.578, 0.55);
    lines[1][9] = Point(0.589, 0.6);
    lines[1][10] = Point(0.578, 0.55);
    lines[1][11] = Point(0.615, 0.47);
}

float time = 0;
int u = 0;

void lerp (Point* start, Point* end, float time)
{ 
	glBegin(GL_LINE_STRIP);
	float x, y;
	for (int i = 0; i < 5; i++) {
		x = start[i].x * (1 - time) + end[i].x * time;
		y = start[i].y * (1 - time) + end[i].y * time;
		glVertex2f(x, y);
	}
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	for (int i = 5; i < 7; i++) {
		x = start[i].x * (1 - time) + end[i].x * time;
		y = start[i].y * (1 - time) + end[i].y * time;
		glVertex2f(x, y);
	}
	glEnd();
	
	glBegin(GL_LINE_STRIP);
	for (int i = 7; i < 12; i++) {
		x = start[i].x * (1 - time) + end[i].x * time;
		y = start[i].y * (1 - time) + end[i].y * time;
		glVertex2f(x, y);
	}
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	time += 0.02;
	if (time > 1) {
		time -= 1;
		u = 1 - u;
	}
	lerp(lines[u], lines[1 - u], time);
	glutSwapBuffers();
}

void spinDisplay(void)
{
	glutPostRedisplay(); 
}


int main(int argc, char** argv)
{
 	glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
 	glutInitWindowSize(1024, 768);
 	glutInitWindowPosition(150, 150);
 	glutCreateWindow("NguyenVanHoang_16020231_Tuan07");
 	init();
 	glutDisplayFunc(display);
 	glutIdleFunc(spinDisplay); 
 	glutMainLoop();
 	return 0;
}



