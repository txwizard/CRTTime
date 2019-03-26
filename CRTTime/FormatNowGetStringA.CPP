// FormatNowGetStringA.C : Define the ANSI (narrow character) current time format string loader.
//
#undef UNICODE
#undef _UNICODE

#include "CRTTime_Pvt.H"

LPTSTR    __stdcall FormatNowGetStringA ( const void *    pFormat , const HMODULE phDllhModule )
{
	#include ".\FormatNowGetString.INL"
}	// FormatNowGetStringA