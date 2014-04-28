#include "Appearance.h"

void Appearance::setShape2Square()
{
    /* Load polygon (shape) data into vertex array */
    shape[0].x = 0.0F;	shape[0].y = 0.0F;
    shape[1].x = 20.0F;	shape[1].y = 0.0F;
    shape[2].x = 20.0F;	shape[2].y = 20.0F;
    shape[3].x = 0.0F;	shape[3].y = 20.0F;
}
void Appearance::setShape2Hill()
{
	// Create Trapezium shape.
	shape[0].x = 100.0F;	shape[0].y = 0.0F;
    shape[1].x = 200.0F;	shape[1].y = 0.0F;
    shape[2].x = 400.0F;	shape[2].y = 160.0F;
    shape[3].x = 0.0F;	shape[3].y = 160.0F;
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
