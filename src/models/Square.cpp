/*
 * Square.cpp
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */

#include "Square.h"

Square::Square(Position *position, int width, int height) {
	// TODO Auto-generated constructor stub
	position1 = position->getX();
	position2 = position->getY();
	position3 = position->getX() + width;
	position4 = position->getY();
	position5 = position->getX() + width;
	position6 = position->getY() + height;
	position7 = position->getX();
	position8 = position->getY() + height;
}

Square::~Square() {
	// TODO Auto-generated destructor stub
}

int Square::getPosition1() {
	return position1;
}

int Square::getPosition2() {
	return position2;
}

int Square::getPosition3() {
	return position3;
}

int Square::getPosition4() {
	return position4;
}

int Square::getPosition5() {
	return position5;
}

int Square::getPosition6() {
	return position6;
}

int Square::getPosition7() {
	return position7;
}

int Square::getPosition8() {
	return position8;
}


