/*
 * File name:		input.cpp
 * Description:		Input-event module
 *
 * Author: 			Claude C. Chibelushi
 * Date:			04/10/04
 *					Modified 19/01/09 by CCC: porting to C++
 *
 */



#include		"input.h"		/* include file for user input module */

		/*----------------------------------------------------------------------------\
		 *                                                                            |
		 *                       INITIALISATION AND CLEAN UP           				  |
		 *                                                                            |
		 *----------------------------------------------------------------------------*/

/*
	Construct and initialise an input module.

	Parameter list
		none

 */
Input::Input()
	{
	}


/*
	Destruct input module

	Parameter list
		none
 */
Input::~Input()
	{
	return;			
	}

		/*----------------------------------------------------------------------------\
		 *                                                                            |
		 *                       KEYBOARD INPUT POLLING		           				  |
		 *                                                                            |
		 *----------------------------------------------------------------------------*/


/*
	Check for keyboard event.

	Parameter list
		hWnd:			handle of window

	Returns		
		event:			code for keyboard event
 */


keyEvent Input::checkUserInput(HWND hWnd)
	{
	keyEvent		event;
   

   /* Terminate if user has pressed the Esc key */

	if ( IS_KEY_DOWN(VK_ESCAPE) )
		{
		event = QUIT;

		// Request window destruction if user has pressed the Esc key 
		PostMessage(hWnd, WM_DESTROY, 0, 0);
		}
	else if ( IS_KEY_DOWN(VK_UP) )
		event = UP;
	else if ( IS_KEY_DOWN(VK_DOWN) )
		event = DOWN;
	else if ( IS_KEY_DOWN(VK_LEFT) )
		event = LEFT;
	else if ( IS_KEY_DOWN(VK_RIGHT) )
		event = RIGHT;
	else if ( IS_KEY_DOWN(VK_SPACE) )
		event = SPACE;
	else if(IS_KEY_DOWN(0x57) )
		event = W;
	else if(IS_KEY_DOWN(0x41) )
		event = A;
	else if(IS_KEY_DOWN(0x53) )
		event = S;
	else if(IS_KEY_DOWN(0x44) )
		event = D;
	else 
		event = QUIET;
	

	return event;
	}

