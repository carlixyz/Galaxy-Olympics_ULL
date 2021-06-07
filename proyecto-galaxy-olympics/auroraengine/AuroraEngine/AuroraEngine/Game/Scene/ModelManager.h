#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"

#include "Model.h"

class cModelManager : public cResourceManager, public cSingleton<cModelManager>
{
	public:
		friend class cSingleton<cModelManager>;

	protected:
		cModelManager() { ; } // Protected constructor

	private:
		virtual cResource * LoadResourceInternal( std::string lacNameID, const std::string &lacFile );
};
#endif

