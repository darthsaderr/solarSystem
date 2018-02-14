#include "glglobal.h"
#include "sadielib.h"
#include <stdlib.h>
#include <vector>
#include "vips.h"
#include "final.h"
#define USE_MATH_DEFINES
#include <cmath>
using namespace std;

const int screen=800;
double angle=0;
double FPS=60;
System solar;

///////////////////////TIMER FUNCTION//////////////////////
void timer(int v) {
  if (solar.moving()) {
    angle += 1.0;
		solar.animate(angle);
    /*if (angle >= 360) {
      angle = 0;
    }*/
    glutPostRedisplay();
  }
	wait(v);
  glutTimerFunc(1000/FPS, timer, v);
}

string material="GL_DIFFUSE";
//////////////////////BUILD SOLAR SYSTEM//////////////////////
void buildsystem(){
	Planet thesun(100,2500,0,"Sun");
		thesun.setcolor(0.7f,0.5f,0.1f);
		//thesun.setmat("GL_EMISSION",0.7f,0.5f,0.1f,0.0f);
		thesun.setmat(material,1.0f,1.0f,1.0f,0.0f);
		solar.addCenterStar(thesun);

	Planet mercury(15,115,29.4,"Mercury");
		mercury.setmat(material,0.9f,0.9f,0.9f,1.0f);
		mercury.setdist(solar.centerrad()+195);
		mercury.setcolor(0.9f,0.3f,0.3f);
	Planet venus(20,135,21.8,"Venus");
		venus.setmat(material,0.8f,0.8f,0.8f,1.0f);
		venus.setdist(solar.centerrad()+820);
		venus.setcolor(0.3f,0.4f,0.8f);
	Planet earth(25,140.0,18.5,"Earth");
		earth.setmat(material,0.8f,0.8f,0.8f,1.0f);
		earth.setdist(solar.centerrad()+1730);
		earth.setcolor(0.2f,0.2f,0.9f);
	Planet mars(20,125,15.0,"Mars");
		mars.setmat(material,0.8f,0.8f,0.8f,1.0f);
		mars.setdist(solar.centerrad()+2420);
		mars.setcolor(1.0f,0.1f,0.1f);
	Planet jupiter(40,930.0,8.1,"Jupiter");
		jupiter.setmat(material,0.9f,0.9f,0.9f,1.0f);
		jupiter.setdist(solar.centerrad()+4500);
		jupiter.setrings(3);
		jupiter.setcolor(0.8f,0.6f,0.3f);
		jupiter.setringcolor(1.0f,1.0f,1.0f);
	Planet saturn(35,760,6.0,"Saturn");
		saturn.setmat(material,0.9f,0.9f,0.9f,1.0f);
		saturn.setdist(solar.centerrad()+9100);
		saturn.setrings(50);
		saturn.setcolor(0.8f,0.4f,0.2f);
		saturn.setringcolor(0.9f,0.9f,1.0f);
	Planet uranus(25,260,4.2,"Uranus");
		uranus.setmat(material,0.8f,0.8f,0.8f,1.0f);
		uranus.setdist(solar.centerrad()+11730);
		uranus.setrings(1);
		uranus.setcolor(0.3f,0.6f,0.8f);
		uranus.setringcolor(1.0f,1.0f,1.0f);
	Planet neptune(25,250,3.4,"Neptune");
		neptune.setmat(material,0.8f,0.8f,0.8f,1.0f);
		neptune.setdist(solar.centerrad()+12530);
		neptune.setrings(3);
		neptune.setcolor(0.1f,0.1f,1.0f);
		neptune.setringcolor(1.0f,1.0f,1.0f);
	Planet pluto(10,112,2.9,"Pluto");
		pluto.setmat(material,0.8f,0.8f,0.8f,1.0f);
		pluto.setdist(13930);
		pluto.setcolor(0.2f,0.4f,0.4f);
	solar.addplanet(mercury);
	solar.addplanet(venus);
	solar.addplanet(earth);
	solar.addplanet(mars);
	solar.addplanet(jupiter);
	solar.addplanet(saturn);
	solar.addplanet(uranus);
	solar.addplanet(neptune);
	solar.addplanet(pluto);
}

double size=20000;

////////////////////////INIT///////////////////////////////
void myInit(){
	glClearColor(0.01,0.01,0.01,0.0);
	//glColor3f(0.6f,0.3f,0.5f);
	//glColor3f(1.0,1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-size,size*2,-size,size,-size*3,size*3);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	buildsystem();
	solar.makesun();
	//solar.print();
	solar.startorb();
}

//////////////////////DISPLAY FUNCTION/////////////////////////
int eye[3]={1,8000,1};
int look[3]={0,0,0};
int up[3]={0,1,0};

void displayTheThing(void) {
	gluLookAt(eye[0],eye[1],eye[2],look[0],look[1],look[2],up[0],up[1],up[2]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	solar.animate(angle);
	glPopMatrix();
	glutSwapBuffers();
}

///////////////////////KEYBOARD////////////////////////////////
void kb(unsigned char key,int x, int y){
	if(key=='q'||'\033'){
		exit(0);
	}
	if(key=='a'||key=='A'){
		solar.startorb();
		glutPostRedisplay();
	}
}

///////////////////////////MAIN////////////////////////////////
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen,screen);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Officially Official Final Project");
	glutKeyboardFunc(qexit);
	glutTimerFunc(100,timer,150);
	glutDisplayFunc(displayTheThing);
	//glViewport(0, 0, size,size);
	myInit();
	glutFullScreen();
	glutMainLoop();
  return 0;
}
