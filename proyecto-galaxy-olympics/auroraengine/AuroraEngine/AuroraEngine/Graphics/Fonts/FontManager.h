#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "../../Utility/ResourceManager.h"
#include "../../Utility/Singleton.h"

#include "Font.h"
#include <vector>

enum eMenuState {
	eMainMenu = 0,
	eCredits,
	eHof,
    eResult};

class cFontManager : public cResourceManager,
							public cSingleton<cFontManager>
{
	public:
		friend class cSingleton<cFontManager>;

		void Init(unsigned int luiMaxSize);

		void UpdateHUD(float lfTimestep); 

		void RenderHUD();
		
		void UpdateMenu(float lfTimestep);

		void RenderMenu();

		inline float GetAcumulatedTime() { return mfAcTime; }

		inline void SetMenuState(int liState) { leMenuState = liState;}
		inline int GetMenuState() { return leMenuState; }
		inline void Reset() 
		{	miSelected = 1;
			mfGametime = 0.0f;			
			mfAcTime = 0.0f;
			lbTimeStop = false;
			MenuMusic = false;
			lfCreditsPos = 200;
			Message = "";
		}
		std::string ConvertToTime(float mfTime);
		inline void SetMarkTime() {mfMarkTime = mfAcTime;}
		void ReadHof(std::string lsFilename);
		void WriteHof(std::string lsFilename);
		std::string Message;
		bool MenuMusic;
	protected:
		cFontManager() { ; }// Protected Constructor
		
	private:

		float lfHelpPos;
		float lfCreditsPos;
		int leMenuState;
		float mfTimeSinceLastPress;
		int miSelected;
		float mfGametime;
		float mfAcTime;
		float mfMarkTime;
		bool lbTimeStop;
	

		std::vector <float> hof;
		
		virtual cResource* LoadResourceInternal( std::string lacNameID, const std::string &lacFile );
};
#endif 