#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Object.h"

class cBackground : public cObject
{
	public:
		cBackground() { this->meType = eBackground; }
	//	void Init();

	//	void Init( const std::string &lacNameID,const std::string &lacFile );

	//	void Deinit();
		
		void Update( float lfTimestep );
		
		void Render();
		
};
#endif