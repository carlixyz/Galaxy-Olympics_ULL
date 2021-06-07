#pragma once
#include "camera.h"

class cMenuCamera :
	public cCamera
{
public:
	void Init();
	void Update(float lfTimestep);
private:
	float lfAngle;
};
