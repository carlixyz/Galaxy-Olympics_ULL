#ifndef BEHAVIOUR_BASE
#define BEHAVIOUR_BASE


//#include "..\Character.h"
class cCharacter; // One Foward Declaration for a lot of crossed includes (What a mess!)

class cBehaviourBase
{
public:
	// Inicializa los atributos del comportamiento y es llamada en el 
	// momento en que se asocia este comportamiento a un personaje
	virtual void Init(cCharacter* lpCharacter) = 0;
	
	// Deinicializa los atributos del comportamiento y es llamada en el 
	// momento en que se elimina este comportamiento de un personaje
	virtual void Deinit() = 0;

	// Esta función se llama cada frame para actualizar la logica asociada
	// al comportamiento
	virtual void Update(float lfTimestep) = 0;
};

#endif
