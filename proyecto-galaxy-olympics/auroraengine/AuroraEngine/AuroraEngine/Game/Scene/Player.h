#ifndef PLAYER_H
#define PLAYER_H

#include "../../Libraries/MathLib/MathLib.h"
#include "Object.h"

enum ePlayerState {
	ePS_Crash = 0,
	ePS_Running,
	ePS_Turbo,
	ePS_StandBy	};


class cPlayer : public cObject
{
	public:
		cPlayer() { meType = ePlayer;  meState = ePS_Running; mfFloatingSwap = 0.0f; mfTurboBoost = 10.0f; mfDelay = 0.0f; mbSfx = false; }
		void Update( float lfTimestep );
		void Render();	
		void SetCollisionObject(cObject *CollisionObject);
		inline void AddTurbo(void){	this->mfTurboBoost += 0.35f * (mfTurboBoost < 100.0f ) ; }
		void Reset();		
		inline void SetInitialPos(cVec3 lvInitialPos){ InitialPos = lvInitialPos;}
		
		float & GetTurboAmount() {return mfTurboBoost;}

	private:
		float mfFloatingSwap ;	// float para Alternar entre flotar ascendiendo/descendiendo
		float mfTurboBoost;
		float mfDelay;
		bool mbSfx;
		bool mbCrash;

		cMatrix mAuxMatrix ;	// Matriz de composición para transformaciónes del player.
		cMatrix tmpMatrix;		// Matriz Temporal para bloquear el avance del player
		cMatrix mAwesomeMatrix;	// Matriz para accidente
		cObject *mCollisionObject;
		ePlayerState meState;
		cVec3 InitialPos;
		

		void Advance(float & lfTimestep, float lfSpeed);
		void Control(float & lfTimestep, float lfSpeed);
};
#endif