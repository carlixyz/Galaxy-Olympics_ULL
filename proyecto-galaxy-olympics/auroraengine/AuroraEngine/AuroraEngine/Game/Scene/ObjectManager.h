#ifndef OBJ_MANAGER
#define OBJ_MANAGER

#include "Player.h"

//#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"
#include <list>

class cObjectManager : public cSingleton<cObjectManager>//, public cResourceManager
{
public:	
	friend class cSingleton<cObjectManager>;

		bool Init(const char * lacLevelFile); // cargar el nivel del juego

		void Update(float lfTimestep); // actualizar todos los objetos

		void Render(); // renderizar level

		bool DeInit();

		inline cPlayer * GetPlayer() const{ return mpPlayer; } // Devuelve puntero al player

	//	inline  cPlayer  & GetPlayer() { return *mpPlayer; }  // Usar esta alternativa para pasar referencias


protected:
	cObjectManager() { ; }

private:

	typedef std::list<cObject *> cObjectList;
	typedef cObjectList::iterator cObjectListIt;

	cObjectList mObjects;

	cPlayer * mpPlayer;
//	virtual cResource * LoadResourceInternal( std::string lacNameID, void * lpMemoryData, int luiTypeID );
	
};

#endif