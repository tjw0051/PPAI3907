/*
 * File name:		simulation.cpp
 * Description:		Simulation module
 *
 * Author: 			Claude C. Chibelushi
 * Date:			04/10/04
 *					Modified 02/10/05, by CCC: addition of calls to flow-control module
 *					Modified 19/01/09 by CCC: porting to C++
 *					Modified 06/02/09 by CCC: implementation of double buffering
 *							(functions changed: simInit) and of changes required for 
 *							illustrative examples of drawing functionality  
 *							(e.g. worldDataModuleInit()).
 *					Modified 22/01/10 by CCC: flow-control functionality integrated into Simulation class
 *
 */



#include		"simulation.h"		/* include file for simulation */



/* Convention on function return value: 0 means error; 1 means OK */


		/*----------------------------------------------------------------------------\
		 *                                                                            |
		 *                       INITIALISATION AND CLEAN UP           				  |
		 *                                                                            |
		 *----------------------------------------------------------------------------*/

/*
	Constructs and initialises simulation module.

	Parameter list
 		none
 */
Simulation::Simulation()
	{
	/* TO DO: add relevant code */


	}

/*
	Destructs simulation module

	Parameter list
		none
 */
Simulation::~Simulation()
	{
	/* TO DO: add relevant code */

	simCleanUp();

	return;			
	}

/*
	Simulation entry point.

	Parameter list
 		hWnd:			handle of window
		message:		pointer to message 
 */

int Simulation::simMain(HWND hWnd, MSG * msg)
{
	if ( simInit(hWnd) )
	{
		simLoop(hWnd, msg);
		simCleanUp();

		return 1;
	}

	return 0;
}



/*
	Simulation initialisation.

	Parameter list
 		hWnd:			handle of window
 */

int Simulation::simInit(HWND hWnd)
{
	frameRate = 2;

	// Initialise:	world data module,
	//				graphics module,
	//				dynamics / behaviour module,
	//				flow control module
	if( world.worldDataModuleInit(&graphics) && 
		graphics.graphicsModuleInit(hWnd) )	
	{
		ShowCursor(FALSE);  /* hide mouse cursor */
		return 1;
	}

	return 0;
}


/*
	Simulation clean-up prior to shut-down.

	Parameter list
		none
 */

int Simulation::simCleanUp()
{
	world.worldCleanUp();			// release world objects
	graphics.graphicsCleanUp();		// release graphics objects

	ShowCursor(TRUE);				// show mouse cursor

	return 1;
}

		/*----------------------------------------------------------------------------\
		 *                                                                            |
		 *									GAME LOOP			    				  |
		 *                                                                            |
		 *----------------------------------------------------------------------------*/



/*
	Simulation loop.

	Parameter list
 		hWnd:			handle of window
		message:		pointer to message 
 */

int Simulation::simLoop(HWND hWnd, MSG * msg)
{
	frameStartTime = GetTickCount();
	//Sleep(20);
	
	/* Main loop  */

	ZeroMemory( msg, sizeof(*msg) );
	/* retrieve messages (for e.g. user interaction devices) */
	while( msg->message != WM_QUIT ) 	/* drop out of loop if "quit" message received */
	{
		/* Windows-part of loop body */
		if( PeekMessage( msg, NULL, 0U, 0U, PM_REMOVE ) )
      	/* Note: PeekMessage() does not wait for message to be placed in queue
         before returning (whereas GetMessage() does wait) */
		{
			TranslateMessage( msg ); 	/* translate keyboard message */
			DispatchMessage( msg );		/* dispatch message to window procedure (via Windows) */
		}

		gameLoopDelay(frameStartTime);

		/* Simulation-part of loop body */
		simProc(hWnd);
		
	}
   return 1;
}

int Simulation::gameLoopDelay(int frameStartTime)
{
	frameProcessingTime = GetTickCount() - frameStartTime;
	if(frameProcessingTime < frameRate)
	{
		Sleep(frameRate - frameProcessingTime);
	}
	return 1;
}
/*
	Simulation processing.

	Parameter list
 		hWnd:			handle of window
 */

int Simulation::simProc(HWND hWnd)
{
	keyEvent		event;

	/* Read user input (if any), and activate control logic */
	event = kbd.checkUserInput(hWnd);
	simControlLogic(hWnd, event);

   return 1;
}


/*----------------------------------------------------------------------------\
 *                                                                            |
 *						CONTROL LOGIC BASED ON USER INPUT             		  |
 *                                                                            |
 *----------------------------------------------------------------------------*/



/*
	Control logic.

	Parameter list
 		hWnd:			handle of window
		event:			code for user input event
 */

int Simulation::simControlLogic(HWND hWnd, keyEvent event)
{
	if (event != QUIT)
	{
		world.update(event);					// update parameters of virtual world
  		simDisplayFrame(hWnd);			// display frame
	}

   return 1;
}

/*
 Draws a frame of the animation (using graphics context of backbuffer).
		  
 Parameter list
	none
 */

int Simulation::simDisplayFrame(HWND hWnd)
{
	// (i.1) display HUD
	graphics.drawHUD();			// draw HUD

	// (i.2) display world on HUD
	world.draw(&graphics);

	// (ii) display back buffer 
	graphics.displayBackBuffer(hWnd);

	return 1;
}
