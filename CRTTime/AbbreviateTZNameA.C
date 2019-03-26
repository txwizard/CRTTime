// AbbreviateTZNameA.C : Define the ANsi (narrow character) time zone abbreviator.
//

#undef UNICODE
#undef _UNICODE

#include "CRTTime_Pvt.H"

size_t    __stdcall AbbreviateTZNameA ( char    * plpszDest )
{
	return EMPTY_STRING_LENGTH;
}	// AbbreviateTZNameA