#include "WorldObject.h"

WorldObject::WorldObject()
{
	viewport.left = 10; 
	viewport.top = 10;
	viewport.right = 900; //650
	viewport.bottom = 700; // 490
	particleModel.setPosition(300, 500);
	appearance.setShape2Hill();
}
WorldObject::WorldObject(int shape, int posX, int posY)
{
	//viewport = 0, 0, 650, 490; //10, 10, 650, 490
	viewport.left = 10;
	viewport.top = 10;
	viewport.right = 900; //650
	viewport.bottom = 700; // 490
	particleModel.setPosition(posX, posY);

	if(shape = 0)
		appearance.setShape2Hill();
}
double WorldObject::getAngleAtPos(Point2D pos)
{
	if(pos.x > dispBuffObj[3].x && pos.x < dispBuffObj[0].x)
		return (sqrt(pow(dispBuffObj[0].x - dispBuffObj[3].x, 2) + pow(dispBuffObj[0].y - dispBuffObj[3].y, 2)));
	if(pos.x > dispBuffObj[0].x && pos.x < dispBuffObj[1].x)
		return 0;
	if(pos.x > dispBuffObj[1].x && pos.x < dispBuffObj[2].x)
		return (sqrt(pow(dispBuffObj[2].x - dispBuffObj[1].x, 2) + pow(dispBuffObj[1].y - dispBuffObj[2].y, 2)));

}
int WorldObject::draw(GraphicsM * pGraphicsModule)
{
	dispBufUpdate();	// update content of display buffer (with outline of square at its current position)
	pGraphicsModule->drawPolygon(dispBuffObj, 4, true); // display content of buffer

	return 1;
}

int WorldObject::dispBufUpdate()
{
    /* TO DO: add relevant code */

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
