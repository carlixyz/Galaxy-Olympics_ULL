#include "FontManager.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "../../Utility/Debug.h"
#include "../../Input/InputManager.h"
#include "../../Game/InputConfiguration.h"
#include "../../Game/Game.h"
#include "../../Game/SoundManager.h"

#define kfSCREEN_OFFSET_Y (float)(cGame::Get().mProperties.muiHeight>>1)
#define kfSCREEN_OFFSET_X (float)(cGame::Get().mProperties.muiWidth>>1)

//using namespace std; //

void cFontManager::UpdateHUD(float lfTimestep)
{
	this->mfAcTime += lfTimestep;
}

void cFontManager::RenderHUD()
{
	cResource * lpFont = cFontManager::Get().SearchResource("Font1").GetResource();
	((cFont *)lpFont)->SetColour( 0.0f , 0.0f, 0.0f );
	((cFont *)lpFont)->Write( 5, 265, 0, "galaxy olympics", 0, FONT_ALIGN_CENTER );
	((cFont *)lpFont)->SetColour( 0.0f , 1.0f, 0.0f );
	((cFont *)lpFont)->Write( 0, 270, 0, "galaxy olympics", 0, FONT_ALIGN_CENTER );

	//Render time
	std::stringstream lsMinutes (std::stringstream::in | std::stringstream::out);
	std::stringstream lsSeconds (std::stringstream::in | std::stringstream::out);
	std::stringstream lsMiliseconds (std::stringstream::in | std::stringstream::out);
	std::stringstream lsTurboAmount (std::stringstream::in | std::stringstream::out);

	int liSecondsForLevel = 5;
	int liMinutes = (/*liSecondsForLevel -*/ (int)mfAcTime)/(int)60;
	int liSeconds = (/*liSecondsForLevel - */(int)mfAcTime)%60;
	int liMiliseconds=(int)((mfAcTime - (int)mfAcTime)*100);
	
	if (liMinutes <=0 ) liMinutes = 0;
	if (liSeconds <=0 ) liSeconds = 0;	
		
	lsMinutes << ((liMinutes < 10)?"0":"") << liMinutes;
	lsSeconds << ((liSeconds < 10)?"0":"") << liSeconds;
    
	if (lbTimeStop)
		liMiliseconds = 0;

	lsMiliseconds << ((liMiliseconds < 10)?"0":"") << liMiliseconds;

	lsTurboAmount << " Q-boost: " << std::setprecision(1) << (int)((cObjectManager::Get().GetPlayer()->GetTurboAmount()* 100.0f) /100.0f) << " %" ;


	((cFont *)lpFont)->SetColour( 0.0f , 0.0f, 0.0f );
	((cFont *)lpFont)->WriteBox( 162, -272, 0, 200, lsMinutes.str().c_str(), 0, FONT_ALIGN_CENTER);
	((cFont *)lpFont)->WriteBox( 182, -272, 0, 200, std::string(":").c_str(), 0, FONT_ALIGN_CENTER);
	((cFont *)lpFont)->WriteBox( 202, -272, 0, 200, lsSeconds.str().c_str(), 0, FONT_ALIGN_CENTER);
	((cFont *)lpFont)->WriteBox( 222, -272, 0, 200, std::string(":").c_str(), 0, FONT_ALIGN_CENTER);
	((cFont *)lpFont)->WriteBox( 242, -272, 0, 200, lsMiliseconds.str().c_str(), 0, FONT_ALIGN_CENTER);

	((cFont *)lpFont)->WriteBox( -kfSCREEN_OFFSET_X+2, -272, 0, 500, (lsTurboAmount.str().c_str()), 0 , FONT_ALIGN_LEFT);

	((cFont *)lpFont)->SetColour( 1.0f, 1.0f, 1.0f );
	((cFont *)lpFont)->WriteBox( 160, -270, 0, 200, lsMinutes.str().c_str(), 0, FONT_ALIGN_CENTER);
	((cFont *)lpFont)->WriteBox( 180, -270, 0, 200, std::string(":").c_str(), 0, FONT_ALIGN_CENTER);
	((cFont *)lpFont)->WriteBox( 200, -270, 0, 200, lsSeconds.str().c_str(), 0, FONT_ALIGN_CENTER);
	((cFont *)lpFont)->WriteBox( 220, -270, 0, 200, std::string(":").c_str(), 0, FONT_ALIGN_CENTER);
	((cFont *)lpFont)->WriteBox( 240, -270, 0, 200, lsMiliseconds.str().c_str(), 0, FONT_ALIGN_CENTER);

	((cFont *)lpFont)->WriteBox( -kfSCREEN_OFFSET_X, -270, 0, 500, (lsTurboAmount.str().c_str()), 0 , FONT_ALIGN_LEFT);
	
}

