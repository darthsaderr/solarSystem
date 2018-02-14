#include "glglobal.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "vips.h"
#include "polyline.h"
using namespace std;

//////////////////////////////POLYLINE CLASS IMPLEMENTATION////////////
polyLine::polyLine(){
	linenum=0;
	picture.clear();
}

polyLine::polyLine(segment a){
	linenum=1;
	picture.push_back(a);
}

void polyLine::print(){
	int a;
	for(a=0;a<linenum;a++){
		picture[a].print();
		cout << endl;
	}
}

/*void polyLine::setcorners(double& L,double& R,double& B,double& T){
	L=xmin;
	R=xmax;
	B=ymin;
	T=ymax;
}*/
void polyLine::newseg(segment a){
	picture.push_back(a);
}

void polyLine::openfile(char* filename){
	ifstream fin;
	fin.open(filename);
	//cout << filename << endl;
	if(fin.fail()){
		cout << "file failure\n";
		return;
	}
	int i,j;
	double points,x,y,lines;
	segment S;
	fin >> linenum;
	for(i=0;i<linenum;i++){
		fin >> points;
		for(j=0;j<points;j++){
			fin >> x >> y;
			point r(x,y);
			S.newpoint(r);
		} 
		this->newseg(S);
		S.clear();
	}
	fin.close();
}

void polyLine::pdraw(){
	vector<point>::iterator spi;
	for(int k=0;k<linenum;k++){
		picture[k].sdraw();
	}
}

void polyLine::P_scale(double sx,double sy){
	glScaled(sx,sy,1);
}

void polyLine::P_rotate(double angle){
	glRotated(angle,0,0,1);
}

void polyLine::P_move(double tx,double ty){
	glTranslated(tx,ty,0);
}

////////////////////////SEGMENT CLASS IMPLEMENTATION/////////////////
segment::segment(){}

segment::segment(int x,int y){
	seg.push_back(point(x,y));
}

void segment::newpoint(point a){
	seg.push_back(a);
}

void segment::sdraw(){
	vector<point>::iterator si;
	glBegin(GL_LINE_STRIP);
	for(si=seg.begin();si!=seg.end();si++){
		glVertex2d(si->x,si->y);
	}
	glEnd();
	glFlush();
}


void segment::clear(){
	seg.clear();
}
void segment::print(){
	vector<point>::iterator vpi;
	for(vpi=seg.begin();vpi!=seg.end();vpi++){
		vpi->print();
	}
}












