#include "TextureManager.h"
#include "Texture.h"

cResource * cTextureManager::LoadResourceInternal(std::string lacNameID, const std::string &lacFile)
{
	cTexture * lpTexture = new cTexture();
	if(!lpTexture->Init(lacNameID, lacFile))
	{
		delete lpTexture;
		return NULL;
	}

	return lpTexture;
}
