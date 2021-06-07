#include "InputAction.h"
#include <math.h>

void cInputAction::Init()
{
	mbBecomePressed = false;
	mbBecomeReleased = false;
	mbIsPressed = false;
	mbWasPressed = false;
	mfValue = 0.0f;
	mfTimePressed = 0.0f;
}

void cInputAction::Update(float lfTimestep, float lfValue)
{
	mbWasPressed = mbIsPressed;
	mbIsPressed = (lfValue > 0.0f);
	
	if (mbIsPressed && mbWasPressed) //Si la accion esta activa y estaba activada antes
		mfTimePressed += fabs(lfTimestep); //incrementamos el tiempo
	else
		mfTimePressed = 0.0f;

	mbBecomePressed = (mbIsPressed && !mbWasPressed);
	mbBecomeReleased = (mbWasPressed && !mbIsPressed);

	mfValue = lfValue;
}
