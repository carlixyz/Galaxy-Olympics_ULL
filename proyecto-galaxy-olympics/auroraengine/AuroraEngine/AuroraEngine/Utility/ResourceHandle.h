#ifndef RESOURCE_HANDLE_H
#define RESOURCE_HANDLE_H

#include <stdlib.h>

class cResourceManager;
class cResource;

static const unsigned kuiInvalidKey = 0;

class cResourceHandle
{
public:

	cResourceHandle() { mpManager = NULL; muiKey = kuiInvalidKey; }

	cResource * GetResource(); //función para acceder a un recurso

	inline bool IsValidHandle() { return muiKey != kuiInvalidKey; } //Comprueba que un Handle es válido

	inline void Invalidate() { muiKey = kuiInvalidKey; } //libera un handle

	inline unsigned GetID() { return muiID; }

	inline unsigned GetKey() { return muiKey; }

protected:

	friend class cResourceManager;

	void Init( cResourceManager * lpManager,
		unsigned luiID,
		unsigned luiKey );

	cResourceManager * mpManager;

	unsigned int muiID;

	unsigned int muiKey;
};
#endif