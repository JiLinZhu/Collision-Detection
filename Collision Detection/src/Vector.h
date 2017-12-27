/*
 * Vector.h
 *
 *  Created on: Dec 23, 2017
 *      Author: jilin
 */

#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct {
	double x;
	double y;
}Vector;

typedef struct {
	int numPoints;
	Vector *points;
	Vector *normals;
}Shape;

Shape* shapeCreate( );

Vector vectorCreate( double x1, double y1, double x2, double y2 );

Vector unitVector( Vector v );

Vector normVector( Vector v );

double magnitude( Vector v );

double dotProd( Vector v, Vector w );

double proj( Vector v, Vector axis );

#endif /* VECTOR_H_ */

