#ifndef CHASER_SNAP_ORIENTATION
#define CHASER_SNAP_ORIENTATION

#include "BehaviourBase.h"
#include "../Character.h"

class cChaserSnapOrientation :
	public cBehaviourBase
{
public:
	void Init(cCharacter *lpCharacter);
	void Deinit();
	void Update(float lfTimestep);

	void SetTarget(cVec3 lTarget);

private:
	cCharacter * mpCharacter; //puntero al personaje
	cVec3 mTarget;			  //posicion del objetivo
};

#endif
