// FormatNowLocalA.C : Define the ANSI (narrow character) current local time formatter.
//
#undef UNICODE
#undef _UNICODE

#include ".\CRTTime_Pvt.H"

LPTSTR LIBSPEC_CRTTIME2_API FormatNowLocalA
(
    const void *  pFormat ,
    const HMODULE phDllhModule
)
{
    #include ".\FormatNowLocal.INL"
}   // FormatNowLocalA