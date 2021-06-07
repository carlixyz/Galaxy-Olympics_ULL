#ifndef DEBUG_CAMERA_H
#define DEBUG_CAMERA_H

#include "Camera.h"


class cDebugCamera : public  cCamera // Developer´s Camera
{
public:
	 void Init(); 
	 void Update(float lfTimestep);

private:
	cVec3 mOld_pos;
	cVec3 mNew_pos;

};
#endif 
