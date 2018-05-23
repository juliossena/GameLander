/*
 * Triangle.h
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */

#ifndef MODELS_TRIANGLE_H_
#define MODELS_TRIANGLE_H_
#include "Position.h"

class Triangle {

	int position1;
	int position2;
	int position3;
	int position4;
	int position5;
	int position6;

public:
	Triangle(Position *position, int width, int height, int orientation);
	virtual ~Triangle();
	int getPosition1();
	int getPosition2();
	int getPosition3();
	int getPosition4();
	int getPosition5();
	int getPosition6();
};

#endif /* MODELS_TRIANGLE_H_ */
