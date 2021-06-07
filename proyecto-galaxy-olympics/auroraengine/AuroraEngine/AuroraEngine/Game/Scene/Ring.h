#ifndef RING_H
#define RING_H

#include "Object.h"
#include "../SoundManager.h"

class cRing : public cObject
{
	public:
		cRing();
		//	void Init();
	//	void Init( const std::string &lacNameID,const std::string &lacFile );
	//	void Deinit();
		
		void Update( float lfTimestep );
		
		void Render();
		
};
#endif