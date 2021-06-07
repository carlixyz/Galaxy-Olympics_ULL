#include "Skybox.h"

#include "ObjectManager.h"
#include "../../Libraries/MathLib/MathLib.h"

//#include "../../Graphics/GraphicManager.h"
//#include "../../Utility/Debug.h"

void cSkybox::Update( float lfTimestep )
{ 
	// 1) Conseguír puntero y posición del Player
	cPlayer * lpPlayer = cObjectManager::Get().GetPlayer();

	if (lpPlayer != NULL )// Checar que el Player existe
	{

	// 2) Orientar target = posición eje 'Z' de player 
	cVec3 & lvCenter = cVec3( 0.0f, 0.0f, lpPlayer->GetMatrix().GetPosition().z );

	// 3) Actualizamos posición de Skybox según ubicación del player
	this->mWorldMatrix.SetPosition( lvCenter );
	}


//	Debug().ToOutput("\n sX:%f sY:%f sZ:%f", mWorldMatrix.rows[3].x, mWorldMatrix.rows[3].y, mWorldMatrix.rows[3].z);
	
	//	..según camara activa No sale bien, parece que es por alternar entre 3 camaras (3d, 2d, etc)

	// mModel.mCollisionObject.Update(mWorldMatrix); 
	// creo q para lo unico que podrían servír colis|iones aqui es para verificar el dibujado de objetos proximos 
}

void cSkybox::Render()
{
	mModel.Render(mWorldMatrix); 
//	mModel.mCollisionObject.Render();

}
