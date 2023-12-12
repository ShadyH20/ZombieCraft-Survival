//#include <math.h>/*
//#include <stdio.h>
//#include <stdlib.h>*/
#include <glut.h>


void triangularPrism()
{
	glBegin(GL_QUADS);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(-0.5, 0, -0.5);
	glVertex3f(-0.5, 0, 0.5);

	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, 1, 0);
	glVertex3f(-0.5, 1, 0);
	glVertex3f(-0.5, 0, -0.5);

	glVertex3f(0.5, 1, 0);
	glVertex3f(-0.5, 1, 0);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(0.5, 0, 0.5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 1, 0);
	glVertex3f(0.5, 0, -0.5);

	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(-0.5, 1, 0);
	glVertex3f(-0.5, 0, -0.5);
	glEnd();

	//glDisable(GL_LIGHTING);
}


