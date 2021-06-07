#include "FileUtils.h"


std::string
cFileUtils::GetDirectory(const std::string lacFile)
{
	for (int liCharIndex=lacFile.length()-1;liCharIndex >= 0;--liCharIndex)
	{
		if (lacFile[liCharIndex] == '\\' || lacFile[liCharIndex] == '/')
		{
			return lacFile.substr(0, liCharIndex);
		}
	}
	return "";
}

std::string
cFileUtils::GetFilename(const std::string lacFile)
{
	for (int liCharIndex = lacFile.length()-1; liCharIndex >= 0; --liCharIndex)
	{
		if (lacFile[liCharIndex] == '\\' || lacFile[liCharIndex] == '/')
		{
			return lacFile.substr(liCharIndex +1);
		}
	}
	return lacFile;
}

float cFileUtils::clamp(float lfValue, float lfMin, float lfMax)
{

	//True should cast to 1.0, false to 0.0
  float minAlpha = static_cast<float>(lfValue < lfMin);

  float maxAlpha = static_cast<float>(lfValue > lfMax);

  //Equals max if maxAlpha = 1.0, result otherwise. //Equals min if minAlpha = 1.0, result otherwise.
  return ( maxAlpha * lfMax + (1 - maxAlpha) * (minAlpha * lfMin + (1 - minAlpha) * lfValue) );

 } 

float cFileUtils::RandomFloat(float a, float b)
{

    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}



