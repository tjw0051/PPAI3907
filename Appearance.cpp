#include "Appearance.h"

void Appearance::setShape2Square()
    {
    /* Load polygon (shape) data into vertex array */
    shape[0].x = 0.0F;	shape[0].y = 0.0F;
    shape[1].x = 10.0F;	shape[1].y = 0.0F;
    shape[2].x = 10.0F;	shape[2].y = 10.0F;
    shape[3].x = 0.0F;	shape[3].y = 10.0F;
    }

Point2D Appearance::getShapeFromVert(int vert)
{
	return shape[vert];
}
int Appearance::getWidth()
{
	return shape[2].x;
}
int Appearance::getHeight()
{
	return shape[2].y;
}