#include "BoundingBox.h"
#include "../../Graphics/GraphicManager.h"

void cBoundingBox::Init(  cMatrix &Transformation, cVec3 & Min, cVec3 & Max)
{
	mcTransformation = Transformation;
	
		
	MinInit = Min;
	MaxInit = Max;
	CenterInit = cVec3((Min.x + Max.x)*0.5f, (Min.y + Max.y)*0.5f, (Min.z + Max.z)*0.5f);
	P1Init.x = MaxInit.x;
	P1Init.y = MaxInit.y;
	P1Init.z = MaxInit.z;

    P2Init.x = MaxInit.x;
	P2Init.y = MinInit.y;
	P2Init.z = MaxInit.z;

    P3Init.x = MinInit.x;
	P3Init.y = MinInit.y;
	P3Init.z = MaxInit.z;

    P4Init.x = MinInit.x;
	P4Init.y = MaxInit.y;
	P4Init.z = MaxInit.z;

	P5Init.x = MaxInit.x;
	P5Init.y = MaxInit.y;
	P5Init.z = MinInit.z;

    P6Init.x = MaxInit.x;
	P6Init.y = MinInit.y;
	P6Init.z = MinInit.z;

    P7Init.x = MinInit.x;
	P7Init.y = MinInit.y;
	P7Init.z = MinInit.z;

    P8Init.x = MinInit.x;
	P8Init.y = MaxInit.y;
	P8Init.z = MinInit.z;

}
bool cBoundingBox::CheckPointCollision( cVec3 & lrObjPosition )
{
	return	lrObjPosition.x <= Max.x && lrObjPosition.x >= Min.x &&
			lrObjPosition.y <= Max.y && lrObjPosition.y >= Min.y &&
			lrObjPosition.z <= Max.z && lrObjPosition.z >= Min.z ;
}

bool cBoundingBox::CheckCollision(cCollision &lrBB)
{

	return 
		CheckPointCollision(((cBoundingBox &)lrBB).FakeP1) ||
		CheckPointCollision(((cBoundingBox &)lrBB).FakeP2) ||
		CheckPointCollision(((cBoundingBox &)lrBB).FakeP3) ||
		CheckPointCollision(((cBoundingBox &)lrBB).FakeP4) ||
		CheckPointCollision(((cBoundingBox &)lrBB).FakeP5) ||
		CheckPointCollision(((cBoundingBox &)lrBB).FakeP6) ||
		CheckPointCollision(((cBoundingBox &)lrBB).FakeP7) ||
		CheckPointCollision(((cBoundingBox &)lrBB).FakeP8) ||
		lrBB.CheckPointCollision(FakeP1) ||
		lrBB.CheckPointCollision(FakeP2) ||
		lrBB.CheckPointCollision(FakeP3) ||
		lrBB.CheckPointCollision(FakeP4) ||
		lrBB.CheckPointCollision(FakeP5) ||
		lrBB.CheckPointCollision(FakeP6) ||
		lrBB.CheckPointCollision(FakeP7) ||
		lrBB.CheckPointCollision(FakeP8) ||
		lrBB.CheckPointCollision(this->Center)||
		CheckPointCollision(((cBoundingBox &)lrBB).Center);
}

cVec3 cBoundingBox::Transform ( cMatrix &lWorld, cVec3 Point)
{
 
   Scale = mcTransformation.rows[0].x;
   cVec3 result;
   result.x = lWorld.rows[3].x + 
		      lWorld.rows[0].x * Scale * Point.x +
		      lWorld.rows[1].x * Scale * Point.y +
     		  lWorld.rows[2].x * Scale * Point.z;
	
  result.y = lWorld.rows[3].y + 
		      lWorld.rows[0].y * Scale * Point.x +
		      lWorld.rows[1].y * Scale * Point.y +
     		  lWorld.rows[2].y * Scale * Point.z;

  result.z = lWorld.rows[3].z + 
		      lWorld.rows[0].z * Scale * Point.x +
		      lWorld.rows[1].z * Scale * Point.y +
     		  lWorld.rows[2].z * Scale * Point.z;
  return result;

}

