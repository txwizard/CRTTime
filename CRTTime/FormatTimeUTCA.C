// FormatTimeUTCA.C : Define the ANSI (narrow character) local time formatter.
//
#undef UNICODE
#undef _UNICODE

#include ".\CRTTime_Pvt.H"

LPTSTR LIBSPEC_CRTTIME2_API FormatTimeUTCA
(
	const void *   pFormat,
	const HMODULE  phDllhModule,
	const time_t * plpcrt_time_t_struct
)
{
	#include ".\FormatTimeUTC.INL"
}   // FormatTimeUTCA