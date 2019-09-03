// FormatTimeUTCW.C : Define the Unicode (wide character) local time formatter.
//

#include ".\CRTTime_Pvt.H"

LPTSTR LIBSPEC_CRTTIME2_API FormatTimeUTCW
(
	const void *   pFormat,
	const HMODULE  phDllhModule,
	const time_t * plpcrt_time_t_struct
)
{
	#include ".\FormatTimeUTC.INL"
}   // FormatTimeUTCW