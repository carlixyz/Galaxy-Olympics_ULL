/*
   AngelCode Tool Box Library
   Copyright (c) 2007-2008 Andreas Jonsson
  
   This software is provided 'as-is', without any express or implied 
   warranty. In no event will the authors be held liable for any 
   damages arising from the use of this software.

   Permission is granted to anyone to use this software for any 
   purpose, including commercial applications, and to alter it and 
   redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you 
      must not claim that you wrote the original software. If you use
      this software in a product, an acknowledgment in the product 
      documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and 
      must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source 
      distribution.
  
   Andreas Jonsson
   andreas@angelcode.com
*/

// THIS VERSION IS NOT THE ORIGINAL VERSION OF THE LIBRARY!

#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>
#include "acgfx_font.h"
#include "acutil_unicode.h"
// This is a modification of the original code <
#include "../Textures/TextureManager.h"
#include "../Textures/Texture.h"
#include <cassert>
#pragma warning( disable : 4996 )

//#include "..\..\Utility\Debug.h"
// > This is a modification of the original code

#define LOG(X) printf X

using namespace std;

// Implement private helper classes for loading the bitmap font files

class CFontLoader
{
public:
	CFontLoader(FILE *f, cFont *font, const char *fontFile);

	virtual int Load() = 0; // Must be implemented by derived class

protected:
	void LoadPage(int id, const char *pageFile, const char *fontFile);
	void SetFontInfo(int outlineThickness);
	void SetCommonInfo(int fontHeight, int base, int scaleW, int scaleH, int pages, bool isPacked);
	void AddChar(int id, int x, int y, int w, int h, int xoffset, int yoffset, int xadvance, int page, int chnl);
	void AddKerningPair(int first, int second, int amount);

	FILE *f;
	cFont *font;
	const char *fontFile;

	int outlineThickness;
};

class CFontLoaderTextFormat : public CFontLoader
{
public:
	CFontLoaderTextFormat(FILE *f, cFont *font, const char *fontFile);

	int Load();

	int SkipWhiteSpace(std::string &str, int start);
	int FindEndOfToken(std::string &str, int start);

	void InterpretInfo(std::string &str, int start);
	void InterpretCommon(std::string &str, int start);
	void InterpretChar(std::string &str, int start);
	void InterpretSpacing(std::string &str, int start);
	void InterpretKerning(std::string &str, int start);
	void InterpretPage(std::string &str, int start, const char *fontFile);
};

class CFontLoaderBinaryFormat : public CFontLoader
{
public:
	CFontLoaderBinaryFormat(FILE *f, cFont *font, const char *fontFile);

	int Load();

	void ReadInfoBlock(int size);
	void ReadCommonBlock(int size);
	void ReadPagesBlock(int size);
	void ReadCharsBlock(int size);
	void ReadKerningPairsBlock(int size);
};

//=============================================================================
// cFont
//
// This is the cFont class that is used to write text with bitmap fonts.
//=============================================================================

cFont::cFont()
{
	fontHeight = 0;
	base = 0;
	scaleW = 0;
	scaleH = 0;
	scale = 1.0f;
	hasOutline = false;
	encoding = NONE;
   SetColour(1.0f, 1.0f, 1.0f);
}

void cFont::Deinit()
{
	std::map<int, SCharDescr*>::iterator it = chars.begin();
	while( it != chars.end() )
	{
		delete it->second;
		it++;
	}

   // This is a modification of the original code <
   for( unsigned n = 0; n < pages.size(); n++ )
   {
		cTextureManager::Get().UnloadResource( &pages[n] );
   }
   // > This is a modification of the original code 
}

int cFont::Init(const char *fontFile)
{
	// Load the font
	FILE *f = fopen(fontFile, "rb");
	
	// Determine format by reading the first bytes of the file
	char str[4] = {0};
	fread(str, 3, 1, f);
	fseek(f, 0, SEEK_SET);

	CFontLoader *loader = 0;
	if( strcmp(str, "BMF") == 0 )
		loader = new CFontLoaderBinaryFormat(f, this, fontFile);
	else
		loader = new CFontLoaderTextFormat(f, this, fontFile);

	int r = loader->Load();
	delete loader;

	return r;
}

void cFont::SetTextEncoding(EFontTextEncoding encoding)
{
	this->encoding = encoding;
}