void cFontManager::UpdateMenu(float lfTimestep)
{
	switch(leMenuState)
	{
		case eMainMenu:
			mfTimeSinceLastPress -= lfTimestep;
		
		// 	Write & display the scrolling help Instructions
		if ( lfHelpPos > (-kfSCREEN_OFFSET_X * 15.0f) ) lfHelpPos -= lfTimestep * 100.0f;
		else lfHelpPos = kfSCREEN_OFFSET_X * 2.0f;
	
			if (mfTimeSinceLastPress >0) return;

			if (IsPressed(eIA_MenuSelect))
			{
				switch(miSelected)
				{
				case 1://Play
					cGame::Get().SetMenu(false);
					return;
					break;
				case 2: //Hall of fame
					leMenuState = eHof;
					mfTimeSinceLastPress = 0.50;
					return;
					break;
				case 3: //Credits
					leMenuState = eCredits;
					mfTimeSinceLastPress = 0.50;
					return;
					break;
				case 4: //Exit
					cGame::Get().SetFinished(true);
					return;
					break;
				}
			}

			if (IsPressed(eIA_MenuUp) )	
			{
				cSoundManager::Get().Play("./Data/WAVE/Menu.wav", 1.0f);
				miSelected -=1;
				if (miSelected == 0) miSelected=4;
				mfTimeSinceLastPress = 0.25;
			}
			else
				if (IsPressed(eIA_MenuDown) )	
				{
					cSoundManager::Get().Play("./Data/WAVE/Menu.wav", 1.0f);
					miSelected +=1;
					if (miSelected == 5) miSelected=1;
					mfTimeSinceLastPress = 0.25;
				}
				else
					mfTimeSinceLastPress = 0;
		break;
		case eCredits:
			mfTimeSinceLastPress -= lfTimestep;
			lfCreditsPos += lfTimestep * 20.0f;

			if (mfTimeSinceLastPress >0) return;
			if (IsPressed(eIA_MenuSelect) || (lfCreditsPos >= 1100))	
			{
				leMenuState = eMainMenu;
				mfTimeSinceLastPress = 0.25;
				lfCreditsPos = 200;
			}
		break;	
		case eHof:
		case eResult:
			mfTimeSinceLastPress -= lfTimestep;
			if (mfTimeSinceLastPress >0) return;
			if (IsPressed(eIA_MenuSelect))	
			{
				leMenuState = eMainMenu;
				mfTimeSinceLastPress = 0.25;
			}
		break;
	}
}

