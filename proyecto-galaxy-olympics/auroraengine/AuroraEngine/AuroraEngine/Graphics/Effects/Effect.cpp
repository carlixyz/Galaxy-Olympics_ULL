#include "Effect.h"
#include <assimp.hpp> // C++ importer interface
#include <aiScene.h> // Output data structure
#include <aiPostProcess.h> // Post processing flags
#include <cassert>
#include "EffectManager.h"
#include "../Textures/Texture.h"

#include "../../Utility/Debug.h"

bool cEffect::Init( const std::string &lacNameID, const std::string &lacFile )
{
	//Initialization of the class atributes
	macFile = lacFile;
	macLastTecnique = "";
	mEffect = NULL;
	mTechnique = NULL;
	mCurrentPass = NULL;
	mbLoaded = false;

	//Loading of the effect
	CGcontext lCGContext = cEffectManager::Get().GetCGContext();
	mEffect = cgCreateEffectFromFile(lCGContext, lacFile.c_str(), NULL);

	Debug().ToOutput("Loading effect file : %s \n", lacFile.c_str());

	if (!mEffect) {
		OutputDebugString("Unable to create effect\n");
		const char *lacListing = cgGetLastListing(lCGContext);
		if (lacListing)
		{
			char lacBuffer[512];
			sprintf(lacBuffer, "%s\n", lacListing);
			OutputDebugString(lacBuffer);
		}
		return false;
	}

	// Check if the techniques are valid
	CGtechnique lTechnique = cgGetFirstTechnique(mEffect);
	while (lTechnique) {
		if (cgValidateTechnique(lTechnique) == CG_FALSE)
		{
			char lacBuffer[512];
			sprintf(lacBuffer, "Technique %s did not validate. Skipping. \n", cgGetTechniqueName(lTechnique));
			OutputDebugString( lacBuffer );

			const char *lacListing = cgGetLastListing(lCGContext);
			if (lacListing)
			{
				char lacBuffer[512];
				sprintf(lacBuffer, "%s\n", lacListing);
				OutputDebugString(lacBuffer);
			}
		}
		lTechnique = cgGetNextTechnique(lTechnique);
	}
	;
	mbLoaded = true;
	mErrorShow = mbLoaded;
	return true;
}
void cEffect::Deinit()
{
	cgDestroyEffect( mEffect );
	macLastTecnique = "";
	mEffect = NULL;
	mTechnique = NULL;
	mCurrentPass = NULL;
}

void cEffect::Reload()
{
	Deinit();
	Init( GetNameID(), macFile );
}

bool cEffect::SetTechnique( const std::string &lacTechnique )
{
	if ( macLastTecnique != lacTechnique )
	{
		// Set Technique
		mTechnique=cgGetNamedTechnique( mEffect, lacTechnique.c_str() );
		if ( mTechnique )
		{
			macLastTecnique = lacTechnique;
			return true;
		}
	}
	return false;
}

bool cEffect::SetFirstPass()
{
	if ( mTechnique )
	{
		mCurrentPass = cgGetFirstPass(mTechnique);
		if ( mCurrentPass )
		{
			cgSetPassState(mCurrentPass);
			return true;
		}
	}
	return false;
}

bool cEffect::SetNextPass()
{
	if ( mTechnique )
	{
		assert( mCurrentPass );
		cgResetPassState(mCurrentPass);
		mCurrentPass = cgGetNextPass(mCurrentPass);
		if (mCurrentPass)
		{
			cgSetPassState(mCurrentPass);
			return true;
		}
	}
	return false;
}

void cEffect::SetParam(const std::string &lacName, const cMatrix& lMatrix )
{
	CGparameter lParam = cgGetNamedEffectParameter(mEffect,
		lacName.c_str());
	if (lParam)
	{
		cgSetMatrixParameterfc(lParam, lMatrix.AsFloatPointer());
	}
}

void cEffect::SetParam(const std::string &lacName, float lParamValue )
{
	CGparameter lParam = cgGetNamedEffectParameter(mEffect,
		lacName.c_str());
	if (lParam)
	{
		cgSetParameter1f(lParam, lParamValue);
	}
}

void cEffect::SetParam(const std::string &lacName, const cVec3& lParamValue)
{
  CGparameter lParam = cgGetNamedEffectParameter(mEffect,
	  lacName.c_str());
  if (lParam)
  {
	  cgSetParameter3fv(lParam, lParamValue.AsFloatPointer());
  }
}

void cEffect::SetParam(const std::string &lacName, const cVec4& lParamValue )
{
  CGparameter lParam = cgGetNamedEffectParameter(mEffect,
	  lacName.c_str());
  if (lParam)
  {
	  cgSetParameter4fv(lParam, lParamValue.AsFloatPointer());
  }
}

void cEffect::SetParam(const std::string &lacName, cResourceHandle lParamValue )
{
	CGparameter lParam = cgGetNamedEffectParameter(mEffect, lacName.c_str());
	if (lParam)
	{
		assert(lParamValue.IsValidHandle());
		cTexture * lpTexture = (cTexture*)lParamValue.GetResource();
		unsigned luiTextureHandle = lpTexture->GetTextureHandle();
		cgGLSetupSampler(lParam, luiTextureHandle);
	}
}


void cEffect::SetParam(const std::string &lacName, const float * lfParam, int liCount )
{
	static const unsigned kuiAuxiliarBuffer = 256 * 4;
	static float gFullArray[kuiAuxiliarBuffer];
	CGparameter lParam = cgGetNamedEffectParameter( mEffect, lacName.c_str());
	if (lParam)
	{
		int liNRows = cgGetParameterRows(lParam);
		int liNCols = cgGetParameterColumns(lParam);
		int liASize = cgGetArrayTotalSize(lParam);
		int liNTotal = liNRows*liNCols;
		if (liASize > 0)
		{
			liNTotal *= liASize;
			if ( liCount < liNTotal )
			{
				assert(kuiAuxiliarBuffer > liNTotal);
				assert(kuiAuxiliarBuffer > liCount);
				memcpy(gFullArray, lfParam, sizeof(float) * liCount);
				cgSetParameterValuefr(lParam, liNTotal, gFullArray);
			}
			else
			{
				cgSetParameterValuefr(lParam, liCount, lfParam);
			}


			CGerror err = cgGetError();
			if (err != CG_NO_ERROR && mErrorShow)
			{
				OutputDebugStr(cgGetErrorString( err ));
				OutputDebugStr("\n\n");

			// Just one advice and then disable this warning because it´s Too anoying 
			mErrorShow = !mErrorShow;
			}
		}
	}
}