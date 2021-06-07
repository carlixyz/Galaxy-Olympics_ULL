#ifndef MATERIAL_H
#define MATERIAL_H

#include "../../Utility/Resource.h"
#include "../../Utility/ResourceHandle.h"
#include <vector>
#include <sstream>
#include <aiMaterial.h> // C++ importer interface
#include "MaterialData.h"

struct cTextureData
{
	std::string macShaderTextureID;
	cResourceHandle mTexture;
};

class cMaterial : public cResource
{
public:
	
	cMaterial() { mbLoaded = false; }

	virtual bool Init( const std::string &lacNameID, const std::string &lacFile );
	
	virtual bool Init( const std::string &lacNameID,void * lpMemoryData,int liDataType);
	
	virtual void Deinit();
	
	virtual bool IsLoaded() { return mbLoaded; }
	
	void PrepareRender();
	
	bool EnableFirstPass();
	
	bool EnableNextPass();

	//void SetMaterial();

	bool SetFirstPass();

	bool SetNextPass();

	cResourceHandle GetEffect() { return mEffect; }

private:
	
	void ReadAllTextures(aiMaterial * lpAiMaterial,	cMaterialData * lpMaterialData);
	
	std::string macFile;
	
	std::vector<cTextureData> maTextureData;
	
	cResourceHandle mEffect;
	
	bool mbLoaded;
};

#endif;

