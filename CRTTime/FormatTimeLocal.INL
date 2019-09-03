// FormatNowUTC.INL : Define the ANSI (narrow character) AND Unicode (wide 
//                    character) current UTC time formatters.
//

//LPTSTR LIBSPEC_CRTTIME2_API FormatTimeLocal
//(
//	const void*   pFormat,
//	const HMODULE phDllhModule,
//	const time_t* plpcrt_time_t_struct
//)

	struct tm	crt_tm_struct;								// The struct keyword is required because I'm compiling as straight C.

	LPTSTR		lpszFormatString	= NULL;
	int			uintResult			= 0;

	LPTSTR		rlpOutputBuffer		= ( LPTSTR ) AllocCString_WW ( CRTTIME_NOW_OUTPUT_BUFCAP );

	if ( rlpOutputBuffer )
	{
		lpszFormatString			= FormatNowGetString ( pFormat ,
												           phDllhModule );

		if ( lpszFormatString )
		{
			if ( ( errno = _localtime64_s ( &crt_tm_struct , plpcrt_time_t_struct ) ) == CRT_TIME_CONVERSION_SUCCESS )
			{	// Success. Call _tcsftime through _tcsftime2. Gee, aren't we imaginative? No, but we're standards adherent.
				if ( uintResult = _tcsftime2 ( rlpOutputBuffer ,
					                           CRTTIME_NOW_OUTPUT_BUFCAP ,
						                       lpszFormatString ,
						                       &crt_tm_struct ) )
				{
					return rlpOutputBuffer;
				}	// TRUE (anticipated outcome) block, if ( uintResult = _tcsftime2 ( rlpOutputBuffer , CRTTIME_NOW_OUTPUT_BUFCAP , lpszFormatString , &crt_tm_struct ) )
				else
				{
					return NULL;
				}	// FALSE (unanticipated outcome) block, if ( uintResult = _tcsftime2 ( rlpOutputBuffer , CRTTIME_NOW_OUTPUT_BUFCAP , lpszFormatString , &crt_tm_struct ) )
			}	// TRUE (anticipated outcome) block, if ( ( errno = _localtime64_s ( &crt_tm_struct , plpcrt_time_t_struct ) ) == CRT_TIME_CONVERSION_SUCCESS )
			else
			{
				return NULL;
			}	// FALSE (unanticipated outcome) block, if ( ( errno = _localtime64_s ( &crt_tm_struct , plpcrt_time_t_struct ) ) == CRT_TIME_CONVERSION_SUCCESS )
		}	// TRUE (anticipated outcome) block, if ( lpFormatString )
		else
		{
			return NULL;
		}	// FALSE (unanticipated outcome) block, if ( lpFormatString )
	}	// TRUE (anticipated outcome) block, if ( rlpOutputBuffer )
	else
	{
		SetLastError ( CRTTIME_ERR_OUT_OF_MEMORY );
		return NULL;
	}	// FALSE (unanticipated outcome) block, if ( rlpOutputBuffer )