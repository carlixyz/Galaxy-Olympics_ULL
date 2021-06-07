#ifndef SKELETAL_MANAGER_H
#define SKELETAL_MANAGER_H

#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"

class cSkeletalMesh;

class cSkeletalManager : public cResourceManager, public cSingleton<cSkeletalManager>
{
public:
	virtual void Init( unsigned luiMaxSize);
	friend class cSingleton<cSkeletalManager>;
	cSkeletalMesh * CreateSkeletalMesh( const std::string& lacCoreModelName);

protected:
	cSkeletalManager() {;}

private:
	virtual cResource * LoadResourceInternal( std::string lacNameID, const std::string &lacFile);

};
#endif