void cFontManager::RenderMenu()
{
	cResource * lpGalaxy = cFontManager::Get().SearchResource("Title").GetResource();
	cResource * lpFont = cFontManager::Get().SearchResource("Font1").GetResource();
	cResource * lpSpaceFont = cFontManager::Get().SearchResource("Space").GetResource();
	((cFont *)lpGalaxy)->SetColour( 0.0f , 0.0f, 1.0f );
	((cFont *)lpGalaxy)->SetHeight(70.0f );
	((cFont *)lpGalaxy)->Write( 5, lfCreditsPos-5, 0, "galaxy olympics", 0, FONT_ALIGN_CENTER );
	((cFont *)lpGalaxy)->SetColour( 0.0f , 1.0f, 0.0f );
	((cFont *)lpGalaxy)->Write( 0, lfCreditsPos, 0, "galaxy olympics", 0, FONT_ALIGN_CENTER );

	
	int liMenuX = -120;
	int liMenuY = 60;

	switch(leMenuState)
	{
	case eMainMenu:
		//36, 87, 129
		((cFont *)lpSpaceFont)->SetColour( 0.141f , 0.341f, 0.505f );
		((cFont *)lpSpaceFont)->Write( liMenuX, liMenuY, 0, "new game", 0, FONT_ALIGN_LEFT );
		((cFont *)lpSpaceFont)->Write( liMenuX, liMenuY-(40*1), 0, "records", 0, FONT_ALIGN_LEFT );
		((cFont *)lpSpaceFont)->Write( liMenuX, liMenuY-(40*2), 0, "credits", 0, FONT_ALIGN_LEFT );
		((cFont *)lpSpaceFont)->Write( liMenuX, liMenuY-(40*4), 0, "exit", 0, FONT_ALIGN_LEFT );

		//72, 173, 255
		((cFont *)lpSpaceFont)->SetColour( 0.282f , 0.678f, 1.0f );
		((cFont *)lpSpaceFont)->Write( liMenuX-(miSelected==1?8:4), liMenuY+(miSelected==1?8:4), 0, "new game", 0, FONT_ALIGN_LEFT );
		((cFont *)lpSpaceFont)->Write( liMenuX-(miSelected==2?8:4), liMenuY-(40*1)+(miSelected==2?8:4), 0, "records", 0, FONT_ALIGN_LEFT );
		((cFont *)lpSpaceFont)->Write( liMenuX-(miSelected==3?8:4), liMenuY-(40*2)+(miSelected==3?8:4), 0, "credits", 0, FONT_ALIGN_LEFT );
		((cFont *)lpSpaceFont)->Write( liMenuX-(miSelected==4?8:4), liMenuY-(40*4)+(miSelected==4?8:4), 0, "exit", 0, FONT_ALIGN_LEFT );
	
		((cFont *)lpSpaceFont)->SetColour( 1.0f , 1.0f, 1.0f );
		((cFont *)lpSpaceFont)->Write(lfHelpPos, 20-kfSCREEN_OFFSET_Y, 0,
			"- Try to Reach the goal the faster as possible - Use Arrows Keys to move & lShift for Brake - Get Rings and use Quantic Jumps with Hyper-Boosts! with Space bar - This is only a Demo version with 1 of 15 Trials: Ring Jet-Pack Test, so relax, take it easy, fly away and Have Fun!..",
			0, FONT_ALIGN_LEFT );

		MenuMusic = false;

		break;
	case eCredits:
		{
			if (!MenuMusic){ cSoundManager::Get().Play("./Data/WAVE/MovPlayer.wav", 0.0f); MenuMusic =true;}
		vector<string> credits;
		vector<bool> titles;
		credits.push_back("main programmers:"); titles.push_back(true);
		credits.push_back("carlos lopez"); titles.push_back(false);
		credits.push_back("manuel padron"); titles.push_back(false);
		credits.push_back("pedro santana"); titles.push_back(false);
		credits.push_back("jose manuel garcia"); titles.push_back(false);
		credits.push_back(""); titles.push_back(false);
		credits.push_back(""); titles.push_back(false);
		credits.push_back("main 3d designers:"); titles.push_back(true);
		credits.push_back("juan j. burgos"); titles.push_back(false);
		credits.push_back("juan f. hernandez"); titles.push_back(false);
		credits.push_back("moises vigueras"); titles.push_back(false);
		credits.push_back(""); titles.push_back(false);
		credits.push_back(""); titles.push_back(false);
		credits.push_back("sound & music:"); titles.push_back(true);
		credits.push_back("pedro santana"); titles.push_back(false);
		credits.push_back("jose manuel garcia"); titles.push_back(false);
		credits.push_back(""); titles.push_back(false);
		credits.push_back(""); titles.push_back(false);
		credits.push_back("original models designs:"); titles.push_back(true);
		credits.push_back("carlos lopez"); titles.push_back(false);
		credits.push_back(""); titles.push_back(false);
		credits.push_back(""); titles.push_back(false);
		credits.push_back("original idea:"); titles.push_back(true);
		credits.push_back("carlos lopez"); titles.push_back(false);
		credits.push_back("manuel padron"); titles.push_back(false);
		credits.push_back(""); titles.push_back(false);

		//Black
		int liSpace = 0;
		for (int i=0; i<credits.size(); i++)
		{
		  ((cFont *)lpSpaceFont)->SetColour( 0.0f , 0.0f, 0.0f );
		  if (titles[i]) liSpace = 0; else liSpace = 80;
		  ((cFont *)lpSpaceFont)->Write( -348+liSpace, lfCreditsPos-55-(i*30)-2, 0, credits[i].c_str(), 0, FONT_ALIGN_LEFT );
		  if (titles[i])
			  ((cFont *)lpSpaceFont)->SetColour( 1.0f , 1.0f, 1.0f );
		  else		
			  ((cFont *)lpSpaceFont)->SetColour( 0.282f , 0.678f, 1.0f );
       	  ((cFont *)lpSpaceFont)->Write( -350+liSpace, lfCreditsPos-55-(i*30), 0, credits[i].c_str(), 0, FONT_ALIGN_LEFT );
		}

		}
		break;
	case eHof:
		{
	if (!MenuMusic){ cSoundManager::Get().Play( "./Data/WAVE/Ring.wav", 0.0f); MenuMusic =true;}		
		//Black
		int liSpace = 0;
		for (int i=0; i<hof.size(); i++)
		{
		  ((cFont *)lpSpaceFont)->SetColour( 0.0f , 0.0f, 0.0f );
		  ((cFont *)lpSpaceFont)->Write( 2, lfCreditsPos-85-(i*30)-2, 0, ConvertToTime(hof[i]).c_str(), 0, FONT_ALIGN_CENTER );
		  switch (i)
		  {
		  case 0:
			  ((cFont *)lpSpaceFont)->SetColour( 1.0f , 0.84f, 0.0f );
			  break;
		  case 1:
			  ((cFont *)lpSpaceFont)->SetColour( 0.75f , 0.75f, 0.75f );
			  break;
		  case 2:
			  ((cFont *)lpSpaceFont)->SetColour( 0.64f , 0.44f, 0.39f );
			  break;
		  default:
			  ((cFont *)lpSpaceFont)->SetColour( 1.0f , 1.0f, 1.0f );
			  break;
		  }
/*		  if (i>2)
			  ((cFont *)lpSpaceFont)->SetColour( 1.0f , 1.0f, 1.0f );
		  else		
			  ((cFont *)lpSpaceFont)->SetColour( 0.282f , 0.678f, 1.0f );*/
       	  ((cFont *)lpSpaceFont)->Write( 0, lfCreditsPos-85-(i*30), 0, ConvertToTime(hof[i]).c_str(), 0, FONT_ALIGN_CENTER );
		}

		}
		break;
	case eResult:
		{
		
		((cFont *)lpSpaceFont)->SetColour( 0.0f , 0.0f, 0.0f );
		((cFont *)lpSpaceFont)->Write( 2, lfCreditsPos-147, 0, "Your Time was:", 0, FONT_ALIGN_CENTER );
		((cFont *)lpSpaceFont)->SetColour( 0.282f , 0.678f, 1.0f );
		((cFont *)lpSpaceFont)->Write( 0, lfCreditsPos-145, 0, "Your Time was:", 0, FONT_ALIGN_CENTER );

		((cFont *)lpSpaceFont)->SetColour( 0.0f , 0.0f, 0.0f );
		((cFont *)lpSpaceFont)->Write( 2, lfCreditsPos-187, 0, ConvertToTime(mfMarkTime).c_str(), 0, FONT_ALIGN_CENTER );
		((cFont *)lpSpaceFont)->SetColour( 1.0f , 1.0f, 1.0f );
		((cFont *)lpSpaceFont)->Write( 0, lfCreditsPos-185, 0, ConvertToTime(mfMarkTime).c_str(), 0, FONT_ALIGN_CENTER );

		if ((Message=="") && (mfMarkTime < hof.back()))
		{
			hof.push_back(mfMarkTime);
			sort (hof.begin(), hof.end());
		}

		if (mfMarkTime > hof.back())
			Message = "Too slow! Try again!";
		else
			Message = "Congrats! You have a record!";

		if (!MenuMusic){ cSoundManager::Get().Play( "./Data/WAVE/starwars.wav", 0.0f); MenuMusic =true;}

		((cFont *)lpSpaceFont)->SetColour( 0.0f , 0.0f, 0.0f );
		((cFont *)lpSpaceFont)->Write( 2, lfCreditsPos-247, 0, Message.c_str(), 0, FONT_ALIGN_CENTER );
		((cFont *)lpSpaceFont)->SetColour( 1.0f , 1.0f, 1.0f );
		((cFont *)lpSpaceFont)->Write( 0, lfCreditsPos-245, 0, Message.c_str(), 0, FONT_ALIGN_CENTER );
		}
		break;
	}
}

