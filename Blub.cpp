#include "Blub.h"
#define PI 3.14159265
using namespace std;

Blub::Blub(int inPosX, int inPosY)
{
	sideJoints = new BlubJoint[4];

	sideJoints[0] = BlubJoint(inPosX - 20, inPosY - 20);
	sideJoints[1] = BlubJoint(inPosX + 20, inPosY - 20);
	sideJoints[2] = BlubJoint(inPosX + 20, inPosY + 20);
	sideJoints[3] = BlubJoint(inPosX - 20, inPosY + 20);

	sideJoints[0].addJoint(&sideJoints[1]);
	sideJoints[1].addJoint(&sideJoints[0]);
	
	sideJoints[1].addJoint(&sideJoints[2]);
	sideJoints[2].addJoint(&sideJoints[1]);

	sideJoints[2].addJoint(&sideJoints[3]);
	sideJoints[3].addJoint(&sideJoints[2]);

	sideJoints[3].addJoint(&sideJoints[0]);
	sideJoints[0].addJoint(&sideJoints[3]);

	centerJoint = BlubJoint(inPosX, inPosY);

	centerJoint.addJoint(&sideJoints[0]);
	centerJoint.addJoint(&sideJoints[1]);
	centerJoint.addJoint(&sideJoints[2]);
	centerJoint.addJoint(&sideJoints[3]);

	sideJoints[0].addJoint(&centerJoint);
	sideJoints[1].addJoint(&centerJoint);
	sideJoints[2].addJoint(&centerJoint);
	sideJoints[3].addJoint(&centerJoint);
}
Blub::Blub(double radius, int precision, int inPosX, int inPosY)
{
	this->radius = radius;
	this->precision = precision;
	centerJoint = BlubJoint(inPosX, inPosY);
	double argN = (2 * PI) / precision;
	sideJoints = new BlubJoint[precision];
	for (i = 0; i < precision; i++)
	{
		sideJoints[i] = BlubJoint(inPosX + radius*cos(argN*i), inPosY + radius*sin(argN*i));
		sideJoints[i].addJoint(&centerJoint);
		centerJoint.addJoint(&sideJoints[i]);
	}
	for (i = 0; i < precision; i++){
		sideJoints[i].addJoint(&sideJoints[(i - 1) % precision]);
		sideJoints[i].addJoint(&sideJoints[(i + 1) % precision]);
	}

	/*for (i = 0; i < precision; i++)
	{
		sideJoints[i].addJoint(&sideJoints[(i+1)%precision]);
		sideJoints[(i+1)%precision].addJoint(&sideJoints[i]);
		centerJoint.addJoint(&sideJoints[i]);
		sideJoints[i].addJoint(&centerJoint);
	}*/

}
Blub::Blub(Blub& blub1, Blub& blub2, int start)
{
	precision = blub1.precision;
	BlubJoint* tempBlubPtr = blub1.sideJoints;
	sideJoints = new BlubJoint[precision + blub2.precision];
	for (i = 0; i < precision; i++)
	{
		sideJoints[(i + start) % (blub1.precision + blub2.precision)] = tempBlubPtr[i];
	}
	precision += blub2.precision;
	tempBlubPtr = blub2.sideJoints;
	for (i = blub1.precision; i < precision; i++)
	{
		sideJoints[(i+start)%(blub1.precision+blub2.precision)] = tempBlubPtr[i-blub1.precision];
	}
	radius = sqrt(blub1.radius*blub1.radius + blub2.radius*blub2.radius);
	double argN = (2 * PI) / precision;
	for (i = 0; i < precision; i++)
	{
		for (j = 0; j < i; j++){
			sideJoints[i].addJoint(&sideJoints[j], sqrt(
				(radius*cos(argN*i) - radius*cos(argN*j))*(radius*cos(argN*i) - radius*cos(argN*j)) +
				(radius*sin(argN*i) - radius*sin(argN*j))*(radius*sin(argN*i) - radius*sin(argN*j))
				 ));
			sideJoints[j].addJoint(&sideJoints[i], sqrt(
				(radius*cos(argN*i) - radius*cos(argN*j))*(radius*cos(argN*i) - radius*cos(argN*j)) +
				(radius*sin(argN*i) - radius*sin(argN*j))*(radius*sin(argN*i) - radius*sin(argN*j))
				));
		}

	}

}
void Blub::move(int duration)
{
	for (int i = 0; i < precision; i++)
	{
		centerJoint.getAcceleration();
		centerJoint.move(duration);
		sideJoints[i].getAcceleration();
		sideJoints[i].move(duration);
	}
}
void Blub::moveCommand(double inAccX, double inAccY)
{
	for (i = 0; i < precision; i++)
	{
		sideJoints[i].accelerationBonusVect[0] += inAccX;
		sideJoints[i].accelerationBonusVect[1] += inAccY;
	}
}