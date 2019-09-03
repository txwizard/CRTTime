// FormatTimeLocalA.C : Define the ANSI (narrow character) local time formatter.
//
#undef UNICODE
#undef _UNICODE

#include ".\CRTTime_Pvt.H"

LPTSTR LIBSPEC_CRTTIME2_API FormatTimeLocalA
(
    const void *   pFormat ,
    const HMODULE  phDllhModule ,
    const time_t * plpcrt_time_t_struct
)
{
    #include ".\FormatTimeLocal.INL"
}   // FormatTimeLocalA