///////////////////////////////////////////////////////////
//  Point.cpp
//  Implementation of the Class Point
//  Created on:      28-Oct-2012 18:38:53
//  Original author: rbirke00
///////////////////////////////////////////////////////////

#include "Point.h"




Point::Point(){
	this->xval = 0;
	this->yval = 0;
}


Point::Point(int y, int x){
	this->xval = x;
	this->yval = y;
}


Point::~Point(){

}


int Point::getXval(){

	return xval;
}


int Point::getYval(){

	return yval;
}


void Point::setXval(int newVal){

	xval = newVal;
}


/**
 * the y value
 */
void Point::setYval(int newVal){

	yval = newVal;
}