/*
 * Position.h
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */

#ifndef MODELS_POSITION_H_
#define MODELS_POSITION_H_

class Position {
	int x;
	int y;
public:
	Position(int X, int Y);
	virtual ~Position();
	int getX();
	int getY();
};

#endif /* MODELS_POSITION_H_ */
