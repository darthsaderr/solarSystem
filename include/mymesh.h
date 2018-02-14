#ifndef MYMESH_H
#define MYMESH_H
#include<vector>
#include<string>
#include "glglobal.h"
#include "vips.h"

class face{
	public:
		face();
		face(std::vector<point>);
		void addpoint(point);
		void draw();
		void findnorm();
		point getnorm();
		void print();
		void clear();
	private:
		std::vector<point> points;
		point norm;
		int nump;
};

enum render {MODE_WIRE, MODE_SOLID, MODE_WIRE_SOLID};
class mymesh{
	public:
		mymesh();
		void addface(face);
		void setmodesolid();
		void draw();
		void print();
		void move(double,double,double);//tx,ty,tz
		void scale(double,double,double);//Sx,Sy,Sz
		void rotate(double,char);
	private:
		std::vector<face> faces;
		render mode;
};
#endif
