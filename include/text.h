#ifndef TEXT_H
#define TEXT_H

/* 
    This is an interface to writing text into glut windows.  It uses the
    freglut_std.h definitions.   The following fonts are supported. 
    Presumably, somewhere in the guts of some library, somebody has made
    these into bitmaps.

    2013 Update:  These work with glutBitmapCharacter, since the non-free
    version of glut doesn't have the glutBitmapString function.

    David Schulz

    GLUT_STROKE_ROMAN
    GLUT_STROKE_MONO_ROMAN
    GLUT_BITMAP_9_BY_15
    GLUT_BITMAP_8_BY_13
    GLUT_BITMAP_TIMES_ROMAN_10
    GLUT_BITMAP_TIMES_ROMAN_24
    GLUT_BITMAP_HELVETICA_10
    GLUT_BITMAP_HELVETICA_12
    GLUT_BITMAP_HELVETICA_18

*/

#include <string>
#include "polyline.h"
#include "glglobal.h"

extern void drawString(void*,std::string);

// first arg is lower left corner, then message, then optional font
extern void
drawText(point,const std::string&,void* font=GLUT_BITMAP_HELVETICA_10);

extern void 
drawText(point lleft,int value,void* font=GLUT_BITMAP_HELVETICA_10);

extern void 
drawText(point lleft,double value,void* font=GLUT_BITMAP_HELVETICA_10);

extern void 
drawText(point, point, void* font=GLUT_BITMAP_HELVETICA_10);


#endif
