#include "Camera.h"
#include "../Utility/Debug.h"

void cCamera::Init() 
{
	mView.LoadIdentity();
	mProj.LoadIdentity();
	mViewProj.LoadIdentity();
}

void cCamera::SetLookAt( const cVec3 &lvPosition, const cVec3 &lvTarget, const cVec3 &lvUpWorld )
{
	mView.LoadLookAt(lvPosition, lvTarget, lvUpWorld);
	RefreshViewProj();
}
void cCamera::SetYaw(float rad)
{
	cMatrix lYaw ; 
	mView *= lYaw.LoadRotation(mView.GetUp(), rad ) ;  
}

void cCamera::SetPitch(float rad)
{
	cMatrix lRot ; 
	mView *= lRot.LoadRotation(cVec3(1.0f,0.0f,0.0f), rad ) ;
}

void cCamera::SetOrtho( float lfLeft, float lfRight, float lfBottom, float lfTop, float lfZNear, float lfZNFar )
{
	mProj.LoadOrtho(lfLeft, lfRight, lfBottom, lfTop, lfZNear, lfZNFar);
	RefreshViewProj();
}

void cCamera::SetPerspective( float lfFOVY_Rad, float lfAspect, float lfZNear, float lfZFar)
{
	mProj.LoadPerpective(lfFOVY_Rad, lfAspect, lfZNear, lfZFar);
	RefreshViewProj();
}