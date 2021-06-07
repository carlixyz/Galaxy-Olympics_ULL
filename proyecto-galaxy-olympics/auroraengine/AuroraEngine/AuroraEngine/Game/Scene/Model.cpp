#include "Model.h"
#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>
#include <cassert>
#include "../../Graphics/Meshes/MeshManager.h"
#include "../../Graphics/Meshes/Mesh.h"

#include "../../Graphics/Material/MaterialManager.h"
#include "../../Graphics/Material/MaterialData.h"
#include "../../Graphics/Material/Material.h"
#include "../../Utility/FilesUtils.h"
//#include "../../Utility/Debug.h"


bool cModel::Init(const std::string &lacNameID,const std::string &lacFile, bool lbBoundingBox)
{
	macFile = lacFile;
	mbLoaded = false;

	//Creamos una instancia del importador
	Assimp::Importer lImporter;

	//Cargamos la escena
	const aiScene* lpScene = lImporter.ReadFile(lacFile.c_str(), 
		aiProcess_CalcTangentSpace		|
		aiProcess_Triangulate			|
		aiProcess_JoinIdenticalVertices	|
		aiProcess_SortByPType);

	float fMaxX=0, fMinX=0, fMaxY=0, fMinY=0, fMaxZ=0, fMinZ=0;
	
	for (unsigned j=0; j< lpScene->mNumMeshes; j++)
		for (unsigned i=0; i< (lpScene->mMeshes[j])->mNumVertices; i++)
		{
			aiVector3D vertex;
			vertex = (lpScene->mMeshes[j])->mVertices[i];
			if (vertex.x > fMaxX) fMaxX=vertex.x;
			if (vertex.x < fMinX) fMinX=vertex.x;
			if (vertex.y > fMaxY) fMaxY=vertex.y;
			if (vertex.y < fMinY) fMinY=vertex.y;
			if (vertex.z > fMaxZ) fMaxZ=vertex.z;
			if (vertex.z < fMinZ) fMinZ=vertex.z;
		}
	

	cMatrix lcTransformation;
	lcTransformation.rows[0].x = lpScene->mRootNode->mChildren[1]->mTransformation.a1;
	lcTransformation.rows[0].y = lpScene->mRootNode->mChildren[1]->mTransformation.a2;
	lcTransformation.rows[0].z = lpScene->mRootNode->mChildren[1]->mTransformation.a3;
	lcTransformation.rows[0].w = lpScene->mRootNode->mChildren[1]->mTransformation.a4;
	lcTransformation.rows[1].x = lpScene->mRootNode->mChildren[1]->mTransformation.b1;
	lcTransformation.rows[1].y = lpScene->mRootNode->mChildren[1]->mTransformation.b2;
	lcTransformation.rows[1].z = lpScene->mRootNode->mChildren[1]->mTransformation.b3;
	lcTransformation.rows[1].w = lpScene->mRootNode->mChildren[1]->mTransformation.b4;
	lcTransformation.rows[2].x = lpScene->mRootNode->mChildren[1]->mTransformation.c1;
	lcTransformation.rows[2].y = lpScene->mRootNode->mChildren[1]->mTransformation.c2;
	lcTransformation.rows[2].z = lpScene->mRootNode->mChildren[1]->mTransformation.c3;
	lcTransformation.rows[2].w = lpScene->mRootNode->mChildren[1]->mTransformation.c4;
	lcTransformation.rows[3].x = lpScene->mRootNode->mChildren[1]->mTransformation.d1;
	lcTransformation.rows[3].y = lpScene->mRootNode->mChildren[1]->mTransformation.d2;
	lcTransformation.rows[3].z = lpScene->mRootNode->mChildren[1]->mTransformation.d3;
	lcTransformation.rows[3].w = lpScene->mRootNode->mChildren[1]->mTransformation.d4;

	if (lbBoundingBox)
	{
		mCollisionObject = new cBoundingBox();
		mCollisionObject->Init( lcTransformation,
  			cVec3(fMinX,fMinY,fMinZ),cVec3(fMaxX,fMaxY,fMaxZ)	);
	}
	else
	{
		mCollisionObject = new cBoundingSphere();
		mCollisionObject->Init( lcTransformation,
  			cVec3((fMinX+fMaxX)*0.5f,(fMinY+fMaxY)*0.5f,(fMinZ+fMaxZ)*0.5f),
			cVec3(fMaxX,fMaxY,fMaxZ)	);
	}
	

	//Debug().ToOutput(" Scale:%f", lpScene->mRootNode->mChildren[1]->mTransformation.a1);	

	//Comprobamos que todo ha ido bien
	if( !lpScene) 
	{
		printf( lImporter.GetErrorString());
		return false;
	}

	ProcessScene(lpScene);
	lImporter.FreeScene();
	mbLoaded = true;
	return true;
}

