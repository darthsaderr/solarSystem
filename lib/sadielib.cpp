#include"glglobal.h"
#include<iostream>
#include<fstream>
#include<cmath>
#include<time.h>
#include<vector>
#include"polyline.h"
#include"sadielib.h"
#include "vips.h"
using namespace std;

//////////////////////EXIT KEYBOARD HANDLER/////////////////////////
void qexit(unsigned char key,int x,int y){
	if(key=='q'){
		exit(0);
	}
}

///////////////////////////DELAY FUNCTION FOR ANIMATION//////////
void wait(int milli){
	struct timespec req={0};
	req.tv_sec=0;
	req.tv_nsec=milli*1000000L;
	nanosleep(&req, (struct timespec*)NULL);
}

////////////////////CARDIOID////////////////////////////////
void cardioid(int a){
	segment heart;
	double x,y;
	int i;
	for(i=0;i<2*M_PI;i+=0.1){
		x=a*cos(i)*(1-cos(i));
		y=a*sin(i)*(1-cos(i));
		heart.newpoint(point(x,y));
		
	}
	heart.print();
	heart.sdraw();
}

//////////////////ROSE////////////////////////////////////
void rose(int a,int n){
	int i;
	if(!n%2){
		n=n*2;
	}
	segment rose;
	double x,y;
	for(i=0;i<2*M_PI;i+=0.1){
		x=cos(n*i)*(cos(i));
		y=cos(n*i)*(sin(i));
		rose.newpoint(point(x,y));
		//cout << "x=" << il->x << " y=" << il->y << endl;
	}
	rose.sdraw();
}

/////////////////ARCHIMEDIAN SPIRAL///////////////////////
void archimede(int a){
	segment spiral;
	double x,y;
	int i;
	for(i=0;i<2*M_PI;i+=0.1){
		x=a*i*cos(i);
		y=a*i*sin(i);
		spiral.newpoint(point(x,y));
	} 
	spiral.sdraw();
	//glFlush();
}

/////////////ROSETTE CLASS/////////////////////////
rosette::rosette(){
	sides=4;
	rad=1;
}

rosette::rosette(int s){
	sides=s;
	rad=1;
}

rosette::rosette(int s,double r){
	sides=s;
	rad=r;
}

void rosette::newSide(){
	sides+=1;
	this->draw();
	glutPostRedisplay();
}

void rosette::lessSide(){
	if(sides>4){
		sides-=1;
	}
	this->draw();
	glutPostRedisplay();
}

void rosette::setradius(double i){
	rad=i;
}
void rosette::draw(){
	glColor3f(0.8,0.4,0.6);
	double angle=2*M_PI/sides;
	double i,x,y;
	//cout << "building...\n";
	rose.clear();
	for(i=0;i<2*M_PI;i+=angle){
		x=cos(i);
		y=sin(i);
		//cout << "x=" << x << " y=" << y << endl;
		rose.push_back(point(x,y));
	}
	//cout << "drawing...\n";
	glClear(GL_COLOR_BUFFER_BIT);
	vector<point>::iterator vip,piv;
	glBegin(GL_LINES);
	for(vip=rose.begin();vip!=rose.end();vip++){
		for(piv=rose.begin();piv!=rose.end();piv++){
			//if(vip->x != piv->x && vip->y != piv->y){
			glVertex2d(vip->x,vip->y);
			glVertex2d(piv->x,piv->y);
			//cout << "Line from " << vip->x << "," << vip->y << " to " << piv->x << "," << piv->y << endl;
			//}
		}
	}
	glEnd();
	glFlush();
	//glutPostRedisplay();
}

//////////////////ARCH CLASS///////////////////
arch::arch(){
	type='r';
	rad=10;
}

arch::arch(char t){
	if(type=='r'||type=='p'||type=='o'){
		type=t;
	} else {
		cout << "invalid type.\n";
	}
	rad=10;
}

arch::arch(char t,int r){
	if(type=='r'||type=='p'||type=='o'){
		type=t;
	} else {
		cout << "invalid type.\n";
	}
	rad=r;
}

arch::arch(int r){
	type='r';
	rad=r;
}

void arch::setType(char t){
	if(type=='r'||type=='p'||type=='o'){
		type=t;
		build();
	} else {
		cout << "invalid type.\n";
	}
}

