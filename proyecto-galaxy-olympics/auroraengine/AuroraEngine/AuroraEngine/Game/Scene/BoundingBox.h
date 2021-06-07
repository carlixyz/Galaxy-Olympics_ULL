#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "../../Libraries/MathLib/MathLib.h"
#include "Collision.h"

struct cBoundingBox : public  cCollision
{
	cVec3 Max;
	cVec3 Min;
	cVec3 Center;

	cVec3 MaxInit;
	cVec3 MinInit;
	cVec3 CenterInit;

	cVec3 FakeP1, FakeP2, FakeP3, FakeP4, FakeP5, FakeP6, FakeP7, FakeP8;
	cVec3 P1, P2, P3, P4, P5, P6, P7, P8;
	cVec3 P1Init, P2Init, P3Init, P4Init, P5Init, P6Init, P7Init, P8Init;

	float Scale;
	void Init( cMatrix &Transformation, cVec3 & Min, cVec3 & Max);
	void Update(cMatrix &lWorld);						// Actualiza la posición de caja de colisión
	void Render();										// dibuja caja colision, quita rendimiento, usar solo para debug!
	bool CheckPointCollision( cVec3 & lrObjPosition );	// Toma la posición de otro objeto cualquier y verifica si hay collision
	bool CheckCollision( cCollision & lrBB );	
	cVec3 Transform ( cMatrix &lWorld, cVec3 Point);
};


#endif