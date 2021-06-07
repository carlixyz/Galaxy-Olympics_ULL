#ifndef RESOURCE_H
#define RESOURCE_H

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string>


class cResource
{
public:
	
	virtual bool Init( const std::string &lacNameID,
		const std::string &lacFile ) { return false; }

	virtual bool Init( const std::string &lacNameID,
		void * lacMemoryData ) { return false; }
	
	virtual void Deinit() { ; }
	
	virtual bool IsLoaded() { return false; }
	
	virtual void Reload() { ; }
	
	bool IsThisResource( const std::string &lacNameID )
	{ return macNameID == lacNameID; }
	
	inline void SetNameID( const std::string &lacNameID )
	{ macNameID = lacNameID; }
	
	inline std::string GetNameID( ) { return macNameID; }
	
private:
		std::string macNameID;

};

#endif