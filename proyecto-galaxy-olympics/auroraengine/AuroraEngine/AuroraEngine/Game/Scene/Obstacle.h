#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Object.h"

class cObstacle : public cObject
{
	public:
		cObstacle() { this->meType = eObstacle; }
	//	void Init();

	//	void Init( const std::string &lacNameID,const std::string &lacFile );

	//	void Deinit();
		
		void Update( float lfTimestep );
		
		void Render();
		
};
#endif