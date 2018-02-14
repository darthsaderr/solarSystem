#include "final.h"
#include "glglobal.h"
#include <cmath>
#include <string>
#include <vector>
using namespace std;

//////////////////////////PLANET CLASS//////////////////////////

Planet::Planet(){
	hasrings=false;
}

Planet::Planet(string s){
	name=s;
	hasrings=false;
}

Planet::Planet(int s,double r,double os,string n){
	slices=s;
	stacks=s;
	radius=r;
	name=n;
	orbspeed=os;
	hasrings=false;
	color[0]=color[1]=color[2]=0.9f;
}

void Planet::setsize(int sl,int st,double r){
	slices=sl;
	stacks=st;
	radius=r;
}

void Planet::setrings(int r){
	hasrings=true;
	ring=r;
}

double Planet::velocity(){
	return orbspeed;
}

double Planet::transx(double i){
	return dist*cos(i)*orbspeed;
}

double Planet::transz(double i){
	return dist*sin(i)*orbspeed;
}

void Planet::setdist(double d){
	dist=d;
}

void Planet::setcolor(GLfloat a, GLfloat b, GLfloat c){
	color[0]=a;
	color[1]=b;
	color[2]=c;
}

void Planet::setringcolor(GLfloat a, GLfloat b, GLfloat c){
	ringcolor[0]=a;
	ringcolor[1]=b;
	ringcolor[2]=c;
}

void Planet::setmat(string m,GLfloat n1,GLfloat n2,GLfloat n3,GLfloat n4){
	matval[0]=n1;
	matval[1]=n2;
	matval[2]=n3;
	matval[3]=n4;
	material=m;
}

void Planet::draw(double aa){
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	if(material=="GL_EMISSION"){
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,matval);
	} if(material=="GL_SPECULAR"){
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,matval);
	} if(material=="GL_DIFFUSE"){
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,matval);
	}
	glColor3fv(color);
	if(name=="Saturn" || name=="Jupiter"){
		glRotated(15,1,0,0);
	}
	glTranslated(dist*cos(aa*orbspeed),50,dist*sin(aa*orbspeed));
	glutSolidSphere(radius,stacks,slices);

	if(hasrings){
		double d=radius*1.2,k=d/80;
		int i;
		glColor3fv(ringcolor);
		glPushMatrix();
		if(name!="Uranus"){
			glRotated(60,1,0,0);
		}
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		//glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,ringcolor);
		glutSolidTorus(k,d+k,15,15);
		if(ring>1){
			for(i=0;i<ring;i++){
				glutSolidTorus(k,d+k,10,25);
				d+=k;
			}
		}
		//glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,ringcolor);
		glPopAttrib();
		glPopMatrix();
		glPopMatrix();
	}

	glPopAttrib();

}

void Planet::print(){
	cout << "Name: " << name << endl;
	cout << "Stacks: " << stacks << endl;
	cout << "Slices: " << slices << endl;
	cout << "Radius: " << radius << endl;
	cout << "Distance from sun: " << dist << endl;
	cout << "Material: " << material << endl << endl;
}

//////////////////////////SYSTEM CLASS//////////////////////////

System::System(){
	position[0]=0;
	position[1]=0;
	position[2]=0;
	animation=false;
}

System::System(Planet x){
	centerstar=x;
	position[0]=0;
	position[1]=0;
	position[2]=0;
	animation=false;
}

System::System(double a[4]){
	for(int i=0;i<4;i++){
		position[i]=a[i];
	}
}

void System::addCenterStar(Planet a){
	centerstar=a;
	centerstar.setdist(0);
	centerstar.orbspeed=0;
}

void System::setpos(GLfloat a,GLfloat b,GLfloat c){
	position[0]=a;
	position[1]=b;
	position[2]=c;
}

Planet System::operator[](const int n){
	return planets.at(n);
}

double System::centerrad(){
	return centerstar.radius;
}

void System::makesun(){
	GLfloat pos[3];
	for(int i=0;i<3;i++){
		pos[i]=position[i];
	}
	GLfloat color[3]={1.0,1.0,1.0};
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	/*glLightfv(GL_LIGHT0,GL_AMBIENT,centerstar.color);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,centerstar.color);
  glLightfv(GL_LIGHT0,GL_POSITION,position);

	pos[0]+=centerstar.radius;
	glLightfv(GL_LIGHT1,GL_AMBIENT,centerstar.color);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,centerstar.color);
  glLightfv(GL_LIGHT1,GL_POSITION,pos);
	pos[0]-=centerstar.radius;*/

	/*pos[2]+=centerstar.radius;
	glLightfv(GL_LIGHT2,GL_AMBIENT,centerstar.color);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,centerstar.color);
  glLightfv(GL_LIGHT2,GL_POSITION,pos);
	pos[2]-=centerstar.radius;*/

	pos[0]-=centerstar.radius;
	glLightfv(GL_LIGHT3,GL_AMBIENT,centerstar.color);
	glLightfv(GL_LIGHT3,GL_DIFFUSE,centerstar.color);
  glLightfv(GL_LIGHT3,GL_POSITION,pos);
	pos[0]+=centerstar.radius;

	pos[2]-=centerstar.radius;
	glLightfv(GL_LIGHT4,GL_AMBIENT,centerstar.color);
	glLightfv(GL_LIGHT4,GL_DIFFUSE,centerstar.color);
  glLightfv(GL_LIGHT4,GL_POSITION,pos);
	pos[2]+=centerstar.radius;

}

void System::draw(){
	vector<Planet>::iterator piv;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(piv=planets.begin();piv!=planets.end();piv++){
		glPushMatrix();
		piv->draw(1);
		glPopMatrix();
	}
}

bool System::moving(){
	return animation;
}

void System::startorb(){
	animation=true;
}

int System::numplanets(){
	return planets.size();
}

void System::print(){
	vector<Planet>::iterator piv;
	for(piv=planets.begin();piv!=planets.end();piv++){
		piv->print();
	}
}

void System::addplanet(Planet p){
	planets.push_back(p);
}

void System::animate(double a){
	vector<Planet>::iterator piv;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	double aa=a*M_PI/180;
	centerstar.draw(0);
	for(piv=planets.begin();piv!=planets.end();piv++){
		glPushMatrix();
		piv->draw(aa);
		glPopMatrix();
	}
	glPopMatrix();
}
