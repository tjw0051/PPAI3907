#ifndef _PARTICLEMODEL_H
#define _PARTICLEMODEL_H

#include "dataTypes.h"
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

class ParticleModel
{
private:

	Point2D 	pos;
	Point2D displacement;
	Point2D velocity;
	Point2D acceleration;
	Point2D newAccel;

	int mass;
	double gravity;
	Point2D sForce; // sliding force
	Point2D netForce;

	int currentTime, previousTime;

public:
	/* Set / get attributes of game object */
		void setPosition(float xCoord, float yCoord);   // Set world position of game object
		Point2D getPosition();							// Get position of game object

		int moveRight();			// Move particle towards right
		int moveLeft();
		int moveUp();
		int moveDown();
		int brake();
		ParticleModel();
		Point2D getVel();
		void setVel(Point2D velocity);
		Point2D getAccel();
		void setAccel(Point2D acceleration);
		Point2D getDisplacement();
		void setDisplacement(Point2D newDisplacement);
		void moveConstDispl();
		void moveConstVel();
		void moveConstAccel();
		int updateNetForce();
		int updateAccel();
		int slidingMotion();
		int slidingForce(double theta, double frCoef);
		int updateState();
};

#endif