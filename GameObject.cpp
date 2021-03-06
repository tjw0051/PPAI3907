#include "GameObject.h"

GameObject::GameObject()
{
	//viewport = 0, 0, 650, 490; //10, 10, 650, 490
	viewport.left = 10; 
	viewport.top = 10;
	viewport.right = 900; //650
	viewport.bottom = 700; // 490
	slidingTheta = 0;
	slidingfrCoef = 0;
	particleModel.setPosition(100.0F, 650.0F);
	appearance.setShape2Square();
}
int GameObject::update()
{
	particleModel.updateDragForce();
	particleModel.slidingForce(slidingTheta, slidingfrCoef); // 2, 0.4
	particleModel.updateNetForce();
	particleModel.updateAccel();
	particleModel.moveConstAccel();

	worldCollisionCheck();
	if(impulse == true)
	{
		particleModel.moveNull();
		impulse = false;
	}

	return 1;
}
void GameObject::fire(Point2D originPos)
{
	particleModel.randomProjectile(originPos);
	impulse = true;
}
void GameObject::release()
{
	particleModel.moveNull();
}
int GameObject::update(keyEvent kEvent)
{
	
	particleModel.updateDragForce();
	particleModel.slidingForce(slidingTheta, slidingfrCoef); // 2, 0.4
	particleModel.updateNetForce();
	particleModel.updateAccel();
	particleModel.moveConstAccel();
	
	switch(kEvent) 
		{
			case D:
				particleModel.moveRight();
				break;
			case A:
				particleModel.moveLeft();
				break;
			case W:
				particleModel.moveUp();
				break;
			case S:
				particleModel.moveDown();
				break;
			case SPACE:
				particleModel.brake();
					break;
			default:
				particleModel.moveNull();
				break;
	}
	worldCollisionCheck();
	return 1;
}

Point2D GameObject::convertToPoint2D(float angle, float magnitude)
{
	Point2D vector;
	vector.y = sin(angle)*magnitude;  //sin(angle)*magnitude
	vector.x =	cos(angle)*magnitude;  //cos(angle)*magnitude
	return vector;
}

int GameObject::draw(GraphicsM * pGraphicsModule)
{
	dispBufUpdate();	// update content of display buffer (with outline of square at its current position)
	pGraphicsModule->drawPolygon(dispBuffObj, 4, true); // display content of buffer

	return 1;
}

int GameObject::dispBufUpdate()
{
    /* TO DO: add relevant code */

    // update display object (content of display buffer (with calculated vertex coordinates of square at its current position))
    for (int vert = 0; vert < 4; ++vert)
      {
      dispBuffObj[vert].x = appearance.getShapeFromVert(vert).x + particleModel.getPosition().x;
	  dispBuffObj[vert].y = appearance.getShapeFromVert(vert).y + particleModel.getPosition().y;
      }
    return 1;
}
void GameObject::setSlidingForce(double theta, double frCoef)
{
	slidingTheta = theta;
	slidingfrCoef = frCoef;
}
RECT GameObject::BoundingBox()
{
	RECT boundingBox;
	boundingBox.left = particleModel.getPosition().x;
	boundingBox.top = particleModel.getPosition().y;
	boundingBox.right = particleModel.getPosition().x + appearance.getWidth();
	boundingBox.bottom = particleModel.getPosition().y + appearance.getHeight();
	
	return boundingBox;
}
RECT GameObject::movingBoundingBox()
{
	Point2D vel = particleModel.getVel();
	Point2D accel = particleModel.getAccel();
	RECT boundingBox;
	boundingBox.left = particleModel.getPosition().x + vel.x + accel.x;
	boundingBox.top = particleModel.getPosition().y + vel.y + accel.y;
	boundingBox.right = particleModel.getPosition().x + appearance.getWidth() + vel.x + accel.x;
	boundingBox.bottom = particleModel.getPosition().y + appearance.getHeight() + vel.y + accel.y;
	
	return boundingBox;
}

void GameObject::collision()
{
	Point2D newPoint2D;
	newPoint2D.x = particleModel.getAccel().x;
	newPoint2D.y = 0;
	particleModel.setAccel(newPoint2D);
	newPoint2D.x = particleModel.getVel().x;
	particleModel.setVel(newPoint2D);
}
void GameObject::isColliding(bool val)
{
	//if(val = true)
		
}
int GameObject::worldCollisionCheck()
{
	if(BoundingBox().left < viewport.left) // player off left of screen
	{
		newPos.x = 0;
		newPos.y = 0;
		particleModel.setVel(newPos);
		particleModel.setPosition(viewport.left, particleModel.getPosition().y);
	}
	if(BoundingBox().right > viewport.right)
	{
		newPos.x = 0;
		newPos.y = 0;
		particleModel.setVel(newPos);
		particleModel.setPosition(viewport.right - appearance.getWidth(), particleModel.getPosition().y);
	}
	if(BoundingBox().top < viewport.top)
	{
		newPos.x = 0;
		newPos.y = 0;
		particleModel.setVel(newPos);
		particleModel.setPosition(particleModel.getPosition().x, viewport.top);
	}
	if(BoundingBox().bottom > viewport.bottom - 40)
	{
		newPos.x = 0;
		newPos.y = 0;
		particleModel.setVel(newPos);
		particleModel.setPosition(particleModel.getPosition().x, viewport.bottom - appearance.getHeight() - 40);
	}
	
	return 1;
}
Point2D GameObject::getPos()
{
	return particleModel.getPosition();
}
