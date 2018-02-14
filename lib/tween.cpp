#include"polyline.h"
#include"tween.h"
#include"sadielib.h"
#include <cmath>
#include<iostream>

using namespace std;

/////////////////SHAPE2 CLASS IMPLEMENTATION//////////////
shape2::shape2(){
	s.clear();
}

shape2::shape2(point a){
	s.push_back(a);
}

shape2::shape2(double x,double y){
	s.push_back(point(x,y));
}

void shape2::print(){
	vector<point>::iterator pi;
	for(pi=s.begin();pi!=s.end();pi++){
		pi->print();
	}
	cout << endl;
}


void shape2::newpoint(point a){
	s.push_back(a);
}

void shape2::newpoint(double x,double y){
	s.push_back(point(x,y));
}

void shape2::clear(){
	s.clear();
}

void shape2::draw(){
	vector<point>::iterator pi;
	if(s.size()>1){
		glBegin(GL_LINE_LOOP);
	} else {
		glBegin(GL_POINTS);
	}
	for(pi=s.begin();pi!=s.end();pi++){
		glVertex2d(pi->x,pi->y);
	}
	glEnd();
	glFlush();
	glutPostRedisplay();

}

point shape2::lerp(point a,point b,double t){
	double m=a.x+(b.x-a.x)*t;
	double n=a.y+(b.y-a.y)*t;
	//cout << "lerping\n";
	return (point(m,n));
}

int shape2::size(){
	return s.size();
}

/*point shape2::at(int n){
	return this->at(n);
}*/

point shape2::operator[](const int i){
	return s[i];
}

point shape2::findcenter(){
	point A=s[0];
	//A.print();
	point B=s[1];
	//B.print();
	point C=s[2];
	//C.print();
	point a=B-A;
	//a.print();
	point b=C-B;
	//b.print();
	point c=A-C;
	//c.print();
	point aperp(-a.y,a.x);
	//aperp.print();
	point center;
	center=A+(a+(aperp*(b*c)/(aperp*c)))/2;
	//center.print();
	return center;
}

shape2 shape2::tangentpoints(){
	shape2 t=*this;
	shape2 n;
	point s;
	point p,q,w;
	double La,Lb;
	point A=t[0];
//	cout << "A=";
//	A.print();
	point B=t[1];
//	cout << "B=";
//	B.print();
	point C=t[2];
//	cout << "C=";
//	C.print();
	point a=B-A;
//	cout << "a=";
//	a.print();
//	a.ab().print();
	point b=C-B;
//	cout << "b=";
//	b.print();
	point c=A-C;
//	cout << "c=";
//	c.print();
	La=(a.ab()+c.ab()-b.ab())/2.0;
	//La.print();
	Lb=(a.ab()+b.ab()-c.ab())/2.0;
	//Lb.print();
	p=A+(a/a.ab())*La;
	q=B+(b/b.ab())*Lb;
	w=A-(c/c.ab())*La;
	cout << "p=";
	p.print();
	cout << "q=";
	q.print();
	cout << "w=";
	w.print();
	n.newpoint(p);
	n.newpoint(q);
	n.newpoint(w);
	return n;
}
