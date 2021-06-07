#include "Game.h" 	// Aurora Engine

#include "../Input/InputManager.h"
#include "../Graphics/Textures/TextureManager.h"
#include "../Graphics/Material/MaterialManager.h"
#include "../Graphics/Meshes/MeshManager.h"
#include "../Graphics/Effects/EffectManager.h"
#include "../Graphics/Fonts/FontManager.h"
#include "Scene/ModelManager.h"
#include "SoundManager.h"

//#include "../Graphics/Skeletal/SkeletalManager.h"
//#include "../Character/CharacterManager.h"
//#include "../Lua/LuaManager.h"

#include "../Utility/Debug.h"

#ifdef _WIN32
  #include <windows.h>
  #include "../Window/Window.h" 
#endif

extern tActionMapping kaActionMapping[];

bool cGame::Init()
{
	mfTimeSinceLastPress = 0;
	mbFinished = false;
	mbPlaying = true;
	mbResetGame = false;

	mProperties.LoadConfiguration("./Data/config.xml");
	OutputDebugString( "Se ha cargado la configuración ./Data/config.xml \n");

	bool lbResult = cWindow::Get().Init( mProperties );

	if ( lbResult )	// Init OpenGL
	{
		lbResult = cGraphicManager::Get().Init( &cWindow::Get() );
		if (!lbResult) cWindow::Get().Deinit(); // If something fails Kill Window
	}

	cInputManager::Get().Init(kaActionMapping, eIA_Count);
	cMaterialManager::Get().Init(20);
	cTextureManager::Get().Init(20);
	cEffectManager::Get().Init(5);	
	cMeshManager::Get().Init(20);
	cModelManager::Get().Init(5);

	
	cObjectManager::Get().Init("./Data/Level.xml"); // DESDE AQUI se puede organizar el cargador de modelos

//	mScene = cModelManager::Get().LoadResource( "TestLevel", "./Data/Scene/dragonsmall.DAE" );
	cSoundManager::Get().Init();

//	cSoundManager::Get().AddSource(0.0f, 0.0f, 0.0f, "./Data/WAVE/fondo.wav");
	
	//Inicializamos Lua
//	cLuaManager::Get().Init(); // Necesita aclararse, dá error al pulsar G y F...
	
	// Init Camera 2D para el texto
	float lfRight = (float) mProperties.muiWidth / 2.0f;
	float lfLeft = -lfRight;
	float lfTop = (float) mProperties.muiHeight / 2.0f;
	float lfBottom = -lfTop;
	m2DCamera.Init();
	m2DCamera.SetOrtho(lfLeft, lfRight, lfBottom, lfTop, 0.1f, 100.0f);
	m2DCamera.SetLookAt(cVec3(0.0f, 0.0f, 1.0f), cVec3(0.0f, 0.0f, 0.0f), cVec3(0.0f, 1.0f, 0.0f) );
	
	// Init 3D Cameras
	mDevCamera.Init();
	mGameCamera.Init();
	mMenuCamera.Init();

	float lfAspect = (float)mProperties.muiWidth/(float)mProperties.muiHeight;
	mDevCamera.SetPerspective( 45.0f, lfAspect, 0.1f, 10000.0f );
	mGameCamera.SetPerspective( 45.0f, lfAspect, 15.0f, 10000.0f );
	mMenuCamera.SetPerspective( 45.0f, lfAspect, 0.1f, 10000.0f );
	
	// Init the Font
	cFontManager::Get().Init(3);
	cFontManager::Get().LoadResource("Title", "./Data/Fonts/Galaxy.fnt");
	cFontManager::Get().LoadResource("Font1", "./Data/Fonts/Galaxy.fnt");
	cFontManager::Get().LoadResource("Space", "./Data/Fonts/Space.fnt");
	cFontManager::Get().ReadHof("./Data/records.rcd");
	// Set menu on
	mbInMenu = true;


	return lbResult;
}

