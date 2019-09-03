//	File Name:			FormatTimeBoth.INL
//
//	File Abstract:		This C source file defines both ANSI and Unicode 
//						implementations of FormatTimeBoth, and is included by
//						both FormatTimeBothA.C and FormatTimeBothW.C, which set
//						the character encoding before this file is included.
//
//	File Remarks:		Other than the character encoding, both routines are
//						identical.

// BOOL LIBSPEC_CRTTIME2_API FormatTimeBoth (
//	const void *    pFormatLocal ,
//  const void *    pFormatUtc ,
//  const HMODULE   phDllhModule ,
//  LPCRT_TIME_BOTH plpTimeInfo )

	if ( plpTimeInfo )
	{
		//	--------------------------------------------------------------------
		//	Unless the caller gave us a UTC time, read the current time from the
		//	system clock. The CRT time function, which is presumed to be the
		//	data source, returns UTC time, since that is the definition of Time
		//	Since the Epoch (Unix Time).
		//	--------------------------------------------------------------------

		Unless ( plpTimeInfo->UniverslSystemTime )
		{	// Unless the caller already did so, Initialize the time_t structure (an integer of some size, either 32 or 64 bits).
			Unless ( time ( ( time_t* ) &plpTimeInfo->UniverslSystemTime ) > CRT_TIME_ERROR )
			{	// If time ( ) returns zero, your program is in very serious trouble, as probably is your Windows installation.
				SetLastError ( CRTTIME_ERR_TIME_FAILURE );
				return FALSE;
			}	// Unless ( time ( ( time_t* ) &plpTimeInfo->UniverslSystemTime ) > CRT_TIME_ERROR )
		}	// Unless ( plpTimeInfo->UniverslSystemTime )

		if ( ( errno = _localtime64_s ( &plpTimeInfo->TimeLocal , &plpTimeInfo->UniverslSystemTime ) ) == CRT_TIME_CONVERSION_SUCCESS )
		{
			if ( ( errno = _gmtime64_s ( &plpTimeInfo->TimeUtc , &plpTimeInfo->UniverslSystemTime ) ) == CRT_TIME_CONVERSION_SUCCESS )
			{
				if ( plpTimeInfo->TimeStringLocal = FormatTimeLocal ( pFormatLocal , phDllhModule , ( time_t * ) &plpTimeInfo->UniverslSystemTime ) )
				{ 
					if ( plpTimeInfo->TimeStringUtc = FormatTimeUTC ( pFormatUtc   , phDllhModule , ( time_t * ) &plpTimeInfo->UniverslSystemTime ) )
					{
						#if defined ( UNICODE )
						plpTimeInfo->StringsAreUnicode = TRUE;
						#endif	/* #if defined ( UNICODE ) */
						return TRUE;				// Everything succeeded.
					}	// TRUE (anticipated outcome) block, if ( plpTimeInfo->TimeStringUtc = FormatTimeUTC ( pFormatUtc ,   phDllhModule , ( time_t * ) &plpTimeInfo->UniverslSystemTime ) )
					else
					{	// Clean up so that we don't leak memory if the caller continues.
						plpTimeInfo->TimeStringLocal = ( LPTSTR ) FreeBuffer_WW ( plpTimeInfo->TimeStringLocal );
						return FALSE;				// FormatTimeUTC calls SetLastError on its way out.
					}	// FALSE (unanticipated outcome) block, if ( plpTimeInfo->TimeStringUtc = FormatTimeUTC ( pFormatUtc ,   phDllhModule , ( time_t * ) &plpTimeInfo->UniverslSystemTime ) )
				}	// TRUE (anticipated outcome) block, if ( plpTimeInfo->TimeStringLocal = FormatTimeLocal ( pFormatLocal , phDllhModule , ( time_t * ) &plpTimeInfo->UniverslSystemTime ) )
				else
				{
					return FALSE;					// FormatTimeLocal calls SetLastError on its way out.
				}	// FALSE (unanticipated outcome) block, if ( plpTimeInfo->TimeStringLocal = FormatTimeLocal ( pFormat, phDllhModule, ( time_t * ) &plpTimeInfo->UniverslSystemTime ) ) 
			}	// TRUE (anticipated outcome) block, if ( plpTimeInfo->TimeStringLocal = FormatTimeLocal ( pFormatLocal , phDllhModule , ( time_t * ) &plpTimeInfo->UniverslSystemTime ) )
			else
			{
				SetLastError ( CRTTIME_ERR_UTCTIME_FAILURE );
				return FALSE;
			}	// FALSE (unanticipated outcome) block, if ( plpTimeInfo->TimeStringLocal = FormatTimeLocal ( pFormatLocal , phDllhModule , ( time_t * ) &plpTimeInfo->UniverslSystemTime ) )
		}	// TRUE (anticipated outcome) block, if ( ( errno = _localtime64_s ( &plpTimeInfo->TimeLocal , &plpTimeInfo->UniverslSystemTime ) ) == CRT_TIME_CONVERSION_SUCCESS )
		else
		{
			SetLastError ( CRTTIME_ERR_LOCALTIME_FAILURE );
			return FALSE;
		}	// FALSE (unanticipated outcome) block, if ( ( errno = _localtime64_s ( &plpTimeInfo->TimeLocal , &plpTimeInfo->UniverslSystemTime ) ) == CRT_TIME_CONVERSION_SUCCESS )
	}	// TRUE (anticipated outcome) block, if ( plpTimeInfo )
	else
	{	// Report the null reference exception.
		SetLastError ( CRTTIME_ERR_TIMEINFO_IS_NULL );
		return FALSE;
	}	// FALSE (unanticipated outcome) block, if ( plpTimeInfo )