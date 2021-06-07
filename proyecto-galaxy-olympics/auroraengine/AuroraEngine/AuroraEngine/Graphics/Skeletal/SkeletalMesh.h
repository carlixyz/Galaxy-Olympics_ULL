#ifndef SKELETAL_MESH_H
#define SKELETAL_MESH_H

#include "../Meshes/Mesh.h"
#include "../../Libraries/MathLib/MathLib.h"

class CalModel;

class cSkeletalMesh : public cMesh
{
public:
	cSkeletalMesh() : cMesh() { }
	friend class cSkeletalCoreModel;
	virtual bool Init(const std::string &lacNameID, void * lpMemoryData, int liDataType);
	virtual void Deinit();
	virtual void Update(float lfTimestep);
	virtual void PrepareRender(cResourceHandle lMaterial);
	inline void SetWorldMatrix(cMatrix &lWorld){ mWorldMatrix = lWorld; };
	virtual void RenderMesh();
	virtual bool IsLoaded() { return (mpCal3DModel != NULL); }
	void RenderSkeleton();
	bool PlayAnim(const std::string & lacAnimName, float lfWeight, float lfDelayIn, float lfDelayOut =0.0f);
	void StopAnim(const std::string &lacAnimName, float lfDelayOut = 0.0f);
private:
	cMatrix mWorldMatrix;
	CalModel * mpCal3DModel;
	cSkeletalCoreModel * mpCoreModel;
};

#endif