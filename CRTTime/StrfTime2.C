// StrfTime2.cpp : Defines an exported functions for the DLL application.
//

#undef UNICODE
#undef _UNICODE

#include ".\CRTTime_Pvt.H"

size_t LIBSPEC_CRTTIME2_API strftime2 (
	PTCHAR            pstrDest ,
	size_t            pintMaxSize ,
	const PTCHAR      pstrformat ,
	const struct tm * plptimeStruct
)
{
	#include ".\strftime2.INL"
}	// strftime2