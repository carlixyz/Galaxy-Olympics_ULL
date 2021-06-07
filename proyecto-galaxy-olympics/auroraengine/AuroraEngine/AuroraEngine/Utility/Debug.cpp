#include "Debug.h"

#define DBG_CHAR_SIZE 256 // If there is some buffer overrun, change it to 4096

Debug &Debug::ToOutput(void)
{
	static Debug dbgInstance;
	
	return dbgInstance; 
}
std::fstream &  Debug::ToFile(const char *FileName)
{
	static std::fstream out( FileName, std::ios::out );
	return out;
}

void Debug::ToOutput(const char *format, ...)
{
	char buf[DBG_CHAR_SIZE], *p = buf;
	va_list args;
	int     n;

	va_start(args, format);
	//_vsnprintf disabled for deprecation (but maybe this works better, some issue with \n maybe )
	n =  _vsnprintf_s(p, sizeof buf - 3,DBG_CHAR_SIZE, format, args); // buf-3 is room for CR/LF/NUL
	va_end(args);

	p += (n < 0) ? sizeof buf - 3 : n;

	while ( p > buf  &&  isspace(p[-1]) )
		*--p = '\0';

	*p++ = '\r';
	*p++ = '\n';
	*p   = '\0';

	OutputDebugString(buf);
}
void Debug::ToMsgBox(const char *format, ...)
{
		char buf[DBG_CHAR_SIZE], *p = buf;
	va_list args;
	int     n;

	va_start(args, format);//_vsnprintf disabled for deprecation (but maybe it works better)
	n =  _vsnprintf_s(p, sizeof buf - 3,DBG_CHAR_SIZE, format, args); // buf-3 is room for CR/LF/NUL
	va_end(args);

	p += (n < 0) ? sizeof buf - 3 : n;

	while ( p > buf  &&  isspace(p[-1]) )
		*--p = '\0';

	*p++ = '\r';
	*p++ = '\n';
	*p   = '\0';

	  MessageBox( NULL, buf, "Debug Message Box", MB_OK );
}


Debug &Debug::Endl(Debug &dbgInstance)
  {
	   std::ostringstream oss;
	   oss << std::endl;
	   OutputDebugString( oss.str().c_str() );
	   /* write newline and flush output */
	   return dbgInstance;
   }
	/*
		void ToOutput(LPCTSTR lpOutputString, ... )
	{
		TCHAR OutMsg[DBG_CHAR_SIZE];

		va_list argptr;
		va_start(argptr, lpOutputString);

		wvsprintf(OutMsg, lpOutputString, argptr);
		OutputDebugString(OutMsg);

		va_end(argptr);
	}*/