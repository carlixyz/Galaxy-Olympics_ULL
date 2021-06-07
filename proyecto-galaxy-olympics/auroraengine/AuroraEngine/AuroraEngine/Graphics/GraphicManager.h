#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include "GLHeaders.h"
#include "..\Utility\Singleton.h"
#include "..\Libraries\MathLib\MathLib.h"

#include "Camera.h"
#include "DebugCamera.h"
#include "InGameCamera.h"

class cWindow;

class cGraphicManager : public cSingleton<cGraphicManager>
{
public:
	bool Init( cWindow * lpWindow );
	bool Deinit();
	void SwapBuffer();
	void DrawPoint( const cVec3 &lvPosition,const cVec3 &lvColor );
	void DrawLine( const cVec3 &lvPosition1, const cVec3 &lvPosition2, const cVec3 &lvColor );
	void DrawGrid();
	void DrawAxis();

	void SetWorldMatrix( const cMatrix &lMatrix );
	void RefreshWorldView();
	void ActivateCamera( cCamera * lpCamera );

	cCamera * GetActiveCamera() { return mpActiveCamera; }
	const cMatrix &GetWVPMatrix() { return mWVPMatrix; }

	friend class cSingleton<cGraphicManager>;
protected:
	cGraphicManager() { ; } // Protected constructor
private:
	cMatrix mWVPMatrix;
	cWindow* mpWindow;
	GLuint mPixelFormat;
	HGLRC mHRC;
	cCamera * mpActiveCamera;
	cMatrix mWorldMatrix;

	bool CreateContext( cWindow * lpWindow );
	void InitializeGLState();
} ;


#endif