#include "SoundManager.h"
#include "Scene/ObjectManager.h"
#include "Scene/Player.h"
#include <sstream>


void cSoundManager::Init()
{
	
	mDevice = alcOpenDevice(NULL);                                       //Open the device
	mContext = alcCreateContext(mDevice, NULL);                           //Give the device a context
	alcMakeContextCurrent(mContext); 
	miNumSources = 0;
	sources = new ALuint[MAX_NUM_SOURCES];
	buffers = new ALuint[MAX_NUM_SOURCES];
	sourcePositions = new float*[MAX_NUM_SOURCES];

	AddSource(0.0f, 0.0f, 0.0f, "./Data/WAVE/fondo.wav");
}

int cSoundManager::AddSource(float x, float y, float z, const char* lacFile)
{
	
	sources[miNumSources] = miNumSources;
	
	sourcePositions[miNumSources] = new float[3];
	sourcePositions[miNumSources][0] = x;
	sourcePositions[miNumSources][1] = y;
	sourcePositions[miNumSources][2] = z;

	FILE *fp;										//Variables to store info about the WAVE file (all of them is not needed for OpenAL)
    char type[4];
    DWORD size,chunkSize;
    short formatType,channels;
    DWORD sampleRate,avgBytesPerSec;
    short bytesPerSample,bitsPerSample;
    DWORD dataSize;

	unsigned char* buf;
	//Loading of the WAVE file
    fp = NULL;																				//Create FILE pointer for the WAVE file
    fp=fopen(lacFile,"rb");													//Open the WAVE file
	if (fp)																					//Check that the WAVE file is OK
	{  
		fread(type,sizeof(char),4,fp);														//Reads the first bytes in the file
		if(type[0]=='R' && type[1]=='I' && type[2]=='F' && type[3]=='F')						//Should be "RIFF"
		{								
			fread(&size, sizeof(DWORD),1,fp);												//Continue to read the file
			fread(type, sizeof(char),4,fp);													//Continue to read the file
			if (type[0]=='W' && type[1]=='A' && type[2]=='V' && type[3]=='E')				//This part should be "WAVE"
			{                                            
				fread(type,sizeof(char),4,fp);												//Continue to read the file
				if (type[0]=='f' && type[1]=='m' && type[2]=='t' && type[3]==' ')				//This part should be "fmt "
				{													
					fread(&chunkSize,sizeof(DWORD),1,fp);									//Now we know that the file is a acceptable WAVE file
					fread(&formatType,sizeof(short),1,fp);									//Info about the WAVE data is now read and stored
					fread(&channels,sizeof(short),1,fp);
					fread(&sampleRate,sizeof(DWORD),1,fp);
					fread(&avgBytesPerSec,sizeof(DWORD),1,fp);
					fread(&bytesPerSample,sizeof(short),1,fp);
					fread(&bitsPerSample,sizeof(short),1,fp);
					fread(type,sizeof(char),4,fp);
					if (type[0]=='d' && type[1]=='a' && type[2]=='t' && type[3]=='a')           //This part should be "data"
					{
						fread(&dataSize,sizeof(DWORD),1,fp);                                //The size of the sound data is read
						buf= new unsigned char[dataSize];									//Allocate memory for the sound data	
						fread(buf,sizeof(BYTE),dataSize,fp);
																							//Stores the sound data
						ALuint frequency=sampleRate;;                                       //The Sample Rate of the WAVE file
						ALenum format=0;                                                    //The audio format (bits per sample, number of channels)
						
						alGenBuffers(1, &buffers[miNumSources]);                                           //Generate one OpenAL Buffer and link to "buffer"
						alGenSources(1, &sources[miNumSources]);											//Generate one OpenAL Source and link to "source"
						 
						if(bitsPerSample == 8)												//Figure out the format of the WAVE file
						{
							if(channels == 1)
								format = AL_FORMAT_MONO8;
							else if(channels == 2)
								format = AL_FORMAT_STEREO8;
						}
						else if(bitsPerSample == 16)
						{
							if(channels == 1)
								format = AL_FORMAT_MONO16;
							else if(channels == 2)
								format = AL_FORMAT_STEREO16;
						}
						alBufferData(buffers[miNumSources], format, buf, dataSize, frequency);                    //Store the sound data in the OpenAL Buffer	
					}
				}				
			}
		}
	}
	//Sound setting variables
	
	alEnable(AL_DISTANCE_MODEL);
	alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	
	ALfloat SourcePos[] = { sourcePositions[miNumSources][0], sourcePositions[miNumSources][1], sourcePositions[miNumSources][2]};                                    //Position of the source sound
	ALfloat SourceVel[] = { 0.0, 0.0, 1.0 };  //Velocity of the source sound
	
	//cPlayer* lPlayer = cObjectManager::Get().GetPlayer();

	//ALfloat ListenerPos[] = { lPlayer->GetMatrix().GetPosition().x, lPlayer->GetMatrix().GetPosition().y, lPlayer->GetMatrix().GetPosition().z};                                  //Position of the listener
	//ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };                                  //Velocity of the listener
	//ALfloat ListenerOri[] = { 0.0, 0.0, 1.0,  0.0, 1.0, 0.0 };                 //Orientation of the listener
	//																			//First direction vector, then vector pointing up) 
	////Listener                                                                               
	//alListenerfv(AL_POSITION,    ListenerPos);                                  //Set position of the listener
	//alListenerfv(AL_VELOCITY,    ListenerVel);                                  //Set velocity of the listener
	//alListenerfv(AL_ORIENTATION, ListenerOri);                                  //Set orientation of the listener

	////Source
	//alSourcei (sources[miNumSources], AL_BUFFER,   buffers[miNumSources]);									//Link the buffer to the source
	//alSourcef (sources[miNumSources], AL_PITCH,    1.0f     );                                 //Set the pitch of the source
	//alSourcef (sources[miNumSources], AL_GAIN,     1.0f     );  
	//alSourcef(sources[miNumSources], AL_ROLLOFF_FACTOR, 1.0f);
	//alSourcef(sources[miNumSources], AL_REFERENCE_DISTANCE, 1.0f);	//Set the gain of the source
	//alSourcefv(sources[miNumSources], AL_POSITION, SourcePos);                                 //Set the position of the source
	//alSourcefv(sources[miNumSources], AL_VELOCITY, SourceVel);                                 //Set the velocity of the source
	//alSourcei (sources[miNumSources], AL_LOOPING,  AL_FALSE);                                 //Set if source is looping sound
	
	miNumSources += 1;
	return miNumSources;
	
}

