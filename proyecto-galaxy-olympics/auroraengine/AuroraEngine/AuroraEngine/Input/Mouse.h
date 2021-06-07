#ifndef MOUSE_H
#define MOUSE_H

#include <Windows.h>
#include "GenericDevice.h"

#include "ois\includes\OISInputManager.h"
#include "ois\includes\OISException.h"
#include "ois\includes\OISMouse.h"
#include "ois\includes\OISEvents.h"

enum eMouse
{
   // Buttons
   eMouse_ButtonRight = 0,
   eMouse_ButtonLeft,
   eMouse_ButtonMiddle,
   eMouse_Button3,
   eMouse_Button4,
   eMouse_Button5,
   eMouse_Button6,
   eMouse_Button7,
   eMouse_ButtonLast = eMouse_Button7,

   // Movement
   eMouse_Wheel,
   eMouse_Left, 
   eMouse_Right,
   eMouse_Up,
   eMouse_Down,
   eMouse_MovementLast = eMouse_Down,  

   // Coordenates 
   eMouse_CordX,
   eMouse_CordY,

   eMouse_Total
};

class cMouse : public cGenericDevice, public OIS::MouseListener
{
   public:
      cMouse() : mbIsValid(false) { ; }
      void Init(void);
      void Deinit(void);
      void Update(void);
      float Check(unsigned luiEntry);
      inline bool IsValid(void) { return mbIsValid; }

      // Listeners for the Mouse
      bool mouseMoved( const OIS::MouseEvent &arg );
      bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
      bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

   private:
      OIS::Mouse* mpOISMouse;

      float mafInput[eMouse_Total];
      unsigned muiMouseIndex;
      bool mbIsValid;
};

#endif