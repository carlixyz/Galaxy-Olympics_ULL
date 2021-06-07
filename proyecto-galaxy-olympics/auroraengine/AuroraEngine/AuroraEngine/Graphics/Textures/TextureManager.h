#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"

class cTextureManager: public cResourceManager, public cSingleton<cTextureManager>
{
public:

	friend class cSingleton<cTextureManager>;

protected:
	cTextureManager() { ; }

private:
	virtual cResource * LoadResourceInternal(std::string lacNameID, const std::string &lacFile);
};

#endif