bool cSoundManager::isPlaying(ALuint sourceId)
{
	ALint state;
	if(alIsSource(sourceId) == AL_FALSE)
		return false;

	state = AL_INITIAL;
	alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

	switch(state)
	{
	case AL_PLAYING:
		return true;
	default:
		break;
	}
	return false;
}


void cSoundManager::Update(float lfTimestep)
{

	for(int i = 0; i < miNumSources; i++)
	{
		if(!isPlaying(sources[i]))
		{
			ALfloat SourcePos[] = { sourcePositions[i][0], sourcePositions[i][1], sourcePositions[i][2]};                                    //Position of the source sound
			ALfloat SourceVel[] = { 0.0, 0.0, 10.0 };  //Velocity of the source sound
	
			cPlayer* lPlayer = cObjectManager::Get().GetPlayer();
		
			ALfloat ListenerPos[] = { lPlayer->GetMatrix().GetPosition().x, lPlayer->GetMatrix().GetPosition().y, lPlayer->GetMatrix().GetPosition().z};                                  //Position of the listener
			ALfloat ListenerVel[] = { 0.0, 0.0, 1.0 };                                  //Velocity of the listener
			ALfloat ListenerOri[] = { 0.0, 0.0, 1.0,  0.0, 1.0, 0.0 };                 //Orientation of the listener
																				//First direction vector, then vector pointing up) 
			//Listener                                                                               
			alListenerfv(AL_POSITION,    ListenerPos);                                  //Set position of the listener
			alListenerfv(AL_VELOCITY,    ListenerVel);                                  //Set velocity of the listener
			alListenerfv(AL_ORIENTATION, ListenerOri);                                  //Set orientation of the listener

			//Source

			alSourcei (sources[i], AL_BUFFER,   buffers[i]);									//Link the buffer to the source
			alSourcef (sources[i], AL_PITCH,    1.0f     );                                 //Set the pitch of the source
			alSourcef (sources[i], AL_GAIN,     1.0f     );  
			alSourcef(sources[i], AL_ROLLOFF_FACTOR, 1.0f);
			alSourcef(sources[i], AL_REFERENCE_DISTANCE, 1.0f);	//Set the gain of the source
			//alSourcefv(sources[miNumSources], AL_POSITION, SourcePos);                                 //Set the position of the source
			alSourcefv(sources[i], AL_VELOCITY, SourceVel);                                 //Set the velocity of the source
			alSourcei (sources[i], AL_LOOPING,  AL_FALSE);                                 //Set if source is looping sound
			
			alSourcePlay(sources[i]);
		}
	}
}

