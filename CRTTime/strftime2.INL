// strftime2.INL : Define strftime2, the ANSI encoding, and wcsftime2, the wide character (Unicode) encoding.
	TCHAR * lpFormatString		= NULL;
	size_t  rintNChars			= EMPTY_STRING_LENGTH;

	if ( pstrformat )
	{
		if ( ( lpFormatString = PrepareForCRT ( pstrformat ) ) )
		{
			if ( rintNChars = _tcsftime ( pstrDest ,
										  pintMaxSize ,
					                      pstrformat ,
						                  plptimeStruct ) )
			{
				return rintNChars;
			}	// TRUE (anticipated outcome) block, if ( intNChars = _tcsftime ( strDest , maxsize , lpFormatString , timeptr )
			else
			{	// CRT function _tcsftime returned nothing.
				return CRTTIME_ERR_FORMAT_STR_NULL;
			}	// FALSE (unanticipated outcome) block, if ( intNChars = _tcsftime ( strDest , maxsize , lpFormatString , timeptr )
		}	// TRUE (anticipated outcome) block, if ( ( lpFormatString = PrepareForCRT ( format ) ) )
		else
		{	// Function PrepareForCRT returned nothing.
			return CRTTIME_ERR_FORMAT_STR_NULL;
		}	// FALSE (unanticipated outcome) block, if ( ( lpFormatString = PrepareForCRT ( format ) ) )
	}	// TRUE (anticipated outcome) block, if ( format )
	else
	{	// The supplied input string is a null reference.
		return CRTTIME_ERR_FORMAT_STR_NULL;
	}	// FALSE (unanticipated outcome) block, if ( format )
// strftime2