// FormatNowLocalW.C : Define the Unicode (wide characteer) current local time formatter.
//

#include ".\CRTTime_Pvt.H"

LPTSTR LIBSPEC_CRTTIME2_API FormatNowLocalW
(
    const void *  pFormat ,
    const HMODULE phDllhModule
)
{
    #include ".\FormatNowLocal.INL"
}   // FormatNowLocalW