// Internal
SCharDescr *cFont::GetChar(int id)
{
	std::map<int, SCharDescr*>::iterator it = chars.find(id);
	if( it == chars.end() ) return 0;

	return it->second;
}

// Internal
float cFont::AdjustForKerningPairs(int first, int second)
{	
	SCharDescr *ch = GetChar(first);
	if( ch == 0 ) return 0;
	for( unsigned n = 0; n < ch->kerningPairs.size(); n += 2 )
	{
		if( ch->kerningPairs[n] == second )
			return ch->kerningPairs[n+1] * scale;
	}

	return 0;
}

float cFont::GetTextWidth(const char *text, int count)
{
	if( count <= 0 )
		count = GetTextLength(text);

	float x = 0;

	for( int n = 0; n < count; )
	{
		int charId = GetTextChar(text,n,&n);

		SCharDescr *ch = GetChar(charId);
		if( ch == 0 ) ch = &defChar;

		x += scale * (ch->xAdv);

		if( n < count )
			x += AdjustForKerningPairs(charId, GetTextChar(text,n));
	}

	return x;
}

void cFont::SetHeight(float h)
{
	scale = h / float(fontHeight);
}

float cFont::GetHeight()
{
	return scale * float(fontHeight);
}

float cFont::GetBottomOffset()
{
	return scale * (base - fontHeight);
}

float cFont::GetTopOffset()
{
	return scale * (base - 0);
}

// Internal
// Returns the number of bytes in the string until the null char
int cFont::GetTextLength(const char *text)
{
	if( encoding == UTF16 )
	{
		int textLen = 0;
		for(;;)
		{
			unsigned int len;
			int r = acUtility::DecodeUTF16(&text[textLen], &len);
			if( r > 0 )
				textLen += len;
			else if( r < 0 )
				textLen++;
			else
				return textLen;
		}
	}

	// Both UTF8 and standard ASCII strings can use strlen
	return (int)strlen(text);
}

// Internal
int cFont::GetTextChar(const char *text, int pos, int *nextPos)
{
	int ch;
	unsigned int len;
	if( encoding == UTF8 )
	{
		ch = acUtility::DecodeUTF8(&text[pos], &len);
		if( ch == -1 ) len = 1;
	}
	else if( encoding == UTF16 )
	{
		ch = acUtility::DecodeUTF16(&text[pos], &len);
		if( ch == -1 ) len = 2;
	}
	else
	{
		len = 1;
		ch = (unsigned char)text[pos];
	}

	if( nextPos ) *nextPos = pos + len;
	return ch;
}

// Internal
int cFont::FindTextChar(const char *text, int start, int length, int ch)
{
	int pos = start;
	int nextPos;
	int currChar = -1;
    while( pos < length )
	{
		currChar = GetTextChar(text, pos, &nextPos);
		if( currChar == ch )
			return pos;
		pos = nextPos;
	} 

	return -1;
}

void cFont::InternalWrite(float x, float y, float z, const char *text, int count, float spacing)
{
   // This is a modification of the original code <
	int page = -1;
   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
   glBegin(GL_QUADS);

	y += scale * float(base);

	for( int n = 0; n < count; )
	{
		int charId = GetTextChar(text, n, &n);
		SCharDescr *ch = GetChar(charId);
		if( ch == 0 ) ch = &defChar;

		// Map the center of the texel to the corners
		// in order to get pixel perfect mapping
		float u = (float(ch->srcX)+0.5f) / scaleW;
		float v = (float(ch->srcY)+0.5f) / scaleH;
		float u2 = u + float(ch->srcW) / scaleW;
		float v2 = v + float(ch->srcH) / scaleH;

		float a = scale * float(ch->xAdv);
		float w = scale * float(ch->srcW);
		float h = scale * float(ch->srcH);
		float ox = scale * float(ch->xOff);
		float oy = scale * float(ch->yOff);

		if( ch->page != page )
		{
         glEnd();
         page = ch->page;
         cResource * lpResource = pages[page].GetResource();
         assert(lpResource);
         cTexture * lpTexture = (cTexture*)lpResource;
         unsigned luiTextureHandle = lpTexture->GetTextureHandle();
         glBindTexture( GL_TEXTURE_2D, luiTextureHandle );
         glBegin(GL_QUADS);    
		}

      glColor4f (mfR, mfG, mfB, mfA);
      glTexCoord2f( u, v );
      glVertex3f (x+ox, y-oy, z);
      glTexCoord2f( u2, v );
      glVertex3f (x+w+ox, y-oy, z);
      glTexCoord2f( u2, v2 );
      glVertex3f (x+w+ox, y-h-oy, z);
      glTexCoord2f( u, v2 );
      glVertex3f (x+ox, y-h-oy, z);

		x += a;
		if( charId == ' ' )
			x += spacing;

		if( n < count )
			x += AdjustForKerningPairs(charId, GetTextChar(text,n));
	}
   glEnd();

   // > This is a modification of the original code
}