void arch::setRadius(int r){
	rad=r;
}

void arch::build(){
	double i,x,y,cx,cy;
	double frad;
	arc.clear();
	if(type=='r'){
///////////////////////ROUND ARCH////////////////////////////
		arc.push_back(point(cos(0)*rad,sin(0)*rad-rad));
		for(i=0;i<M_PI;i+=0.01){
			x=rad*cos(i);
			y=rad*sin(i);
			arc.push_back(point(x,y));
		}	
		arc.push_back(point(cos(M_PI)*rad,sin(M_PI)*rad-rad));
	} else if(type=='p'){
/////////////////////////POINTED ARCH///////////////////////////
		arc.push_back(point(cos(0)*rad/2,sin(0)*rad/2-rad));
		for(i=0;i<M_PI/3;i+=0.01){
			x=cos(i)*rad-(rad/2);
			y=sin(i)*rad;
			arc.push_back(point(x,y));
		} 
		for(i=M_PI*2/3;i<M_PI;i+=0.01){
			x=rad*cos(i)+(rad/2);
			y=rad*sin(i);
			arc.push_back(point(x,y));
		}
		arc.push_back(point(cos(M_PI)*rad/2,sin(M_PI)*rad/2-rad));
	} else if(type=='o'){
/////////////////////////OGEE ARCH///////////////////////////
		frad=rad/1.5;
		arc.push_back(point(cos(0)*rad,sin(0)*rad-rad));
		for(i=0;i<M_PI/3;i+=0.01){//right side
			x=rad*cos(i);
			y=rad*sin(i);
			arc.push_back(point(x,y));
		}
		cx=rad/1.49;
		cy=rad*1.51;
		for(i=M_PI*4/3;i>M_PI;i-=0.01){//top right
			x=frad*cos(i)+cx;
			y=frad*sin(i)+cy;
			arc.push_back(point(x,y));
		}
		x=cx;
		y=cy;
		arc.push_back(point(x,y));x=-cx;
		y=cy;
		arc.push_back(point(x,y));
		for(i=M_PI*2;i>M_PI*5/3;i-=0.01){//top left
			x=frad*cos(i)-cx;
			y=frad*sin(i)+cy;
			arc.push_back(point(x,y));
		}
		for(i=M_PI*2/3;i<M_PI;i+=0.01){//left side
			x=rad*cos(i);
			y=rad*sin(i);
			arc.push_back(point(x,y));
		}
		arc.push_back(point(cos(M_PI)*rad,sin(M_PI)*rad-rad));
	} else {
		cout << "cannot draw. invalid type\n";
		exit(0);
	}
}

void arch::draw(){
	vector<point>::iterator ipa;
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_POLYGON);
	//glBegin(GL_POINTS);
	//glBegin(GL_LINE_LOOP);
	//cout << "drawing...\n";
	for(ipa=arc.begin();ipa!=arc.end();ipa++){
		glVertex2d(ipa->x,ipa->y);
		//cout << "x=" << ipa->x << " y=" << ipa->y << endl;
	}
	glEnd();
	glFlush();
}

/////////////////////CIRCLE CLASS/////////////////////////////
circle::circle(){
	radius=1;
	circ.clear();
}

circle::circle(point c,double r){
	center=c;
	radius=r;
}

void circle::print(){
	vector<point>::iterator cp;
	for(cp=circ.begin();cp!=circ.end();cp++){
		cp->print();
	}
}

void circle::build(){
	double i,x,y;
	for(i=0;i<2*M_PI;i+=0.01){
		x=cos(i)*radius+center.x;
		y=sin(i)*radius+center.y;
		circ.push_back(point(x,y));
	}
}

void circle::draw(){
	vector<point>::iterator cc;
	glBegin(GL_POINTS);
	for(cc=circ.begin();cc!=circ.end();cc++){
		glVertex2d(cc->x,cc->y);
	}
	glEnd();
	glFlush();
	glutPostRedisplay();
}

void circle::setradius(double r){
	radius=r;
}

void circle::clear(){
	circ.clear();
	radius=0;
	center=point(0,0);
}

void circle::setradius(point a){
	double x,y,hyp;
	x=a.x;
	y=a.y;
	hyp=x*x+y*y;
	hyp=sqrt(hyp);
	//cout << "x=" << a.x << " y=" << a.y << " hypotenuse=" << hyp << endl;
	radius=hyp;
}

