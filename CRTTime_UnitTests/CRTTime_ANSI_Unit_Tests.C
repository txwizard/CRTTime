// CRTTime2_ANSI_Unit_Tests.C : Define the ANSI unit tests.
//

#undef UNICODE
#undef _UNICODE

#include ".\CRTTime_Unit_Tests.H"

int     __stdcall CRTTime2_ANSI_Unit_Tests ( const struct tm *			plpcrt_tm_struct )
{
	_tprintf ( TEXT ( "Exercising the library with ANSI character strings.\n" ) );
	#include ".\CRTTime_Unit_Tests.INL"
}	// CRTTime2_ANSI_Unit_Tests