void cFont::Write(float x, float y, float z, const char *text, int count, unsigned int mode)
{
	if( count <= 0 )
		count = GetTextLength(text);

	if( mode == FONT_ALIGN_CENTER )
	{
		float w = GetTextWidth(text, count);
		x -= w/2;
	}
	else if( mode == FONT_ALIGN_RIGHT )
	{
		float w = GetTextWidth(text, count);
		x -= w;
	}

	InternalWrite(x, y, z, text, count);
}

void cFont::WriteML(float x, float y, float z, const char *text, int count, unsigned int mode)
{
	if( count <= 0 )
		count = GetTextLength(text);

	// Get first line
	int pos = 0;
	int len = FindTextChar(text, pos, count, '\n'); 
	if( len == -1 ) len = count;
	while( pos < count )
	{
		float cx = x;
		if( mode == FONT_ALIGN_CENTER )
		{
			float w = GetTextWidth(&text[pos], len);
			cx -= w/2;
		}
		else if( mode == FONT_ALIGN_RIGHT )
		{
			float w = GetTextWidth(&text[pos], len);
			cx -= w;
		}

		InternalWrite(cx, y, z, &text[pos], len);

		y -= scale * float(fontHeight);

		// Get next line
		pos += len;
		int ch = GetTextChar(text, pos, &pos);
		if( ch == '\n' )
		{
			len = FindTextChar(text, pos, count, '\n');
			if( len == -1 )
				len = count - pos;
			else 
				len = len - pos;
		}
	}
}

void cFont::WriteBox(float x, float y, float z, float width, const char *text, int count, unsigned int mode)
{
	if( count <= 0 )
		count = GetTextLength(text);

	float currWidth = 0, wordWidth;
	int lineS = 0, lineE = 0, wordS = 0, wordE = 0;
	int wordCount = 0;

	const char *s = " ";
	float spaceWidth = GetTextWidth(s, 1);
	bool softBreak = false;
	
	for(; lineS < count;)
	{
		// Determine the extent of the line
		for(;;)
		{
			// Determine the number of characters in the word
			while( wordE < count && 
				GetTextChar(text,wordE) != ' ' &&
				GetTextChar(text,wordE) != '\n' )
				// Advance the cursor to the next character
				GetTextChar(text,wordE,&wordE);

			// Determine the width of the word
			if( wordE > wordS )
			{
				wordCount++;
				wordWidth = GetTextWidth(&text[wordS], wordE-wordS);
			}
			else
				wordWidth = 0;

			// Does the word fit on the line? The first word is always accepted.
			if( wordCount == 1 || currWidth + (wordCount > 1 ? spaceWidth : 0) + wordWidth <= width )
			{
				// Increase the line extent to the end of the word
				lineE = wordE;
				currWidth += (wordCount > 1 ? spaceWidth : 0) + wordWidth;

				// Did we reach the end of the line?
				if( wordE == count || GetTextChar(text,wordE) == '\n' )
				{
					softBreak = false;

					// Skip the newline character
					if( wordE < count )
						// Advance the cursor to the next character
						GetTextChar(text,wordE,&wordE);

					break;
				}				

				// Skip the trailing space
				if( wordE < count && GetTextChar(text,wordE) == ' ' )
					// Advance the cursor to the next character
					GetTextChar(text,wordE,&wordE);

				// Move to next word
				wordS = wordE;
			}
			else
			{
				softBreak = true;

				// Skip the trailing space
				if( wordE < count && GetTextChar(text,wordE) == ' ' )
					// Advance the cursor to the next character
					GetTextChar(text,wordE,&wordE);

				break;
			}
		}

		// Write the line
		if( mode == FONT_ALIGN_JUSTIFY )
		{
			float spacing = 0;
			if( softBreak )
			{
				if( wordCount > 2 )
					spacing = (width - currWidth) / (wordCount-2);
				else
					spacing = (width - currWidth);
			}
			
            InternalWrite(x, y, z, &text[lineS], lineE - lineS, spacing);
		}
		else
		{
			float cx = x;
			if( mode == FONT_ALIGN_RIGHT )
				cx = x + width - currWidth;
			else if( mode == FONT_ALIGN_CENTER )
				cx = x + 0.5f*(width - currWidth);

			InternalWrite(cx, y, z, &text[lineS], lineE - lineS);
		}

		if( softBreak )
		{
			// Skip the trailing space
			if( lineE < count && GetTextChar(text,lineE) == ' ' )
				// Advance the cursor to the next character
				GetTextChar(text,lineE,&lineE);

			// We've already counted the first word on the next line
			currWidth = wordWidth;
			wordCount = 1;
		}
		else
		{
			// Skip the line break
			if( lineE < count && GetTextChar(text,lineE) == '\n' )
				// Advance the cursor to the next character
				GetTextChar(text,lineE,&lineE);

			currWidth = 0;
			wordCount = 0;
		}
		
		// Move to next line
		lineS = lineE;
		wordS = wordE;
		y -= scale * float(fontHeight);
	}
}

