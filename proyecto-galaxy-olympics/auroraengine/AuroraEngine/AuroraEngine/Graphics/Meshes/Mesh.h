#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "../../Utility/Resource.h"
#include "../../Utility/ResourceHandle.h"
#include "../../Game/Scene/BoundingBox.h"

static int kuiStaticMesh = 0;
static int kuiSkeletalMesh = 1;
struct aiMesh;

class cMesh : public cResource
{
public:
	cMesh()  { mbLoaded = false; }

	virtual bool Init( const std::string &lacNameID, void * lpMemoryData );
	void Reload(void * lpMemoryData);
	virtual void Deinit();
	virtual bool IsLoaded() { return mbLoaded; }
	virtual void PrepareRender(cResourceHandle lMaterial) {;}
	virtual void RenderMesh();
	virtual void Update(float lfTimestep){}
	
protected:

	std::string macFile;
	unsigned mVboVertices;
	std::vector<unsigned> maVboTexture;
	unsigned mVboNormals;
	unsigned mVboIndex;
	int muiIndexCount;
	bool mbLoaded;
	
};

#endif
