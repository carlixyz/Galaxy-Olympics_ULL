
#ifndef SINGLETON
#define SINGLETON

template<typename T> class cSingleton
{
public:
	static T& Get()
	{
		static T lInstance;
		return lInstance;
	}
};

#endif
