// wcsftime2_l.C : Defines an exported functions for the DLL application.
//

#include "CRTTime_Pvt.H"

size_t LIBSPEC_CRTTIME2_API wcsftime2_l (
	PTCHAR            pstrDest ,
	size_t            pintMaxSize ,
	const PTCHAR      pstrformat ,
	const struct tm * plptimeStruct ,
	_locale_t         plocale
)
{
	return EMPTY_STRING_LENGTH;
}	// wcsftime2_l