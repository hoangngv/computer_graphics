// #define GL_SILENCE_DEPRECATION

/* -- INCLUDE FILES ------------------------------------------------------ */
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <gl/gl.h>
#include <gl/glut.h>

#endif

// screen constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

static GLfloat angle = 0.0;
bool rotate = false;

void myInit( void ) {
  	glClearColor( 1.0, 1.0, 1.0, 0.0 ); // white background
  	glLoadIdentity( );
  	glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 ); // left, right, bottom, top, near, and far values in the arguments
}

// render 
void drawPolygon()  {	
    glClear( GL_COLOR_BUFFER_BIT ); // clear color buffer
	glMatrixMode( GL_MODELVIEW ); // reset modelview matrix
	glLoadIdentity();
	
	glRotatef(angle, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    	glColor3f( 0.0, 1.0, 0.0 );
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
    glEnd();
    
    glFlush( );
    glutSwapBuffers(); // swap the front/back buffer to update the screen
    
    if (rotate){
    	angle -= 0.1;
	}
}

void idle(){
	glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // GLUT_UP or GLUT_DOWN => the callback was due to a release or press respectively
    	rotate = !rotate;
   	}
}

/* ----------------------------------------------------------------------- */

int main( int argc, char *argv[] )  {
  	// Initialize GLUT.
  	glutInit( &argc, argv );
  	// Set the mode to draw in.
  	glutInitDisplayMode( GLUT_DOUBLE );
  	// Set the window size in screen pixels.
  	glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
  	// Set the window position in screen pixels.
  	glutInitWindowPosition( 100, 100 );
  	// Create the window.
  	glutCreateWindow ( "NguyenVanHoang_16020231_Tuan2" );
  	// Set rendering function
  	glutDisplayFunc( drawPolygon );
  	// Initialize some things.
  	glutMouseFunc(handleMouse);
  	glutIdleFunc(idle);
  	myInit( );
  	// Start GLUT main loop
  	glutMainLoop( );
  	return 0;
}

/* ----------------------------------------------------------------------- */
