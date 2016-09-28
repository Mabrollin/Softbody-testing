#include "BlubJoint.h"

using namespace std;

BlubJoint::BlubJoint()
{
	pos[0] = 0;
	pos[1] = 0;
	velocityVect[0] = 0;
	velocityVect[1] = 0;
	accelerationVect[0] = 0;
	accelerationVect[1] = 0;
	accelerationBonusVect[0] = 0;
	accelerationBonusVect[1] = 0;
}
BlubJoint::BlubJoint(double posX, double posY)
{
	pos[0] = posX;
	pos[1] = posY;
	velocityVect[0] = 0;
	velocityVect[1] = 0;
	accelerationVect[0] = 0;
	accelerationVect[1] = 0;
	accelerationBonusVect[0] = 0;
	accelerationBonusVect[1] = 0;
	
}
void BlubJoint::move(int duration)
{

	velocityVect[0] -= 2 * velocityVect[0] * duration / 1000000.0;
	velocityVect[1] -= 2 * velocityVect[1] * duration / 1000000.0;
	
	velocityVect[0] += (accelerationVect[0]  + accelerationBonusVect[0])* duration / 1000000.0;
	velocityVect[1] += (accelerationVect[1] + accelerationBonusVect[1])* duration / 1000000.0;
	
	pos[0] += velocityVect[0] * duration / 1000000.0;
	pos[1] += velocityVect[1] * duration / 1000000.0;

	if (pos[0] < 0)
	{
		pos[0] = 0;
		
		
	}
	if (pos[1] < 0)
	{
		pos[1] = 0;
		
		
	}
	if (pos[0] > 800)
	{
		pos[0] = 800;
		
		
	}
	if (pos[1] > 600)
	{
		pos[1] = 600;
		
		
	}
}
void BlubJoint::addJoint(BlubJoint* newJointPtr)
{
	int i;
	BlubJoint** temp1 = connectedJoints;
	connectedJoints = new BlubJoint*[nrOfConnectedJoints+1];
	for (i = 0; i < nrOfConnectedJoints; i++)
	{
		connectedJoints[i] = temp1[i];
	}
	connectedJoints[nrOfConnectedJoints] = newJointPtr;
	

	double* temp2 = connectedJointsLengths;
	connectedJointsLengths = new double [nrOfConnectedJoints + 1];
	for (i = 0; i < nrOfConnectedJoints; i++)
	{
		connectedJointsLengths[i] = temp2[i];
	}
	connectedJointsLengths[nrOfConnectedJoints] = std::sqrt(
		(pos[0] - connectedJoints[nrOfConnectedJoints]->pos[0])*(pos[0] - connectedJoints[nrOfConnectedJoints]->pos[0]) +
		(pos[1] - connectedJoints[nrOfConnectedJoints]->pos[1])*(pos[1] - connectedJoints[nrOfConnectedJoints]->pos[1]));
	nrOfConnectedJoints++;
}
void BlubJoint::addJoint(BlubJoint* newJointPtr, double diameter)
{
	int i;
	BlubJoint** temp1 = connectedJoints;
	connectedJoints = new BlubJoint*[nrOfConnectedJoints + 1];
	for (i = 0; i < nrOfConnectedJoints; i++)
	{
		connectedJoints[i] = temp1[i];
	}
	connectedJoints[nrOfConnectedJoints] = newJointPtr;


	double* temp2 = connectedJointsLengths;
	connectedJointsLengths = new double[nrOfConnectedJoints + 1];
	for (i = 0; i < nrOfConnectedJoints; i++)
	{
		connectedJointsLengths[i] = temp2[i];
	}
	connectedJointsLengths[nrOfConnectedJoints] = diameter;
	nrOfConnectedJoints++;
}
void BlubJoint::getAcceleration()
{
	double actLength;
	double deltLength[2] = { 0, 0 };
	accelerationVect[0] = 0;
	accelerationVect[1] = 0;
	acceleration =1000;


	for (int i = 0; i < nrOfConnectedJoints; i++)
	{
		actLength = std::sqrt(
			(pos[0] - connectedJoints[i]->pos[0])*(pos[0] - connectedJoints[i]->pos[0])
			+ (pos[1] - connectedJoints[i]->pos[1])*(pos[1] - connectedJoints[i]->pos[1])
			);
		if (connectedJointsLengths[i] - actLength > 1.2)
		{
	
			deltLength[0] += (pos[0] - connectedJoints[i]->pos[0]);
			deltLength[1] += (pos[1] - connectedJoints[i]->pos[1]);
		}
		else if (connectedJointsLengths[i] - actLength < -1.2)
		{
			deltLength[0] -=  (pos[0] - connectedJoints[i]->pos[0]);
			deltLength[1] -=  (pos[1] - connectedJoints[i]->pos[1]);
		}
		else
		{
			
		}
	}
	actLength = std::sqrt(deltLength[0] * deltLength[0] + deltLength[1] * deltLength[1]);
	if (actLength != 0.0){
		accelerationVect[0] = deltLength[0] / actLength;
		accelerationVect[1] = deltLength[1] / actLength;
		accelerationVect[0] *= acceleration;
		accelerationVect[1] *= acceleration;
	}
	else
	{

	}
	
}
void BlubJoint::operator=(BlubJoint& cpyJoint)
{
	int i;
	pos[0] = cpyJoint.pos[0];
	pos[1] = cpyJoint.pos[1];
	/*accelerationVect[0] = cpyJoint.accelerationVect[0];
	accelerationVect[1] = cpyJoint.accelerationVect[0];
	accelerationBonusVect[0] = cpyJoint.accelerationBonusVect[0];
	accelerationBonusVect[1] = cpyJoint.accelerationBonusVect[0];
	acceleration = cpyJoint.acceleration;
	velocityVect[0] = cpyJoint.velocityVect[0];
	velocityVect[1] = cpyJoint.velocityVect[1];
	velocity = cpyJoint.velocity;*/
	
	//for (i = 0; i < cpyJoint.nrOfConnectedJoints; i++)
	//{
	//	this->addJoint(cpyJoint.connectedJoints[i]);
	//}
}