#include <cassert>
#include "Texture.h"
#include "../GLHeaders.h"
#include "SOIL/SOIL.h"

bool cTexture::Init(const std::string &lacNameID, const std::string &lacFile)
{
	macFile = lacFile;
	muiTextureHandle = SOIL_load_OGL_texture(
					macFile.c_str(),
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS |	SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_COMPRESS_TO_DXT);
	assert( muiTextureHandle !=0);
	return muiTextureHandle != 0;
}

void cTexture::Deinit()
{
	glDeleteTextures(1, &muiTextureHandle);
	muiTextureHandle = 0;
}

