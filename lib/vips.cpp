#include "glglobal.h"
#include <iostream>
#include "vips.h"
#include <cmath>

using namespace std;

///////////////////POINT CLASS IMPLEMENTATION////////////////////
point::point(){
	x=0;
	y=0;
	z=0;
}
point::point(double a,double b,double c){
	x=a;
	y=b;
	z=c;
}

point::point(double a,double b){
	x=a;
	y=b;
	z=0;
}

void point::print(){
	cout << "(" << x << "," << y << "," << z << ")\n";
}

void point::draw(){
	glBegin(GL_POINTS);
	glVertex2d(x,y);
	glEnd();
	glFlush();
	glutPostRedisplay();
}

bool point::operator==(const point a){
	point t=*this;
	if(t.x==a.x && t.y==a.y && t.z==a.z){
		return true;
	} else return false;
}

double point::operator*(const point a){ //dot product
	point t=*this;
	point f;
	f.x=t.x*a.x;
	f.y=t.y*a.y;
	return f.x+f.y;
}


point point::operator*(const double i){ //scalar
	point t=*this;
	point f;
	f.x=t.x*i;
	f.y=t.y*i;
	f.z=t.z*i;
	return f;
}

/*point point::operator*(const double i,const point t){
	point f;
	f.x=t.x*i;
	f.y=t.y*i;
	f.z=t.z*i;
	return f;

}*/

point point::operator%(const point i){
	point k=*this;
	if(k.z==0 || i.z==0){
		return(point(0,0,0));
	} 
	point a(1,0,0);
	point b(0,1,0);
	point c(0,0,1);

	point n=a*(k.y*i.z - k.z*i.y) - b*(k.z*b.x - k.x*i.z) + c*(k.x*i.y - k.y*i.x);
	return n;
}

point point::operator/(const point a){
	point t=*this;
	point f;
	f.x=t.x/a.x;
	f.y=t.y/a.y;
	if(a.z!=0){
		f.z=t.z/a.z;
	}
	return f;
}

point point::operator/(const double i){
	point t=*this;
	point f;
	f.x=t.x/i;
	f.y=t.y/i;
	if(i!=0){
		f.z=t.z/i;
	}
	return f;
}

point point::operator-(const point a){
	point t=*this;
	point f;
	f.x=t.x-a.x;
	f.y=t.y-a.y;
	f.z=t.z-a.z;
	return f;
}

point point::operator-(const double i){
	point t=*this;
	point f;
	f.x=t.x-i;
	f.y=t.y-i;
	f.z=t.z-i;
	return f;
}


point point::operator+(const point a){
	point t=*this;
	point f;
	f.x=t.x+a.x;
	f.y=t.y+a.y;
	f.z=t.z+a.z;
	return f;
}

point point::operator+(const double i){
	point t=*this;
	point f;
	f.x=t.x+i;
	f.y=t.y+i;
	f.z=t.z+i;
	return f;
}

point point::squareR(){
	point t=*this;
	t.x=sqrt(t.x);
	t.y=sqrt(t.y);
	t.z=sqrt(t.z);
	return t;

}

double point::ab(){
	point t=*this;
	double a,b,c,d;
	a=t.x*t.x;
	//b=t.y*t.y;
	c=t.z*t.z;
	d=a+c;
	d=sqrt(d);
	return d;
}


point point::finddistance(point a){
	return *this-a;
}

point point::midpoint(point a){
	point t=*this;
	point m= (t+a)*0.5;
	//m.print();
	return m;
}


//////////////////FACE CLASS/////////////////////////////////
/*face::face(){
	
}

face::face(vector<point> p){
	fp=p;
}

point face::normal(){
	if(fp.size()<3){
		cout << "Error: Face does not exist.\n";
		return(point(0,0,0));
	} 
	point a,b;
	a=fp.at(1)-fp.at(0);
	b=fp.at(2)-fp.at(1);
	return a%b;
}

void face::addpoint(point p){
	fp.push_back(p);
}*/

////////////////////////LINE CLASS IMPLEMENTATION////////////////
shape::shape(){
	ps.clear();
}

shape::shape(point a){
	ps.push_back(a);
}

shape::shape(double x,double y){
	ps.push_back(point(x,y));
}

point shape::operator[](const int i){
	return ps.at(i);
}

void shape::print(){
	vector<point>::iterator pi;
	for(pi=ps.begin();pi!=ps.end();pi++){
		pi->print();
	}
	cout << endl;
}

void shape::newpoint(point a){
		ps.push_back(a);
}

void shape::clear(){
	ps.clear();
}

void shape::move(point a){
	vector<point>::iterator pi;
	int i=0;
	for(pi=ps.begin();pi!=ps.end();pi++){
		ps.push_back(*pi+ps[i]);
	}
}

void shape::draw(){
	vector<point>::iterator pi;
	if(ps.size()>1){
		glBegin(GL_LINE_STRIP);
	} else {
		glBegin(GL_POINTS);
	}
	for(pi=ps.begin();pi!=ps.end();pi++){
		glVertex2d(pi->x,pi->y);
	}
	glEnd();
	glFlush();
	glutPostRedisplay();
}

vector<point> shape::getvect(){
	return ps;
}

point shape::lerp(point a,point b,double t){
	double m=a.x+(b.x-a.x)*t;
	double n=a.y+(b.y-a.y)*t;
	return (point(m,n));
}

int shape::size(){
	return ps.size();
}

point shape::at(int n){
	point i=this->at(n);
	i.print();
	return i;
}

point shape::findcenter(){
	point A=ps[0];
	//A.print();
	point B=ps[1];
	//B.print();
	point C=ps[2];
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

shape shape::tangentpoints(){
	shape t=*this;
	shape n;
	point s;
	point p,q,w;
	double La,Lb;
	point A=ps[0];
//	cout << "A=";
//	A.print();
	point B=ps[1];
//	cout << "B=";
//	B.print();
	point C=ps[2];
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
	La=(a.ab()+c.ab()-b.ab())/2;
	//La.print();
	Lb=(a.ab()+b.ab()-c.ab())/2;
	//Lb.print();
	p=A+(a/a.ab())*La;
	q=B+(b/b.ab())*Lb;
	w=A-(c/c.ab())*La;
	//cout << "p=";
	//p.print();
	//cout << "q=";
	//q.print();
	//cout << "w=";
	//w.print();
	n.newpoint(p);
	n.newpoint(q);
	n.newpoint(w);
	return n;
}
