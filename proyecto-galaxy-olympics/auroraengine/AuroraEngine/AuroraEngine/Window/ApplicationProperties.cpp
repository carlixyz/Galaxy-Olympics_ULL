#include "ApplicationProperties.h"

#include <windows.h>
#include <tinystr.h>
#include <tinyxml.h>

void cApplicationProperties::LoadConfiguration(char * filename)
{
	TiXmlDocument doc(filename);
		
	if(!doc.LoadFile())
		OutputDebugString("Application Properties XML Load: FAILED\n");

	TiXmlHandle lhDoc(&doc);
	TiXmlElement* lpElement;
	TiXmlHandle lhRoot(0);
	
	lpElement = lhDoc.FirstChild("Application").Element();
	lhRoot = TiXmlHandle(lpElement);

	if(lpElement->Attribute("name"))// The Query String had a bug with spaces 
		this->macApplicationName = lpElement->Attribute("name");	
	
	if(lpElement->Attribute("fullscreen"))
	{
		std::string const & lsBoolean = lpElement->Attribute("fullscreen");
		this->mbFullscreen = ( lsBoolean == "true" );
	}

	lpElement = lhRoot.FirstChild("BitsPerPixel").Element();
	this->muiBits = atoi(lpElement->GetText());

	lpElement = lhRoot.FirstChild("Size").Element();

	lpElement->QueryIntAttribute("width", & this->muiWidth);

	lpElement->QueryIntAttribute("height", & this->muiHeight);
/*
	if(lpElement->Attribute("width"))
		this->muiWidth = atoi(lpElement->Attribute("width")); 

	if(lpElement->Attribute("height"))
		this->muiHeight = atoi(lpElement->Attribute("height"));
*/
}
