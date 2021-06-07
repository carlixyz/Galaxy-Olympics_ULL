#include "ChaserSnapOrientation.h"
#include <string>

void cChaserSnapOrientation::Init(cCharacter *lpCharacter)
{
	mpCharacter = lpCharacter;
	mTarget = cVec3(3.8f, 0.0f, -3.4f);
}

void cChaserSnapOrientation::Deinit()
{
	mpCharacter = NULL;
}

void cChaserSnapOrientation::Update(float lfTimestep)
{
	cVec3 lDistanceVec = mTarget - mpCharacter->GetPosition();

	float lfDisplacement = mpCharacter->GetSpeed() * lfTimestep;

	if (lfDisplacement >= lDistanceVec.Length())
	{
		mpCharacter->SetPosition(mTarget);
	} 
	else 
	{
		cVec3 lNewPosition = mpCharacter->GetPosition() + (lfDisplacement * lDistanceVec.Normalize());
		mpCharacter->SetPosition(lNewPosition);
	}

	if(lDistanceVec.Length() > 0.01f)
	{
		mpCharacter->SetYaw(atan2f(lDistanceVec.x, lDistanceVec.z));
	}
}

void cChaserSnapOrientation::SetTarget(cVec3 lTarget)
{
	mTarget = lTarget;
}