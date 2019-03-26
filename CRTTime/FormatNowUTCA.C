// FormatNowUTCA.C : Define the ANSI (narrow character) current UTC time formatter.
//
#undef UNICODE
#undef _UNICODE

#include "CRTTime_Pvt.H"

LPTSTR LIBSPEC_CRTTIME2_API FormatNowUTCA ( void * pFormat , const HMODULE phDllhModule )
{
	#include ".\FormatNowUTC.INL"
}	// FormatNowUTCA