void cFontManager::Init(unsigned int luiMaxSize)
{
	miSelected = 1;
	mfGametime = 0.0f;
	mfMarkTime = 0.0f;
	mfAcTime = 0.0f;
    lbTimeStop = false;
	lfCreditsPos = 200;
	muiMaxSize = luiMaxSize;
	// Initialize the structures
	maResources.resize( muiMaxSize );
	mFreeResourceSlot.clear();
	for ( unsigned luiIndex = 0; luiIndex < muiMaxSize; ++luiIndex )
	{
		// Initialize the resource slot
		maResources[luiIndex].muiKey = kuiInvalidKey;
		maResources[luiIndex].mpResource = NULL;
		// Add the free index to the list
		mFreeResourceSlot.push_back( luiIndex );
	}
	// Prepare the first key
	muiNextKey = kuiInvalidKey + 1;
	
}

cResource * cFontManager::LoadResourceInternal( std::string lacNameID, const std::string &lacFile )
{
	//Create a texture
	cFont* lpFont = new cFont();
	
	//Load texture //    mFont.Init( "./Src/Data/Fonts/Test1.fnt" );
	// mFontHandle = cFontManager::Get().LoadResource("Font1", "./Data/Fonts/Test1.fnt");
	if (!lpFont->Init( lacNameID, lacFile ) )
	{
		delete lpFont;
		return NULL;
	}

	//Return texture as resource
	return lpFont;
}

