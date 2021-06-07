#ifndef CHARACTER
#define CHARACTER

#include "../Libraries/MathLib/MathLib.h"
#include "..\Utility\ResourceHandle.h"
#include "..\Graphics\Skeletal\SkeletalMesh.h"
#include "../Game/Scene/Submodel.h"

#include "../Character/Behaviour/BehaviourManager.h"

//class cBehaviourBase;

class cCharacter
{
public:
	void Init(int liIdCharacter);
	void Deinit();
	void Update(float lfTimestep);
	void Render();

	inline const cVec3 &GetPosition() const { return mPosition; }
	inline float GetYaw() const { return mfYaw; }
	inline float GetSpeed() const { return mfSpeed; }
	inline float GetAngSpeed() const { return mfAngSpeed; }
	inline int GetId() const { return miId; }

	//Devuelve el vector Front del personaje
	inline cVec3 GetFront() const { return cVec3( sinf(mfYaw), 0.0f, cosf(mfYaw) );}
	//Devuelve el vector Left del personaje.
	inline cVec3 GetLeft() const { return cVec3( sinf(mfYaw + HALF_PI), 0.0f, cosf(mfYaw + HALF_PI) ); }
	//Devuelve el vector Right del personaje
	inline cVec3 GetRight() const { return -GetLeft(); }
	//Devuelve el comportamiento actual del personaje
	inline cBehaviourBase* GetBehaviour() { return mpActiveBehaviour; }

	void Jogging();
	void StopJogging();
	void PlayWave();
	void StopWave();
	
	//Setters
	void SetPosition( const cVec3 &lPosition );
	void SetYaw( float lfYaw );
	void SetSpeed( float lfSpeed );
	void SetAngSpeed( float lfAngSpeed );
	void SetBehaviour(cBehaviourBase * lBehaviour);
	void SetResourceHandle(cResourceHandle mResourceHandle);
	void SetObject(cSubmodel lObject);

private:
	cVec3 mPosition;
	float mfYaw;
	float mfSpeed;
	float mfAngSpeed;
	cBehaviourBase* mpActiveBehaviour;
	int miId;
	cResourceHandle mResourceHandle;
	cSubmodel mObject;

	bool mbJogging;
};

#endif
