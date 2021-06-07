#ifndef BEHAVIOUR_MANAGER_H
#define BEHAVIOUR_MANAGER_H

#include "..\..\Utility\Singleton.h"
#include <list>
#include "BehaviourBase.h"


enum eBehaviours {
	eCHASER_NO_ORIENTATION = 0,
	eCHASER_SNAP_ORIENTATION,
	eCHASER_WITH_ORIENTATION,
	ePATROL,
	ePLAYER_CONTROLLER,

	eBEHAVIOURS_Count
};

//Asumiremos que esta clase no realizar� ninguna llamada al Init() y
//Deinit() de los comportamientos. Cada personaje al que se le asigne
//un comportamiento ser� el encargado de llamar al Init() y Deinit()
//del comportamiento cuando corresponda. Esto es as�, ya que la
//inicializaci�n y destrucci�n de un comportamiento est�n relacionados
//con el momento en que se asocia un comportamiento a un personaje.
//Recuerden que deben llamar al DestroyBehaviour del comportamiento
//asignado a un personaje en la funci�n Deinit() del personaje, justo
//despu�s de llamar al Deinit() de dicho comportamiento.
class cBehaviourManager: public cSingleton<cBehaviourManager>
{
public:
	friend class cSingleton<cBehaviourManager>;

	//Devuelve true
	bool Init();
	//Elimina todos los comportamientos de la lista.
	bool Deinit();
	//Crea un nuevo comportamiento del tipo indicado en leBehaviour y lo
	//inserta en la lista,devolviendo un puntero al comportamiento creado.
	cBehaviourBase* CreateBehaviour( eBehaviours leBehaviour );
	//Elimina todos los comportamientos de la lista.
	void DestroyBehaviour(cBehaviourBase* lpBehaviour);

private:
	typedef std::list<cBehaviourBase*> cBehaviourList;
	typedef cBehaviourList::iterator cBehaviourListIt;
	cBehaviourList mBehaviours; //Lista de comportamientos
};
#endif