// This is a modification of the original code <
/*
void cFont::PrepareEffect()
{
	CGraphics *gfx = render->GetGraphics();

	gfx->SetEffect(fxFile.c_str());

	if( hasOutline )
		gfx->SetEffectTechnique("RenderWithOutline");
	else
		gfx->SetEffectTechnique("RenderWithoutOutline");
}

void cFont::PreparePixelPerfectOutput()
{
	IDirect3DDevice9 *dev = render->GetDevice();
	CGraphics *gfx = render->GetGraphics();

	// Determine size of view port
	D3DVIEWPORT9 vp;
	dev->GetViewport(&vp);

	// Clear world matrix
	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	gfx->SetMatrix(D3DTS_WORLD, &mtx);

	// Setup orthogonal view
	// Origin is in lower-left corner
	D3DXMatrixOrthoOffCenterLH(&mtx, 0, (float)vp.Width, 0, (float)vp.Height, vp.MinZ, vp.MaxZ);
	gfx->SetMatrix(D3DTS_VIEW, &mtx);

	D3DXMatrixIdentity(&mtx);
	gfx->SetMatrix(D3DTS_PROJECTION, &mtx);

	// Adjust the scale of the font so that the 
	// resolution of texture is the same as the screen
	scale = 1.0f;
}*/
// > This is a modification of the original code 

//=============================================================================
// CFontLoader
//
// This is the base class for all loader classes. This is the only class
// that has access to and knows how to set the cFont members.
//=============================================================================

CFontLoader::CFontLoader(FILE *f, cFont *font, const char *fontFile)
{
	this->f = f;
	this->font = font;
	this->fontFile = fontFile;

	outlineThickness = 0;
}

void CFontLoader::LoadPage(int id, const char *pageFile, const char *fontFile)
{
	string str;

	// Load the texture from the same directory as the font descriptor file

	// Find the directory
	str = fontFile;
	for( size_t n = 0; (n = str.find('/', n)) != string::npos; ) str.replace(n, 1, "\\");
	size_t i = str.rfind('\\');
	if( i != string::npos )
		str = str.substr(0, i+1);
	else
		str = "";

	// Load the font textures
	str += pageFile;
  
   // This is a modification of the original code <
   cResourceHandle lHandle = cTextureManager::Get().LoadResource(str.c_str(),str.c_str());
	font->pages[id] = lHandle;
   // > This is a modification of the original code 
}

void CFontLoader::SetFontInfo(int outlineThickness)
{
	this->outlineThickness = outlineThickness;
}

