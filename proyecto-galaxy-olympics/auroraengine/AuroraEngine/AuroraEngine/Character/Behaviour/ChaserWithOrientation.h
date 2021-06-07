#ifndef CHASER_WITH_ORIENTATION
#define CHASER_WITH_ORIENTATION

#include "BehaviourBase.h"
#include "../Character.h"

class cChaserWithOrientation :
	public cBehaviourBase
{
public:
	void Init(cCharacter *lpCharacter);
	void Deinit();
	void Update(float lfTimestep);

	void SetTarget(cVec3 lTarget);
	bool EndPointReached();
private:
	cCharacter * mpCharacter; //puntero al personaje
	cVec3 mTarget;			  //posicion del objetivo
};

#endif
