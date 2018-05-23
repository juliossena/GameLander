/*
 * Triangle.cpp
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */

#include "Triangle.h"
#include "Position.h"
#include <iostream>
using namespace std;

//Orientatio, se = 1 normal, 2 90 graus, 3 180 graus, 4 270 graus
Triangle::Triangle(Position *position, int width, int height, int orientation) {
	// TODO Auto-generated constructor stub
	if (orientation == 1) {
		position1 = position->getX();
		position2 = position->getY();
		position3 = position->getX() + width;
		position4 = position->getY();
		position5 = ((float)(position->getX()) + (width / 2.0));
		position6 = position->getY() + height;

	} else if(orientation == 2) {
		position1 = position->getX();
		position2 = position->getY();
		position3 = position->getX() ;
		position4 = position->getY() + width;
		position5 = position->getY() + width;
		position6 = ((float)(position->getX() + width) / 2.0);
	} else if (orientation == 3) {
		position1 = position->getX();
		position2 = position->getY();
		position3 = position->getX() + width;
		position4 = position->getY();
		position5 = ((float)(position->getX() + width) / 2.0);
		position6 = position->getY() - height;
	} else if (orientation == 4) {
		position1 = position->getX();
		position2 = position->getY();
		position3 = position->getX();
		position4 = position->getY() - width;
		position5 = position->getX() - height;
		position6 = position->getY() - (width / 2.0);

	}

}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}

int Triangle::getPosition1() {
	return position1;
}

int Triangle::getPosition2() {
	return position2;
}

int Triangle::getPosition3() {
	return position3;
}

int Triangle::getPosition4() {
	return position4;
}

int Triangle::getPosition5() {
	return position5;
}

int Triangle::getPosition6() {
	return position6;
}

