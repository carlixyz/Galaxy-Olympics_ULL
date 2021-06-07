#include "ModelManager.h"
#include "Model.h"

cResource * cModelManager::LoadResourceInternal( std::string lacNameID, const std::string &lacFile )
{
	cModel * lpScene = new cModel();
	if (!lpScene->Init( lacNameID, lacFile, true ))
	{
		delete lpScene;
		return NULL;
	}
	return lpScene;
}