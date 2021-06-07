#ifndef MODEL_H
#define MODEL_H

#include "../../Utility/Resource.h"
#include "../../Utility/ResourceHandle.h"
#include "../../Libraries/MathLib/MathLib.h"
#include <vector>
#include <aiScene.h>
#include "Submodel.h"
#include "Collision.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"


struct aiScene;
struct aiNode;

class cModel : public cResource
{
public:
	cModel() { 	mbLoaded = false; 	}
	
//	virtual bool Init( const std::string &lacNameID,const std::string &lacFile );

	virtual bool Init( const std::string &lacNameID,const std::string &lacFile, bool lbBoundingBox );
	
	virtual void Deinit();
	
	virtual bool IsLoaded() { return mbLoaded; }
	
	void Update( float lfTimestep );
	
	void Render(cMatrix &lWorld);

	void ConvertNodesToObjects( aiNode *lpNode, cMatrix lTransform );

	cCollision  *mCollisionObject;
private:

	typedef std::vector<cResourceHandle> cMeshHandleList;
	typedef cMeshHandleList::iterator cMeshHandleListIt;
	typedef std::vector<cSubmodel *> cSubmodelList;
	cSubmodelList mSubmodelList;
	cMeshHandleList mMeshList;
	std::vector<cResourceHandle> mMaterialList;
	std::vector<unsigned> mMeshMaterialIndexList;
	std::string macFile;
	bool mbLoaded;

	void ProcessScene(const aiScene* lpScene);
	
};

#endif