void cSoundManager::Deinit()
{
	//fclose(fp);                                                                 //Close the WAVE file
 //   delete[] buf;                                                               //Delete the sound data buffer
                                            
	for(int i = 0; i < miNumSources; i++)
	{
		alDeleteSources(1, &sources[i]);
		alDeleteBuffers(1, &buffers[i]);
		//delete[] sourcePositions[i];
	}

	mSoundList.clear();
//	SourceList.clear();
                                      
    alcMakeContextCurrent(NULL);                                                //Make no context current
    alcDestroyContext(mContext);                                                 //Destroy the OpenAL Context
    alcCloseDevice(mDevice);   
	delete sourcePositions;
	miNumSources = 0;
}



void cSoundManager::Play (const char* lacFile, float lfGain)
{
	FILE *fp;										//Variables to store info about the WAVE file (all of them is not needed for OpenAL)
    char type[4];
    DWORD size,chunkSize;
    short formatType,channels;
    DWORD sampleRate,avgBytesPerSec;
    short bytesPerSample,bitsPerSample;
    DWORD dataSize;
	ALuint source;                                                      //Is the name of source (where the sound come from)
	ALuint buffer;
	unsigned char* buf;
	//Loading of the WAVE file
    fp = NULL;																				//Create FILE pointer for the WAVE file
    fp=fopen(lacFile,"rb");													//Open the WAVE file
	if (fp)																					//Check that the WAVE file is OK
	{  
		fread(type,sizeof(char),4,fp);														//Reads the first bytes in the file
		if(type[0]=='R' && type[1]=='I' && type[2]=='F' && type[3]=='F')						//Should be "RIFF"
		{								
			fread(&size, sizeof(DWORD),1,fp);												//Continue to read the file
			fread(type, sizeof(char),4,fp);													//Continue to read the file
			if (type[0]=='W' && type[1]=='A' && type[2]=='V' && type[3]=='E')				//This part should be "WAVE"
			{                                            
				fread(type,sizeof(char),4,fp);												//Continue to read the file
				if (type[0]=='f' && type[1]=='m' && type[2]=='t' && type[3]==' ')				//This part should be "fmt "
				{													
					fread(&chunkSize,sizeof(DWORD),1,fp);									//Now we know that the file is a acceptable WAVE file
					fread(&formatType,sizeof(short),1,fp);									//Info about the WAVE data is now read and stored
					fread(&channels,sizeof(short),1,fp);
					fread(&sampleRate,sizeof(DWORD),1,fp);
					fread(&avgBytesPerSec,sizeof(DWORD),1,fp);
					fread(&bytesPerSample,sizeof(short),1,fp);
					fread(&bitsPerSample,sizeof(short),1,fp);
					fread(type,sizeof(char),4,fp);
					if (type[0]=='d' && type[1]=='a' && type[2]=='t' && type[3]=='a')           //This part should be "data"
					{
						fread(&dataSize,sizeof(DWORD),1,fp);                                //The size of the sound data is read
						buf= new unsigned char[dataSize];									//Allocate memory for the sound data	
						fread(buf,sizeof(BYTE),dataSize,fp);
																							//Stores the sound data
						ALuint frequency=sampleRate;;                                       //The Sample Rate of the WAVE file
						ALenum format=0;                                                    //The audio format (bits per sample, number of channels)
						
						alGenBuffers(1, &buffer);                                           //Generate one OpenAL Buffer and link to "buffer"
						alGenSources(1, &source);											//Generate one OpenAL Source and link to "source"
						 
						if(bitsPerSample == 8)												//Figure out the format of the WAVE file
						{
							if(channels == 1)
								format = AL_FORMAT_MONO8;
							else if(channels == 2)
								format = AL_FORMAT_STEREO8;
						}
						else if(bitsPerSample == 16)
						{
							if(channels == 1)
								format = AL_FORMAT_MONO16;
							else if(channels == 2)
								format = AL_FORMAT_STEREO16;
						}
						alBufferData(buffer, format, buf, dataSize, frequency);                    //Store the sound data in the OpenAL Buffer	
					}
				}				
			}
		}
	}
	cPlayer* lPlayer = cObjectManager::Get().GetPlayer();

	ALfloat SourcePos[] = { 0.0, 0.0, 1.0 };                                    //Position of the source sound
	ALfloat SourceVel[] = { 0.0, 0.0, 1.0 };                                    //Velocity of the source sound
	ALfloat ListenerPos[] = { 0.0f, 0.0f, 1.0f};                                              //Position of the listener
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };                                  //Velocity of the listener
	ALfloat ListenerOri[] = { 0.0, 0.0, 1.0,  0.0, 1.0, 0.0 };                 //Orientation of the listener
																				//First direction vector, then vector pointing up) 
	//Listener                                                                               
	alListenerfv(AL_POSITION,    ListenerPos);                                  //Set position of the listener
	alListenerfv(AL_VELOCITY,    ListenerVel);                                  //Set velocity of the listener
	alListenerfv(AL_ORIENTATION, ListenerOri);                                  //Set orientation of the listener

	//Source
	alSourcei (source, AL_BUFFER,   buffer);									//Link the buffer to the source
	alSourcef (source, AL_PITCH,    1.0f     );                                 //Set the pitch of the source
	alSourcef (source, AL_GAIN,     1.0f     );  
	alSourcefv(source, AL_POSITION, SourcePos);                                 //Set the position of the source
	alSourcefv(source, AL_VELOCITY, SourceVel);                                 //Set the velocity of the source
	alSourcei (source, AL_LOOPING,  AL_FALSE );                                 //Set if source is looping sound

	alSourcePlay(source);                                                       //Play the sound buffer linked to the source
}