std::string cFontManager::ConvertToTime(float mfTime)
{
	std::stringstream lsMinutes (std::stringstream::in | std::stringstream::out);
	std::stringstream lsSeconds (std::stringstream::in | std::stringstream::out);
	std::stringstream lsMiliseconds (std::stringstream::in | std::stringstream::out);
	std::stringstream lsTime (std::stringstream::in | std::stringstream::out);

	int liMinutes = ( (int)mfTime)/(int)60;
	int liSeconds = ((int)mfTime)%60;
	int liMiliseconds=(int)((mfTime - (int)mfTime)*100);
			
	lsMinutes << ((liMinutes < 10)?"0":"") << liMinutes;
	lsSeconds << ((liSeconds < 10)?"0":"") << liSeconds;
    lsMiliseconds << ((liMiliseconds < 10)?"0":"") << liMiliseconds;

	lsTime << lsMinutes.str() << ":" << lsSeconds.str() << ":" << lsMiliseconds.str();
	return lsTime.str();
}

void cFontManager::ReadHof(std::string lsFilename)
{
	hof.clear();
	fstream filestr;
	 try {

	filestr.open (lsFilename.c_str(), fstream::in);
	filestr.clear();
	filestr.seekg(0, ios::beg);
	bool open = filestr.is_open();
	for (int i=0; i<10; i++)
	{
		float lfValue;
		string lsValue;
	    getline (filestr,lsValue);  
		stringstream lsStream(lsValue);
		lsStream >> lfValue;
		hof.push_back(lfValue);
	}
	  }
  catch (ifstream::failure e) {
	  std::string w;
	  w=e.what();
	  cout << e.what();
  }

    filestr.close();
	
	sort (hof.begin(), hof.end());
	while (hof.size()>10) hof.pop_back();
}

void cFontManager::WriteHof(std::string lsFilename)
{
	sort (hof.begin(), hof.end());
	while (hof.size()>10) hof.pop_back();
	ofstream filestr;
	filestr.open (lsFilename.c_str());
	for(int i=0;i<10;i++)
	{
		stringstream lsStream;
		lsStream << hof[i];
		string lsValue = lsStream.str()+"\n";
		filestr << lsValue.c_str();
	}
    filestr.close();
}