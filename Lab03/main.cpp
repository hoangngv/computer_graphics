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
	P = (1-t)*A + t*B => P is one of the points when tweening from A to B
	t = 0 => just A, t = 1 => just B
	P (0 <= t <= 1)	
*/

// screen constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct Point {
	float x, y;
	Point(float x_, float y_) : x(x_), y(y_) {
	}
	Point() : x(0.f), y(0.f) {
	}
};

Point *startPoints, *endPoints;
float deltaT = 0.0005;
float currentT = 0.0;
int numberOfPoints;


void initBase(void) {
  	glClearColor(0.0, 0.0, 0.0, 0.0); // white background
  	//glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, -1.0, 1.0); // left, right, bottom, top, near, and far values in the arguments
}

// initialize 
void initPoints(){
	// as well as the number of vertex pairs
	numberOfPoints = 3;
	
	startPoints = new Point[numberOfPoints];
	endPoints = new Point[numberOfPoints];
	
	startPoints[0] = Point(100.f, 100.f);
	startPoints[1] = Point(200.f, 300.f);
	startPoints[2] = Point(100.f, 500.f);
	
	endPoints[0] = Point(700.f, 500.f);
	endPoints[1] = Point(600.f, 300.f);
	endPoints[2] = Point(700.f, 100.f);
}

// lerp function
float lerp(float A, float B, float t){
	return (1-t)*A + t*B;
}

// tweening, use GL_LINE_LOOP to connect every single point in turn together (1->2->3->...)
void drawTweening(Point *start, Point *end, int n, float t){
	glBegin(GL_LINE_LOOP);
	for (int i=0; i<n; i++){
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

int main( int argc, char *argv[] )  {
  	// Initialize GLUT.
  	glutInit(&argc, argv);
  	// Set the mode to draw in.
  	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  	// Set the window size in screen pixels.
  	glutInitWindowSize(1, 1);
  	// Set the window position in screen pixels.
  	glutInitWindowPosition(100, 100);
  	// Create the window.
  	glutCreateWindow ("NguyenVanHoang_16020231_Tuan3");
  	glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
  	
  	initBase();
  	initPoints();
  	// Set rendering function
  	glutDisplayFunc( display );
  	glutMainLoop( );
  	return 0;
}

/* ----------------------------------------------------------------------- */
