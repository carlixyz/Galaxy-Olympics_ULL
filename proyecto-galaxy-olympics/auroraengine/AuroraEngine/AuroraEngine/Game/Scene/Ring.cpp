#include "Ring.h"

#include "../../Libraries/MathLib/MathLib.h"

cRing::cRing()  
{
	meType = eRing ; 
	//int sourceId = cSoundManager::Get().AddSource(mWorldMatrix.GetPosition().x, mWorldMatrix.GetPosition().y, mWorldMatrix.GetPosition().z, "./Data/WAVE/RingSound.wav");

}

void cRing::Update( float lfTimestep )
{
	//Aqui se controlara el comportamiento de los objetos

  // Set the world matrix 

	cMatrix lRot ; 
	lRot.LoadRotation(cVec3( 0.0f, 0.0f, 1.0f), lfTimestep * kfAngSpeed  ) ;

	mWorldMatrix = lRot * mWorldMatrix;// ( Aplicar siempre, SIEMPRE, primero la rotación y después posición, beware)
	
	this->mModel.mCollisionObject->Update(mWorldMatrix);

	cObject::Update(lfTimestep);

}

void cRing::Render()
{
	mModel.Render(mWorldMatrix);
    mModel.mCollisionObject->Render();
}
