#include "Background.h"

#include "ObjectManager.h"
#include "../../Libraries/MathLib/MathLib.h"

//#include "../../Graphics/GraphicManager.h"
//#include "../../Utility/Debug.h"

void cBackground::Update( float lfTimestep )
{ 
	//Aqui se controlara el comportamiento de los objetos
	//mModel.
	cMatrix lRot ; 
	lRot.LoadRotation(cVec3( -0.5f, 0.0f, -0.5f), lfTimestep * kfAngSpeed  ) ;

	mWorldMatrix = lRot * mWorldMatrix;
	//mModel.mCollisionObject->Update(mWorldMatrix);
	//cObject::Update(lfTimestep);

}

void cBackground::Render()
{
	mModel.Render(mWorldMatrix); 
}
