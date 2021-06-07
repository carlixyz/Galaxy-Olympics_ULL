#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "../Game/InputConfiguration.h"

#include <vector>
#include "InputAction.h"
#include "InputEntry.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Pad.h"
#include "../Utility/Singleton.h"


#define IsPressed( ACTION )cInputManager::Get().GetAction( ACTION ).GetIsPressed()
#define BecomePressed( ACTION )cInputManager::Get().GetAction( ACTION ).GetBecomePressed()
#define IsReleased(ACTION) cInputManager::Get().GetAction(ACTION).GetIsReleased()
#define GetValue(ACTION) cInputManager::Get().GetAction(ACTION).GetValue()

class OIS::InputManager;

enum eDevices {
	eKeyboard = 0,
	eMouse = 1,
	ePad = 2
};

struct tActionMapping
{
	int miAction; // Id de la accion
	int miDevice; // Id del dispositivo
	int miChannel;// Id del canal
};

class cInputManager: public cSingleton<cInputManager>
{
	
public:
	friend class cSingleton<cInputManager>;

	void Init(const tActionMapping laActionMapping[], unsigned luiActionCount);
	void Update(const float &lfTimestep);
	void Deinit();

	inline cInputAction &GetAction(const int &lActionId) { return mActions[lActionId]; }

protected:
	cInputManager() { ; }

private:
	float Check(int liDevice, int liChannel);
	
	std::vector<cInputAction> mActions;
	std::vector<cGenericDevice *> mDevices;
	std::vector<std::vector <cInputEntry> > mMapped;

	friend class cKeyboard;
	friend class cMouse;
	friend class cPad;
	OIS::InputManager * mpOISInputManager;
};

#endif
