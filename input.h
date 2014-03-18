/*
 * File name:		input.h
 * Description:		Header file for input.cpp
 *
 * Author: 			Claude C. Chibelushi
 * Date:			04/10/04
 *					Modified 19/01/09 by CCC: porting to C++
 *
 */
 

#ifndef _INPUT_H
#define _INPUT_H

#include	<windows.h>

#define IS_KEY_DOWN(virt_key_code)  ( (GetAsyncKeyState(virt_key_code) & 0x8000) ? 1 : 0 )
#define IS_KEY_UP(virt_key_code)  ( (GetAsyncKeyState(virt_key_code) & 0x8000) ? 0 : 1 )

/* possible key events */
typedef enum EVENT {QUIT, UP, DOWN, LEFT, RIGHT, QUIET, SPACE, W, A, S, D}	keyEvent;


class Input
	{
	public:

		// Constructor and destructor
		Input();
		~Input();

		keyEvent checkUserInput(HWND hWnd);	// Check for keyboard event

	};


#endif /* _INPUT_H */
