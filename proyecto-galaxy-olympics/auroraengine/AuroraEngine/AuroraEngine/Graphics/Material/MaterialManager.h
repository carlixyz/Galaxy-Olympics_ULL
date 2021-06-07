#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"

class cMaterialManager : public cResourceManager, public cSingleton<cMaterialManager>
{
	public:
		friend class cSingleton<cMaterialManager>;
	
	protected:
		cMaterialManager() { ; } // Protected constructor
		
	private:
		virtual cResource * LoadResourceInternal( std::string lacNameID, void * lpMemoryData, int liDataType );
		virtual cResource * LoadResourceInternal( std::string lacNameID, const std::string &lacFile ) ;

};

#endif;

