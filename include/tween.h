#ifndef TWEEN_H
#define TWEEN_H

#include"glglobal.h"
#include"vips.h"
#include<cmath>

class shape2{ //list of points
	public:
		shape2();
		shape2(point);
		shape2(double,double);
		point operator[](const int);
		void print();
		void newpoint(point);
		void newpoint(double,double);
		void clear();
		void draw();
		int size();
	//	point at(int);
		point lerp(point,point,double); //a,b,t
			//a+(b-a)*t
		//shape2 perp(point);
		point findcenter();
		shape2 tangentpoints();
		
	private:
		std::vector<point> s;
};

#endif
