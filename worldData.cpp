/*
 * File name:	worldData.cpp
 * Description:	World data module.
 *
 * Author: 			Claude C. Chibelushi
 * Date:			04/10/04
 *					Modified 27/09/06, by CCC: addition of function for setting object shape
 *					Modified 19/01/09 by CCC: porting to C++
 *							 06/02/09 by CCC: additional functionality required  
 *                           for illustrative examples of GDI drawing functionality.
 *
 */
 

/*							TO DO
--------------------------------------------------------------------
				absolute collision detection with world
*/


#include "worldData.h"

/*----------------------------------------------------------------------------\
 *                                                                            |
 *                       INITIALISATION AND CLEAN UP                   		  |
 *                                                                            |
 *----------------------------------------------------------------------------*/

/*
	Constructs and initialises a world data management module

	Parameter list
		none
 */

WorldData::WorldData()
	{
	/* TO DO: add relevant code */
		
	}

/**
    Initialises the world

	Parameter list
         none.
  */
int WorldData::worldDataModuleInit(GraphicsM * graphics)
{
		viewport = graphics->getViewport();
		//GameObject gameObject1 = GameObject(&viewport);

		//slopePolygon
		//slopeObject = WorldObject(0, 300, 600);

	return 1;
}


/*
	Destructs world data management module

	Parameter list
		none
 */
WorldData::~WorldData()
	{
	/* TO DO: add relevant code */

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
		default:
			// TO DO: service "all-other-keys" as approriate

			break;
		}
	gameObject1.update(kEvent);
	//slopeObject.update(kEvent);
	//worldCollisionCheck(&gameObject1);
	/*
	//update collision with slope
	collisionCheck();
	*/
	collisionCheck();
	return 1;
}

int WorldData::collisionCheck()
{
	if(rectIntersect(slopeObject.BoundingBox(), gameObject1.BoundingBox()))
	{
		gameObject1.setSlidingForce(2, 0.4);
	}
	else
		gameObject1.setSlidingForce(0, 0);
	/*
	foreach worldobject
	check collision with each side
	 - player sliding force - get angle from worldobject
	check collision with top
	 - stop y vel.
	*/
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
		


	return 1;
}


/*
 * Updates content of display buffer.
 *
 * Parameter list
 *        none.
 */



