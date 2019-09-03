//	File Name:			FormatTimeBothA.C
//
//	File Abstract:		This C source file defines the ANSI (narrow character)
//						implementation of FormatTimeBoth.

#undef UNICODE
#undef _UNICODE

#include ".\CRTTime_Pvt.H"

BOOL LIBSPEC_CRTTIME2_API FormatTimeBothA ( const void * pFormatLocal , const void * pFormatUtc , const HMODULE phDllhModule , LPCRT_TIME_BOTH plpTimeInfo )
{
	#include ".\FormatTimeBoth.INL"
}	// FormatTimeBothA