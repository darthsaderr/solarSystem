#include <iostream>
#include <sstream>
#include"polyline.h"
#include<string>

// seems that fonts are only defined in the freeglut.h header 
 #include <GL/freeglut.h>
#include "glglobal.h"

using namespace std;

/*
    possible fonts are listed in desText.h

    First, move cursor to lower left
    Then print the bitmap.
*/

void drawString(void* font,string s) {
    string::iterator i;
    for (i = s.begin(); i != s.end(); i++) {
	glutBitmapCharacter(font,*i);
    }
}

void drawText(point lleft, const string& message, void* font) {

    glRasterPos3f(lleft.x, lleft.y, lleft.z;
    drawString(font,message);
}

void drawText(point lleft, int value, void* font) {
    ostringstream ss;
    ss << value;
    //cout << "drawText int " << value << " (" << ss.str().c_str() << ")\n";
    drawText(lleft, ss.str().c_str(), font);
}

void drawText(point lleft, double value, void* font) {
    ostringstream ss;
    ss << value;
    drawText(lleft, ss.str().c_str(), font);
}

void drawPoint(point lleft, point p, void* font) {
    ostringstream ss;
    ss.setf(ios::showpoint);
    ss.precision(1);
    ss << "(" << p.x << "," << p.y << "," << p.z << ")";
    drawText(lleft, ss.str().c_str(), font);
}

