#ifndef SADIELIB_H
#define SADIELIB_H

#include"glglobal.h"
#include"vips.h"
#include"mymesh.h"
#include"sadielib.h"
#include<cmath>
#include<vector>


////HEADER FILE FOR MY PERSONAL GRAPHICS LIBRARY
class point;
void qexit(unsigned char,int,int);//exit window with press of q
void wait(int);
/////////////curves assignment/////////////////
void cardioid(int);
void rose(int,int);
void archimede(int);

////rosette class///////////////////
class rosette{
	public:
		rosette();
		rosette(int);
		rosette(int,double);//sides,radius
		void newSide();//adds a side
		void lessSide();//subtracts a side
		void setradius(double);
		void draw();
	private:
		int sides;
		double rad;
		std::vector<point> rose;
};
///////////////ARCHES////////////////////////
class arch{
	public:
		arch();
		arch(char);
		arch(char,int);
		arch(int);
		void setType(char);
		void setRadius(int);
		void build();
		void draw();
	private:
		std::vector<point> arc;
		char type;
		int rad;
};

////////////////////CIRCLE///////////////////
class circle{
	public:
		circle();
		circle(point,double);
		void print();
		void build();
		void draw();
		void setradius(double);
		void setradius(point);
		void setcenter(point);
		void clear();
		point getcenter();
	private:
		point center;
		double radius;
		std::vector<point> circ;
};

///////////////////HOUSE//////////////////////
class house{
	public:
		house();
		void build();
		void draw();
		void print();
		void H_scale(double,double);//Sx,Sy
		void H_rotate(double);//angle(degrees) always around Z axis
		void H_move(double,double);//tx,ty
	private:
		std::vector<point> outline;
		std::vector<point> shed;
		std::vector<point> door;
		std::vector<point> window;
		std::vector<point> shedwindow;
};
/////////////SNOWFLAKE///////////////////
class sf{
	public:
		sf();
		void build();
		void draw();
		void print();
		void xreflect();
		void yreflect();
		void swivel();
		//double extents(double*);
	private:
		std::vector<point> arm;
		std::vector<std::vector<point> > holes;
};

////////////////////////PRISM///////////////////////////////
class aster:public sf{
	public:
		aster();
		void build();
		void draw();
		void zreflect();
	private:
		std::vector<point> b;
		std::vector<point> norm;
		std::vector<face> faces;
};

#endif
