// FormatNowUTCW.C : Define the Unicode (wide characteer) current UTC time formatter.
//

#include ".\CRTTime_Pvt.H"

LPTSTR LIBSPEC_CRTTIME2_API FormatNowUTCW
(
    const void *  pFormat ,
    const HMODULE phDllhModule
)
{
    #include ".\FormatNowUTC.INL"
}   // FormatNowUTCW