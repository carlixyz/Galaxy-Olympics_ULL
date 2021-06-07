#include "Player.h"

#include "../../Input/InputManager.h"
#include "../../Game/Game.h"
#include "../../Game/InputConfiguration.h"
#include "../../Game/SoundManager.h"
#include "../../Utility/FileUtils.h"
#include "../../Graphics/Fonts/FontManager.h"
//#include "../../Utility/Debug.h"

#define kfCRASH_DELAY 2.5f

#define kfPLAYER_OFFSET_Y (float)(cGame::Get().mProperties.muiHeight>>6)
#define kfPLAYER_OFFSET_X (float)(cGame::Get().mProperties.muiWidth>>6)


void cPlayer::Update( float lfTimestep )
{
	// Simulando animación de flotar en el espacio...
	mfFloatingSwap += lfTimestep * kfSPEED_SLOW ;
	mAuxMatrix.rows[3].y = sin( mfFloatingSwap*0.5f)+cos(mfFloatingSwap*0.25f) ;

//	tmpMatrix = mWorldMatrix;

  switch(this->meState)
  {
	case ePS_Running:
					this->Advance(lfTimestep, kfSPEED_NORMAL );				// Update Input
					this->Control(lfTimestep, kfSPEED_NORMAL ); 
		

					this->mAwesomeMatrix = mWorldMatrix;					// Update aditionals Matrix
					this->mAwesomeMatrix = 0.0f;							// Not Used by default

					if (IsPressed(eIA_TurboBoost)&& (mfTurboBoost > 0.0f) )	// Check State 
					this->meState = ePS_Turbo; 
					break;
	
	case ePS_Turbo:
					this->Advance(lfTimestep, kfSPEED_TURBO );
					this->Control(lfTimestep, kfSPEED_SLOW );
					this->mfTurboBoost -= lfTimestep * 10.0f;

					if ( !mbSfx ){
						cSoundManager::Get().Play("./Data/WAVE/Sound.wav", 0.0f);
					   cSoundManager::Get().Play("./Data/WAVE/Satelite.wav", 0.0f);
					   mbSfx = true; }

					this->mAwesomeMatrix.LoadRotation( this->mWorldMatrix.GetRight(), mfFloatingSwap * kfSPEED_TURBO); 
					this->mAwesomeMatrix.SetPosition( this->mWorldMatrix.GetPosition() );
					this->mAwesomeMatrix.Transpose(); // Simular efecto super-Cosmico

					if( IsReleased(eIA_TurboBoost) || (mfTurboBoost < 0.0f) )
					{	this->meState = ePS_Running; mbSfx = false; }
					break;

	case ePS_Crash:
					this->Advance(lfTimestep, kfSPEED_SLOW );
					this->Control(lfTimestep, kfSPEED_SLOW );

					this->mAwesomeMatrix.LoadRotation( this->mWorldMatrix.GetRight(), mfFloatingSwap * kfSPEED_SLOW); 
					this->mAwesomeMatrix.SetPosition( this->mWorldMatrix.GetPosition() );

					if ( !mbCrash ){ cSoundManager::Get().Play("./Data/WAVE/explosion.wav", 0.0f); mbCrash = true; }
					
					mfDelay += lfTimestep;
					if (mfDelay < kfCRASH_DELAY) // Hacemos que Sinergia gire un rato
						break;
        
					mfDelay = 0.0f;
					this->meState = ePS_Running;
					mbCrash = false;
					break;	

	case ePS_StandBy:
					break;
	default:
  ;}

	// Ajustamos posición X e Y dentro de los limites predefinidos
	mWorldMatrix.rows[3].x = cFileUtils::clamp( mWorldMatrix.rows[3].x, -kfPLAYER_OFFSET_X, kfPLAYER_OFFSET_X);
	mWorldMatrix.rows[3].y = cFileUtils::clamp( mWorldMatrix.rows[3].y, -kfPLAYER_OFFSET_Y, kfPLAYER_OFFSET_Y);
	
	if ((mWorldMatrix.rows[3].z>=cGame::Get().GetZMeta()) && (cGame::Get().GetResetGame()==false))
	{
		cFontManager::Get().SetMarkTime();
		cGame::Get().SetResetGame(true);
	}

	//mWorldMatrix = tmpMatrix;
	this->mModel.mCollisionObject->Update( mWorldMatrix + mAuxMatrix );
}

void cPlayer::Render()
{
	mModel.Render(this->mWorldMatrix + mAuxMatrix + mAwesomeMatrix); 
	this->mModel.mCollisionObject->Update( mWorldMatrix + mAuxMatrix + mAwesomeMatrix);
	mModel.mCollisionObject->Render();	
}

void cPlayer::SetCollisionObject(cObject *CollisionObject)
{
	mCollisionObject = CollisionObject;
	if (CollisionObject)
	meState = ePS_Crash;
//	else
//		meState = ePS_Running;
}

void cPlayer::Control(float & lfTimestep, float lfSpeed)
{	
	if (IsPressed(eIA_MoveUp) )	
	{	// Ascender
			mWorldMatrix.rows[3].y += lfTimestep *  lfSpeed;
	//		cSoundManager::Get().Play("./Data/WAVE/Satelite.wav", 0.0f);
	}

	if (IsPressed(eIA_MoveDown) )
	{
		// Descender
			mWorldMatrix.rows[3].y -= lfTimestep *  lfSpeed;
	//		cSoundManager::Get().Play("./Data/WAVE/MovPlayer.wav", 0.0f);
	}

	if (IsPressed(eIA_MoveRight)  )	// Desplazamiento Derecha
	{
			mWorldMatrix.rows[3].x -= lfTimestep *  lfSpeed;
	//		cSoundManager::Get().Play("./Data/WAVE/MovPlayer.wav", 0.0f);
	}
	
	if (IsPressed(eIA_MoveLeft) )	// Desplazamiento Izquierda
	{
		mWorldMatrix.rows[3].x += lfTimestep *  lfSpeed;
	//	cSoundManager::Get().Play("./Data/WAVE/MovPlayer.wav", 0.0f);
	}
}

void cPlayer::Advance(float & lfTimestep, float lfSpeed)
{
//	if (IsPressed(eIA_Sprint) )		// Acelerar
	if (cGame::Get().mbPlaying)
		mWorldMatrix.rows[3].z += lfTimestep *  lfSpeed;

	if (IsPressed(eIA_Brake) )		// Frenar (Retroceder por ahora)
		mWorldMatrix.rows[3].z -= lfTimestep *  lfSpeed * 0.7f  ; // agregar un * 0.7f y le da un poco más de realismo
}

void cPlayer::Reset()
{
	mWorldMatrix.rows[3].x=InitialPos.x;
	mWorldMatrix.rows[3].y=InitialPos.y;
	mWorldMatrix.rows[3].z=InitialPos.z;
	mfTurboBoost = 10.0f;
	mbSfx = false;
	mbCrash = false;
	mfFloatingSwap = 0.0f;
	mfDelay = 0;
	mCollisionObject = NULL;
	meState = ePS_Running;
	Update(0.0f);
}