void CFontLoader::SetCommonInfo(int fontHeight, int base, int scaleW, int scaleH, int pages, bool isPacked)
{
	font->fontHeight = fontHeight;
	font->base = base;
	font->scaleW = scaleW;
	font->scaleH = scaleH;
	font->pages.resize(pages);
   // This is a modification of the original code <
/*	for( int n = 0; n < pages; n++ )
		font->pages[n] = 0; */
   // > This is a modification of the original code 

	if( isPacked && outlineThickness )
		font->hasOutline = true;
}

void CFontLoader::AddChar(int id, int x, int y, int w, int h, int xoffset, int yoffset, int xadvance, int page, int chnl)
{
	// Convert to a 4 element vector
	// TO DO: Does this depend on hardware? It probably does
	if     ( chnl == 1 ) chnl = 0x00010000;  // Blue channel
	else if( chnl == 2 ) chnl = 0x00000100;  // Green channel
	else if( chnl == 4 ) chnl = 0x00000001;  // Red channel
	else if( chnl == 8 ) chnl = 0x01000000;  // Alpha channel
	else chnl = 0;

	if( id >= 0 )
	{
		SCharDescr *ch = new SCharDescr;
		ch->srcX = x;
		ch->srcY = y;
		ch->srcW = w;
		ch->srcH = h;
		ch->xOff = xoffset;
		ch->yOff = yoffset;
		ch->xAdv = xadvance;
		ch->page = page;
		ch->chnl = chnl;

		font->chars.insert(std::map<int, SCharDescr*>::value_type(id, ch));
	}

	if( id == -1 )
	{
		font->defChar.srcX = x;
		font->defChar.srcY = y;
		font->defChar.srcW = w;
		font->defChar.srcH = h;
		font->defChar.xOff = xoffset;
		font->defChar.yOff = yoffset;
		font->defChar.xAdv = xadvance;
		font->defChar.page = page;
		font->defChar.chnl = chnl;
	}
}

void CFontLoader::AddKerningPair(int first, int second, int amount)
{
	if( first >= 0 && first < 256 && font->chars[first] )
	{
		font->chars[first]->kerningPairs.push_back(second);
		font->chars[first]->kerningPairs.push_back(amount);
	}
}

//=============================================================================
// CFontLoaderTextFormat
//
// This class implements the logic for loading a BMFont file in text format
//=============================================================================

CFontLoaderTextFormat::CFontLoaderTextFormat(FILE *f, cFont *font, const char *fontFile) : CFontLoader(f, font, fontFile)
{
}

int CFontLoaderTextFormat::Load()
{
	string line;

	

	while( !feof(f) )
	{
		// Read until line feed (or EOF)
		line = "";
		line.reserve(256);
		while( !feof(f) )
		{
			char ch;
			if( fread(&ch, 1, 1, f) )
			{
				if( ch != '\n' ) 
					line += ch; 
				else
					break;
			}
		}

		if (line == "") break; //Yorman y Jos� Manuel (a�adido)

		// Skip white spaces
		int pos = SkipWhiteSpace(line, 0);

		// Read token
		int pos2 = FindEndOfToken(line, pos);
		string token = line.substr(pos, pos2-pos);

		//DEBUG_MSG("%d - %s", ++i, token.c_str());
		
		
		// Interpret line
		if( token == "info" )
			InterpretInfo(line, pos2);
		else if( token == "common" )
			InterpretCommon(line, pos2);
		else if( token == "char" )
			InterpretChar(line, pos2);
		else if( token == "kerning" )
			InterpretKerning(line, pos2);
		else if( token == "page" )
			InterpretPage(line, pos2, fontFile);
	}

	fclose(f);

	// Success
	return 0;
}

int CFontLoaderTextFormat::SkipWhiteSpace(string &str, int start)
{
	unsigned n = start;
	while( n < str.size() )
	{
		char ch = str[n];
		if( ch != ' ' && 	ch != '\t' && ch != '\r' &&  ch != '\n' )
			break;

		++n;
	}

	return n;
}

int CFontLoaderTextFormat::FindEndOfToken(string &str, int start)
{
	unsigned n = start;
	if( str[n] == '"' )
	{
		n++;
		while( n < str.size() )
		{
			char ch = str[n];
			if( ch == '"' )
			{
				// Include the last quote char in the token
				++n;
				break;
			}
			++n;
		}
	}
	else
	{
		while( n < str.size() )
		{
			char ch = str[n];
			if( ch == ' ' ||
				ch == '\t' ||
				ch == '\r' ||
				ch == '\n' ||
				ch == '=' )
				break;

			++n;
		}
	}

	return n;
}

