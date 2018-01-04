/*
 * main.c
 *
 *  Created on: Dec 30, 2017
 *      Author: jilin
 */

#include "Vector.h"

int main( void ){
	Shape *s = shapeCreate();
	Shape *t = shapeCreate();
	if ( collisionDetectedSAT( s, t ) )
		printf("Collision Detected.");
	else
		printf("No Collision.");

	return 0;
}
