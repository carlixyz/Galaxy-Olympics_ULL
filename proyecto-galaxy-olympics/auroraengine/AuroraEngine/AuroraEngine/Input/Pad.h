#ifndef PAD_H
#define PAD_H

#include <Windows.h>
#include "GenericDevice.h"

#include "OISInputManager.h"
#include "OISException.h"
#include "OISJoystick.h"
#include "OISEvents.h"

enum ePad
{
   // Buttons
   ePad_Button1 = 0,
   ePad_Button2,
   ePad_Button3,
   ePad_Button4,
   ePad_Button5,
   ePad_Button6,
   ePad_Button7,
   ePad_Button8,
   ePad_Button9,
   ePad_Button10,
   ePad_Button11,
   ePad_Button12,
   ePad_ButtonLast = ePad_Button12,

   // Axis
   ePad_AxisFirst, 
   ePad_Axis1Y = ePad_AxisFirst,
   ePad_Axis1X,
   ePad_Axis2Y,
   ePad_Axis2X,
   ePad_Axis3Y,
   ePad_Axis3X,
   ePad_AxisLast = ePad_Axis3X,  

   // POV 
   ePad_POVX,
   ePad_POVY,

   ePad_Total
};

class cPad : public cGenericDevice, public OIS::JoyStickListener
{
   public:
      cPad() : mbIsValid(false) { ; }
      void Init()                         { Init(0); }
      void Init( int luiPadIndex );

      void Deinit(void);
      void Update(void);
      float Check(unsigned luiEntry);
      inline bool IsValid(void) { return mbIsValid; }

      // Listeners for the Pad
      bool buttonPressed( const OIS::JoyStickEvent &lArg, int liButton );
      bool buttonReleased( const OIS::JoyStickEvent &lArg, int liButton );
      bool axisMoved( const OIS::JoyStickEvent &lArg, int liAxis );
      bool povMoved( const OIS::JoyStickEvent &lArg, int liPov );
      bool vector3Moved( const OIS::JoyStickEvent &lArg, int liIndex);

   private:
      OIS::JoyStick* mpOISJoystick;

      float mafInput[ePad_Total];
      unsigned muiPadIndex;
      bool mbIsValid;
};

#endif