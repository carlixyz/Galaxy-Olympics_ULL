#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include "Collision.h"

struct cBoundingSphere 
	: public cCollision 
{
	void Init(cMatrix &Transformation,cVec3 & lvCenterPos, cVec3 & lvMax = cVec3(1.0f, 1.0f,1.0f) );// 3er parametro no es necesario

	void Update(cMatrix &lWorld);						// Actualiza  posición de colisión
	void Render();										// Pinta colision, lastra rendimiento, usar solo en debug!

	bool CheckPointCollision( cVec3 & lrObjPosition ) ;	// Toma posición de otro objeto y verifica
	bool CheckCollision( cCollision & lrBB ) ;			// Toma Colision de otro objeto y verifica

	cVec3 Transform ( cMatrix &lWorld, cVec3 Point); //Maybe should be in parent class
	cVec3 mvMax; //Maximum in each axis for radius
	cVec3 mvMaxInit;
	cVec3 mvCenterInit; // Initial Position of the center
	cVec3 mvCenter; //Position of the center
	float mfRadius;
};

#endif