void CFontLoaderTextFormat::InterpretKerning(string &str, int start)
{
	// Read the attributes
	int first = 0;
	int second = 0;
	int amount = 0;

	int pos, pos2 = start;
	while( true )
	{
		pos = SkipWhiteSpace(str, pos2);
		pos2 = FindEndOfToken(str, pos);

		string token = str.substr(pos, pos2-pos);

		pos = SkipWhiteSpace(str, pos2);
		if( pos == str.size() || str[pos] != '=' ) break;

		pos = SkipWhiteSpace(str, pos+1);
		pos2 = FindEndOfToken(str, pos);

		string value = str.substr(pos, pos2-pos);

		if( token == "first" )
			first = strtol(value.c_str(), 0, 10);
		else if( token == "second" )
			second = strtol(value.c_str(), 0, 10);
		else if( token == "amount" )
			amount = strtol(value.c_str(), 0, 10);

		//if( pos == str.size() ) break;  //orig Jes�s
		if( pos2 == str.size() -1 ) break;  //Yorman  y Jos� Manuel (a�adido)
	}

	// Store the attributes
	AddKerningPair(first, second, amount);
}

void CFontLoaderTextFormat::InterpretChar(string &str, int start)
{
	// Read all attributes
	int id = 0;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	int xoffset = 0;
	int yoffset = 0;
	int xadvance = 0;
	int page = 0;
	int chnl = 0;

	int pos, pos2 = start;
	while( true )
	{
		pos = SkipWhiteSpace(str, pos2);
		pos2 = FindEndOfToken(str, pos);

		string token = str.substr(pos, pos2-pos);

		pos = SkipWhiteSpace(str, pos2);
		if( pos == str.size() || str[pos] != '=' ) break;

		pos = SkipWhiteSpace(str, pos+1);
		pos2 = FindEndOfToken(str, pos);

		string value = str.substr(pos, pos2-pos);

		if( token == "id" )
			id = strtol(value.c_str(), 0, 10);
		else if( token == "x" )
			x = strtol(value.c_str(), 0, 10);
		else if( token == "y" )
			y = strtol(value.c_str(), 0, 10);
		else if( token == "width" )
			width = strtol(value.c_str(), 0, 10);
		else if( token == "height" )
			height = strtol(value.c_str(), 0, 10);
		else if( token == "xoffset" )
			xoffset = strtol(value.c_str(), 0, 10);
		else if( token == "yoffset" )
			yoffset = strtol(value.c_str(), 0, 10);
		else if( token == "xadvance" )
			xadvance = strtol(value.c_str(), 0, 10);
		else if( token == "page" )
			page = strtol(value.c_str(), 0, 10);
		else if( token == "chnl" )
			chnl = strtol(value.c_str(), 0, 10);

		//if( pos == str.size() ) break;  //orig Jes�s
		if( pos2 >= str.size() -1 ) break;  //Yorman  y Jos� Manuel (a�adido)
	}

	// Store the attributes
	AddChar(id, x, y, width, height, xoffset, yoffset, xadvance, page, chnl);
}

void CFontLoaderTextFormat::InterpretCommon(string &str, int start)
{
	int fontHeight;
	int base;
	int scaleW;
	int scaleH;
	int pages;
	int packed;

	// Read all attributes
	int pos, pos2 = start;
	while( true )
	{
		pos = SkipWhiteSpace(str, pos2);
		pos2 = FindEndOfToken(str, pos);

		string token = str.substr(pos, pos2-pos);

		pos = SkipWhiteSpace(str, pos2);
		if( pos == str.size() || str[pos] != '=' ) break;

		pos = SkipWhiteSpace(str, pos+1);
		pos2 = FindEndOfToken(str, pos);

		string value = str.substr(pos, pos2-pos);

		if( token == "lineHeight" )
			fontHeight = (short)strtol(value.c_str(), 0, 10);
		else if( token == "base" )
			base = (short)strtol(value.c_str(), 0, 10);
		else if( token == "scaleW" )
			scaleW = (short)strtol(value.c_str(), 0, 10);
		else if( token == "scaleH" )
			scaleH = (short)strtol(value.c_str(), 0, 10);
		else if( token == "pages" )
			pages = strtol(value.c_str(), 0, 10);
		else if( token == "packed" )
			packed = strtol(value.c_str(), 0, 10);

		//if( pos == str.size() ) break; //orig Jes�s
		if( pos2 == str.size() - 1) break; //Yorman  y Jos� Manuel (a�adido)
	}

	SetCommonInfo(fontHeight, base, scaleW, scaleH, pages, packed ? true : false);
}

