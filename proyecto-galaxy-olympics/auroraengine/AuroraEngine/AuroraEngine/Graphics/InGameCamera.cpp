#include "IngameCamera.h"

#include "../Game/Scene/ObjectManager.h"
#include "../Game/Game.h"

#include "../Game/InputConfiguration.h"
#include "../Input/InputManager.h"

//#include "../Utility/Debug.h"


#define kfCAMERA_OFFSET_Y (float)(cGame::Get().mProperties.muiHeight>>6)
#define kfCAMERA_OFFSET_X (float)(cGame::Get().mProperties.muiWidth>>6)

void cIngameCamera::Init() 
{
	this->mfCamera_PlayerDist =  -15.0f;
}

void cIngameCamera::Update(float lfTimestep)
{	

	// 1) Conseguír puntero y posición del Player
	cPlayer * lpPlayer = cObjectManager::Get().GetPlayer();

 if (lpPlayer != NULL )// Checar que el Player existe
 {
	cMatrix & lrPMatrix = lpPlayer->GetMatrix();

	// 2) Orientar target = posición eje 'Z' de player 
	cVec3 & lvTarget = cVec3( 0.0f, 0.0f, lrPMatrix.GetPosition().z );

	// 3) ajustar posición eje 'Z' camara = posición de player + separación preestablecida
	cVec3 & lvCameraPos = cVec3( 0.0f, 0.0f, lvTarget.z + mfCamera_PlayerDist );


	// 3.5) le damos un poco más de realismo con un desplazamiento suave de camara
		lvCameraPos.x += lrPMatrix.GetPosition().x *-0.35f ;
		lvCameraPos.y += lrPMatrix.GetPosition().y   *-0.35f;

	//	lvTarget.x += lrPMatrix.GetPosition().x ;
	//	lvTarget.y += lrPMatrix.GetPosition().y  ;


	// 4) actualizar...
	this->SetLookAt( lvCameraPos, lvTarget );
 }
}

