// #define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <gl/gl.h>
#include <gl/glut.h>

#endif

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct Point {
	float x;
	float y;
	float z;
};

Point P[10001];
float angleY = 0, angleX = 0, angleZ = 0, transX = 0, transY = 0, transZ = 0;
int p, n;
int first[10001], second[10001], third[10001];

ifstream fi ("face.dat");

void initBase() {
  	glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
  	glMatrixMode( GL_PROJECTION );
  	glLoadIdentity( );
  	glOrtho( -5.0, 5.0, -5.0, 5.0, -5.0, 5.0 );
	fi >> p;
	for (int i = 0; i < p; ++i){
		fi >> P[i].x >> P[i].y >> P[i].z;
	}
	fi >> n;
	for (int i = 0; i < n; ++ i) {
		fi >> first[i] >> second[i] >> third[i]; 
	}
}

void display() {
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);
	glRotatef(angleZ, 0.0, 0.0, 1.0);
	glTranslatef(transX, transY, transZ);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < n; ++i){
		glBegin(GL_LINE_LOOP);
			glVertex3f(P[first[i]].x, P[first[i]].y, P[first[i]].z);
			glVertex3f(P[second[i]].x, P[second[i]].y, P[second[i]].z);
			glVertex3f(P[third[i]].x, P[third[i]].y, P[third[i]].z);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-P[first[i]].x, P[first[i]].y, P[first[i]].z);
			glVertex3f(-P[second[i]].x, P[second[i]].y, P[second[i]].z);
			glVertex3f(-P[third[i]].x, P[third[i]].y, P[third[i]].z);
		glEnd();
	}	
	
	glFlush();
    glutSwapBuffers();	
}

void reshape(int w, int h) {
	cout << w << ' ' << h << endl;
	glViewport(0, 0, w, h);
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}

void handleKey(unsigned char key, int x, int y) {
	switch(key) {
		case 'q':
			angleY += 1;
			break;
		case 'e':
			angleY -= 1;
			break;
		case 'z':
			angleX += 1;
			break;
		case 'c':
			angleX -= 1;
			break;
		case 'v':
			angleZ += 1;
			break;
		case 'b':
			angleZ -= 1;
			break;
		case 'd':
			transX += 0.03;
			break;
		case 'a':
			transX -= 0.03;
			break;
		case 'w':
			transY += 0.03;
			break;
		case 's':
			transY -= 0.03;
			break;
		case 'r':
			transZ += 0.03;
			break;
		case 't':
			transZ -= 0.03;
			break;	
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutCreateWindow("NguyenVanHoang_16020231_Tuan08");
  
  initBase();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(handleKey);
  glutMainLoop();
}
