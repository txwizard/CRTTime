// PrepareForCRTW.C : Define the Unicode (wide character) time zone token substituor.
//

#include "CRTTime_Pvt.H"

wchar_t * __stdcall PrepareForCRTW ( const wchar_t * plpszFormat )
{
	#include ".\PrepareForCRT.INL"
}	// PrepareForCRTW