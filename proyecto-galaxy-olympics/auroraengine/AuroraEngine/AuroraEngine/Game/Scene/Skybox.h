#ifndef SKYBOX_H
#define SKYBOX_H

#include "Object.h"

class cSkybox : public cObject
{
	public:
		cSkybox() { this->meType = eSkybox; }
	//	void Init();

	//	void Init( const std::string &lacNameID,const std::string &lacFile );

	//	void Deinit();
		
		void Update( float lfTimestep );
		
		void Render();
		
};
#endif