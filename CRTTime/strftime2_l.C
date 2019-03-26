// StrfTime2_l.C : Defines an exported functions for the DLL application.
//

#undef UNICODE
#undef _UNICODE

#include "CRTTime_Pvt.H"

size_t LIBSPEC_CRTTIME2_API strftime2_l (
	PTCHAR            pstrDest ,
	size_t            pintMaxSize ,
	const PTCHAR      pstrformat ,
	const struct tm * plptimeStruct ,
	_locale_t         plocale
)
{
	return EMPTY_STRING_LENGTH;
}	// strftime2_l