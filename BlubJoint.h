#ifndef BLUBJOINT_H
#define BLUBJOINT_H
#include <iostream> 
//this is the class declaration
using namespace std;
class BlubJoint
{
public:
	double pos[2];
	double accelerationVect[2];
	double accelerationBonusVect[2];
	double acceleration = 0;
	double velocityVect[2];
	double velocity = 0;
	int nrOfConnectedJoints = 0;
	BlubJoint** connectedJoints = NULL;
	double* connectedJointsLengths = NULL;
	BlubJoint();
	BlubJoint(double, double);
	void move(int);
	void addJoint(BlubJoint* connectedJoint);
	void addJoint(BlubJoint* connectedJoint, double);
	void getAcceleration();
	void operator=(BlubJoint&);
};
#endif
