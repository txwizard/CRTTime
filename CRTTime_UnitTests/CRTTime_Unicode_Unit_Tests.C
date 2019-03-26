// CRTTime2_Unicode_Unit_Tests.C : Define the ANSI unit tests.
//

#include ".\CRTTime_Unit_Tests.H"

int     __stdcall CRTTime2_Unicode_Unit_Tests ( const struct tm *			plpcrt_tm_struct )
{
	_tprintf ( TEXT ( "Exercising the library with Unicode character strings.\n" ) );
	#include ".\CRTTime_Unit_Tests.INL"
}	// CRTTime2_Unicode_Unit_Tests