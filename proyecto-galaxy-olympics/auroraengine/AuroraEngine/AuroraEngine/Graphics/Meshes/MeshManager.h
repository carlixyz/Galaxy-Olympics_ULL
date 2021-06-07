#ifndef MESH_MANAGER
#define MESH_MANAGER

#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"

class cMeshManager : public cResourceManager, public cSingleton<cMeshManager>
{
public:	
	friend class cSingleton<cMeshManager>;

protected:
	cMeshManager() { ; }

private:
	virtual cResource * LoadResourceInternal( std::string lacNameID, void * lpMemoryData, int luiTypeID );
	
};

#endif
