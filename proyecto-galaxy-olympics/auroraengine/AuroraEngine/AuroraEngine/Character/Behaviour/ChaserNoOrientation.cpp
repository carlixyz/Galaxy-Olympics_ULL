#include "ChaserNoOrientation.h"
#include <string>

void cChaserNoOrientation::Init(cCharacter *lpCharacter)
{
	mpCharacter = lpCharacter;
	mTarget = cVec3(0.0f, 0.0f, 0.0f);
}

void cChaserNoOrientation::Deinit()
{
	mpCharacter = NULL;
}

void cChaserNoOrientation::Update(float lfTimestep)
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
}

void cChaserNoOrientation::SetTarget(cVec3 lTarget)
{
	mTarget = lTarget;
}