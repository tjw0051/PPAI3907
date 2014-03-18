/*
 * File name:		dataTypes.h
 * Description:		Header file for custom data types
 *
 * Author: 			Claude C. Chibelushi
 * Date:			02/10/05
 *					Modified 19/01/09 by CCC: porting to C++
 *
 */
 

#ifndef _DATATYPES_H
#define _DATATYPES_H

/*	2D structure (contains x and y components) */
struct	tagPoint2D
	{
	float x, y;				/* x and y coordinates of a point */
	}; 
typedef	tagPoint2D	Point2D,			/* 2D point */
					* pPoint2D;			/* pointer to 2D point */
/*
struct tagPoint4D
{
	float x, y, height, width;
};
typedef tagPoint4D Point4D, 
						* pPoint4D;

struct tagRectangle
{
	float x, y, height, width;
};
typedef tagRectangle Rectangle, 
						* pRectangle;
*/

#endif /* _DATATYPES_H */
