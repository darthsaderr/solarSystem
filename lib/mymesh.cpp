#include<iostream>
#include<vector>
#include "vips.h"
#include "mymesh.h"
using namespace std;

/////////////////////////FACE CLASS/////////////////////////////
face::face(){
	nump=0;
}

face::face(vector<point> a){
	points=a;
	nump=a.size();
}

void face::findnorm(){
	if(nump<3) {
		cout << "error: not a face. less than three sides.\n";
		return;
	}
	point a,b;
	a=points.at(1)-points.at(0);
	b=points.at(2)-points.at(1);
	norm=a%b;
}

void face::addpoint(point p){
	points.push_back(p);
	nump++;
}

void face::clear(){
	points.clear();
	norm=point(0,0,0);
	nump=0;
}

void face::draw(){
	vector<point>::iterator fip;
	//glBegin(GL_POLYGON);
	//glNormal3d(norm.x,norm.y,norm.z);

	for(fip=points.begin();fip!=points.end();fip++){
		//glBegin(GL_POLYGON);
		//glNormal3f(norm.x,norm.y,norm.z);
		glVertex3d(fip->x,fip->y,fip->z);
	}
}

point face::getnorm(){
	return norm;
}

void face::print(){
	vector<point>::iterator pv;
	for(pv=points.begin();pv!=points.end();pv++){
		pv->print();
	}
}
/////////////////////////MY MESH CLASS//////////////////////////
mymesh::mymesh(){

}

void mymesh::addface(face f){
	faces.push_back(f);
}

void mymesh::draw(){
	vector<face>::iterator fi;
	point n;
	if(faces.empty()) return;
	if(mode==MODE_SOLID){
		glBegin(GL_POLYGON);
	} else {
		glBegin(GL_LINE_LOOP);
	}
	for(fi=faces.begin();fi!=faces.end();fi++){
			n=fi->getnorm();
			glNormal3f(n.x,n.y,n.z);
			fi->draw();
	}
	glEnd();
}

void mymesh::print(){
	vector<face>::iterator fi;
	vector<point>::iterator vi;
	vector<point>::iterator ni;
	for(fi=faces.begin();fi!=faces.end();fi++){
		fi->print();
	}
}

void mymesh::setmodesolid(){
	mode=MODE_SOLID;
}

void mymesh::move(double tx,double ty,double tz){//tx,ty,tz
	glTranslated(tx,ty,tz);
}

void mymesh::scale(double sx,double sy,double sz){//Sx,Sy,Sz
	glScaled(sx,sy,sz);
}

void mymesh::rotate(double n,char a){
	if(a=='y'||a=='Y'){
		glRotated(n,0.0,1.0,0.0);
	} else if(a=='x'||a=='X'){
		glRotated(n,1.0,0.0,0.0);
	} else if(a=='z'||a=='Z'){
		glRotated(n,0.0,0.0,1.0);
	}
}
