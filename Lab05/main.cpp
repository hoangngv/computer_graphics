#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <gl/gl.h>
#include <gl/glut.h>

#endif

#include <fstream>

// screen constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void initBase(void) {
  	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
  	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);	
  	glLoadIdentity();
  	gluOrtho2D(0.0, 1024.0, 0.0, 768.0);
}

void drawDinosaur(const char * fileName) {

	std::ifstream inFile;
	inFile.open(fileName);	// read the data file

	if(inFile.fail()) return;
	glClear(GL_COLOR_BUFFER_BIT);    

	GLint numOfPolyLines, numOfPoints;
	GLfloat x ,y;
	inFile >> numOfPolyLines;		        
	
	// traverse and draw each poly line
	for (int iPoly = 0; iPoly < numOfPolyLines; iPoly++) {
		inFile >> numOfPoints;
		glBegin(GL_LINE_STRIP);	    
		for (int i = 0; i < numOfPoints; i++) {
			inFile >> x >> y;        
			glVertex2f(x, y);
		}
		glFlush();
		glEnd();
	}
	glFlush();
	inFile.close();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawDinosaur("dinosaur.dat");
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1, 1);
	glutInitWindowPosition(150, 150);
	
	glutCreateWindow("NguyenVanHoang_16020231_Tuan05");
  	glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
  	
	initBase();
  	glutDisplayFunc(display);
  	glutMainLoop();
	return(0);
}
