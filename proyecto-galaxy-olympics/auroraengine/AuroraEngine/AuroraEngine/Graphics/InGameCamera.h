#ifndef INGAME_CAMERA_H
#define INGAME_CAMERA_H

#include "Camera.h"

class cIngameCamera : public  cCamera // Developer´s Camera
{
public:

	void Init(); 
	 void Update(float lfTimestep);

private:
	cVec3 mvCameraPos;
//	cVec3 mvPlayerPos;
	float mfCamera_PlayerDist; // Separación entre jugador y Camara

};
#endif 
// GL_MODELVIEW = WorldMatrix * ViewMatrix
// GL_PROJECTION = ProyectionMatrix