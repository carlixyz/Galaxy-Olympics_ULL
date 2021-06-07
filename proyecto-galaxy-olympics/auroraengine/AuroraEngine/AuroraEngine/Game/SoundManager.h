#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "../Utility/Singleton.h"

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <al.h>
#include <alc.h>
#include <sstream>
#include <list>
#include <string>


#define MAX_NUM_SOURCES 60


class cSoundManager : public cSingleton<cSoundManager>
{
public:
	friend class cSingleton<cSoundManager>;
	void Init();
	void Deinit();
	void Update(float lfTimestep);
	void Play(const char* lacFile, float lfGain);
	int AddSource(float x, float y, float z, const char* lacFile);

	void PlayFile(const char* lacFile, float lfGain);
	

private:
	ALCdevice *mDevice;                                                          //Create an OpenAL Device
    ALCcontext *mContext; 
	ALuint* sources;
	ALuint* buffers;
	float** sourcePositions;

	typedef std::list<std::string> SoundFilesList ;
	typedef SoundFilesList::iterator lSoundIt;

	SoundFilesList mSoundList;

//	std::vector<ALuint>	SourceList ;

	int miNumSources; 

	bool isPlaying(ALuint sourceId);
	
};

#endif