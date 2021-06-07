#pragma once
#ifndef GENERICDEVICE_H
#define GENERICDEVICE_H

class cGenericDevice
{
public:
	virtual void Init() = 0;
	virtual void Deinit() = 0;
	virtual void Update(void) = 0;
	virtual float Check(unsigned luiEntry) = 0;
	virtual bool IsValid(void) = 0;
};

#endif
