#include "ParticleModel.h"


/*
 * Sets position of particle.
 *
 * Parameter list
 *        xPos		x-coordinate of position.
 *        yPos		y-coordinate of position.
 */
ParticleModel::ParticleModel()
{
	//displacement.x = rand() % -2 + 2;
	//displacement.y = rand() % -2 + 2;
	//velocity.x = rand() % -2 + 2;
	//velocity.y = rand() % -2 + 2;
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
	dragFactor = 1.0;
	/*
	displacement.x = rand() % 1 + 3;
	displacement.y = rand() % 1 + 3; */
	previousTime = GetTickCount();
}
void ParticleModel::moveConstDispl()
{
	pos.x = pos.x + displacement.x;
	pos.y = pos.y + displacement.y;
}
void ParticleModel::moveConstVel()
{
	// update world position of object by adding displacement (i.e.  velocity x time step) to  previous position
	currentTime = GetTickCount();
	pos.x = pos.x +  velocity.x * (currentTime - previousTime)/10;
	pos.y = pos.y +  velocity.y * (currentTime - previousTime)/10;
	previousTime = currentTime;
}
void ParticleModel::moveConstAccel()
{
	currentTime = GetTickCount();

	pos.x += velocity.x * ((currentTime - previousTime)/10) + 0.5f * acceleration.x * ((currentTime - previousTime)/10) * ((currentTime - previousTime)/10);
	pos.y += velocity.y * ((currentTime - previousTime)/10) + 0.5f * acceleration.y * ((currentTime - previousTime)/10) * ((currentTime - previousTime)/10);

	velocity.x += acceleration.x * ((currentTime - previousTime)/10);
	velocity.y += acceleration.y * ((currentTime - previousTime)/10);
	
	previousTime = currentTime;
}
int ParticleModel::updateNetForce()
{
	// sliding force
	netForce.x = (sForce.x + moveForce.x) + drag.x;
	netForce.y = (sForce.y + moveForce.y) + drag.y + gravity;
	return 1;
}
int ParticleModel::updateDragForce()
{
	drag.x = -dragFactor * velocity.x;
	drag.y = -dragFactor * velocity.y;
	return 1;
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
int ParticleModel::slidingForce(double theta, double frCoef) //theta = angle of plane, frCoef = coefficient of friction.
{
	int forceMag = mass * gravity * (sin(theta) - frCoef * cos(theta));
	// To do: check to ensure that magnitude is not negative

	sForce.x = forceMag * cos(theta); 
	sForce.y = forceMag * sin(theta); 
	return 1;
}
int ParticleModel::updateAccel()
{
	acceleration.x = netForce.x/mass;
	acceleration.y = netForce.y/mass;

	return 1;
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
int ParticleModel::moveRight()
{
// update world position of object.
//pos.x += displacement.x;
	//moveConstDispl();
	//moveConstVel();
	//newAccel.x = getAccel().x + 10.0;
	//newAccel.y = getAccel().y;
	//setAccel(newAccel);

	//velocity.x += acceleration.x;
	//acceleration.x += 1.0;
	moveForce.x += 0.05;

return 1;
}
int ParticleModel::moveLeft()
{

// update world position of object.
//pos.x -= displacement.x; 
	//moveConstDispl();
	//moveConstVel();
	//newAccel.x = getAccel().x - 10.0;
	//newAccel.y = getAccel().y;
	//setAccel(newAccel);#
	//setVel(newAccel);

	//acceleration.x -= 1.0;
	moveForce.x -= 0.05;
return 1;
}
int ParticleModel::moveUp()
{

// update world position of object.
//pos.y -= displacement.y; 
	//newAccel.x = getAccel().x;
	//newAccel.y = getAccel().y - 20.0;
	//setAccel(newAccel);
	//setVel(newAccel);

	//acceleration.y -= 1.0;
	moveForce.y -= 0.05;

return 1;
}
int ParticleModel::moveDown()
{
// update world position of object.
//pos.y += displacement.y; 
	//newAccel.x = getAccel().x;
	//newAccel.y = getAccel().y + 20.0;
	//setAccel(newAccel);
	//setVel(newAccel);

	//acceleration.y += 1.0;
	moveForce.x += 0.05;

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