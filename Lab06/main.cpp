#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <gl/gl.h>
#include <gl/glut.h>

#endif

#define CHECKBOARD_WIDTH 64
#define CHECKBOARD_HEIGHT 64
#define CHECKBOARD_COLOR_NUM_CHANNELS 3

GLubyte checkImage[CHECKBOARD_HEIGHT][CHECKBOARD_WIDTH][CHECKBOARD_COLOR_NUM_CHANNELS];
GLuint texName;

void makeCheckImage(void);
void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1, 1);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutReshapeWindow(640, 480);

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

void makeCheckImage(void)
{
    int value;
    for (int row=0; row<CHECKBOARD_HEIGHT; row++) {
        for (int col=0; col<CHECKBOARD_WIDTH; col++) {
            value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
            for (int channel = 0; channel < CHECKBOARD_COLOR_NUM_CHANNELS; channel++) {
                checkImage[row][col][channel] = (GLubyte)value;
            }
        }
    }
}

void init(void)
{
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-3.5f, 3.5f, -3.5f, 3.5f);

    makeCheckImage();
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CHECKBOARD_WIDTH,
                 CHECKBOARD_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 checkImage);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName);

    glBegin(GL_QUADS);
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex2f(-3.0f, -1.0f);
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex2f(-1.0f, -1.0f);
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex2f(-1.0f, 1.0f);
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex2f(-3.0f, 1.0f);
	
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex2f(1.0f, -1.0f);
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex2f(3.0f, -1.0f);
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex2f(3.5f, 1.0f);
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex2f(1.5f, 1.0f);
    glEnd();

    glFlush();
    glDisable(GL_TEXTURE_2D);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}
