#include "Character.h"
#include "../Graphics/GraphicManager.h"
#include "Behaviour/BehaviourBase.h"
#include "Behaviour/BehaviourManager.h"
#include "..\Graphics\Skeletal\SkeletalMesh.h"
#include "..\Game\InputConfiguration.h"
#include "..\Input\InputManager.h"


void cCharacter::Init(int liIdCharacter)
{
	mfYaw = 0.0f;
	mfSpeed = 0.0f;
	mfAngSpeed = 0.0f;
	mpActiveBehaviour = NULL;
	miId=liIdCharacter;
	mbJogging = false;
	//cSkeletalMesh* lpSkeletalMesh = (cSkeletalMesh*) mResourceHandle.GetResource();
	//lpSkeletalMesh->PlayAnim("Idle", 1.0f, 1.0f);
}

void cCharacter::Deinit()
{
	mObject.Deinit();
	if(mpActiveBehaviour != NULL)
	{
		mpActiveBehaviour->Deinit();
		cBehaviourManager::Get().DestroyBehaviour(mpActiveBehaviour);
	}
	mpActiveBehaviour = NULL;
}

void cCharacter::Update(float lfTimestep)
{

	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh *) mResourceHandle.GetResource();	

	if(mpActiveBehaviour != NULL)
		mpActiveBehaviour->Update(lfTimestep);

	cMatrix lWorld;
	lWorld.LoadIdentity();

	// Estas lineas de code, me volvieron loco tratando de desifrar por que diablos rotaba todo el texto del HUD! 
//	lWorld.LoadRotation(cVec3(0.0f, 1.0f, 0.0f), mfYaw);
//	lWorld.SetPosition(mPosition);
	mObject.SetLocalMatrix(lWorld);
	mObject.Update(lfTimestep);
}

void cCharacter::Render()
{
	//Componemos la matrix de world
	cMatrix lWorld;
	lWorld.LoadIdentity();

//	lWorld.LoadRotation(cVec3(0.0f, 1.0f, 0.0f), mfYaw); // Nuevamente aparecen aquí la señorita a Tomar PC! XP
//	lWorld.SetPosition(cVec3(mPosition.x, mPosition.y + 500.0f, 10000.0f));

	//Establecemos la matrix de world
	cGraphicManager::Get().SetWorldMatrix(lWorld);

	//Dibujamos el personaje
	cGraphicManager::Get().DrawPoint(cVec3(0.0f,0.0f, 0.0f), cVec3(1.0f, 0.0f, 0.0f));
	cGraphicManager::Get().DrawLine(cVec3(0.0f, 0.0f, 0.0f), cVec3(0.0f, 0.0f, 1.0f), cVec3(1.0f, 0.0f, 0.0f));

	//Dibujamos el esqueleto
	//mObject.SetWorldMatrix(lWorld);
	mObject.Render(lWorld);
}

void cCharacter::Jogging()
{
	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh *) mResourceHandle.GetResource();
	if(!mbJogging)
	{
		mbJogging = true;
		lpSkeletonMesh->PlayAnim("Jog", 1.0f, 0.1f);
		lpSkeletonMesh->StopAnim("Idle", 0.1f);
	}
}

void cCharacter::StopJogging()
{
	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh *) mResourceHandle.GetResource();
	
	if(mbJogging) 
	{
		mbJogging = false;
		lpSkeletonMesh->PlayAnim("Idle", 1.0f, 0.1f);
		lpSkeletonMesh->StopAnim("Jog", 0.1f);
	}
}

void cCharacter::PlayWave()
{
	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh *) mResourceHandle.GetResource();
	lpSkeletonMesh->PlayAnim("Wave", 1.0f, 0.1f, 0.1f);
}

void cCharacter::StopWave()
{
	cSkeletalMesh* lpSkeletonMesh = (cSkeletalMesh *) mResourceHandle.GetResource();
	lpSkeletonMesh->StopAnim("Wave", 0.1f);
}



void cCharacter::SetPosition(const cVec3 &lPosition)
{
	mPosition = lPosition;
}

void cCharacter::SetYaw(float lfYaw)
{
	mfYaw = lfYaw;
}

void cCharacter::SetSpeed( float lfSpeed)
{
	mfSpeed = lfSpeed;
}

void cCharacter::SetAngSpeed( float lfAngSpeed)
{
	mfAngSpeed = lfAngSpeed;
}

void cCharacter::SetBehaviour(cBehaviourBase * lBehaviour)
{
	mpActiveBehaviour = lBehaviour;
	mpActiveBehaviour->Init(this);
}

void cCharacter::SetResourceHandle(cResourceHandle lResourceHandle)
{
	mResourceHandle = lResourceHandle;
}

void cCharacter::SetObject(cSubmodel lObject)
{
	mObject = lObject;
}