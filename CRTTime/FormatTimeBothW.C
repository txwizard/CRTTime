//	File Name:			FormatTimeBothW.C
//
//	File Abstract:		This C source file defines the Unicode (Wide character)
//						implementation of FormatTimeBoth.

#include ".\CRTTime_Pvt.H"

BOOL LIBSPEC_CRTTIME2_API FormatTimeBothW ( const void * pFormatLocal , const void * pFormatUtc , const HMODULE phDllhModule , LPCRT_TIME_BOTH plpTimeInfo )
{
	#include ".\FormatTimeBoth.INL"
}	// FormatTimeBothW