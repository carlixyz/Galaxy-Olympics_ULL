#include <windows.h>
#include <iostream>
#include <sstream>
#include "InputManager.h"
#include "../Window/Window.h"


void cInputManager::Init(const tActionMapping laActionMapping[], unsigned luiActionCount)
{
	OIS::ParamList pl;

	std::ostringstream wnd;
	wnd << (size_t)cWindow::Get().GetHWND();

	pl.insert(std::make_pair( std::string("WINDOW"), wnd.str()));
	pl.insert(std::make_pair( std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair( std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

	mpOISInputManager = OIS::InputManager::createInputSystem(pl);
	mpOISInputManager->enableAddOnFactory(OIS::InputManager::AddOn_All);

	//Inicializando los dispositivos
	cGenericDevice * lpKeyboard = new cKeyboard;
	cGenericDevice * lpMouse = new cMouse;
	cGenericDevice * lpPad = new cPad;
	
	lpKeyboard->Init();
	lpMouse->Init();
	lpPad->Init();

	// Añado el dispositivo a la lista
	mDevices.push_back(lpKeyboard);
	mDevices.push_back(lpMouse);
	mDevices.push_back(lpPad);

	//Inicializo el vector de acciones
	mActions.resize( luiActionCount );

	//Inicializo la estructura de mapeos
	mMapped.resize(luiActionCount);

	int liIndex = 0;
	//para cada accion almaceno el dispositivo y el canal que la maneja
	while (laActionMapping[liIndex].miAction >= 0 )
	{
		cInputEntry lEntry;
		lEntry.muiDevice = laActionMapping[liIndex].miDevice;
		lEntry.muiChannel = laActionMapping[liIndex].miChannel;
		mMapped[laActionMapping[liIndex].miAction].push_back(lEntry);
		++liIndex;
	}
}

void cInputManager::Update(const float &lfTimestep)
{
	int liSize = mDevices.size();
	//Actualizo todos los dispositivos
	for (int liDeviceId = 0; liDeviceId < liSize; ++liDeviceId)
	{
		if (mDevices[liDeviceId] != NULL)
			mDevices[liDeviceId]->Update();
	}

	liSize = mMapped.size();
	//Chequeo las acciones y actualizo
	for ( int lActionId = 0; lActionId < liSize; ++lActionId)
	{
		int liMapSize = mMapped[lActionId].size();
		float lfValue = 0.0f;
		for (int liMapId =0; liMapId < liMapSize; ++liMapId)
		{
			const cInputEntry& lEntry = mMapped[lActionId][liMapId];
			lfValue += Check(lEntry.muiDevice, lEntry.muiChannel);
		}

		mActions[lActionId].Update(lfTimestep, lfValue);
	}
}


float cInputManager::Check(int liDevice, int liChannel)
{
	if (mDevices[liDevice] != NULL && mDevices[liDevice]->IsValid() )
		return (mDevices[liDevice]->Check(liChannel));
	return 0.0f;
}


void cInputManager::Deinit()
{
	int liSize = mDevices.size();
	for (int liDeviceId = 0; liDeviceId < liSize; ++liDeviceId)
	{
		mDevices[liDeviceId]->Deinit();
		delete(mDevices[liDeviceId]);
	}

	mDevices.resize(0);
	mActions.resize(0);
	mMapped.resize(0);

	if(mpOISInputManager)
	{
		OIS::InputManager::destroyInputSystem(mpOISInputManager);
		mpOISInputManager = NULL;
	}
	
}


