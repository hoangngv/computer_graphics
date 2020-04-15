// #define GL_SILENCE_DEPRECATION

/* -- INCLUDE FILES ------------------------------------------------------ */
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <gl/gl.h>
#include <gl/glut.h>

#endif

#include <math.h>

/*
	Level 0: draw a triangle
	Level 1: draw a triangle but at each edge, draw a 60 degree angle to create a shape like a star
	Level 2: draw an equilateral triangle on each middle part
	Level 3: complete Koch Snowflake using recursion
*/

// screen constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const GLint KOCH_DEPTH = 3;
const GLfloat PI = 3.14159;

GLfloat x = 0.0f;
GLfloat y = 0.0f;

void initBase(void) {
  	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
  	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0f);
	glMatrixMode(GL_PROJECTION);	
  	glLoadIdentity();
  	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); // left, right, bottom, top, near, and far values in the arguments
}

void drawSnowFlake(GLint degree, GLfloat length, GLint kochDepth) {
	GLfloat rad = PI*degree/180.0;
	GLfloat x_new = x + length*cos(rad);
	GLfloat y_new = y + length*sin(rad);
	
	if (kochDepth == 0) {
		glVertex2f(x, y);
		glVertex2f(x_new, y_new);
		x = x_new;
		y = y_new;
	} else {
		kochDepth--;
		length /= 3;
		drawSnowFlake(degree, length, kochDepth);
		degree += 60;
		drawSnowFlake(degree, length, kochDepth);
		degree -= 120;
		drawSnowFlake(degree, length, kochDepth);
		degree += 60;
		drawSnowFlake(degree, length, kochDepth);
	}
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	
	GLint depth = KOCH_DEPTH;
	
	glBegin(GL_LINES);
		x = -0.5f;
		y = 0.0f;
		drawSnowFlake(0, 1.0, depth);
		
		x = 0.0f;
		y = -sqrt(3.0)/2.0;
		drawSnowFlake(120, 1.0, depth);
		
		x = 0.5f;
		y = 0.0f;
		drawSnowFlake(-120, 1.0, depth);
	glEnd();
	
	glFlush();
	glutSwapBuffers();
	//glutPostRedisplay();
}

/* ----------------------------------------------------------------------- */

int main(int argc, char *argv[]) {
  	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(1, 1);
  	glutInitWindowPosition(100, 100);
  	
  	glutCreateWindow ("NguyenVanHoang_16020231_Tuan04");
  	glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
  	
  	initBase();
  	glutDisplayFunc(display);
  	glutMainLoop();
  	return 0;
}

/* ----------------------------------------------------------------------- */
