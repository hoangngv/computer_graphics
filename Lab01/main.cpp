// #define GL_SILENCE_DEPRECATION

/* -- INCLUDE FILES ------------------------------------------------------ */
// For Windows
#include <gl/gl.h>
#include <gl/glut.h>

// screen constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 60;

void myInit( void ) {
  glClearColor( 1.0, 1.0, 1.0, 0.0 ); // white background
  //glColor3f( 0.00, 0.28, 0.73 );
  //glPointSize( 3.0 );
  glMatrixMode( GL_PROJECTION ); // initialize Projection Matrix
  glLoadIdentity( );
  glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 ); // left, right, bottom, top, near, and far values in the arguments
}

// render 
void drawPolygon( void )  {	
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear color buffer
 		glMatrixMode( GL_MODELVIEW ); // reset modelview matrix
 		glLoadIdentity();
 		
        glBegin(GL_POLYGON);
        	glColor3f( 0.f, 1.f, 0.f );
            glVertex2f(50.0f, 50.0f);
            glVertex2f(250.0f, 50.0f);
            glVertex2f(250.0f, 150.0f);
            glVertex2f(50.0f, 150.0f);
        glEnd();
        
        glBegin(GL_POLYGON);
        	glColor3f( 1.f, 0.f, 0.f );
            glVertex2f(350.0f, 50.0f);
            glVertex2f(400.0f, 50.0f);
            glVertex2f(450.0f, 100.0f);
            glVertex2f(375.0f, 150.0f);
            glVertex2f(300.0f, 100.0f);
        glEnd();
        
        glBegin(GL_POLYGON);
        	glColor3f( 1.f, 1.f, 0.f );
            glVertex2f(550.0f, 50.0f);
            glVertex2f(600.0f, 50.0f);
            glVertex2f(650.0f, 100.0f);
            glVertex2f(600.0f, 150.0f);
            glVertex2f(550.0f, 150.0f);
            glVertex2f(500.0f, 100.0f);
        glEnd();
        
		glFlush( );
  	    glutSwapBuffers( ); // swap the front/back buffer to update the screen
}

/* ----------------------------------------------------------------------- */

int main( int argc, char *argv[] )  {
  // Initialize GLUT.
  glutInit( &argc, argv );
  // Set the mode to draw in.
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
  // Set the window size in screen pixels.
  glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
  // Set the window position in screen pixels.
  glutInitWindowPosition( 100, 150 );
  // Create the window.
  glutCreateWindow ( "NguyenVanHoang_16020231_Tuan1" );
  // Set the callback funcion to call when we need to draw something.
  
  myInit( );
  // Set rendering function
  glutDisplayFunc( drawPolygon );
  // Initialize some things.
  
  // Start GLUT main loop
  glutMainLoop( );
}

/* ----------------------------------------------------------------------- */
