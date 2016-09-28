#ifndef BLUB_H
#define BLUB_H
#include "BlubJoint.h"
//this is the class declaration
class Blub
{
public:
	//int color[3] = { 255, 255, 255 };
	int i, j;
	BlubJoint* sideJoints;
	BlubJoint centerJoint;
	int precision;
	double radius;
	Blub(int, int);
	Blub(double, int, int, int);
	Blub(Blub&, Blub&, int);
	void move(int);
	void moveCommand(double, double);
};
#endif
