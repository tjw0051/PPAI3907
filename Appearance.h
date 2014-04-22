

#ifndef _APPEARANCE_H
#define _APPEARANCE_H

#include "dataTypes.h"

class Appearance
{
private:
	Point2D		shape[4];


public:
	void setShape2Square();
	void setShape2Hill();
	Point2D getShapeFromVert(int vert);
	int getWidth();
	int getHeight();
	



};

#endif