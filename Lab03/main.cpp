// #define GL_SILENCE_DEPRECATION

/* -- INCLUDE FILES ------------------------------------------------------ */
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <gl/gl.h>
#include <gl/glut.h>

#endif

/* 	
	Theory:
		P = (1-t)*A + t*B => P is the point calculated at time t while mapping from A to B
		P (0 <= t <= 1), t = 0 => that's A, t = 1 => that's B
*/

// screen constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;

struct Point {
	float x, y;
	Point(float x_, float y_) : x(x_), y(y_) {
	}
	Point() : x(0.f), y(0.f) {
	}
};

Point *startPoints, *endPoints;
float deltaT = 0.0002;
float currentT = 0.0;
int numberOfPoints;

void initBase(void) {
  	glClearColor(1.0, 1.0, 1.0, 0.0); // white background	
  	glLoadIdentity();
  	glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, -1.0, 1.0); // left, right, bottom, top, near, and far values in the arguments
}

// initialize points and undertake point mapping
void initPoints(){
	numberOfPoints = 9; // as well as the number of vertex pairs
	
	startPoints = new Point[numberOfPoints];
	endPoints = new Point[numberOfPoints];
	
	startPoints[0] = Point(100.f, 100.f);
	startPoints[1] = Point(100.f, 400.f);
	startPoints[2] = Point(150.f, 430.f);
	startPoints[3] = Point(200.f, 460.f);
	startPoints[4] = Point(250.f, 490.f);
	startPoints[5] = Point(300.f, 460.f);
	startPoints[6] = Point(350.f, 430.f);
	startPoints[7] = Point(400.f, 400.f);
	startPoints[8] = Point(400.f, 100.f);
		
	endPoints[0] = Point(700.f, 200.f);
	endPoints[1] = Point(700.f, 300.f);
	endPoints[2] = Point(800.f, 300.f);
	endPoints[3] = Point(830.f, 400.f);
	endPoints[4] = Point(900.f, 400.f);
	endPoints[5] = Point(970.f, 400.f);
	endPoints[6] = Point(1000.f, 300.f);
	endPoints[7] = Point(1100.f, 300.f);
	endPoints[8] = Point(1100.f, 200.f);
}

// lerp function
float lerp(float A, float B, float t){
	return (1-t)*A + t*B;
}

// tweening, use GL_LINE_LOOP to connect every single point in turn (1->2->3->...)
void drawTweening(Point *start, Point *end, int n, float t){
	glBegin(GL_LINE_LOOP);
	for (int i=0; i<n; i++){
		glColor3f(0.0, 0.3, 0.4);
		// calculate x, y at time t
		float x = lerp(start[i].x, end[i].x, t);
		float y = lerp(start[i].y, end[i].y, t);
		glVertex2f(x, y);
	}
	glEnd();
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	drawTweening(startPoints, endPoints, numberOfPoints, currentT);
	currentT += deltaT;
	if (currentT >= 1.0 || currentT <= 0.0) deltaT = -deltaT;
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

/* ----------------------------------------------------------------------- */

int main(int argc, char *argv[]) {
  	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	glutInitWindowSize(1, 1);
  	glutInitWindowPosition(100, 100);
  	
  	glutCreateWindow ("NguyenVanHoang_16020231_Tuan03");
  	glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
  	
  	initBase();
  	initPoints();
  	
  	glutDisplayFunc( display );
  	glutMainLoop( );
  	return 0;
}

/* ----------------------------------------------------------------------- */