void CFontLoaderTextFormat::InterpretInfo(string &str, int start)
{
	int outlineThickness;

	// Read all attributes
	int pos, pos2 = start;
	while( true )
	{
		pos = SkipWhiteSpace(str, pos2);
		pos2 = FindEndOfToken(str, pos);

		string token = str.substr(pos, pos2-pos);

		pos = SkipWhiteSpace(str, pos2);
		if( pos == str.size() || str[pos] != '=' ) 
			break;



		pos = SkipWhiteSpace(str, pos+1);
		pos2 = FindEndOfToken(str, pos);

		string value = str.substr(pos, pos2-pos);

		if( token == "outline" )
			outlineThickness = (short)strtol(value.c_str(), 0, 10);

		//if( pos >= str.size() ) break; //orig Jes�s
		if( pos2 >= str.size() -1) 	break; //Yorman  y Jos� Manuel (a�adido)


	}

	SetFontInfo(outlineThickness);
}

void CFontLoaderTextFormat::InterpretPage(string &str, int start, const char *fontFile)
{
	int id = 0;
	string file;

	// Read all attributes
	int pos, pos2 = start;
	while( true )
	{
		pos = SkipWhiteSpace(str, pos2);
		pos2 = FindEndOfToken(str, pos);

		string token = str.substr(pos, pos2-pos);

		pos = SkipWhiteSpace(str, pos2);
		if( pos == str.size() || str[pos] != '=' ) break;

		pos = SkipWhiteSpace(str, pos+1);
		pos2 = FindEndOfToken(str, pos);

		string value = str.substr(pos, pos2-pos);

		if( token == "id" )
			id = strtol(value.c_str(), 0, 10);
		else if( token == "file" )
			file = value.substr(1, value.length()-2);

		//if( pos == str.size() ) break; //orig Jes�s
		if( pos2 >= str.size() - 1) break; //Yorman  y Jos� Manuel (a�adido)
	}

	LoadPage(id, file.c_str(), fontFile);
}

//=============================================================================
// CFontLoaderBinaryFormat
//
// This class implements the logic for loading a BMFont file in binary format
//=============================================================================

CFontLoaderBinaryFormat::CFontLoaderBinaryFormat(FILE *f, cFont *font, const char *fontFile) : CFontLoader(f, font, fontFile)
{
}

int CFontLoaderBinaryFormat::Load()
{
	// Read and validate the tag. It should be 66, 77, 70, 2, 
	// or 'BMF' and 2 where the number is the file version.
	char magicString[4];
	fread(magicString, 4, 1, f);
	if( strncmp(magicString, "BMF\003", 4) != 0 )
	{
		LOG(("Unrecognized format for '%s'", fontFile));
		fclose(f);
		return -1;
	}

	// Read each block
	char blockType;
	int blockSize;
	while( fread(&blockType, 1, 1, f) )
	{
		// Read the blockSize
		fread(&blockSize, 4, 1, f);

		switch( blockType )
		{
		case 1: // info
			ReadInfoBlock(blockSize);
			break;
		case 2: // common
			ReadCommonBlock(blockSize);
			break;
		case 3: // pages
			ReadPagesBlock(blockSize);
			break;
		case 4: // chars
			ReadCharsBlock(blockSize);
			break;
		case 5: // kerning pairs
			ReadKerningPairsBlock(blockSize);
			break;
		default:
			LOG(("Unexpected block type (%d)", blockType));
			fclose(f);
			return -1;
		}
	}

	fclose(f);

	// Success
	return 0;
}

