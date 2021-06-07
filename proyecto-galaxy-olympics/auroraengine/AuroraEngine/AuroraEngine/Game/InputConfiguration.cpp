#include "InputConfiguration.h"
#include "..\Input\InputManager.h"

tActionMapping kaActionMapping[] = {
	{ eIA_CloseApplication, eKeyboard, OIS::KC_ESCAPE},
	{ eIA_MoveLeft, eKeyboard, OIS::KC_LEFT },
	{ eIA_MoveRight, eKeyboard, OIS::KC_RIGHT },
	{ eIA_MoveUp, eKeyboard, OIS::KC_UP },
	{ eIA_MoveDown, eKeyboard, OIS::KC_DOWN },
	{ eIA_Sprint, eKeyboard, OIS::KC_RETURN	},
	{ eIA_MenuSelect, eKeyboard, OIS::KC_RETURN },
	{ eIA_Brake, eKeyboard,	OIS::KC_LSHIFT	},
	{ eIA_TurboBoost,eKeyboard, OIS::KC_SPACE },
	{ eIA_PlayJog, eKeyboard, OIS::KC_A },
	{ eIA_StopJog, eKeyboard, OIS::KC_S },
	{ eIA_PlayWave, eKeyboard, OIS::KC_F },
	{ eIA_StopWave, eKeyboard, OIS::KC_G },
	{ eIA_CameraSwap, eKeyboard, OIS::KC_C },
	{ eIA_CameraLeft, eKeyboard, OIS::KC_LEFT },
	{ eIA_CameraRight, eKeyboard, OIS::KC_RIGHT },
	{ eIA_CameraUp, eKeyboard, OIS::KC_PGUP },
	{ eIA_CameraDown, eKeyboard, OIS::KC_PGDOWN },
	{ eIA_CameraFoward, eKeyboard, OIS::KC_UP },
	{ eIA_MenuUp, eKeyboard, OIS::KC_UP },
	{ eIA_CameraBack, eKeyboard, OIS::KC_DOWN },
	{ eIA_MenuDown, eKeyboard, OIS::KC_DOWN },
	{ eIA_CameraYawLeft, eKeyboard, OIS::KC_HOME },
	{ eIA_CameraYawRight, eKeyboard, OIS::KC_END },
	{ eIA_CameraPitchUp, eKeyboard, OIS::KC_LSHIFT },
	{ eIA_CameraPitchDown, eKeyboard, OIS::KC_LCONTROL },
	{ eIA_MouseYaw, eMouse, eMouse_CordX},
	{ eIA_MousePitch, eMouse, eMouse_CordY},
	{ -1, -1, -1 }
};

/*
tActionMapping kaActionMapping[] = {
	{ eIA_CloseApplication, eKeyboard, OIS::KC_ESCAPE},
	{ eIA_MoveLeft, eKeyboard, OIS::KC_LEFT },
	{ eIA_MoveRight, eKeyboard, OIS::KC_RIGHT },
	{ eIA_MoveUp, eKeyboard, OIS::KC_UP },
	{ eIA_MoveDown, eKeyboard, OIS::KC_DOWN },
	{ eIA_PlayJog, eKeyboard, OIS::KC_A },
	{ eIA_StopJog, eKeyboard, OIS::KC_S },
	{ eIA_PlayWave, eKeyboard, OIS::KC_F },
	{ eIA_StopWave, eKeyboard, OIS::KC_G },
	{ eIA_CameraSwap, eKeyboard, OIS::KC_C },
	{ eIA_CameraLeft, eKeyboard, OIS::KC_J },
	{ eIA_CameraRight, eKeyboard, OIS::KC_L },
	{ eIA_CameraUp, eKeyboard, OIS::KC_I },
	{ eIA_CameraDown, eKeyboard, OIS::KC_K },
	{ eIA_CameraFoward, eKeyboard, OIS::KC_U },
	{ eIA_CameraBack, eKeyboard, OIS::KC_O },

	{ -1, -1, -1 }
};
*/

