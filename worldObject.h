#ifndef _WORLDOBJECT_H
#define _WORLDOBJECT_H

#include "dataTypes.h"
#include "ParticleModel.h"
#include "Appearance.h"
#include "input.h"
#include "graphics.h"

class WorldObject
{

private:
		ParticleModel particleModel;
		Appearance appearance;
		Point2D		dispBuffObj[4];
		RECT viewport;

public:
	WorldObject();
	WorldObject(int shape, int posX, int posY);
	//GameObject(RECT * viewport);
	int update(keyEvent kEvent);
	int draw(GraphicsM * pGraphicsModule);
	int dispBufUpdate();
	RECT BoundingBox();
	double getAngleAtPos(Point2D pos);
};
#endif