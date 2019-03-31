// wcsftime2.C : Defines an exported functions for the DLL application.
//

#include ".\CRTTime_Pvt.H"

size_t LIBSPEC_CRTTIME2_API wcsftime2 (
	PTCHAR            pstrDest ,
	size_t            pintMaxSize ,
	const PTCHAR      pstrformat ,
	const struct tm * plptimeStruct
)
{
	#include ".\strftime2.INL"
}	// wcsftime2