#ifndef POLYLINE_H
#define POLYLINE_H

#include"glglobal.h"
#include"vips.h"
#include<vector>


class segment{
	friend class polyLine;
	public:
		segment();
		segment(int,int);
		void newpoint(point);
		void clear();
		void print();
		void sdraw();
	protected:
		std::vector<point> seg;
};

class polyLine{
	public:
		polyLine();
		polyLine(segment);
		void print();
		//void setcorners(double&,double&,double&,double&);
		void newseg(segment);
		void openfile(char*);
		void pdraw();
		void tween(polyLine,double);
		void P_scale(double,double);//Sx,Sy
		void P_rotate(double);//angle(degrees) always around Z axis
		void P_move(double,double);//tx,ty

	private:
		int linenum;
		//double xmin,xmax,ymin,ymax;
		std::vector<segment> picture;
};

#endif
