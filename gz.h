/*
 * gz.h - include file for rendering library
 * CSCI 580   USC 
*/

#pragma once

const int GZ_SUCCESS = 0;
const int GZ_FAILURE = 1;

/*
 * display classes
 */
const int GZ_RGBAZ_DISPLAY = 1;

/*
 * rendering classes
 */
const int GZ_Z_BUFFER_RENDER = 1;

typedef int     GzRenderClass;
typedef int     GzDisplayClass;
typedef void    *GzPointer;
typedef float   GzColor[3];
typedef short   GzIntensity;	/* 0 - 4095 in lower 12-bits */
typedef int	GzDepth;	/* z is signed for clipping */


const int RED   = 0;               /* array indicies for color vector */
const int GREEN = 1;
const int BLUE  = 2;

const int X     = 0;               /* array indicies for position vector */
const int Y     = 1;
const int Z     = 2;

const int U     = 0;               /* array indicies for texture coords */
const int V     = 1;
