#include "ParticleModel.h"


ParticleModel::ParticleModel()
{
	velocity.x = 0;
	velocity.y = 0;
	displacement.x = 0;
	displacement.y = 0;
	acceleration.x = 0.0;
	acceleration.y = 0.0;
	netForce.x = 0;
	netForce.y = 0;
	moveForce.x = 0;
	moveForce.y = 0;
	drag.x = 0;
	drag.y = 0;
	mass = 1;
	gravity = 1;
	verticalGravity = gravity;
	dragFactor = 1.0;
	slideAngle = 0;
	srand(time(0));
	previousTime = GetTickCount();
}
void ParticleModel::moveConstDispl()
{
	pos.x = pos.x + displacement.x;
	pos.y = pos.y + displacement.y;
}
void ParticleModel::moveConstVel()
{
	currentTime = GetTickCount();
	pos.x = pos.x +  velocity.x * (currentTime - previousTime)/10;
	pos.y = pos.y +  velocity.y * (currentTime - previousTime)/10;
	previousTime = currentTime;
}
void ParticleModel::moveConstAccel()
{
	lastPos.x = pos.x; 
	lastPos.y = pos.y;

	currentTime = GetTickCount();

	pos.x += velocity.x * ((currentTime - previousTime)/10) + 0.5f * 
		acceleration.x * ((currentTime - previousTime)/10) * ((currentTime - previousTime)/10);
	pos.y += velocity.y * ((currentTime - previousTime)/10) + 0.5f * 
		acceleration.y * ((currentTime - previousTime)/10) * ((currentTime - previousTime)/10);

	velocity.x += acceleration.x * ((currentTime - previousTime)/10);
	velocity.y += acceleration.y * ((currentTime - previousTime)/10);
	
	previousTime = currentTime;
}
int ParticleModel::updateAccel()
{
	acceleration.x = netForce.x/mass;
	acceleration.y = netForce.y/mass;
	return 1;
}
int ParticleModel::updateNetForce()
{
	netForce.x = (sForce.x + moveForce.x) ;						//+ drag.x;
	netForce.y = (sForce.y + moveForce.y) + verticalGravity ;	//+ drag.y;
	return 1;
}
int ParticleModel::updateDragForce()
{
	drag.x = -dragFactor * velocity.x;
	drag.y = -dragFactor * velocity.y;
	return 1;
}
void ParticleModel::setLastPos()
{
	pos.x = lastPos.x;
	pos.y = lastPos.y;
}
int ParticleModel::updateState()
{
	updateDragForce();
	updateNetForce();
	updateAccel();
	moveConstAccel();
	return 1;
}
int ParticleModel::slidingMotion()
{
	//slidingForce(2.0, 1);
	updateState();
	moveConstAccel();
	return 1;
}
//theta = angle of plane, frCoef = coefficient of friction.
int ParticleModel::slidingForce(double theta, double frCoef) 
{
	if(theta != 0 && frCoef != 0)
		verticalGravity = 0; //if on a slope, stop using general vertical gravity.
	else
		verticalGravity = gravity;
	if(theta != 100)
	{
		int forceMag;
		slideAngle = theta;
		if(theta <= 0) //change fall direction depending on slope angle.
			forceMag = mass * gravity * (sin(theta) - frCoef * cos(theta));
		else
			forceMag = mass * gravity * (sin(theta) - -frCoef * cos(theta));
		sForce.x = forceMag * cos(theta);
		sForce.y = forceMag * sin(theta);
		return 1;
	}
	else //if theta is 100, stop gravity for collision with horizontal surfaces.
		verticalGravity = 0;
}

Point2D ParticleModel::getVel()
{
	return velocity;
}
void ParticleModel::setVel(Point2D velocity)
{
	this->velocity = velocity;
}
Point2D ParticleModel::getAccel()
{
	return acceleration;
}
void ParticleModel::setAccel(Point2D acceleration)
{
	this->acceleration = acceleration;
}
Point2D ParticleModel::getDisplacement()
{
	return displacement;
}
void ParticleModel::setDisplacement(Point2D newDisplacement)
{
	displacement = newDisplacement;
}
void ParticleModel::setPosition(float xPos, float yPos)
{
    //position of particle
	pos.x = xPos;
	pos.y = yPos;
}
Point2D ParticleModel::getPosition()
{
	return pos;
}
void ParticleModel::randomProjectile(Point2D originPos)
{
	pos.x = originPos.x;
	pos.y = originPos.y;
	double force = rand() % 10 + 1;
	double angle = rand() / (RAND_MAX/M_PI);
	moveForce.x = -directionalVelocity(force, angle).x;
	moveForce.y = -directionalVelocity(force, angle).y;
}
int ParticleModel::moveRight()
{
	if(slideAngle < 0 && slideAngle > -(0.5*M_PI))
	{
		moveForce.x = directionalVelocity(2.0, slideAngle).x;
		moveForce.y = directionalVelocity(2.0, slideAngle).y;
	}
	else
		moveForce.x = directionalVelocity(2.0, slideAngle).x;
		moveForce.y = directionalVelocity(2.0, slideAngle).y;

return 1;
}
int ParticleModel::moveLeft()
{
	if(slideAngle > 0 && slideAngle < (0.5*M_PI))
	{
		moveForce.x = -directionalVelocity(2.0, slideAngle).x;
		moveForce.y = -directionalVelocity(2.0, slideAngle).y;
	}
	else 
	{
		moveForce.x = -directionalVelocity(2.0, slideAngle).x;
		moveForce.y = -directionalVelocity(2.0, slideAngle).y;
	}
return 1;
}
int ParticleModel::moveUp()
{
	double force = 15;
	double xTarget = 500;
	double yTarget = 500;
	double d = 750 - pos.x;
	//double v = force / mass;
	double v = (force / mass);// * ((currentTime - previousTime)/10);
	double g = gravity; //* ((currentTime - previousTime)/10);
	double angle = 0.5*(asin( (-1*500) / (pow((double)15, (int)2)) ));
	//double angleInRads = (angle*M_PI)/180;
	double angle2 = atan(	(pow(v, 2) + sqrt(pow(v, 4) - g*(g*pow(xTarget, 2) + 2*yTarget*pow(v, 2))) )	
					/	(g*xTarget) );
	moveForce.x = -directionalVelocity(force, angle).x;
	moveForce.y = -directionalVelocity(force, angle).y;

	return 1;
}

int ParticleModel::moveDown()
{
// update world position of object.
	moveForce.y = -5.0;

return 1;
}
int ParticleModel::moveNull()
{
	//player released controls - thrust cut off.
	moveForce.x = 0.0;
	moveForce.y = 0.0;
	return 1;
}
int ParticleModel::brake()
{
	acceleration.x = 0.0;
	acceleration.y = 0;
	velocity.x *= 0.98;
	velocity.y *= 0.98;
	moveForce.x = 0.0;
	moveForce.y = 0.0;
	return 1;
}
//takes a direction and velocity and gives the resulting x and y magnitude.
Point2D ParticleModel::directionalVelocity(double velocity, double angle)
{
	double angleInRads = angle;
	Point2D resultantVelocity;
	resultantVelocity.x = velocity * cos(angleInRads);
	resultantVelocity.y = velocity * sin(angleInRads);
	return resultantVelocity;
}