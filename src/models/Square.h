/*
 * Square.h
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */

#ifndef MODELS_SQUARE_H_
#define MODELS_SQUARE_H_
#include "Position.h"

class Square {
	int position1;
	int position2;
	int position3;
	int position4;
	int position5;
	int position6;
	int position7;
	int position8;
public:
	Square(Position *position, int width, int height);
	virtual ~Square();
	int getPosition1();
	int getPosition2();
	int getPosition3();
	int getPosition4();
	int getPosition5();
	int getPosition6();
	int getPosition7();
	int getPosition8();
};

#endif /* MODELS_SQUARE_H_ */
