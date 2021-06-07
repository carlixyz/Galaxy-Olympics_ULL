#include "Pad.h"
#include "InputManager.h"
#include <assert.h>

void cPad::Init( int luiPadIndex )
{
   assert(cInputManager::Get().mpOISInputManager);
   muiPadIndex = luiPadIndex;
   mpOISJoystick = NULL;

   int luiNumPads = cInputManager::Get().mpOISInputManager->getNumberOfDevices(OIS::OISJoyStick);
   if ( luiPadIndex < luiNumPads )
   {
      mpOISJoystick = (OIS::JoyStick*)cInputManager::Get().mpOISInputManager->createInputObject( OIS::OISJoyStick, true );
	   mpOISJoystick->setEventCallback( this );

      mbIsValid = true;
   }
}

void cPad::Deinit(void)
{
   assert(cInputManager::Get().mpOISInputManager);
   cInputManager::Get().mpOISInputManager->destroyInputObject( mpOISJoystick );
   mpOISJoystick = 0;
   mbIsValid = false;
}

void cPad::Update(void)
{
   if (IsValid())
   {
      //This fires off buffered events for keyboards
      assert(mpOISJoystick);
      mpOISJoystick->capture();
   }
   else
   {
      Init( muiPadIndex );
   }
}

float cPad::Check(unsigned luiEntry)
{
   if ( luiEntry < ePad_Total )
   {
      return mafInput[luiEntry];
   }
   return 0.0f;
}

bool cPad::buttonPressed( const OIS::JoyStickEvent &lArg, int liButton ) 
{
   if ( liButton <= ePad_ButtonLast )
   {
      mafInput[liButton] = 1.0f;
   }
   //	std::cout << std::endl << lArg.device->vendor() << ". Button Pressed # " << liButton;
	return true;
}

bool cPad::buttonReleased( const OIS::JoyStickEvent &lArg, int liButton ) 
{
   if ( liButton <= ePad_ButtonLast )
   {
      mafInput[liButton] = 0.0f;
   }
   //	std::cout << std::endl << lArg.device->vendor() << ". Button Released # " << liButton;
	return true;
}

bool cPad::axisMoved( const OIS::JoyStickEvent &lArg, int liAxis )
{
   // Just 3 Axis XY
   if ( liAxis <= ePad_AxisLast - ePad_AxisFirst )      
   {
      unsigned luiAxisIndex = ePad_Axis1Y + liAxis;
      mafInput[luiAxisIndex] = (float)lArg.state.mAxes[liAxis].abs;

      // The Y is inverted
      if ( luiAxisIndex == ePad_Axis1Y || luiAxisIndex == ePad_Axis2Y || luiAxisIndex == ePad_Axis3Y)
      {
         mafInput[luiAxisIndex] = -mafInput[luiAxisIndex];
      }
   }
	//if( lArg.state.mAxes[liAxis].abs > 2500 || lArg.state.mAxes[liAxis].abs < -2500 )
	//	std::cout << std::endl << lArg.device->vendor() << ". Axis # " << liAxis << " Value: " << lArg.state.mAxes[liAxis].abs; 
	return true;
}

bool cPad::povMoved( const OIS::JoyStickEvent &lArg, int liPov )
{
//	std::cout << std::endl << lArg.device->vendor() << ". POV" << liPov << " ";

   if( lArg.state.mPOV[liPov].direction & OIS::Pov::North ) //Going up
      mafInput[ePad_POVY] = 1.0f;   // std::cout << "North";
	else if( lArg.state.mPOV[liPov].direction & OIS::Pov::South ) //Going down
		mafInput[ePad_POVY] = -1.0f;  //std::cout << "South";

	if( lArg.state.mPOV[liPov].direction & OIS::Pov::East ) //Going right
		mafInput[ePad_POVX] = 1.0f;   // std::cout << "East";
	else if( lArg.state.mPOV[liPov].direction & OIS::Pov::West ) //Going left
		mafInput[ePad_POVX] = -1.0f;  // std::cout << "West";

	if( lArg.state.mPOV[liPov].direction == OIS::Pov::Centered ) //stopped/centered out
   {
		mafInput[ePad_POVX] = 0.0f;
      mafInput[ePad_POVY] = 0.0f;  
   }
	return true;
}

bool cPad::vector3Moved( const OIS::JoyStickEvent &lArg, int liIndex)
{
	/*std::cout.precision(2);
	std::cout.flags(std::ios::fixed | std::ios::right);
	std::cout << std::endl << lArg.device->vendor() << ". Orientation # " << liIndex 
		<< " X Value: " << lArg.state.mVectors[liIndex].x
		<< " Y Value: " << lArg.state.mVectors[liIndex].y
		<< " Z Value: " << lArg.state.mVectors[liIndex].z;
	std::cout.precision();
	std::cout.flags();*/ 
	return true;
}
