/*
 * File name:		worldData.h
 * Description:		Header file for worldData.cpp
 *
 * Author: 			Claude C. Chibelushi
 * Date:			04/10/04
 *					Modified 27/09/06, by CCC: addition of setShape2Square() function prototype.
 *					Modified 19/01/09 by CCC: porting to C++
 *							 06/02/09 by CCC: additional functionality required  
 *                           for illustrative examples of GDI drawing functionality.
 *
 */
 

#ifndef _WORLDDATA_H
#define _WORLDDATA_H

#include	<windows.h>
#include	"dataTypes.h"		/* include file for custom data types */
#include	"graphics.h"		/* include file for graphics module */
#include	"input.h"			/* include file for user input module */

#include "GameObject.h"


class WorldData
	{
	private:

		

		GameObject gameObject1, gameObject2;
	    // Appearance attributes (for object display)
					// array to store a polygonal shape consisting of four vertices (e.g. a square) 
				// array to store display coordinates of a polygonal object

		// Dynamics parameters (for physics simulation) 
						// position of particle used as physics model of game object
		RECT viewport;
		
	public:

		// Constructors and destructor
		WorldData();
		~WorldData();

		int worldDataModuleInit(GraphicsM * pGraphicsModule);						// Initialise the world
		void worldCleanUp();							// Release objects, if applicable

		int update(keyEvent kEvent);					// Update the world's dynamics state

		//int worldCollisionCheck(GameObject * gameObject);
		int draw(GraphicsM * pGraphicsModule);			// Draw the world

	private: 
		
		/* Apply physics formulae to particle */
		
				// Set shape of object to square

		/* Graphics data update (before actual display) */
				// Update display buffer
	};

#endif /* _WORLDDATA_H */
