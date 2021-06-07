#ifndef PLAYER_CONTROLLER
#define PLAYER_CONTROLLER

#include "BehaviourBase.h"
#include "../../Libraries/MathLib/MathLib.h"
#include "../Character.h"

class cPlayerController :
	public cBehaviourBase
{
public:
	void Init(cCharacter *lpCharacter);
	void Deinit();
	void Update(float lfTimestep);

private:
	cCharacter * mpCharacter; //puntero al personaje
};

#endif