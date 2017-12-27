/*
 * Vector.c
 *
 *  Created on: Dec 23, 2017
 *      Author: jilin
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "Vector.h"


Shape* shapeCreate( ){
	int numPoints = 0;
	double x,y;

	printf("Enter the number of vertices: ");
	scanf("%d", &numPoints);

	Shape *s = malloc( sizeof(Shape) ); assert(s);
	s->numPoints = numPoints;
	s->points = malloc( sizeof(Vector) * numPoints ); assert(s->points);
	s->normals = malloc( sizeof(Vector) * numPoints ); assert(s->normals);

	for( int i = 0; i < numPoints; i++ ) {
		printf("Enter Edge #%d's x value: ", i+1);
		scanf("%lf", &x);
		printf("Enter Edge #%d's y value: ", i+1);
		scanf("%lf", &y);
		s->points[i] = vectorCreate( 0, 0, x, y );
	}

	for( int i = 0; i < numPoints-1; i++ )
		s->normals[i] = normVector( vectorCreate( s->points[i].x, s->points[i].y, s->points[i+1].x, s->points[i+1].y ) );
	s->normals[numPoints-1] = normVector( vectorCreate( s->points[numPoints-1].x, s->points[numPoints-1].y, s->points[0].x, s->points[0].y ) );
	return s;
}


Vector vectorCreate( double x1, double y1, double x2, double y2 ){
	Vector v = { x2-x1, y2-y1 };
	return v;
}

Vector unitVector( Vector v ){
	double mag = magnitude( v );
	return vectorCreate( 0, 0, v.x/mag, v.y/mag );
}

Vector normVector( Vector v ){
	return vectorCreate( 0, 0, -1*v.y, v.x );
}

double magnitude( Vector v ){
	return sqrt( v.x*v.x + v.y*v.y );
}

double dotProd( Vector v, Vector w ){
	return v.x*w.x + v.y*w.y;
}

double proj( Vector v, Vector axis ){
	return fabs( dotProd( v, unitVector(axis) ) );
}

