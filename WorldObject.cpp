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
