#ifndef APPLICATION_PROPERTIES
#define APPLICATION_PROPERTIES

#include <iostream>

struct cApplicationProperties
{
public:
	void LoadConfiguration(char * filename); // Funci�n para cargar directamente de un XML

	std::string macApplicationName;			//Nombre de la aplicaci�n y de la ventana
	int muiWidth;							//Ancho de la ventana
	int muiHeight;							//Alto de la ventana
	int muiBits;							//Bits que tendr� cada pixel de la ventana. 24 RGB o 32 RGBA
	bool mbFullscreen;						// True si es a pantalla completa
};

#endif