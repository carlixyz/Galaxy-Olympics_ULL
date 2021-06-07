#include "Patrol.h"
#include "BehaviourManager.h"
#include <cassert>
#include "../../Lua/LuaManager.h"
#include "../CharacterManager.h"
#include "../../Game/Game.h"

void cPatrol::Init(cCharacter *lpCharacter)
{
	mpCharacter = lpCharacter;
	mTargetWaypoint = lpCharacter->GetPosition();
	mpBehaviour = new cChaserWithOrientation();
	mpBehaviour->Init(mpCharacter);
}

void cPatrol::Deinit()
{
	if(mpBehaviour != NULL)
	{
		mpBehaviour->Deinit();
		cBehaviourManager::Get().DestroyBehaviour(mpBehaviour);
	}
	mpBehaviour = NULL;

}

void cPatrol::Update(float lfTimestep)
{
	cCharacter * lEnemy = cCharacterManager::Get().getCharacter(enemyId);
	
	assert(lEnemy);	

	cVec3 lDistanceVec = lEnemy->GetPosition() - mpCharacter->GetPosition();
	if(lDistanceVec.Length() < mfAwareRadius)
	{
		mpBehaviour->SetTarget(lEnemy->GetPosition());
		mpBehaviour->Update(lfTimestep);
		if (mpBehaviour->EndPointReached()){
			cGame::Get().SetFinished(true);
		}
	}
	else 
	{
		mpBehaviour->SetTarget(mTargetWaypoint);
		mpBehaviour->Update(lfTimestep);

		if (mpBehaviour->EndPointReached()) {
			bool lbOk = cLuaManager::Get().CallLua("NextEndPoint", mpCharacter->GetId(), (int*) NULL);
		}
	}	
}

void cPatrol::SetTargetWaypoint( cVec3 lTargetWaypoint )
{
	mTargetWaypoint = lTargetWaypoint;
}

void cPatrol::SetAwareRadius( float lfAwareRadius)
{
	mfAwareRadius = lfAwareRadius;	
}

void cPatrol::SetEnemyId( int liEnemyId )
{
	enemyId = liEnemyId;
}