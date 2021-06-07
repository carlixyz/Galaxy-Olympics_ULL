#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include "../Utility/Singleton.h"
#include "../Graphics/Camera.h"

class cTimeManager : public cSingleton<cTimeManager>
{
public:
	friend class cSingleton<cTimeManager>;
	void Init(cCamera l2DCamera, float lfLevelTime);
	/*void Init(float lfWidth, float lfHeight, float lfLevelTime);*/
	void Update(float lfTimestep);
	void Render();

private:
	float mfLevelTime;
	cCamera m2DCamera;

};

#endif