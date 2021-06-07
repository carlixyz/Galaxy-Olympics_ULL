#include "Mouse.h"
#include "InputManager.h"
#include <assert.h>
//#include "../Utility/Debug.h"

void cMouse::Init(void)
{
   assert(cInputManager::Get().mpOISInputManager);
   
   mpOISMouse = (OIS::Mouse*)cInputManager::Get().mpOISInputManager->createInputObject( OIS::OISMouse, true );
   mpOISMouse->setEventCallback( this );
   
   mbIsValid = true;
 //  Debug() << "\n Mouse Initied \n\n" ;
}

void cMouse::Deinit(void)
{
   assert(cInputManager::Get().mpOISInputManager);

   cInputManager::Get().mpOISInputManager->destroyInputObject( mpOISMouse );
   mpOISMouse = 0;
   mbIsValid = false;
}

void cMouse::Update(void)
{

   if (IsValid())
   {     
      assert(mpOISMouse);
      mpOISMouse->capture();
   }
   else
   {
      Init();
   }
}

float cMouse::Check(unsigned luiEntry)
{
   if ( luiEntry < eMouse_Total )
   {
      return mafInput[luiEntry];
   }
   return 0.0f;
}


bool cMouse::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) 
{
   if ( id <= eMouse_ButtonLast )
   {
      mafInput[id] = 1.0f;
   }
  //	std::cout << std::endl << lArg.device->vendor() << ". Button Pressed # " << liButton;
	return true;
}

bool cMouse::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) 
{
   if ( id <= eMouse_ButtonLast )
   {
      mafInput[id] = 0.0f;
  // Debug() << " \n Provider: " <<  arg.device->vendor() ;
  // Debug() << ". Button Pressed # " << id << " \n ";
   }
  // std::cout << std::endl << lArg.device->vendor() << ". Button Released # " << liButton;
	return true;
}

bool cMouse::mouseMoved( const OIS::MouseEvent &arg )
{
	//	const OIS::MouseState& s = arg.state;

	//	Debug().ToOutput(" \n Axis X %d - Axis Y %d ", arg.state.X.abs, arg.state.Y.abs);
	//	Debug().ToOutput(" \n Height %d - Width %d \n", s.height, s.width);
	//	Debug().ToOutput(" \n Axis X %d - Axis Y %d ", s.X.rel, s.Y.rel);

	//	mafInput[eMouse_CordX] = (float)s.X.rel ;
	//	mafInput[eMouse_CordY] = (float)s.Y.rel ;

		mafInput[eMouse_CordX] = (float)arg.state.X.rel ;
		mafInput[eMouse_CordY] = (float)arg.state.Y.rel ;

	return true;
}
