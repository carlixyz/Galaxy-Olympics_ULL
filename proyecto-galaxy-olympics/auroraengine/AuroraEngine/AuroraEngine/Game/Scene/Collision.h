#ifndef COLLISION_H
#define COLLISION_H

#include "../../Libraries/MathLib/MathLib.h"

struct cBoundingBox;

struct cCollision 
{
	cMatrix mcTransformation;
	// Implementar en según tipo de colision 
	virtual void Init( cMatrix &Transformation, cVec3 & Param1, cVec3 & Param2 ) =0;

	virtual void Update(cMatrix &lWorld)	= 0;					// Actualiza  posición de colisión
	virtual void Render()					= 0;					// Pinta colision, lastra rendimiento, usar solo en debug!

	virtual bool CheckPointCollision( cVec3 & lrObjPosition )	=0;	// Toma  y verifica posición con otro objeto
	virtual bool CheckCollision( cCollision & lrBB  )			=0;	// Toma  y verifica Colision con otro objeto
};

#endif