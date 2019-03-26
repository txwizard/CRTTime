// FormatNowGetStringW.C : Define the Unicode (wide characteer) current time format string loader.
//

#include "CRTTime_Pvt.H"

LPTSTR    __stdcall FormatNowGetStringW ( const void *    pFormat , const HMODULE phDllhModule )
{
	#include ".\FormatNowGetString.INL"
}	// FormatNowGetStringW