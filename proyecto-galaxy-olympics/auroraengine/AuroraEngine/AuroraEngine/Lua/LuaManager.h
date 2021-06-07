#ifndef LUAMANAGER_H
#define LUAMANAGER_H

#include <iostream>
#include <cassert>
#include "LuaFunctions.h"
#include "..\Utility\Singleton.h"

// extern C le dice al compilador que la libreria debe ser compilada
//en C y no en C++
extern "C"
{
	#include "src/lua.h"
	#include "src/lauxlib.h"
	#include "src/lualib.h"
}
class cLuaManager : public cSingleton<cLuaManager>
{

	public:
		void Init();
		void Deinit();
		bool DoString( const char *lacStatement );
		bool DoFile( const char* lacFile );//Carga y ejecuta un fichero .lua
		void Register( const char* lacFuncName, lua_CFunction lpFunc );
		inline lua_State* GetContext() { return mpLuaContext; }

		template <class T, class U, class Z>
		bool CallLua(const char* lacFuncName, T lArg1, U lArg2, Z* lpRet);
		
		template <class Z>
		bool CallLua(const char* lacFuncName, Z* lpRet);
		
		template <class T, class Z>
		bool CallLua(const char* lacFuncName, T lArg1, Z* lpRet);
		
		template <class T, class U, class V, class Z>
		bool CallLua(const char* lacFuncName, T lArg1, U lArg2, V lArg3, Z* lpRet);

		void Pop(int liNElements);
		bool CheckError(int liError);
		static int FuncPanic(lua_State *lpContext);

		void PushArg(int liArg);
		void PushArg(long liArg);
		void PushArg(float lfArg);
		void PushArg( const char* lacArg);
		void PushArg( std::string &lacArg);
		void PushArg( bool lbArg);

		void GetRetValue( int* liRet);
		void GetRetValue( float* lfRet);
		void GetRetValue( long* liRet);
		void GetRetValue( std::string* lacRet);
		void GetRetValue( const char* lacRet);
		void GetRetValue( bool* lbRet);

		friend class cSingleton<cLuaManager>;

	protected:
		cLuaManager(); // Protected constructor
	
	private:
		lua_State* mpLuaContext;
};


template<class Z>
bool cLuaManager::CallLua(const char *lacFuncName, Z *lpRet)
{
	assert(mpLuaContext);

	lua_getglobal(mpLuaContext, lacFuncName);

	int lbExists = lua_isfunction(mpLuaContext, -1);

	if (!lbExists)
	{
		Pop(1);
		return false;
	}

	if (lpRet)
	{
		lua_call(mpLuaContext, 0, 1);
		GetRetValue(lpRet);
		Pop(1);
	} else {
		lua_call(mpLuaContext, 0, 0);
	}

	return true;
}

template<class T, class Z>
bool cLuaManager::CallLua(const char* lacFuncName, T lArg1, Z* lpRet)
{
	assert(mpLuaContext);

	lua_getglobal(mpLuaContext, lacFuncName);

	int lbExists = lua_isfunction(mpLuaContext, -1);

	if (!lbExists)
	{
		Pop(1);
		return false;
	}

	PushArg(lArg1);

	if (lpRet)
	{
		lua_call(mpLuaContext, 1, 1);
		GetRetValue(lpRet);
		Pop(1);
	} else {
		lua_call(mpLuaContext, 1, 0);
	}

	return true;
}

template<class T, class U, class Z>
bool cLuaManager::CallLua(const char *lacFuncName, T lArg1, U lArg2, Z *lpRet)
{
	assert(mpLuaContext);

	lua_getglobal(mpLuaContext, lacFuncName);

	int lbExists = lua_isfunction(mpLuaContext, -1);

	if (!lbExists)
	{
		Pop(1);
		return false;
	}

	//Añadimos los parametros
	PushArg(lArg1);
	PushArg(lArg2);

	if (lpRet)
	{
		lua_call(mpLuaContext, 2, 1);
		GetRetValue(lpRet);
		Pop(1);
	} else {
		lua_call(mpLuaContext, 2, 0);
	}

	return true;
}

template<class T, class U, class V, class Z>
bool cLuaManager::CallLua(const char *lacFuncName, T lArg1, U lArg2, V lArg3, Z *lpRet)
{
	assert(mpLuaContext);

	lua_getglobal(mpLuaContext, lacFuncName);

	int lbExists = lua_isfunction(mpLuaContext, -1);

	if (!lbExists)
	{
		Pop(1);
		return false;
	}

	//Añadimos los parametros
	PushArg(lArg1);
	PushArg(lArg2);
	PushArg(lArg3);

	if (lpRet)
	{
		lua_call(mpLuaContext, 3, 1);
		GetRetValue(lpRet);
		Pop(1);
	} else {
		lua_call(mpLuaContext, 3, 0);
	}

	return true;
}

#endif