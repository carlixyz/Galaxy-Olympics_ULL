#ifndef WINDOW
#define WINDOW

#include <windows.h>
#include "ApplicationProperties.h"
#include "..\Utility\Singleton.h"


class cWindow: public cSingleton<cWindow>
{
public:
	bool Init(cApplicationProperties &lProperties);
	void Update();
	bool Deinit();
	inline bool GetCloseApplication() {return mbCloseApplication;}
	inline HWND GetHWND () {return mWnd;}

	inline unsigned GetWidth() { return mProperties.muiWidth; }
	inline unsigned GetHeight() { return mProperties.muiHeight; }
	inline unsigned GetBpp() { return mProperties.muiBits; }
	inline HDC &GetHDC() { return mDC; }
private:

	static LRESULT CALLBACK WndProc( HWND lWnd, UINT lMsg, WPARAM lWParam, LPARAM lLParam);
	HINSTANCE mInstance;
	HWND mWnd;
	HDC mDC;
	cApplicationProperties mProperties;
	bool mbCloseApplication;
};

#endif