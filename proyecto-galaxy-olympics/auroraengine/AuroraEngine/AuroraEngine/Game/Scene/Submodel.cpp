#include "Submodel.h"

void cSubmodel::Init()
{
	macName = "";
	mLocalMatrix.LoadIdentity();
	mMeshHandles.resize(0);
	mMaterialHandles.resize(0);
}

void cSubmodel::AddMesh( cResourceHandle lMeshHandle, cResourceHandle lMaterialHandle )
{
	mMeshHandles.push_back( lMeshHandle );
	mMaterialHandles.push_back( lMaterialHandle );
}

void cSubmodel::Update( float lfTimestep )
{
	for (unsigned luiIndex = 0; luiIndex < mMeshHandles.size(); ++luiIndex)
	{
		cMesh *lpMesh = (cMesh *) mMeshHandles[luiIndex].GetResource();
		lpMesh->Update(lfTimestep);
	}
}

void cSubmodel::Render(cMatrix &lWorld)
{
	// Set World Matrix
	cGraphicManager::Get().SetWorldMatrix(mLocalMatrix * lWorld);

	for (unsigned luiIndex = 0; luiIndex < mMeshHandles.size(); ++luiIndex)
	{
		cMaterial * lpMaterial = ( cMaterial *) mMaterialHandles[luiIndex].GetResource();
		cMesh *lpMesh = (cMesh *)mMeshHandles[luiIndex].GetResource();

		// Prepare all the parameters for the render
		lpMaterial->PrepareRender();
		lpMesh->PrepareRender(mMaterialHandles[luiIndex]);
		
		// Set the fist pass
		bool lbContinue = lpMaterial->SetFirstPass();
		while (lbContinue)
		{
			// Render Mesh
			lpMesh->RenderMesh();
			// Prepare the next pass
			lbContinue = lpMaterial->SetNextPass();
		}
	}
}

void cSubmodel::Deinit()
{

}