bool cGame::Deinit()
{
	cFontManager::Get().WriteHof("./Data/records.rcd");
	cInputManager::Get().Deinit();
	cTextureManager::Get().Deinit();
	cModelManager::Get().Deinit();
	cMeshManager::Get().Deinit();
	cMaterialManager::Get().Deinit();
//	cBehaviourManager::Get().Deinit();
//	cCharacterManager::Get().Deinit();
	cEffectManager::Get().Deinit();
//	cSkeletalManager::Get().Deinit();

	cSoundManager::Get().Deinit();

	cObjectManager::Get().DeInit();

	cFontManager::Get().Deinit();

	bool lbResult = cGraphicManager::Get().Deinit();
	lbResult = lbResult && cWindow::Get().Deinit();
	
	//Deinicializamos Lua
//	cLuaManager::Get().Deinit();
		
	return lbResult;
}

void cGame::Update(float lfTimestep)
{
	cInputManager::Get().Update(lfTimestep);

	cWindow::Get().Update();

	// Check if we need to close the application
	mbFinished = mbFinished || cWindow::Get().GetCloseApplication();
	mfTimeSinceLastPress -= lfTimestep;
	if (((IsPressed(eIA_CloseApplication)) && (mfTimeSinceLastPress <=0)) || (mbResetGame == true))
	{
		
		if (mbInMenu)
		{
			if (cFontManager::Get().GetMenuState() == 0)
				mbFinished = true;
			else
			{
				cFontManager::Get().SetMenuState(eMainMenu);
				mfTimeSinceLastPress = 0.25;
			}
		}
		else
		{
			cFontManager::Get().Reset();
			cObjectManager::Get().GetPlayer()->Reset();

			cSoundManager::Get().Deinit();
			cSoundManager::Get().Init();

			cObjectManager::Get().Update(lfTimestep);
			mGameCamera.Update(lfTimestep);
			mbInMenu = true;
			mfTimeSinceLastPress = 0.25f;
			if (mbResetGame) 
			{
				cFontManager::Get().SetMenuState(3);
			}
			mbResetGame = false;
			
		}
	}
	
	if (mbFinished)	return;
	
	if (mbInMenu)
	{
		cFontManager::Get().UpdateMenu(lfTimestep);
		mMenuCamera.Update(lfTimestep);
		return;
	}

	cFontManager::Get().UpdateHUD( lfTimestep );
	
	cObjectManager::Get().Update(lfTimestep);
//	cCharacterManager::Get().Update(lfTimestep);	

	if (BecomePressed(eIA_CameraSwap))
		mbPlaying = !mbPlaying; // alternar camara ingame y developer (tecla "C" )

	if (!mbPlaying) mDevCamera.Update(lfTimestep); 
	mGameCamera.Update(lfTimestep); // actualizar siempre camara ingame..
	cSoundManager::Get().Update(lfTimestep);
	
	
}

void cGame::Render()
{
	// 1) Clean the Buffers
	// ---------------------------------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (mbInMenu)
	{
		cMatrix lWorld;
		lWorld.LoadIdentity();
		
		cGraphicManager::Get().SetWorldMatrix(lWorld);
		cGraphicManager::Get().ActivateCamera( &mMenuCamera);	
		cObjectManager::Get().Render();
		
		cGraphicManager::Get().ActivateCamera( &m2DCamera);
		glEnable(GL_TEXTURE_2D);
		lWorld.LoadIdentity();
		cGraphicManager::Get().SetWorldMatrix(lWorld);

		cFontManager::Get().RenderMenu();

		cGraphicManager::Get().SwapBuffer();
		return;
	}
	
	// 2) Activate the 3D Camera
	// ---------------------------------------------------------
	if (mbPlaying)
		cGraphicManager::Get().ActivateCamera( &mGameCamera);
	else
		cGraphicManager::Get().ActivateCamera( &mDevCamera);

	// 3) Render Solid 3D
	// ---------------------------------------------------------
	// Set the world matrix
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
	
	//((cModel *)mScene.GetResource())->Render(lWorld);
		
	cObjectManager::Get().Render();
	


	// 4) Render 3D with transparency
	// ---------------------------------------------------------
	
	// Render Some debug Lines for reference
//	cGraphicManager::Get().DrawGrid(); 

	// 5) Activate 2D Camera
	// ---------------------------------------------------------
	cGraphicManager::Get().ActivateCamera( &m2DCamera);

	// 6) Render 2D Elements
	// ---------------------------------------------------------
	glEnable(GL_TEXTURE_2D);
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);

	cFontManager::Get().RenderHUD();

	// 7) PostProcessing
	// ---------------------------------------------------------

	// 8) Swap Buffers
	// ---------------------------------------------------------
	cGraphicManager::Get().SwapBuffer();
}