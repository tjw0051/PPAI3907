#include "WorldObject.h"

WorldObject::WorldObject()
{
	viewport.left = 10; 
	viewport.top = 10;
	viewport.right = 900;
	viewport.bottom = 700;
	particleModel.setPosition(300, 500);
	appearance.setShape2Hill();
}
WorldObject::WorldObject(int shape, int posX, int posY)
{
	viewport.left = 10;
	viewport.top = 10;
	viewport.right = 900;
	viewport.bottom = 700; 
	particleModel.setPosition(posX, posY);

	if(shape = 0)
		appearance.setShape2Hill();
}
bool WorldObject::checkLineIntersect(RECT object, Point2D line, double theta)
{
	//finds the height along the line at the length of the objects left side.
	double lineLeftPos = line.y + (tan(theta)*(line.x-object.left));
	//finds the height along the line at the length of the objects right side.
	double lineRightPos = line.y + (tan(theta)*(line.x-object.right));
	//check if all corners of RECT are RIGHT of line.
	if(lineLeftPos > object.top && lineLeftPos > object.bottom &&
		lineRightPos > object.top && lineRightPos > object.bottom)
	{
		return false;
	}
	//check if all corners of RECT are LEFT of line.
	if(lineLeftPos < object.top && lineLeftPos < object.bottom &&
		lineRightPos < object.top && lineRightPos < object.bottom)
	{
		return false;
	}
	//if not all corners are left or right, then RECT is overlapping with the line.
	else
		return true;
}
double WorldObject::getAngleAtPos(RECT object)
{
	dispBufUpdate();
	double angle = 0;
	Point2D line;
	if(object.right > dispBuffObj[3].x && object.right < dispBuffObj[0].x)
	{
		angle = atan( (appearance.getShapeFromVert(3).y - appearance.getShapeFromVert(0).y) 
			/ (appearance.getShapeFromVert(0).x - appearance.getShapeFromVert(3).x));
		line.x = dispBuffObj[0].x;
		line.y = dispBuffObj[0].y;
		if(checkLineIntersect(object, line, angle))
			return -angle;
		else
			return 0;
	}
	else if(object.right > dispBuffObj[0].x && object.right < dispBuffObj[1].x)
	{
		return 100;
	}
	else if(object.left > dispBuffObj[1].x && object.left < dispBuffObj[2].x)
	{
		angle = atan( (appearance.getShapeFromVert(2).y - appearance.getShapeFromVert(1).y) 
			/ (appearance.getShapeFromVert(2).x - appearance.getShapeFromVert(1).x));
		line.x = dispBuffObj[2].x;
		line.y = dispBuffObj[2].y;
			return angle;
	}
	else
		return 0;
}
int WorldObject::draw(GraphicsM * pGraphicsModule)
{
	dispBufUpdate();	// update content of display buffer (with outline of square at its current position)
	pGraphicsModule->drawPolygon(dispBuffObj, 4, true); // display content of buffer

	return 1;
}

int WorldObject::dispBufUpdate()
{
    // update display object (content of display buffer (with calculated vertex coordinates of square at its current position))
    for(int vert = 0; vert < 4; ++vert)
    {
      dispBuffObj[vert].x = appearance.getShapeFromVert(vert).x + particleModel.getPosition().x;
	  dispBuffObj[vert].y = appearance.getShapeFromVert(vert).y + particleModel.getPosition().y;
    }
    return 1;
}

RECT WorldObject::BoundingBox()
{
	RECT boundingBox;
	boundingBox.left = particleModel.getPosition().x;
	boundingBox.top = particleModel.getPosition().y;
	boundingBox.right = particleModel.getPosition().x + appearance.getWidth();
	boundingBox.bottom = particleModel.getPosition().y + appearance.getHeight();
	
	return boundingBox;
}