void cBoundingBox::Update( cMatrix &lWorld)
{

	P1 = Transform(lWorld,P1Init);
    P2 = Transform(lWorld,P2Init);
    P3 = Transform(lWorld,P3Init);
    P4 = Transform(lWorld,P4Init);
	P5 = Transform(lWorld,P5Init);
    P6 = Transform(lWorld,P6Init);
    P7 = Transform(lWorld,P7Init);
    P8 = Transform(lWorld,P8Init);

	
	//Fake BB for make it easier on collision
	Max.x= -10000.0f;
	if (P1.x>Max.x) Max.x=P1.x;
	if (P2.x>Max.x) Max.x=P2.x;
	if (P3.x>Max.x) Max.x=P3.x;
	if (P4.x>Max.x) Max.x=P4.x;
	if (P5.x>Max.x) Max.x=P5.x;
	if (P6.x>Max.x) Max.x=P6.x;
	if (P7.x>Max.x) Max.x=P7.x;
	if (P8.x>Max.x) Max.x=P8.x;
	Max.y= -10000.0f;
    if (P1.y>Max.y) Max.y=P1.y;
	if (P2.y>Max.y) Max.y=P2.y;
	if (P3.y>Max.y) Max.y=P3.y;
	if (P4.y>Max.y) Max.y=P4.y;
	if (P5.y>Max.y) Max.y=P5.y;
	if (P6.y>Max.y) Max.y=P6.y;
	if (P7.y>Max.y) Max.y=P7.y;
	if (P8.y>Max.y) Max.y=P8.y;
	Max.z=-10000.0f;
    if (P1.z>Max.z) Max.z=P1.z;
	if (P2.z>Max.z) Max.z=P2.z;
	if (P3.z>Max.z) Max.z=P3.z;
	if (P4.z>Max.z) Max.z=P4.z;
	if (P5.z>Max.z) Max.z=P5.z;
	if (P6.z>Max.z) Max.z=P6.z;
	if (P7.z>Max.z) Max.z=P7.z;
	if (P8.z>Max.z) Max.z=P8.z;

	Min.x=10000.0f;
	if (P1.x<Min.x) Min.x=P1.x;
	if (P2.x<Min.x) Min.x=P2.x;
	if (P3.x<Min.x) Min.x=P3.x;
	if (P4.x<Min.x) Min.x=P4.x;
	if (P5.x<Min.x) Min.x=P5.x;
	if (P6.x<Min.x) Min.x=P6.x;
	if (P7.x<Min.x) Min.x=P7.x;
	if (P8.x<Min.x) Min.x=P8.x;
	Min.y=10000.0f;
    if (P1.y<Min.y) Min.y=P1.y;
	if (P2.y<Min.y) Min.y=P2.y;
	if (P3.y<Min.y) Min.y=P3.y;
	if (P4.y<Min.y) Min.y=P4.y;
	if (P5.y<Min.y) Min.y=P5.y;
	if (P6.y<Min.y) Min.y=P6.y;
	if (P7.y<Min.y) Min.y=P7.y;
	if (P8.y<Min.y) Min.y=P8.y;
	Min.z=10000.0f;
    if (P1.z<Min.z) Min.z=P1.z;
	if (P2.z<Min.z) Min.z=P2.z;
	if (P3.z<Min.z) Min.z=P3.z;
	if (P4.z<Min.z) Min.z=P4.z;
	if (P5.z<Min.z) Min.z=P5.z;
	if (P6.z<Min.z) Min.z=P6.z;
	if (P7.z<Min.z) Min.z=P7.z;
	if (P8.z<Min.z) Min.z=P8.z;

	Center = cVec3((Min.x + Max.x)*0.5f, (Min.y + Max.y)*0.5f, (Min.z + Max.z)*0.5f);

	FakeP1 = cVec3(Max.x,Max.y,Max.z);
	FakeP2 = cVec3(Max.x,Min.y,Max.z);
	FakeP3 = cVec3(Min.x,Min.y,Max.z);
	FakeP4 = cVec3(Min.x,Max.y,Max.z);
	
	FakeP5 = cVec3(Max.x,Max.y,Min.z);
	FakeP6 = cVec3(Max.x,Min.y,Min.z);
	FakeP7 = cVec3(Min.x,Min.y,Min.z);
	FakeP8 = cVec3(Min.x,Max.y,Min.z);

	// Re-iniciar y actualizar valores, solo por tener todos los calculos juntos en update
}

void cBoundingBox::Render()
{
	//Don't remove this drawline (are for debugging)
	/*cGraphicManager::Get().DrawAxis();
*/
	cMatrix lWorld;
	cGraphicManager::Get().SetWorldMatrix( lWorld.LoadIdentity() );

	cVec3 & lrColor = cVec3( 1.0f,0.0f,0.0f); // Red Color
/*
	cVec3 CenterLessX = Center;
    cVec3 CenterPlusX = Center;
	CenterLessX.x-=4.0;
	CenterPlusX.x+=4.0;
	cVec3 CenterLessY = Center;
    cVec3 CenterPlusY = Center;
	CenterLessY.y-=4.0;
	CenterPlusY.y+=4.0;


	cGraphicManager::Get().DrawLine( CenterLessX, CenterPlusX , lrColor );
    cGraphicManager::Get().DrawLine( CenterLessY, CenterPlusY , lrColor );*/
	//  Real BB
	
	/*
	cGraphicManager::Get().DrawLine( P1, P2 , lrColor );
	cGraphicManager::Get().DrawLine( P2, P3, lrColor );
	cGraphicManager::Get().DrawLine( P3, P4, lrColor );
	cGraphicManager::Get().DrawLine( P4, P1, lrColor );

	cGraphicManager::Get().DrawLine( P5, P6, lrColor );
	cGraphicManager::Get().DrawLine( P6, P7, lrColor );
	cGraphicManager::Get().DrawLine( P7, P8, lrColor );
	cGraphicManager::Get().DrawLine( P8, P5, lrColor );

	cGraphicManager::Get().DrawLine( P1, P5, lrColor );
	cGraphicManager::Get().DrawLine( P2, P6, lrColor );
	cGraphicManager::Get().DrawLine( P3, P7, lrColor );
	cGraphicManager::Get().DrawLine( P4, P8, lrColor );
*/
//Fake BB	
/*	cGraphicManager::Get().DrawLine( FakeP1, FakeP2, lrColor );
	cGraphicManager::Get().DrawLine( FakeP2, FakeP3, lrColor );
	cGraphicManager::Get().DrawLine( FakeP3, FakeP4, lrColor );
	cGraphicManager::Get().DrawLine( FakeP4, FakeP1, lrColor );
	
	cGraphicManager::Get().DrawLine( FakeP5, FakeP6, lrColor );
	cGraphicManager::Get().DrawLine( FakeP6, FakeP7, lrColor );
	cGraphicManager::Get().DrawLine( FakeP7, FakeP8, lrColor );
	cGraphicManager::Get().DrawLine( FakeP8, FakeP5, lrColor );

	cGraphicManager::Get().DrawLine( FakeP1, FakeP5, lrColor );
	cGraphicManager::Get().DrawLine( FakeP2, FakeP6, lrColor );
	cGraphicManager::Get().DrawLine( FakeP3, FakeP7, lrColor );
	cGraphicManager::Get().DrawLine( FakeP4, FakeP8, lrColor );
*/

}
 