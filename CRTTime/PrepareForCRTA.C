// PrepareForCRTA.C : Define the ANSI (narrow character) time zone token substituor.
//
#undef UNICODE
#undef _UNICODE

#include ".\CRTTime_Pvt.H"

char    * __stdcall PrepareForCRTA
(
    const char    * plpszFormat
)
{
    #include ".\PrepareForCRT.INL"
}   // PrepareForCRTA