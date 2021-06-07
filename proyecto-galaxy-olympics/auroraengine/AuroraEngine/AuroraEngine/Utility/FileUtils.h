#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <ctime>

class cFileUtils
{
	public:
		static std::string GetDirectory(const std::string lacFile);
		static std::string GetFilename(const std::string lacFile);

		static float clamp(float lfValue, float lfMin, float lfMax); // ajustar un valor dentro de un rango

		static inline void RandomInit(){ srand(time(NULL)); }
		static float RandomFloat(float a, float b) ;
};

#endif