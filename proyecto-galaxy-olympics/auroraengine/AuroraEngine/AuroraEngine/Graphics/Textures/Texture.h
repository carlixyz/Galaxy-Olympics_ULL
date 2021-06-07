#ifndef C_TEXTURE
#define C_TEXTURE

#include <string>
#include "../../Utility/Resource.h"

class cTexture : public cResource
{
public:
	cTexture() { muiTextureHandle = 0; }
	virtual bool Init(const std::string &lacNameID, const std::string &lacFile);
	virtual void Deinit();
	virtual bool IsLoaded() { return (muiTextureHandle !=0); }
	inline unsigned int GetTextureHandle() { return muiTextureHandle; }

private:
	std::string macFile;
	unsigned int muiTextureHandle;
};

#endif
