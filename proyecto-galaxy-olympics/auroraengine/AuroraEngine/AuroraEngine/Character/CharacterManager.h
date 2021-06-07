#ifndef CHARACTER_MANAGER
#define CHARACTER_MANAGER

#include "..\Utility\Singleton.h"
#include <list>
#include "Character.h"

class cCharacterManager: public cSingleton<cCharacterManager>
{
public:
	friend class cSingleton<cCharacterManager>;

	bool Init();
	
	//Llama al Update de todos personajes
	void Update(float lfTimestep);
	
	//Llama al Render de todos personajes
	void Render();
	
	//Llama al Deinit de todos personajes
	bool Deinit();
	
	//Crea un nuevo personaje, llama a su Init() y lo añade a la lista.
	//Devuelve un puntero al personaje creado
	cCharacter* CreateCharacter();
	
	//Elimina al personaje de la lista y llama a su Deinit()
	void DestroyCharacter(cCharacter* lpCharacter);

	//Devuelve el personaje si existe y sino un nulo
	cCharacter* getCharacter(int characterId);


protected:
	cCharacterManager() { ; }

private:
	typedef std::list<cCharacter *> cCharacterList;
	typedef cCharacterList::iterator cCharacterListIt;
	cCharacterList mCharacters;
};

#endif
