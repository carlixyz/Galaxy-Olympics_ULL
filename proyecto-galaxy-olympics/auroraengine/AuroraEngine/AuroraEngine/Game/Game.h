#ifndef GAME	// AuRorA EnGinE, Fuck yeah http://d.imagehost.org/0128/Fuck_Yea.png
#define GAME	

#include "../Utility/Singleton.h"
#include "../Utility/ResourceHandle.h"
#include "../Window/ApplicationProperties.h"
#include "../Graphics/GraphicManager.h"
#include "../Graphics/cMenuCamera.h"

#include "Scene/ObjectManager.h"

class cGame: public cSingleton<cGame>
{
public:
	friend class cSingleton<cGame>;

	cApplicationProperties mProperties;

	bool mbLevelLoaded;

	bool mbPlaying; // partida activa o gameover
	
	bool Init();						//Function to initialize the game
	void Update( float lfTimestep );	// Function to update the game
	void Render();						//Function to render the game
	bool Deinit();
	
	inline bool HasFinished() { return mbFinished; }
	inline float GetAcumulatedTime() { return mfAcTime; }
	inline void SetFinished(bool lbFinished){ mbFinished = lbFinished; }
	inline void SetMenu(bool lbInMenu){ mbInMenu = lbInMenu; }
	inline void SetZMeta(float lfZMeta) {mfZMeta = lfZMeta;}
	inline float GetZMeta(){ return mfZMeta;}
	inline void SetResetGame(bool lbReset) {mbResetGame = lbReset;}
	inline bool GetResetGame(){ return mbResetGame;}
protected:
	cGame() { ; }

private:	
	
	bool mbFinished; // Game Exit 
	float mfAcTime;
	
	cMenuCamera mMenuCamera;
	cDebugCamera mDevCamera;
	cIngameCamera mGameCamera;
	cCamera m2DCamera;
	float mfTimeSinceLastPress ;

	bool mbResetGame;
	bool mbInMenu;
	float mfZMeta;
};

#endif
