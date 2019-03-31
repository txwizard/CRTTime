// FormatNowUTC.INL : Define the ANSI (narrow character) AND Unicode (wide 
//                    character) current UTC time formatters.
//

//	LPTSTR LIBSPEC_CRTTIME2_API FormatNowUTC ( void * pFormat , const HMODULE phDllhModule )

// ToDo: Devise a way for these to start with exactly the same time.
	time_t				crt_time_t_struct;
	struct tm			crt_tm_struct;								// The struct keyword is required because I'm compiling as straight C.

	LPTSTR lpszFormatString;
	size_t uintResult = 0;

	LPTSTR rlpOutputBuffer = ( LPTSTR ) AllocBytes_WW( CRTTIME_NOW_OUTPUT_BUFSIZE );

	if ( rlpOutputBuffer )
	{
		lpszFormatString = FormatNowGetString( pFormat ,
			                                   phDllhModule );

		if ( lpszFormatString )
		{
			if ( time ( ( time_t * ) &crt_time_t_struct ) > CRT_TIME_ERROR )
			{
				if ( ( errno = _localtime64_s ( &crt_tm_struct , &crt_time_t_struct ) ) == CRT_TIME_CONVERSION_ERROR )
				{	// Success. Call strftime.
					if ( uintResult = strftime2 ( rlpOutputBuffer ,
						                          CRTTIME_NOW_OUTPUT_BUFCAP ,
						                          lpszFormatString ,
						                          &crt_tm_struct ) )
					{
						return rlpOutputBuffer;
					}	// TRUE (anticipated outcome) block, if ( uintResult = strftime2 ( rlpOutputBuffer , CRTTIME_NOW_OUTPUT_BUFCAP , lpszFormatString , &crt_tm_struct ) )
					else
					{
						return NULL;
					}	// FALSE (unanticipated outcome) block, if ( uintResult = strftime2 ( rlpOutputBuffer , CRTTIME_NOW_OUTPUT_BUFCAP , lpszFormatString , &crt_tm_struct ) )
				}	// TRUE (anticipated outcome) block, if ( ( errno = _localtime64_s ( &crt_tm_struct , &crt_time_t_struct ) ) == CRT_TIME_CONVERSION_ERROR )
				else
				{
					return NULL;
				}	// FALSE (unanticipated outcome) block, if ( ( errno = _localtime64_s ( &crt_tm_struct , &crt_time_t_struct ) ) == CRT_TIME_CONVERSION_ERROR )
			}	// TRUE (anticipated outcome) block, if ( time ( ( time_t * ) &crt_time_t_struct ) > CRT_TIME_ERROR )
			else
			{
				return NULL;
			}	// FALSE (unanticipated outcome) block, if ( time ( ( time_t * ) &crt_time_t_struct ) > CRT_TIME_ERROR )
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