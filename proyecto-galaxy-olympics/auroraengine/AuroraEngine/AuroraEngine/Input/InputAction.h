#pragma once
#ifndef INPUTACTION_H
#define INPUTACTION_H

class cInputAction
{
public:
	void Init();
	void Update(float lfTimestep, float lfValue);
	
	inline bool GetIsPressed(void) const { return mbIsPressed; } //funcion que devuelve si la accion esta activa
	inline bool GetIsReleased(void) const { return !mbIsPressed; } //funcion para comprobar si la accion no esta activa
	inline bool GetBecomePressed(void) const { return mbBecomePressed; } //Indica si la accion ha pasado de activa a inactiva
	inline bool GetBecomeReleased(void) const { return mbBecomeReleased; } //Indica si la accion ha pasado de inactiva a activa
	inline float GetPressedTime(void) const { return mfTimePressed; } //Devuelve el tiempo que la accion lleva activa
	inline float GetValue(void) const { return mfValue; } // Devuelve el valor de la accion

private:
	float mfValue;
	float mfTimePressed;
	bool mbIsPressed;
	bool mbBecomePressed;
	bool mbBecomeReleased;
	bool mbWasPressed;
};

#endif