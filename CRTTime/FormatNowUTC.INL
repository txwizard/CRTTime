// FormatNowUTC.INL : Define the ANSI (narrow character) AND Unicode (wide 
//                    character) current UTC time formatters.
//

//	LPTSTR LIBSPEC_CRTTIME2_API FormatNowUTC ( void * pFormat , const HMODULE phDllhModule )

	time_t		crt_time_t_struct;
	struct tm	crt_tm_struct;								// The struct keyword is required because I'm compiling as straight C.
	LPTSTR		lpszFormatString	= NULL;

	size_t		uintResult			= 0;

	LPTSTR		rlpOutputBuffer		= ( LPTSTR ) AllocCString_WW ( CRTTIME_NOW_OUTPUT_BUFCAP );

	if ( rlpOutputBuffer )
	{
		lpszFormatString = FormatNowGetString ( pFormat ,
			                                    phDllhModule );

		if ( lpszFormatString )
		{
			if ( time ( ( time_t * ) &crt_time_t_struct ) > CRT_TIME_ERROR )
			{
				if ( ( errno = _gmtime64_s ( &crt_tm_struct , &crt_time_t_struct ) ) == CRT_TIME_CONVERSION_SUCCESS )
				{	// Success. Call strftime.
					if ( uintResult = strftime2 ( rlpOutputBuffer ,
						                          CRTTIME_NOW_OUTPUT_BUFCAP ,
						                          lpszFormatString ,
						                          &crt_tm_struct ) )
					{
						#if defined ( UNICODE )
						return rlpOutputBuffer;
						#else
						return FormatTimeCleanup ( rlpOutputBuffer ,
							                       pFormat ,
							                       lpszFormatString ,
							                       FORMATTIMECLEANUP_SUCCESS );
						#endif	/* #if defined ( UNICODE ) */
					}	// TRUE (anticipated outcome) block, if ( uintResult = strftime2 ( rlpOutputBuffer , CRTTIME_NOW_OUTPUT_BUFCAP , lpszFormatString , &crt_tm_struct ) )
					else
					{
						#if defined ( UNICODE )
						return NULL;
						#else
						return FormatTimeCleanup ( rlpOutputBuffer ,
							                       pFormat ,
							                       lpszFormatString ,
							                       FORMATTIMECLEANUP_ERROR );
						#endif	/* #if defined ( UNICODE ) */
					}	// FALSE (unanticipated outcome) block, if ( uintResult = strftime2 ( rlpOutputBuffer , CRTTIME_NOW_OUTPUT_BUFCAP , lpszFormatString , &crt_tm_struct ) )
				}	// TRUE (anticipated outcome) block, if ( ( errno = _gmtime64_s ( &crt_tm_struct , &crt_time_t_struct ) ) == CRT_TIME_CONVERSION_SUCCESS )
				else
				{
					#if defined ( UNICODE )
					return NULL;
					#else
					return FormatTimeCleanup ( rlpOutputBuffer ,
						                       pFormat ,
						                       lpszFormatString ,
						                       FORMATTIMECLEANUP_ERROR );
					#endif	/* #if defined ( UNICODE ) */
				}	// FALSE (unanticipated outcome) block, if ( ( errno = _gmtime64_s ( &crt_tm_struct , &crt_time_t_struct ) ) == CRT_TIME_CONVERSION_SUCCESS )
			}	// TRUE (anticipated outcome) block, if ( time ( ( time_t * ) &crt_time_t_struct ) > CRT_TIME_ERROR )
			else
			{
				#if defined ( UNICODE )
				return NULL;
				#else
				return FormatTimeCleanup ( rlpOutputBuffer ,
					                       pFormat ,
					                       lpszFormatString ,
					                       FORMATTIMECLEANUP_ERROR );
				#endif	/* #if defined ( UNICODE ) */
			}	// FALSE (unanticipated outcome) block, if ( time ( ( time_t * ) &crt_time_t_struct ) > CRT_TIME_ERROR )
		}	// TRUE (anticipated outcome) block, if ( lpFormatString )
		else
		{
			#if defined ( UNICODE )
			return NULL;
			#else
			return FormatTimeCleanup ( rlpOutputBuffer ,
				                       pFormat ,
				                       lpszFormatString ,
				                       FORMATTIMECLEANUP_ERROR );
			#endif	/* #if defined ( UNICODE ) */
		}	// FALSE (unanticipated outcome) block, if ( lpFormatString )
	}	// TRUE (anticipated outcome) block, if ( rlpOutputBuffer )
	else
	{
		SetLastError ( CRTTIME_ERR_OUT_OF_MEMORY );
						
		#if defined ( UNICODE )
		return NULL;
		#else
		return FormatTimeCleanup ( rlpOutputBuffer ,
			                       pFormat ,
			                       lpszFormatString ,
			                       FORMATTIMECLEANUP_ERROR );
		#endif	/* #if defined ( UNICODE ) */
	}	// FALSE (unanticipated outcome) block, if ( rlpOutputBuffer )