void CFontLoaderBinaryFormat::ReadInfoBlock(int size)
{
#pragma pack(push)
#pragma pack(1)
struct infoBlock
{
    unsigned short fontSize;
    unsigned char reserved:4;
    unsigned char bold    :1;
    unsigned char italic  :1;
    unsigned char unicode :1;
    unsigned char smooth  :1;
    unsigned char charSet;
    unsigned short stretchH;
    unsigned char aa;
    unsigned char paddingUp;
    unsigned char paddingRight;
    unsigned char paddingDown;
    unsigned char paddingLeft;
    unsigned char spacingHoriz;
    unsigned char spacingVert;
    unsigned char outline;         // Added with version 2
    char fontName[1];
};
#pragma pack(pop)

	char *buffer = new char[size];
	fread(buffer, size, 1, f);

	// We're only interested in the outline thickness
	infoBlock *blk = (infoBlock*)buffer;
	SetFontInfo(blk->outline);

	delete[] buffer;
}

void CFontLoaderBinaryFormat::ReadCommonBlock(int size)
{
#pragma pack(push)
#pragma pack(1)
struct commonBlock
{
    unsigned short lineHeight;
    unsigned short base;
    unsigned short scaleW;
    unsigned short scaleH;
    unsigned short pages;
    unsigned char packed  :1;
    unsigned char reserved:7;
	unsigned char alphaChnl;
	unsigned char redChnl;
	unsigned char greenChnl;
	unsigned char blueChnl;
}; 
#pragma pack(pop)

	char *buffer = new char[size];
	fread(buffer, size, 1, f);

	commonBlock *blk = (commonBlock*)buffer;

	SetCommonInfo(blk->lineHeight, blk->base, blk->scaleW, blk->scaleH, blk->pages, blk->packed ? true : false);

	delete[] buffer;
}

void CFontLoaderBinaryFormat::ReadPagesBlock(int size)
{
#pragma pack(push)
#pragma pack(1)
struct pagesBlock
{
    char pageNames[1];
};
#pragma pack(pop)

	char *buffer = new char[size];
	fread(buffer, size, 1, f);

	pagesBlock *blk = (pagesBlock*)buffer;

	for( int id = 0, pos = 0; pos < size; id++ )
	{
		LoadPage(id, &blk->pageNames[pos], fontFile);
		pos += 1 + (int)strlen(&blk->pageNames[pos]);
	}

	delete[] buffer;
}

void CFontLoaderBinaryFormat::ReadCharsBlock(int size)
{
#pragma pack(push)
#pragma pack(1)
struct charsBlock
{
    struct charInfo
    {
        unsigned id;
        unsigned short  x;
        unsigned short  y;
        unsigned short  width;
        unsigned short  height;
        short xoffset;
        short yoffset;
        short xadvance;
        unsigned char  page;
        unsigned char  chnl;
    } chars[1];
};
#pragma pack(pop)

	char *buffer = new char[size];
	fread(buffer, size, 1, f);

	charsBlock *blk = (charsBlock*)buffer;

	for( int n = 0; int(n*sizeof(charsBlock::charInfo)) < size; n++ )
	{
		AddChar(blk->chars[n].id,
		        blk->chars[n].x,
				blk->chars[n].y,
				blk->chars[n].width,
				blk->chars[n].height,
				blk->chars[n].xoffset,
				blk->chars[n].yoffset,
				blk->chars[n].xadvance,
				blk->chars[n].page,
				blk->chars[n].chnl);
	}

	delete[] buffer;
}

void CFontLoaderBinaryFormat::ReadKerningPairsBlock(int size)
{
#pragma pack(push)
#pragma pack(1)
struct kerningPairsBlock
{
    struct kerningPair
    {
        unsigned first;
        unsigned second;
        short amount;
    } kerningPairs[1];
};
#pragma pack(pop)

	char *buffer = new char[size];
	fread(buffer, size, 1, f);

	kerningPairsBlock *blk = (kerningPairsBlock*)buffer;

	for( int n = 0; int(n*sizeof(kerningPairsBlock::kerningPair)) < size; n++ )
	{
		AddKerningPair(blk->kerningPairs[n].first,
		               blk->kerningPairs[n].second,
					   blk->kerningPairs[n].amount);
	}

	delete[] buffer;
}

// This is a modification of the original code <
#pragma warning( default : 4996 )
// > This is a modification of the original code

// 2008-05-11 Storing the characters in a map instead of an array
// 2008-05-11 Loading the new binary format for BMFont v1.10
// 2008-05-17 Added support for writing text with UTF8 and UTF16 encoding
