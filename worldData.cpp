/*	

Version Control : GitHub
Repo: https://github.com/tjw0051/PPAI3907

*/


#include "worldData.h"


WorldData::WorldData()
	{
	}

int WorldData::worldDataModuleInit(GraphicsM * graphics)
{
		viewport = graphics->getViewport();

	return 1;
}

WorldData::~WorldData()
	{

	worldCleanUp();

	return;			
	}



/*
 Releases objects

 Parameter list
 	none
 */

void WorldData::worldCleanUp()
	{
	/* TO DO: add relevant code */

	return;			
	}

/*
 * Sets shape of object as square.
 *
 * Parameter list
 *        none.
 */



		/*----------------------------------------------------------------------------\
		 *                                                                            |
		 *                  STATE ACCESS (get / set) FUNCTIONS                        |
		 *                                                                            |
		 *----------------------------------------------------------------------------*/
 
/* TODO: Add functions to set other particle model parameters, e.g. velocity, acceleration, ... */

   
/*
 * Gets position of particle.
 *
 * Parameter list
 *        none.
 */


/* TODO: Add functions to get other particle model parameters, e.g. velocity, acceleration, ... */

		/*----------------------------------------------------------------------------\
		 *                                                                            |
		 *                                  STATE UPDATE                              |
		 *                                                                            |
		 *----------------------------------------------------------------------------*/
 
/*
 * Updates world state.

	Parameter list
         kEvent       input event ID.
 */
int WorldData::update(keyEvent kEvent)
	{
	/* TO DO: add relevant code */
	// For example:
	// update world position of square as determined by user input.
	switch(kEvent)
		{
		// Update parameters of virtual world

		case UP:
			// TO DO: service up-key as approriate
           
			break;
		case DOWN:
			// TO DO: service down-key as approriate
            
			break;
		case RIGHT:
			
			// TO DO: service right-key as approriate
            // For example:
			// update world position of object to move it to the right.
			break;
		case LEFT:
			// TO DO: service left-key as approriate
            
			break;
		case SPACE:
			gameObject2.fire(gameObject1.getPos());
			break;
		default:
			// TO DO: service "all-other-keys" as approriate

			break;
		}
	gameObject1.update(kEvent);
	gameObject2.update();
	//slopeObject.update(kEvent);
	//worldCollisionCheck(&gameObject1);
	/*
	//update collision with slope
	collisionCheck();
	*/
	collisionCheck();
	return 1;
}

int WorldData::collisionCheck() // worldData.cpp
{
	double angle = 0;
	if(rectIntersect(slopeObject.BoundingBox(), gameObject1.BoundingBox()))
	{
		angle = slopeObject.getAngleAtPos(gameObject1.BoundingBox());
		gameObject1.setSlidingForce(angle, 0.8); //-1.012
		if(angle == 100)
		{
			gameObject1.collision();
		}
	}
	else
	{
		gameObject1.isColliding(false);
		gameObject1.setSlidingForce(0, 0);
	}
	return 1;
} 
bool WorldData::rectIntersect(RECT rect1, RECT rect2)
{
	if(rect1.left > rect2.right || rect1.right < rect2.left
		||rect1.bottom < rect2.top || rect1.top > rect2.bottom)
	{
		return false;
	}
	else
		return true;
}
/*
	Updates particle position: move particle towards right.

	Parameter list
		none
 */


/* TO DO: Add other functions to update position using appropriate formulae */

/* TO DO: Add functions to update other particle model parameters, e.g. velocity, acceleration, ... */


	/*----------------------------------------------------------------------------\
	 *                                                                            |
	 *                                   DISPLAY                                  |
	 *                                                                            |
	 *----------------------------------------------------------------------------*/


/*
	Draws the world.

	Parameter list
		pGraphicsModule       pointer to graphics module.
*/
int WorldData::draw(GraphicsM * pGraphicsModule)
{
    /* TO DO: add relevant code */

    /* Display world */
	//pGraphicsModule->drawPolygon(slopePolygon, 4, true);
	//   Draw the square.


		slopeObject.draw(pGraphicsModule);
		gameObject1.draw(pGraphicsModule);
		gameObject2.draw(pGraphicsModule);


	return 1;
}


/*
 * Updates content of display buffer.
 *
 * Parameter list
 *        none.
 */



