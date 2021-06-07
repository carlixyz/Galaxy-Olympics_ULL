#include "BehaviourManager.h"

#include "ChaserNoOrientation.h"
#include "ChaserSnapOrientation.h"
#include "ChaserWithOrientation.h"
#include "Patrol.h"
#include "PlayerController.h"

//Devuelve true
bool cBehaviourManager::Init()
{
	return true;
}		 

//Elimina todos los comportamientos de la lista.
bool cBehaviourManager::Deinit() 
{
	mBehaviours.resize(0);
	return true;
}

//Crea un nuevo comportamiento del tipo indicado en leBehaviour y lo
//inserta en la lista,devolviendo un puntero al comportamiento creado.
cBehaviourBase* cBehaviourManager::CreateBehaviour( eBehaviours leBehaviour )
{
	cBehaviourBase* lBehaviour;
	switch (leBehaviour) 
	{
	case eCHASER_NO_ORIENTATION:
		lBehaviour = new cChaserNoOrientation();
		break;
	case eCHASER_SNAP_ORIENTATION:
		lBehaviour = new cChaserSnapOrientation();
		break;
	case eCHASER_WITH_ORIENTATION:
		lBehaviour = new cChaserWithOrientation();
		break;
	case ePATROL:
		lBehaviour = new cPatrol();
		break;
	case ePLAYER_CONTROLLER:
		lBehaviour = new cPlayerController();
		break;
	default:
		lBehaviour = new cChaserNoOrientation();
	}
	mBehaviours.push_back(lBehaviour);
	return lBehaviour;
} 

//Elimina el behaviour de la lista
void cBehaviourManager::DestroyBehaviour(cBehaviourBase* lpBehaviour) 
{
	mBehaviours.remove(lpBehaviour);
}