#ifndef MY_DEBUG_H
#define MY_DEBUG_H
// "arranged" By CarliXYZ taking lots of bits from here and there, too mixed up to say nothing
// tip: the next lines are equivalent, just keeped for the taste of everyone
// Debug.ToOutput()  << something;
// Debug::ToOutput() << something;  
// Debug()			 << something;

#include <sstream>
#include <windows.h>
#include <fstream>

class Debug	
{
public:

   static Debug &ToOutput(void);						// Use Debug::ToOuput() << something << etc << etc ;
   static std::fstream & ToFile(const char *FileName);	// Use Debug::ToOuput( "FileName.txt" ) << something << etc  ;
   static void ToOutput(const char *format, ...);		// Use Debug::ToOuput( "something %i <%f> ", etc, etc );
   static void ToMsgBox(const char *format, ...);		// same as the last one but sending it to a Windows MessageBox
 
   template <class T>
   inline Debug &operator << (const T & t) // templates needs definitions in headers
   {
		static std::ostringstream oss;			// create a stream
		oss << t;								// insert value to stream
		OutputDebugString( oss.str().c_str() ); // Target Output stream
		return *this;
   }

   inline Debug &operator << (Debug &(*function)(Debug &dbgInstance))//Use Debug() << something; or .ToOutput()<< something;
		{ return function (*this); }  

   static Debug &Endl (Debug &dbgInstance);	// Use Debug() << Debug::Endl << something << Debug::Endl ;
 
   // and so on..
};

#endif // MY_DEBUG_H

// TO DO: Fix some acumulation Stream problem with << operator that repeats the last input
// and Add some ToFile( name.xml, string, ...) Foo 