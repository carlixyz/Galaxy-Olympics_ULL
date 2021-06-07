#include "Window.h"

bool cWindow::Init(cApplicationProperties &lProperties)
{
	//Init vars
	mDC = NULL;
	mWnd = NULL;
	mInstance = GetModuleHandle(NULL);
	mProperties = lProperties;
	mbCloseApplication=false;

	WNDCLASS lWndClass;
	//Redraw on size, and own dc for window
	lWndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	//wndProc handles messages
	lWndClass.lpfnWndProc = (WNDPROC) WndProc;
	//No extra window data
	lWndClass.cbClsExtra = 0;
	//No extra window data
	lWndClass.cbWndExtra = 0;
	//Set the instance
	lWndClass.hInstance = mInstance;
	//Load the default icon
	lWndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	// Load the arrow pointer
	lWndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	// No background required for GL
	lWndClass.hbrBackground = NULL;
	// We dont want a menu
	lWndClass.lpszMenuName = NULL;
	// Set the class name
	lWndClass.lpszClassName = lProperties.macApplicationName.c_str();

	int liRet = RegisterClass(&lWndClass);
	if(!liRet)
	{
		DWORD lError = GetLastError();
		MessageBox(NULL, "Failed to Register the window", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (lProperties.mbFullscreen)
	{
		//Device mode
		DEVMODE lScreenSettings;
		//Clear the memory
		memset( &lScreenSettings, 0, sizeof(lScreenSettings));
		lScreenSettings.dmSize = sizeof(lScreenSettings);
		lScreenSettings.dmPelsWidth = lProperties.muiWidth;
		lScreenSettings.dmPelsHeight = lProperties.muiHeight;
		lScreenSettings.dmBitsPerPel = lProperties.muiBits;
		lScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//try to set selected mode and get results
		LONG lResult = ChangeDisplaySettings(&lScreenSettings, CDS_FULLSCREEN);
		if (lResult != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL, "The Requested Fullscreen mode is not supported by\n your video card. Use windowed mode instead?", "ERROR",
				MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				mProperties.mbFullscreen = false;
			}
			else
			{
				MessageBox(NULL, "Program will now close", "ERROR", MB_OK | MB_ICONSTOP);
				return false;
			}
		}
	}
	
	DWORD lExStyle;
	DWORD lStyle;

	if(mProperties.mbFullscreen)
	{
		//Window Extended Style
		lExStyle = WS_EX_APPWINDOW;
		//Window Style
		lStyle = WS_POPUP;
		// Hide Mouse Pointer
		ShowCursor(FALSE);
	}
	else
	{
		// Window Extended Style
		lExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		// Window Style
		lStyle = WS_OVERLAPPEDWINDOW;
	}

	RECT lWindowRect;
	lWindowRect.left = (long) 0;
	lWindowRect.right = (long) lProperties.muiWidth;
	lWindowRect.top = (long) 0;
	lWindowRect.bottom = (long) lProperties.muiHeight;

	AdjustWindowRectEx(&lWindowRect, lStyle, FALSE, lExStyle);

	//Create the window
	mWnd = CreateWindowEx (lExStyle, 
		lProperties.macApplicationName.c_str(), // Class Name
		lProperties.macApplicationName.c_str(), // Window title
		lStyle |								// Defined window style
		WS_CLIPSIBLINGS |						// Required window style
		WS_CLIPCHILDREN,						// Required window style
		0, 0,									// Window position
		lWindowRect.right - lWindowRect.left,	// Calculate window width
		lWindowRect.bottom - lWindowRect.top,	// Calculate window height
		NULL,									// No parent window
		NULL,									// No menu
		mInstance,								// Instance
		NULL);

	if (!mWnd)
	{
		Deinit();
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	ShowWindow(mWnd, SW_SHOW);
	SetForegroundWindow(mWnd);
	SetFocus(mWnd);

	mDC = GetDC(mWnd);

	if (!mDC)
	{
		Deinit();
		MessageBox (NULL, "Cant't access the HDC", "ERROR", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	return true;	
}


bool cWindow::Deinit()
{
	if (mProperties.mbFullscreen)
	{
		//If so switch back to the desktop resolution
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}
	if(mDC && !ReleaseDC(mWnd, mDC))
	{
		mDC=NULL;
		return false;
	}
	if (mWnd && !DestroyWindow(mWnd))
	{
		mWnd=NULL;
		return false;
	}
	if(!UnregisterClass(mProperties.macApplicationName.c_str(),mInstance))
	{
		mInstance=NULL;
		return false;
	}
	return true;
}


void cWindow::Update()
{
	MSG lMsg;
	//Is There a Message Waiting?
	if (PeekMessage (&lMsg, NULL, 0, 0, PM_REMOVE))
	{
		//Have we received a quit Message?
		if (lMsg.message==WM_QUIT)
		{
			mbCloseApplication =true;
		}
		else
		{
			TranslateMessage(&lMsg);
			DispatchMessage(&lMsg);
		}
	}
}


LRESULT CALLBACK cWindow::WndProc( HWND lWnd, UINT lMsg, WPARAM lWParam, LPARAM lLParam)
{
	switch (lMsg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_SYSCOMMAND:
		{
			switch (lWParam)
			{
			case SC_SCREENSAVE:
				case SC_MONITORPOWER:
				return 0;
			}
			break;
		}
	}
	return DefWindowProc(lWnd, lMsg, lWParam, lLParam);
}


