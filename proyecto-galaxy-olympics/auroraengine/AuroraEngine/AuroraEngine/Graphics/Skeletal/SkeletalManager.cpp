#include "SkeletalManager.h"
#include "SkeletalMesh.h"
#include "SkeletalCoreModel.h"
#include "cal3d/cal3d.h"


void cSkeletalManager::Init( unsigned luiMaxSize )
{
	cResourceManager::Init(luiMaxSize);
	CalLoader::setLoadingMode(LOADER_ROTATE_X_AXIS);
}

cResource * cSkeletalManager::LoadResourceInternal( std::string lacNameID, const std::string &lacFile )
{
	cSkeletalCoreModel * lpSkeletalCoreModel = new cSkeletalCoreModel();
	if (!lpSkeletalCoreModel->Init(lacNameID, lacFile))
	{
		delete lpSkeletalCoreModel;
		return NULL;
	}
	return lpSkeletalCoreModel;
}

cSkeletalMesh * cSkeletalManager::CreateSkeletalMesh( const std::string& lacCoreModelName)
{
	cResourceHandle lHandle = this->SearchResource(lacCoreModelName);
	if(lHandle.IsValidHandle())
	{
		cSkeletalCoreModel * lpCoreModel = (cSkeletalCoreModel *)lHandle.GetResource();
		cSkeletalMesh * lpSkeletalMesh = new cSkeletalMesh;
		if ( lpSkeletalMesh->Init("", lpCoreModel, 0) )
		{
			return lpSkeletalMesh;
		}
		else
		{
			delete lpSkeletalMesh;
		}
	}
	return NULL;
}