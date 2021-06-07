#include "ChaserWithOrientation.h"
#include "../../Libraries/MathLib/MathUtils/Plane.h"
#include <string>

void cChaserWithOrientation::Init(cCharacter *lpCharacter)
{
	mpCharacter = lpCharacter;
	mTarget = cVec3(0.0f, 0.0f, 0.0f);
}

void cChaserWithOrientation::Deinit()
{
	mpCharacter = NULL;
}

void cChaserWithOrientation::Update(float lfTimestep)
{
	cVec3 lDistanceVec = mTarget - mpCharacter->GetPosition();
	
	if (EndPointReached())
	{
		mpCharacter->SetPosition(mTarget);
	}
	else{

	float lfDisplacement = mpCharacter->GetSpeed() * lfTimestep;

	float lfCosAngle = Dot(mpCharacter->GetFront(), lDistanceVec.Normalize());

	if(lfCosAngle > 1.0f) lfCosAngle = 1.0f;
	else if (lfCosAngle < -1.0f) lfCosAngle = -1.0f;

	float lfAngle = acosf(lfCosAngle);
	float lfAngleDisplacement = mpCharacter->GetAngSpeed() * lfTimestep;

	if(lfAngle > lfAngleDisplacement)
		lfAngle = lfAngleDisplacement;
	
	cPlane lPlane;
	cVec3 lVecRight = mpCharacter->GetRight();
	cVec3 lCurrentPosition = mpCharacter->GetPosition(); //Posicion actual del perseguidor
	float lfYaw = mpCharacter->GetYaw();
	lPlane.Init(lVecRight, lCurrentPosition);

	if(lPlane.PointTest(mTarget) < 0.0f)
		mpCharacter->SetYaw(lfYaw + lfAngle);
	else
		mpCharacter->SetYaw(lfYaw - lfAngle);

	cVec3 lNewPosition = lCurrentPosition + (lfDisplacement * mpCharacter->GetFront());
	mpCharacter->SetPosition(lNewPosition);	
	}
}

bool cChaserWithOrientation::EndPointReached()
{
	cVec3 lDistanceVec = mTarget - mpCharacter->GetPosition();
	
	return lDistanceVec.Length() < 0.1f;
}

void cChaserWithOrientation::SetTarget(cVec3 lTarget)
{
	mTarget = lTarget;
}