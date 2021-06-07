#include "LuaFunctions.h"

#include "../Lua/LuaManager.h"
#include "../Character/CharacterManager.h"
#include "../Graphics/GraphicManager.h"

#include "../Character/Behaviour/Patrol.h"
#include "../Character/Behaviour/ChaserWithOrientation.h"
#include "../Character/Behaviour/BehaviourManager.h"

int CreatePlayer(lua_State* lpLuaContext)
{
	//Comprobamos que el contexto de Lua no es NULL
	assert( lpLuaContext );
	
	//Cogemos el numero de argumentos de la pila de Lua
	int liArgCount = lua_gettop( lpLuaContext );
	
	//Comprobamos que recibimos dos argumentos
	assert( liArgCount == 6 );

	//Cogemos los argumentos de la pila
	//Posicion del personaje
	float posX = (float)luaL_checknumber( lpLuaContext, 1 ); 
	float posY = (float)luaL_checknumber( lpLuaContext, 2 ); 
	float posZ = (float)luaL_checknumber( lpLuaContext, 3 ); 
	//Velocidad
	float speed = (float)luaL_checknumber( lpLuaContext, 4 );
	//Velocidad de giro
	float angSpeed = (float)luaL_checknumber( lpLuaContext, 5 );
	//ID
	int Id = luaL_checkinteger( lpLuaContext, 6 ); 
	
	//Creo el caracter
	cBehaviourManager::Get().Init();
	cCharacter *lPlayer = cCharacterManager::Get().CreateCharacter();
	lPlayer->Init(Id);
	lPlayer->SetSpeed(speed);
	lPlayer->SetAngSpeed(angSpeed);
	lPlayer->SetPosition(cVec3(posX, posY, posZ));
	lPlayer->SetBehaviour(cBehaviourManager::Get().CreateBehaviour(ePLAYER_CONTROLLER));	
	
	//Introducimos en la pila el resultado
	lua_pushinteger( lpLuaContext, lPlayer->GetId() );
	
	return 1;
}


int CreatePatrol( lua_State* lpLuaContext )
{
	//Comprobamos que el contexto de Lua no es NULL
	assert( lpLuaContext );
	
	//Cogemos el numero de argumentos de la pila de Lua
	int liArgCount = lua_gettop( lpLuaContext );
	
	//Comprobamos que recibimos dos argumentos
	assert( liArgCount == 8 );
	
	//Cogemos los argumentos de la pila
	//Posicion del personaje
	float posX = (float)luaL_checknumber( lpLuaContext,1 ); 
	float posY = (float)luaL_checknumber( lpLuaContext,2 ); 
	float posZ = (float)luaL_checknumber( lpLuaContext,3 ); 
	//Velocidad
	float speed = (float)luaL_checknumber( lpLuaContext,4 );
	//Velocidad de giro
	float angSpeed = (float)luaL_checknumber( lpLuaContext,5 );
	//ID
	int Id = luaL_checkinteger( lpLuaContext,6 ); 
	//Id del enemigo
	int idEnemy = luaL_checkinteger(lpLuaContext, 7);
	//Radio de accion
	float lfAwareRadius = (float) luaL_checknumber(lpLuaContext, 8);

	//Creo el personaje
	cBehaviourManager::Get().Init();
	cCharacter *lCharacterPatrol = cCharacterManager::Get().CreateCharacter();
	lCharacterPatrol->Init(Id);
	lCharacterPatrol->SetSpeed(speed);
	lCharacterPatrol->SetAngSpeed(angSpeed);
	lCharacterPatrol->SetPosition(cVec3(posX, posY, posZ));
	cPatrol * lBehaviour = (cPatrol*) cBehaviourManager::Get().CreateBehaviour(ePATROL);
	lBehaviour->SetEnemyId(idEnemy);
	lBehaviour->SetAwareRadius(lfAwareRadius);
	lCharacterPatrol->SetBehaviour(lBehaviour);	

	//Introducimos en la pila el resultado
	lua_pushinteger( lpLuaContext, lCharacterPatrol->GetId() );
	
	return 1;
}
int SetPatrolTarget( lua_State* lpLuaContext )
{
	//Comprobamos que el contexto de Lua no es NULL
	assert( lpLuaContext );
	
	//Cogemos el numero de argumentos de la pila de Lua
	int liArgCount = lua_gettop( lpLuaContext );
	
	//Comprobamos que recibimos dos argumentos
	assert( liArgCount == 4 );
	
	//Cogemos los argumentos de la pila
	int CharacterId = luaL_checkinteger( lpLuaContext,1 ); //1º argumento
	float NextPosX = (float)luaL_checknumber( lpLuaContext,2 ); //1º argumento
	float NextPosY = (float)luaL_checknumber( lpLuaContext,3 ); //2º argumento
	float NextPosZ = (float)luaL_checknumber( lpLuaContext,4 ); //3º argumento

	cCharacter *lCharacter=cCharacterManager::Get().getCharacter(CharacterId);
	cPatrol* lBehaviour= (cPatrol*) lCharacter->GetBehaviour();
	lBehaviour->SetTargetWaypoint( cVec3(NextPosX, NextPosY, NextPosZ) );

	return 0;
}
int Drawline( lua_State* lpLuaContext )
{
	//Comprobamos que el contexto de Lua no es NULL
	assert( lpLuaContext );
	
	//Cogemos el numero de argumentos de la pila de Lua
	int liArgCount = lua_gettop( lpLuaContext );
	
	//Comprobamos que recibimos dos argumentos
	assert( liArgCount == 9 );

	//Cogemos los argumentos de la pila
	float vec1_X = (float)luaL_checknumber( lpLuaContext,1 ); //1º argumento
	float vec1_Y = (float)luaL_checknumber( lpLuaContext,2 ); //2º argumento
	float vec1_Z = (float)luaL_checknumber( lpLuaContext,3 ); //3º argumento
	float vec2_X = (float)luaL_checknumber( lpLuaContext,4 ); //4º argumento
	float vec2_Y = (float)luaL_checknumber( lpLuaContext,5 ); //5º argumento
	float vec2_Z = (float)luaL_checknumber( lpLuaContext,6 ); //6º argumento
	float color_R = (float)luaL_checknumber( lpLuaContext,7 ); //7º argumento
	float color_G = (float)luaL_checknumber( lpLuaContext,8 ); //8º argumento
	float color_B = (float)luaL_checknumber( lpLuaContext,9 ); //9º argumento

	cGraphicManager::Get().DrawLine(cVec3(vec1_X, vec1_Y, vec1_Z), cVec3(vec2_X, vec2_Y, vec2_Z), cVec3(color_R, color_G, color_B));
	return 0;
}
void cLuaFunctions::RegisterLuaFunctions()
{
	//Publicamos la funcion en Lua
	cLuaManager::Get().Register("CreatePatrol", CreatePatrol);
	cLuaManager::Get().Register("SetPatrolTarget", SetPatrolTarget);
	cLuaManager::Get().Register("Drawline", Drawline);
	cLuaManager::Get().Register("CreatePlayer", CreatePlayer);
	
	//Cargamos el fichero de script
	cLuaManager::Get().DoFile("./Data/Scripts/DrawPath.lua");
	//cLuaManager::Get().DoFile("./Data/Scripts/personajePerseguidor.lua");
	cLuaManager::Get().DoFile("./Data/Scripts/patrullero con enemigo.lua");
	cLuaManager::Get().DoFile( "./Data/Scripts/WayPointsPath.lua" );

}

 

