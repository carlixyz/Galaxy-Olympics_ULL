#ifndef LUAFUNCTIONS_H
#define LUAFUNCTIONS_H

#include "..\Utility\Singleton.h"

extern void RegisterLuaFunctions();

class cLuaFunctions: public cSingleton<cLuaFunctions>
{

public:
	
		void RegisterLuaFunctions();

};
#endif 