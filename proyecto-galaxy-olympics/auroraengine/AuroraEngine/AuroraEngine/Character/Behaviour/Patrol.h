#ifndef PATROL_H
#define PATROL_H

#include "BehaviourBase.h"
#include "ChaserWithOrientation.h"

class cPatrol :
	public cBehaviourBase
{
public:
	void Init(cCharacter *lpCharacter);
	void Deinit();
	void Update(float lfTimestep);
	inline const cVec3 &GetTargetWaypoint() const {return mTargetWaypoint; }
	void SetTargetWaypoint( cVec3 lTargetWaypoint );
	void SetAwareRadius( float lfAwareRadius);//Establece un nuevo valor del radio de percepción
	void SetEnemyId( int liEnemyId );//Establece el id del enemigo.

private:
	cCharacter * mpCharacter; //puntero al personaje
	cVec3 mTargetWaypoint;	  //Siguiente punto objetivo
	cChaserWithOrientation* mpBehaviour; //Comportamiento perseguidor
	int enemyId; //Id del enemigo
	float mfAwareRadius; //Radio de percepción
};

#endif