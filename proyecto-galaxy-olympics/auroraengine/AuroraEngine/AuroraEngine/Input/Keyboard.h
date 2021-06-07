#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Windows.h>
#include "GenericDevice.h"

#include "ois\includes\OISInputManager.h"
#include "ois\includes\OISException.h"
#include "ois\includes\OISKeyboard.h"
#include "ois\includes\OISEvents.h"

class cKeyboard: public cGenericDevice, public OIS::KeyListener
{
	
public:
	cKeyboard() : mbIsValid(false) { ; }
	void Init();
	void Deinit(void);
	void Update(void);
	float Check(unsigned luiEntry);
	inline bool IsValid(void) { return mbIsValid; }

	bool keyPressed (const OIS::KeyEvent &lArg);
	bool keyReleased (const OIS::KeyEvent &lArg);

private:

	OIS::Keyboard* mpOISKeyboard;

	static const unsigned kuiInputChannelSize = 256; //Channel size
	bool mbIsValid;
	bool mabInputBuffer[kuiInputChannelSize];
};

#endif
