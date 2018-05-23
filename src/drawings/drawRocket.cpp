/*
 * drawRocket.cpp
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */

#include "drawRocket.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../models/Rgb.h"
#include "../models/Triangle.h"
#include "../models/Square.h"

void drawTriangle(Rgb rgb, Triangle *triangle){
	glColor3f(rgb.getR(), rgb.getG(), rgb.getB());
	glBegin(GL_TRIANGLES);
		glVertex2f(triangle->getPosition1() , triangle->getPosition2() );
		glVertex2f(triangle->getPosition3() , triangle->getPosition4() );
		glVertex2f(triangle->getPosition5() , triangle->getPosition6() );
	glEnd();
}

void drawSquare(Rgb rgb, Square *square) {
	glColor3f(rgb.getR(), rgb.getG(), rgb.getB());
	glBegin(GL_POLYGON);
		glVertex3f(square->getPosition1() , square->getPosition2() , 0.0);
		glVertex3f(square->getPosition3() , square->getPosition4() , 0.0);
		glVertex3f(square->getPosition5() , square->getPosition6() , 0.0);
		glVertex3f(square->getPosition7() , square->getPosition8() , 0.0);
	glEnd();
}