void cSoundManager::PlayFile(const char *lacFile, float lfGain)
{

	for( lSoundIt lsIt = mSoundList.begin(); lsIt != mSoundList.end() ; ++lsIt )
	{
		std::string & lsSourceName = (*lsIt);

		if(  lsSourceName.substr(lsSourceName.find_last_of("#") + 1) == lacFile )
		{
			OutputDebugString("\n \n Found COincidence AUDIO ! \n");

			int liFileIndex = lsSourceName[0];
			ALint val;
			alGetSourcei(liFileIndex, AL_SOURCE_STATE, &val);
            if(val != AL_PLAYING)
			{
					alSourceRewind(liFileIndex);
					alSourcePlay(liFileIndex);
					return;
 //                   alSourceStop(source);
			}
			else return;
		}

	

	FILE *fp;										//Variables to store info about the WAVE file (all of them is not needed for OpenAL)
    char type[4];
    DWORD size,chunkSize;
    short formatType,channels;
    DWORD sampleRate,avgBytesPerSec;
    short bytesPerSample,bitsPerSample;
    DWORD dataSize;
	ALuint source;                                                      //Is the name of source (where the sound come from)
	ALuint buffer;
	unsigned char* buf;
	//Loading of the WAVE file
    fp = NULL;																				//Create FILE pointer for the WAVE file
    fp=fopen(lacFile,"rb");													//Open the WAVE file
	if (fp)																					//Check that the WAVE file is OK
	{  
		fread(type,sizeof(char),4,fp);														//Reads the first bytes in the file
		if(type[0]=='R' && type[1]=='I' && type[2]=='F' && type[3]=='F')						//Should be "RIFF"
		{								
			fread(&size, sizeof(DWORD),1,fp);												//Continue to read the file
			fread(type, sizeof(char),4,fp);													//Continue to read the file
			if (type[0]=='W' && type[1]=='A' && type[2]=='V' && type[3]=='E')				//This part should be "WAVE"
			{                                            
				fread(type,sizeof(char),4,fp);												//Continue to read the file
				if (type[0]=='f' && type[1]=='m' && type[2]=='t' && type[3]==' ')				//This part should be "fmt "
				{													
					fread(&chunkSize,sizeof(DWORD),1,fp);									//Now we know that the file is a acceptable WAVE file
					fread(&formatType,sizeof(short),1,fp);									//Info about the WAVE data is now read and stored
					fread(&channels,sizeof(short),1,fp);
					fread(&sampleRate,sizeof(DWORD),1,fp);
					fread(&avgBytesPerSec,sizeof(DWORD),1,fp);
					fread(&bytesPerSample,sizeof(short),1,fp);
					fread(&bitsPerSample,sizeof(short),1,fp);
					fread(type,sizeof(char),4,fp);
					if (type[0]=='d' && type[1]=='a' && type[2]=='t' && type[3]=='a')           //This part should be "data"
					{
						fread(&dataSize,sizeof(DWORD),1,fp);                                //The size of the sound data is read
						buf= new unsigned char[dataSize];									//Allocate memory for the sound data	
						fread(buf,sizeof(BYTE),dataSize,fp);
																							//Stores the sound data
						ALuint frequency=sampleRate;;                                       //The Sample Rate of the WAVE file
						ALenum format=0;                                                    //The audio format (bits per sample, number of channels)
						
						alGenBuffers(1, &buffer);                                           //Generate one OpenAL Buffer and link to "buffer"
						alGenSources(1, &source);											//Generate one OpenAL Source and link to "source"
						 
						if(bitsPerSample == 8)												//Figure out the format of the WAVE file
						{
							if(channels == 1)
								format = AL_FORMAT_MONO8;
							else if(channels == 2)
								format = AL_FORMAT_STEREO8;
						}
						else if(bitsPerSample == 16)
						{
							if(channels == 1)
								format = AL_FORMAT_MONO16;
							else if(channels == 2)
								format = AL_FORMAT_STEREO16;
						}
						alBufferData(buffer, format, buf, dataSize, frequency);                    //Store the sound data in the OpenAL Buffer	
					}
				}				
			}
		}
	}
	cPlayer* lPlayer = cObjectManager::Get().GetPlayer();

	ALfloat SourcePos[] = { 0.0, 0.0, 1.0 };                                    //Position of the source sound
	ALfloat SourceVel[] = { 0.0, 0.0, 1.0 };                                    //Velocity of the source sound
	ALfloat ListenerPos[] = { 0.0f, 0.0f, 1.0f};                                              //Position of the listener
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };                                  //Velocity of the listener
	ALfloat ListenerOri[] = { 0.0, 0.0, 1.0,  0.0, 1.0, 0.0 };                 //Orientation of the listener
																				//First direction vector, then vector pointing up) 
	//Listener                                                                               
	alListenerfv(AL_POSITION,    ListenerPos);                                  //Set position of the listener
	alListenerfv(AL_VELOCITY,    ListenerVel);                                  //Set velocity of the listener
	alListenerfv(AL_ORIENTATION, ListenerOri);                                  //Set orientation of the listener

	//Source
	alSourcei (source, AL_BUFFER,   buffer);									//Link the buffer to the source
	alSourcef (source, AL_PITCH,    1.0f     );                                 //Set the pitch of the source
	alSourcef (source, AL_GAIN,     1.0f     );  
	alSourcefv(source, AL_POSITION, SourcePos);                                 //Set the position of the source
	alSourcefv(source, AL_VELOCITY, SourceVel);                                 //Set the velocity of the source
	alSourcei (source, AL_LOOPING,  AL_FALSE );                                 //Set if source is looping sound

	alSourcePlay(source);    

	std::stringstream lsInteger (std::stringstream::in | std::stringstream::out);

	lsInteger << ((int)source);
	std::string lsFileSource = lsInteger.str();
	lsFileSource += "#";
	lsFileSource += lacFile;

	mSoundList.push_back(lsFileSource);
	}
}







