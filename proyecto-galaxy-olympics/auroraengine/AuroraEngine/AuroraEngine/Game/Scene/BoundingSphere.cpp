#include "BoundingSphere.h"
#include "../../Graphics/GraphicManager.h"

void cBoundingSphere::Init(cMatrix &Transformation, cVec3 &lvCenterPos, cVec3 &lvMax )
{
	mcTransformation = Transformation;
	mvMax = lvMax;
	mvCenterInit = lvCenterPos;

	mvMaxInit.x = lvMax.x - lvCenterPos.x;
	mvMaxInit.y = lvMax.y - lvCenterPos.y;
	mvMaxInit.z = lvMax.z - lvCenterPos.z;

	//Seek the maximum to establish the radius
	if ((mvMaxInit.x>= mvMaxInit.y) && (mvMaxInit.x>=mvMaxInit.z))
		mfRadius = mvMaxInit.y; //mfRadius = mvMaxInit.x; 
	else if ((mvMaxInit.y>= mvMaxInit.x) && (mvMaxInit.y>=mvMaxInit.z))
		mfRadius = mvMaxInit.y;
	else
		mfRadius = mvMaxInit.z;

}

void cBoundingSphere::Update(cMatrix &lWorld)
{
	mvCenter = Transform(lWorld, mvCenterInit);
	
	mvMax.x =  mvMaxInit.x * mcTransformation.rows[0].x;
	mvMax.y =  mvMaxInit.y * mcTransformation.rows[0].y;
	mvMax.z =  mvMaxInit.z * mcTransformation.rows[0].z;

	//Seek the maximum to establish the radius
	if ((mvMax.x>= mvMax.y) && (mvMax.x>=mvMax.z))
		mfRadius = mvMax.x;
	else if ((mvMax.y>= mvMax.x) && (mvMax.y>=mvMax.z))
		mfRadius = mvMax.y;
	else
		mfRadius = mvMax.z;
}

void cBoundingSphere::Render()
{
	mfRadius = 5;
	cMatrix lWorld;
	cGraphicManager::Get().SetWorldMatrix( lWorld.LoadIdentity() );

	cVec3 & lrColor = cVec3( 1.0f,0.0f,0.0f); // Red Color

	cVec3 CenterLessX = mvCenter;
    cVec3 CenterPlusX = mvCenter;
	CenterLessX.x-= mfRadius;
	CenterPlusX.x+= mfRadius;
	cVec3 CenterLessY = mvCenter;
    cVec3 CenterPlusY = mvCenter;
	CenterLessY.y -= mfRadius;
	CenterPlusY.y += mfRadius;
	cVec3 CenterLessZ = mvCenter;
    cVec3 CenterPlusZ = mvCenter;
	CenterLessZ.z -= mfRadius;
	CenterPlusZ.z += mfRadius;

	cGraphicManager::Get().DrawLine( CenterLessX, CenterPlusX , lrColor );
    cGraphicManager::Get().DrawLine( CenterLessY, CenterPlusY , lrColor );
	cGraphicManager::Get().DrawLine( CenterLessZ, CenterPlusZ , lrColor );
    
}

bool cBoundingSphere::CheckPointCollision(cVec3 &lrObjPosition)
{
	return false;
}

bool cBoundingSphere::CheckCollision(cCollision &lrCol)
{
	return false;
}

cVec3 cBoundingSphere::Transform ( cMatrix &lWorld, cVec3 Point)
{
 
   float Scale = mcTransformation.rows[0].x;
   cVec3 result;
   result.x = lWorld.rows[3].x + 
		      lWorld.rows[0].x * Scale * Point.x +
		      lWorld.rows[1].x * Point.y +
     		  lWorld.rows[2].x * Point.z;
	
  result.y = lWorld.rows[3].y + 
		      lWorld.rows[0].y * Point.x +
		      lWorld.rows[1].y * Scale * Point.y +
     		  lWorld.rows[2].y * Point.z;

  result.z = lWorld.rows[3].z + 
		      lWorld.rows[0].z * Point.x +
		      lWorld.rows[1].z * Point.y +
     		  lWorld.rows[2].z * Scale * Point.z;
  return result;

}