void cModel::ProcessScene(const aiScene* lpScene)
{
	for( unsigned luiIndex = 0; luiIndex < lpScene->mNumMeshes; ++luiIndex)
	{
		char lacMeshName[512];
		sprintf(lacMeshName, "%s_%d", macFile.c_str(), luiIndex);
		cResourceHandle lHandle;
		lHandle = cMeshManager::Get().LoadResource(lacMeshName, lpScene->mMeshes[luiIndex], kuiStaticMesh);
		mMeshList.push_back(lHandle);
		int liMaterialIndex = lpScene->mMeshes[luiIndex]->mMaterialIndex;
		mMeshMaterialIndexList.push_back(liMaterialIndex);
	}
	
	// Materials
	assert(lpScene->HasMaterials());
	for (unsigned luiIndex = 0;luiIndex<lpScene->mNumMaterials;++luiIndex)
	{
		// Access the material name
		aiString lName;
		lpScene->mMaterials[luiIndex]->Get(AI_MATKEY_NAME, lName);
		
		// Fill in the material data structure
		cMaterialData lMaterialData;
		lMaterialData.macPath = cFileUtils::GetDirectory(macFile);
		lMaterialData.mpMaterial = lpScene->mMaterials[luiIndex];
		
		// Load the resource
		cResourceHandle lHandle;
		lHandle = cMaterialManager::Get().LoadResource(lName.data, &lMaterialData, kuiStaticMesh);
		
		// Save the material on a vector in the Scene
		mMaterialList.push_back(lHandle);
	}
	if ( lpScene->mRootNode )
	{
		cMatrix lMatrix;
		lMatrix.LoadIdentity();
		ConvertNodesToObjects( lpScene->mRootNode, lMatrix );
	}
}

void cModel::Update( float lfTimestep )
{
	for (unsigned luiIndex=0;luiIndex < mSubmodelList.size();++luiIndex )
	{
		mSubmodelList[luiIndex]->Update(lfTimestep);
	}
}
void cModel::Render(cMatrix &lWorld)
{
	for (unsigned luiIndex=0;luiIndex < mSubmodelList.size();++luiIndex )
	{
		mSubmodelList[luiIndex]->Render(lWorld);
	}

	mCollisionObject->Update(lWorld);
	mCollisionObject->Render(); // too expensive
}

void cModel::Deinit()
{
	delete mCollisionObject;
	mCollisionObject = NULL;
	for (unsigned luiIndex=0;luiIndex < mSubmodelList.size();++luiIndex )
	{
		mSubmodelList[luiIndex]->Deinit();
		delete mSubmodelList[luiIndex];
	}
}

void cModel::ConvertNodesToObjects( aiNode *lpNode, cMatrix lTransform )
{
	// if node has meshes, create a new scene object for it
	cMatrix lNodeTransform( cVec4(lpNode->mTransformation.a1,
								  lpNode->mTransformation.b1,
								  lpNode->mTransformation.c1,
								  lpNode->mTransformation.d1),

							cVec4(lpNode->mTransformation.a2,
								  lpNode->mTransformation.b2,
								  lpNode->mTransformation.c2,
								  lpNode->mTransformation.d2),

							cVec4(lpNode->mTransformation.a3,
								  lpNode->mTransformation.b3,
								  lpNode->mTransformation.c3,
								  lpNode->mTransformation.d3),

							cVec4(lpNode->mTransformation.a4,
								  lpNode->mTransformation.b4,
								  lpNode->mTransformation.c4,
								  lpNode->mTransformation.d4) );

	lTransform = lNodeTransform * lTransform;

	if( lpNode->mNumMeshes > 0)
	{
		cSubmodel *lpObject = new cSubmodel;
		lpObject->Init();
		lpObject->SetName( lpNode->mName.data );
		lpObject->SetLocalMatrix(lTransform);

		for (unsigned luiIndex=0;luiIndex<lpNode->mNumMeshes;++luiIndex)
		{
			unsigned luiMeshIndex = lpNode->mMeshes[luiIndex];
			unsigned luiMaterialIndex;
			luiMaterialIndex = mMeshMaterialIndexList[luiMeshIndex];
			lpObject->AddMesh( mMeshList[luiMeshIndex],	mMaterialList[luiMaterialIndex] );
		}

		mSubmodelList.push_back(lpObject);
	}
	// continue for all child nodes
	for(unsigned luiIndex = 0;luiIndex<lpNode->mNumChildren;++luiIndex)
	{
		ConvertNodesToObjects( lpNode->mChildren[luiIndex], lTransform);
	}
}