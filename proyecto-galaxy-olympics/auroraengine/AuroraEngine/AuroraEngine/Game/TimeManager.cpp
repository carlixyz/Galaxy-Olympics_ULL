#include "TimeManager.h"
#include "../Graphics/GraphicManager.h"
#include "../Graphics/Fonts/FontManager.h"


void cTimeManager::Init(cCamera l2DCamera, float lfLevelTime)
{
	mfLevelTime = 20;
	m2DCamera = l2DCamera;
}

void cTimeManager::Update(float lfTimestep)
{
	mfLevelTime -= lfTimestep;
	if(mfLevelTime < 0)
		mfLevelTime = 0;
}

void cTimeManager::Render()
{
	char sz[101];
    sprintf(sz, "%i", (int)mfLevelTime);
	cResource * lpFont = cFontManager::Get().SearchResource("Font1").GetResource();
	((cFont *)lpFont)->SetColour( 0.0f , 1.0f, 0.0f );
	((cFont *)lpFont)->Write( 250, 200, 0, sz, 0, FONT_ALIGN_CENTER );
}