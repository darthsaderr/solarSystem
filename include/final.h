#ifndef FINAL_H
#define FINAL_H

#include "glglobal.h"
#include <cmath>
#include <string>
#include <iostream>
#include "vips.h"
#include "sadielib.h"

class Planet{
	friend class System;
	public:
		Planet();
		Planet(std::string);
		Planet(int,double,double,std::string);//slices/stacks,radius,orbspeed
		void setsize(int,int,double);
		double velocity();
		void setdist(double);
		void setrings(int);
		void setcolor(GLfloat,GLfloat,GLfloat);
		void setringcolor(GLfloat,GLfloat,GLfloat);
		double transx(double);
		double transz(double);
		void setmat(std::string,GLfloat,GLfloat,GLfloat,GLfloat);
		void draw(double);
		void print();
	protected:
		//basic
		int stacks;
		int slices;
		std::string name;
		double radius;
		double dist;//distance from sun
		double orbspeed; //orbit velocity
		//color & material
		std::string material;
		GLfloat matval[4];
		GLfloat color[3];
		GLfloat ringcolor[3];
		//rings
		bool hasrings;
		int ring;//width of ring
};

class System{
	public:
		System();
		System(Planet);
		System(double[]);//position,color
		Planet operator[](const int);
		void addplanet(Planet);
		void setpos(GLfloat,GLfloat,GLfloat);//position of central star
		bool moving();
		void startorb();
		void addCenterStar(Planet);
		double centerrad();
		int numplanets();
		void makesun();
		void draw();
		void print();
		void animate(double);
	private:
		std::vector<Planet> planets;
		GLfloat position[3];
		Planet centerstar;
		bool animation;
};
#endif
