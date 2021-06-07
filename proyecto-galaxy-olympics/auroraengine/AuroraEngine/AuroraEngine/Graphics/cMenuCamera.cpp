#include "cMenuCamera.h"

void cMenuCamera::Init()
{
	lfAngle = 1.6f;
	this->SetLookAt( cVec3(0.0f, 15.0f, -50.0f), cVec3(0.0f, 12.f, 0.f) );
}

void cMenuCamera::Update(float lfTimestep)
{
	lfAngle += lfTimestep * 0.1f;
	this->SetLookAt( cVec3(0.0f, 15.0f, -50.0f), cVec3(0.0f+90*cos(lfAngle), 12.0f, 0.f+90*sin(lfAngle)) );
}