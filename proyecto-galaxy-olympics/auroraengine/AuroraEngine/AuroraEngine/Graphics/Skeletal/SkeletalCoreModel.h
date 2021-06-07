#ifndef SKELETAL_CORE_MODEL_H
#define SKELETAL_CORE_MODEL_H

#include <string>
#include <list>
#include "../../Utility/Resource.h"
#include "cal3d/cal3D.h"
#include "../GLHeaders.h"

enum eAnimType {
	eAnimType_Cycle = 0,
	eAnimType_Action
};

struct sAnimationDef
{
	std::string macName;
	std::string macAnimationFile;
	eAnimType meAnimType;
	int miAnimID;
};

class cSkeletalMesh;
class cSkeletalCoreModel: public cResource
{
public:
	cSkeletalCoreModel() { mpCoreModel = NULL; }
	friend class cSkeletalMesh;

	virtual bool Init( const std::string &lacNameID, const std::string &lacFile);
	virtual void Deinit();
	virtual bool IsLoaded() { return (mpCoreModel != NULL); }
	sAnimationDef * GetAnimationDef (const std::string lacAnim);

private:

	void CreateBuffers();
	void ReleaseBuffers();

	CalCoreModel * GetCoreModel() { return mpCoreModel; }
	void CreateInstance(cSkeletalMesh * lpMesh);
	std::string macFile;
	std::list<sAnimationDef> mAnimationDefs;
	std::list<int> mMeshIndexes;
	CalCoreModel * mpCoreModel;

	//Vertex Buffers
	unsigned mVboVertices;
	std::vector<unsigned> mVboTexture;
	unsigned mVboNormals;
	unsigned mVboWeight;
	unsigned mVboBoneIx;
	unsigned mVboIndex;
	unsigned muiIndexCount;


};
#endif
