#ifndef VIPS_H
#define VIPS_H

#include<cmath>
#include<vector>

class point{
	public:
		point(double,double,double);
		point(double,double); //just x,y --> 2D point
		point();
		void print();
		void draw();
		bool operator==(const point);
		double operator*(const point);
		point operator*(const double);
		//point operator*(const doouble, const point);
		point operator%(const point);
		point operator-(const point);
		point operator-(const double);
		point operator+(const point);
		point operator+(const double);
		point operator/(const point);
		point operator/(const double);
		point squareR();
		double ab();//length
		point finddistance(point);
		point midpoint(point);
		double x;
		double y;
		double z;
};

/*class face{
	public:
		face();
		face(std::vector<point>);
		point normal();
		void addpoint(point);
	private:
		std::vector<point> fp;
};*/

class shape{ //list of points
	public:
		shape();
		shape(point);
		shape(double,double);
		point operator[](const int);
		void print();
		void newpoint(point);
		void clear();
		void draw();
		int size();
		void move(point);
		std::vector<point> getvect();
		point at(int);
		point lerp(point,point,double); //a,b,t
			//a+(b-a)*t
		//shape perp(point);
		point findcenter();
		shape tangentpoints();
	private:
		std::vector<point> ps;
};

#endif
