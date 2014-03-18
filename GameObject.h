
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "dataTypes.h"
#include "ParticleModel.h"
#include "Appearance.h"
#include "input.h"
#include "graphics.h"


class GameObject
{

private:
		ParticleModel particleModel;
		Appearance appearance;
		Point2D newPos;

		Point2D		dispBuffObj[4];
		RECT viewport;

public:
	GameObject();
	//GameObject(RECT * viewport);
	int update(keyEvent kEvent);
	int draw(GraphicsM * pGraphicsModule);
	RECT BoundingBox();

private:
	int dispBufUpdate();
	int worldCollisionCheck();
	Point2D convertToPoint2D(float angle, float magnitude);
};

#endif // !_GAMEOBJECT_H