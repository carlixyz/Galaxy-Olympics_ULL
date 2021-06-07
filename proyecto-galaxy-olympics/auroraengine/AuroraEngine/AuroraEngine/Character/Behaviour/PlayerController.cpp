#include "PlayerController.h"
#include <string>
#include "..\..\Input\InputManager.h"
#include "..\..\Game\InputConfiguration.h"

//Inicializa el atributo
void cPlayerController::Init(cCharacter *lpCharacter)
{
	mpCharacter = lpCharacter;
}

//Vacío (NO llama al Deinit del personaje)
void cPlayerController::Deinit()
{
}

//Implementa el comportamiento de moverse en función de las teclas
//pulsadas
void cPlayerController::Update(float lfTimestep)
{
	if (BecomePressed(eIA_PlayJog))
	{
		mpCharacter->Jogging();
	}
	else if (BecomePressed(eIA_StopJog))
	{
		mpCharacter->StopJogging();
	}

	if (BecomePressed(eIA_PlayWave))
	{
		mpCharacter->PlayWave();
	} 
	else if( BecomePressed(eIA_StopWave))
	{
		mpCharacter->StopWave();
	}
	
	if (IsPressed(eIA_MoveUp) )
	{
		cVec3 lCurrentPosition = mpCharacter->GetPosition();
		float lfDisplacement = mpCharacter->GetSpeed() * lfTimestep;
		cVec3 lFront = mpCharacter->GetFront();
		cVec3 lNewPosition = lCurrentPosition + (lfDisplacement * lFront);
		mpCharacter->SetPosition(lNewPosition);
	}
	if (IsPressed(eIA_MoveRight))
	{
		float lfYaw = mpCharacter->GetYaw();
		float lfAngleDisplacement = mpCharacter->GetAngSpeed() * lfTimestep;
		mpCharacter->SetYaw(lfYaw + lfAngleDisplacement);
	}
	if (IsPressed(eIA_MoveLeft))
	{
		float lfYaw = mpCharacter->GetYaw();
		float lfAngleDisplacement = mpCharacter->GetAngSpeed() * lfTimestep;
		mpCharacter->SetYaw(lfYaw - lfAngleDisplacement);
	}
}