void circle::setcenter(point c){
	center=c;
}

point circle::getcenter(){
	return center;
}


//////////////////////HOUSE IMPLEMENTATION//////////////////////////
house::house(){

}

void house::build(){
	outline.push_back(point(0,0));
	outline.push_back(point(125,0));
	outline.push_back(point(125,125));
	outline.push_back(point(0,125));
	outline.push_back(point(67,175));
	outline.push_back(point(125,125));
	outline.push_back(point(0,125));

	shed.push_back(point(125,0));
	shed.push_back(point(200,0));
	shed.push_back(point(200,50));
	shed.push_back(point(125,50));
	shed.push_back(point(125,75));
	shed.push_back(point(200,50));
	shed.push_back(point(125,50));

	door.push_back(point(25,50));
	door.push_back(point(25,0));
	door.push_back(point(50,0));
	door.push_back(point(50,50));

	window.push_back(point(75,75));
	window.push_back(point(100,75));
	window.push_back(point(100,100));
	window.push_back(point(75,100));

	shedwindow.push_back(point(136,25));
	shedwindow.push_back(point(136,40));
	shedwindow.push_back(point(183,40));
	shedwindow.push_back(point(183,25));
}

void house::draw(){
	vector<point>::iterator hp;
	glBegin(GL_LINE_LOOP);
	for(hp=outline.begin();hp!=outline.end();hp++){
		glVertex2d(hp->x,hp->y);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for(hp=shed.begin();hp!=shed.end();hp++){
		glVertex2d(hp->x,hp->y);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for(hp=door.begin();hp!=door.end();hp++){
		glVertex2d(hp->x,hp->y);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for(hp=window.begin();hp!=window.end();hp++){
		glVertex2d(hp->x,hp->y);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for(hp=shedwindow.begin();hp!=shedwindow.end();hp++){
		glVertex2d(hp->x,hp->y);
	}
	glEnd();
	glFlush();
	glutPostRedisplay();
}

void house::print(){
	vector<point>::iterator hp;
	for(hp=outline.begin();hp!=outline.end();hp++){
		hp->print();
	} for(hp=shed.begin();hp!=shed.end();hp++){
		hp->print();
	} for(hp=door.begin();hp!=door.end();hp++){
		hp->print();
	} for(hp=window.begin();hp!=window.end();hp++){
		hp->print();
	} for(hp=shedwindow.begin();hp!=shedwindow.end();hp++){
		glVertex2d(hp->x,hp->y);
	}
}

void house::H_scale(double sx,double sy){
	glScaled(sx,sy,1);
}

void house::H_rotate(double angle){
	glRotated(angle,0,0,1);
}

void house::H_move(double tx,double ty){
	glTranslated(tx,ty,0);
}

///////////////////SNOWFLAKE/////////////////////////
sf::sf(){

}

void sf::build(){
	arm.push_back(point(0,25));
	arm.push_back(point(25,25));
	arm.push_back(point(100,75));
	arm.push_back(point(175,50));
	arm.push_back(point(150,100));
	arm.push_back(point(175,125));
	arm.push_back(point(225,100));
	arm.push_back(point(200,150));
	arm.push_back(point(275,125));
	arm.push_back(point(275,175));
	arm.push_back(point(300,125));
	arm.push_back(point(325,100));
	arm.push_back(point(325,75));
	arm.push_back(point(350,100));
	arm.push_back(point(325,150));
	arm.push_back(point(350,175));
	arm.push_back(point(400,125));
	arm.push_back(point(425,150));
	arm.push_back(point(450,175));
	arm.push_back(point(475,200));
	arm.push_back(point(525,150));
	arm.push_back(point(500,100));
	arm.push_back(point(525,100));
	arm.push_back(point(550,125));
	arm.push_back(point(550,150));
	arm.push_back(point(575,125));
	arm.push_back(point(575,100));
	arm.push_back(point(500,50));
	arm.push_back(point(550,25));
	arm.push_back(point(550,50));
	arm.push_back(point(575,25));
	arm.push_back(point(550,0));

	vector<point> a,b,c,d,e,f,g,h,i,j,k;
	//a
	a.push_back(point(50,25));
	a.push_back(point(75,50));
	a.push_back(point(100,25));
	holes.push_back(a);
	//b
	b.push_back(point(100,50));
	b.push_back(point(125,50));
	b.push_back(point(175,25));
	b.push_back(point(125,25));
	holes.push_back(b);
	//c
	c.push_back(point(225,25));
	c.push_back(point(175,75));
	c.push_back(point(200,100));
	c.push_back(point(250,75));
	holes.push_back(c);
	//d
	d.push_back(point(350,0));
	d.push_back(point(375,25));
	d.push_back(point(425,0));
	holes.push_back(d);
	//e
	e.push_back(point(250,75));
	e.push_back(point(275,75));
	e.push_back(point(350,25));
	holes.push_back(e);
	//f
	f.push_back(point(300,75));
	f.push_back(point(250,125));
	f.push_back(point(300,100));
	holes.push_back(f);
	//g
	g.push_back(point(350,50));
	g.push_back(point(375,100));
	g.push_back(point(350,150));
	g.push_back(point(400,100));
	g.push_back(point(400,50));
	holes.push_back(g);
	//h
	h.push_back(point(400,25));
	h.push_back(point(425,75));
	h.push_back(point(475,75));
	h.push_back(point(500,25));
	h.push_back(point(475,25));
	h.push_back(point(450,50));
	h.push_back(point(425,25));
	holes.push_back(h);
	//i
	i.push_back(point(425,100));
	i.push_back(point(450,150));
	i.push_back(point(475,175));
	i.push_back(point(500,150));
	i.push_back(point(475,100));
	holes.push_back(i);
	//j
	j.push_back(point(150,0));
	j.push_back(point(200,25));
	j.push_back(point(250,0));
	holes.push_back(j);
	//k
	k.push_back(point(475,0));
	k.push_back(point(525,25));
	k.push_back(point(525,0));
	holes.push_back(k);

}

/*double sf::extents(double* ext[4]){
	ext[4]={0,0,0,0}; //Xmin, Xmax, Ymin, Ymax
	vector<point>::iterator ep;
	for(ep=arm.begin();ep!=arm.end();ep++){
		if(ep->x < ext[0]){
			ext[0]=ep->x;
		} else if(ep->x > ext[1]){
			ext[1]=ep->x;
		} if(ep->y < ext[2]){
			ext[2]=ep->y;
		} else if(ep->y > ext[3]){
			ext[3]=ep->y;
		}
	}
	return ext;
}*/

void sf::draw(){
	vector<point>::iterator sp,ip;
	vector< vector<point> >::iterator hsp;
	glBegin(GL_LINE_STRIP); 
	for(sp=arm.begin();sp!=arm.end();sp++){
		glVertex2d(sp->x,sp->y);
	}
	glEnd();
	for(hsp=holes.begin();hsp!=holes.end();hsp++){
		glBegin(GL_LINE_LOOP);
		for(ip=hsp->begin();ip!=hsp->end();ip++){
			glVertex2d(ip->x,ip->y);	
		}
		glEnd();
	}
	glFlush();
	glutPostRedisplay();
}

void sf::print(){
	vector<point>::iterator psf;
	for(psf=arm.begin();psf!=arm.end();psf++){
		psf->print();
	}
}

void sf::xreflect(){
	glScaled(1,-1,0);
}

void sf::yreflect(){
	glScaled(-1,1,0);
}

void sf::swivel(){
	glRotated(60,0,0,1);
}
//////////////////////////PRISM CLASS///////////////////////////
aster::aster(){

}

void aster::build(){
	b.push_back(point(0,0,10));
	b.push_back(point(2,0,10));
	b.push_back(point(2,0,2));
	b.push_back(point(5,0,7));
	b.push_back(point(7,0,5));
	b.push_back(point(5,0,5));
	b.push_back(point(10,0,2));
	b.push_back(point(10,0,0));
}

void aster::zreflect(){
	glScaled(1,0,-1);
}

void aster::draw(){
	vector<point>::iterator pv;
	glBegin(GL_LINE_STRIP); 
	for(pv=b.begin();pv!=b.end();pv++){
		glVertex2d(pv->x,pv->y);
	}
	glEnd();
	glFlush();
	glutPostRedisplay();
}

