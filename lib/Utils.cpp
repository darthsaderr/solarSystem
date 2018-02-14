#if defined(WIN32)
#include <windows.h>
#endif

#if defined(__APPLE__)
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <fstream>
#include <ctime>
#include "Utils.h"

using namespace std;

void setWorldWin(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left,right,bottom,top);
}

void setViewPort(GLint left,GLint right,GLint bottom,GLint top){
    glViewport(left,bottom,right-left,top-bottom);
}

// this is a wrapper to nanosleep which sleeps for a certain
// number of milliseconds
void delay(int ms) {
    struct timespec ts;
    ts.tv_sec = ms/1000;
    ts.tv_nsec = 1000000 * (ms%1000);
    nanosleep(&ts,NULL);
}
