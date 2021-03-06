
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
		bool impulse;
		Point2D		dispBuffObj[4];
		RECT viewport;
		double slidingTheta, slidingfrCoef;
public:
	GameObject();
	//GameObject(RECT * viewport);
	int update(keyEvent kEvent);
	int update();
	int draw(GraphicsM * pGraphicsModule);
	RECT BoundingBox();
	RECT movingBoundingBox();
	void setSlidingForce(double theta, double frCoef);
	Point2D getPos();
	void isColliding(bool val);
	void collision();
	void fire(Point2D originPos);
	void release();
private:
	int dispBufUpdate();
	int worldCollisionCheck();
	Point2D convertToPoint2D(float angle, float magnitude);
};

#endif // !_GAMEOBJECT_H