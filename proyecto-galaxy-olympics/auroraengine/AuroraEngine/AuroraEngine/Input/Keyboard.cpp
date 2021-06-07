#include "Keyboard.h"
#include "InputManager.h"
#include <assert.h>

const static unsigned kuiInputBufferSize = 128; // ?


void cKeyboard::Init()
{
	memset(mabInputBuffer, 0, kuiInputChannelSize); // 	memset(mabInputBuffer, 0, kuiInputBufferSize);

	assert(cInputManager::Get().mpOISInputManager);
	OIS::InputManager * lpOISInputManager = cInputManager::Get().mpOISInputManager;
	mpOISKeyboard = (OIS::Keyboard*) lpOISInputManager->createInputObject(OIS::OISKeyboard, true);

	mpOISKeyboard->setEventCallback( this );
	mbIsValid = true;
}


void cKeyboard::Deinit()
{
	assert(cInputManager::Get().mpOISInputManager);
	cInputManager::Get().mpOISInputManager->destroyInputObject(mpOISKeyboard);
	mpOISKeyboard = 0;
	mbIsValid = false;
}

bool cKeyboard::keyPressed(const OIS::KeyEvent &lArg)
{
	mabInputBuffer[lArg.key] = true;
	return true;
}


bool cKeyboard::keyReleased(const OIS::KeyEvent &lArg)
{
	mabInputBuffer[lArg.key] = false;
	return true;
}

void cKeyboard::Update()
{
	assert(mpOISKeyboard);
	mpOISKeyboard->capture();
}


float cKeyboard::Check(unsigned luiEntry)
{
	if (mabInputBuffer[luiEntry])
		return 1.0f;
	return 0.0f;
}

