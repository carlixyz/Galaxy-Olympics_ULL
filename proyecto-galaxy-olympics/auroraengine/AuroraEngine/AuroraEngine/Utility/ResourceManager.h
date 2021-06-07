#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "ResourceHandle.h"
#include "Resource.h"
#include <vector>
#include <list>

class cResource;

struct cInternalResource
{
	unsigned int muiKey;
	cResource * mpResource;
};


class cResourceManager
{

public:
	
	virtual void Init( unsigned luiMaxSize );
	
	void Deinit();
	
	void UnloadResource( cResourceHandle * lpHandle );

	cResourceHandle LoadResource( std::string lacNameID, const std::string &lacFile );

	cResourceHandle LoadResource( std::string lacNameID, void * lpMemoryData, int luiTypeID );
	
	cResourceHandle SearchResource( std::string lacNameID );

protected:
	
	std::vector<cInternalResource> maResources;
	
	std::list<unsigned> mFreeResourceSlot; //guarda todos los índices de las casillas del vector que están libres
	
	int muiNextKey;  //clave que se asignará al siguiente recurso que se almacene
	unsigned muiMaxSize;// es el número máximo de recursos que podemos almacenar
	
	cResource * GetResource( cResourceHandle *lpHandle );
	friend class cResourceHandle;

	cResourceHandle AddResourceToPool( cResource * lpResource );
	
	virtual cResource * LoadResourceInternal( std::string lacNameID, const std::string &lacFile ) { return NULL; };

	virtual cResource * LoadResourceInternal( std::string lacNameID, void * lpMemoryData,int luiTypeID ) {return NULL;}

};

#endif