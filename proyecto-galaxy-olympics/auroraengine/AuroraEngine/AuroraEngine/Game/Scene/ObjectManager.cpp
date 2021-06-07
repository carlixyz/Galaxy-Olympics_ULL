#include "ObjectManager.h"

#include <tinystr.h>
#include <tinyxml.h>

#include "Ring.h"
#include "Obstacle.h"
#include "Skybox.h"
#include "Background.h"
#include "../Game.h"
#include "../../Utility/FileUtils.h"
//#include "../../Utility/Debug.h"

bool cObjectManager::Init(const char *lacLevelFile)
{
 TiXmlDocument doc( lacLevelFile );
 
 if ( doc.LoadFile() )
 {
	TiXmlHandle docHandle( &doc ); //  document´s handle
	TiXmlElement * lpElem;

	lpElem = docHandle.FirstChildElement("Level").ToElement();

	if(!lpElem )// Chequeamos que nuestra raíz es Level
		OutputDebugString(" Level.XML Load: FAILED.\n");

	std::string lacObjType;
	bool lbIsBoundingBox;
	cFileUtils::RandomInit();

	// Buscamos Tags en: <DOC> / <Level> / <Object (Attribs)> ..
	for( lpElem = lpElem->FirstChildElement("Object") ; lpElem ; lpElem = lpElem->NextSiblingElement() )
	{
	  lacObjType = "";
	  lbIsBoundingBox = true;
	  cObject * lpObject;

	  // Buscamos tipo de Objeto 
	  lpElem->QueryValueAttribute( "type", &lacObjType );

	  // 1)INSTANCIACIÓN DE OBJETOS SEGÚN TIPO
	  // Leemos la primera inicial del string y según esta decidimos..
	  OutputDebugString(lacObjType.c_str());
	
	  switch( lacObjType [0] ) 
	  {
		 case 'R':// tipo Ring
			lpObject = new cRing();
			break;
		 case 'I':// tipo  Item
//			lpObject = new cItem();
			break;
		 case 'E':// tipo  Enemy
//			lpObject = new cEnemy();
			break;
		 case 'P':// tipo  Player
			lpObject = new cPlayer();
			mpPlayer = (cPlayer *)lpObject;
			break;
		 case 'O':// tipo  Obstacle 
//			if ( lacObjType != "Obstacle") continue; // Checkup
			lpObject = new cObstacle();
			break;
		 case 'S':// tipo Skybox
			lpObject = new cSkybox();
			break;
		case 'B':// tipo  Background
			lpObject = new cBackground();
			break;
		 default: // tipo indefinido, por Default OBJECT 
			lpObject = new cObject();
		OutputDebugString(" Object without type defined \n ");
	  }
	
	  // 2) INICIALIZACIÓN DE MODELO 3D EN OBJETO
	  if ( lpElem->FirstChild("resource") )
	  {
		TiXmlElement * lpChild = lpElem->FirstChildElement("resource");

		std::string lsCollisionType = lpElem->Attribute("collision");
		
		lpObject->Init( lpChild->Attribute( "name" ), lpChild->Attribute( "modelFile" ),
			( lsCollisionType == "Box" ) ); // true if Box else Spherical
	  }
	  else lpObject->Init( "TestLevel", "./Data/Scene/dragonsmall.DAE" );// Si sale un dragon, algo anda mal


	  // 3) POSICIÓN DE OBJETO EN MUNDO
	  if ( lpElem->FirstChild("position") )
	  {
		  cVec3 lv3Pos;	// Sino existe el tag, se asigna una por default 
		  TiXmlElement * lpChild = lpElem->FirstChildElement("position");

		if ( lpObject->meType != eBackground )
		  {
		  lv3Pos.x = cFileUtils::RandomFloat(-10.0f, 10.0f);
  		  lv3Pos.y = cFileUtils::RandomFloat(-10.0f, 10.0f); // asignar random position a los obstaculos
		  }
		else
		  {
		  lpChild->QueryFloatAttribute("x", &lv3Pos.x);
		  lpChild->QueryFloatAttribute("y", &lv3Pos.y);
		  }
		  
		  lpChild->QueryFloatAttribute("z", &lv3Pos.z);

		  if (lacObjType[0]=='P')
			  mpPlayer->SetInitialPos(lv3Pos);

		  if (lpObject->GetName()=="Meta")
			  cGame::Get().SetZMeta(lv3Pos.z);

		  lpObject->Translate( lv3Pos ); 
	  }
	  
	  // 4) AGREGAMOS OBJETOS A LISTA GENERAL..
	  mObjects.push_back(lpObject);

	//Debug() <<  pObject->Attribute("ResourceName" ) << pObject->Attribute("ModelFile" );
	}	return true ;			
 } 
 return false ;
}

void cObjectManager::Update(float lfTimestep)
{	
	mpPlayer->SetCollisionObject(NULL);
	//Force to update player first to avoid problems with collision detection
	mpPlayer->Update(lfTimestep);

	for (cObjectListIt lpIterator = mObjects.begin(); lpIterator != mObjects.end(); ++lpIterator)
	{
		cObject *lpObject = (*lpIterator);
		if(lpObject->meType != ePlayer)
			lpObject->Update(lfTimestep);
	}
}

void cObjectManager::Render(void)
{
	for (cObjectListIt lpIterator = mObjects.begin(); lpIterator != mObjects.end(); ++lpIterator)
	{
		(*lpIterator)->Render();// Recorremos la lista y Renderizamos cada objeto
	}
}

bool cObjectManager::DeInit(void)
{
	for (cObjectListIt lpIterator = mObjects.begin(); lpIterator != mObjects.end(); ++lpIterator)
	{
		(*lpIterator)->Deinit();// Recorremos la lista y Renderizamos cada objeto
	}
	mObjects.clear();// limpiando el listado de punteros en la lista

	return true;
}

 // std::cout << "type of *&rpInt: " << typeid(rpInt).name() << std::endl;//will show int * 
