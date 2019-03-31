// FormatNowGetString.INL : Define both implementations of the current time
//                          format string loader.
//
//                          Both FormatNowGetStringA.C and FormatNowGetStringW.C
//                          include this file as their body.

// LPTSTR    __stdcall FormatNowGetString ( const void *    pFormat , const HMODULE phDllhModule )

	if ( pFormat != CRTTIME_INVALID_FORMAT )
	{
		UINT uintResourceID = ( UINT ) pFormat;

		if ( uintResourceID > CRTTIME_FORMAT_STRING_ID_LIMIT )
		{
			return ( LPTSTR ) pFormat;
		}	// TRUE (Argument pFormat points to a string.)
		else
		{
			LPTSTR rlpFormatString = NULL;

			#if defined ( UNICODE )
				if ( LoadString ( phDllhModule
										? phDllhModule
										: m_lpDllhModule ,
					              uintResourceID ,
					              rlpFormatString ,
					              RCDATA_INPLACE_POINTER ) )
				{
					return rlpFormatString;
				}	// TRUE (anticipated outcome) block, if ( LoadString ( phDllhModule ? phDllhModule : m_lpDllhModule , uintResourceID , rlpFormatString ,RCDATA_INPLACE_POINTER ) )
				else
				{
					return NULL;
				}	// FALSE (unanticipated outcome) block, if ( LoadString ( phDllhModule ? phDllhModule : m_lpDllhModule , uintResourceID , rlpFormatString ,RCDATA_INPLACE_POINTER ) )
			#else
				rlpFormatString = ( LPTSTR )  HeapAlloc ( m_hProcHeap , 
					                                      HEAP_ZERO_MEMORY ,
					                                      RCDATA_MAX_BUFFER_BYTES_P6C );

				if ( rlpFormatString )
				{
					if ( LoadString( phDllhModule
										? phDllhModule
										: m_lpDllhModule ,
									 uintResourceID ,
									 rlpFormatString ,
									 RCDATA_MAX_LENGTH_P6C ) )
					{
						return rlpFormatString;
					}	// TRUE (anticipated outcome) block, if ( LoadString ( phDllhModule ? phDllhModule : m_lpDllhModule , uintResourceID , rlpFormatString ,RCDATA_INPLACE_POINTER ) )
					else
					{
						return NULL;
					}	// FALSE (unanticipated outcome) block, if ( LoadString ( phDllhModule ? phDllhModule : m_lpDllhModule , uintResourceID , rlpFormatString ,RCDATA_INPLACE_POINTER ) )
				}	// TRUE (anticipated outcome) block, if ( rlpFormatString )
				else
				{
					SetLastError ( CRTTIME_ERR_OUT_OF_MEMORY );
					return NULL;
				}	// FALSE (unanticipated outcome) block, if ( rlpFormatString )
			#endif /* #if defined ( UNICODE ) */
		}
	}	// TRUE (anticpated outcome) block, if ( pFormat != CRTTIME_INVALID_FORMAT )
	else
	{
		SetLastError ( CRTTIME_ERR_NULL_FORMAT_STRING );
		return CRTTIME_INVALID_FORMAT;
	}	// FALSE (unanticpated outcome) block, if ( pFormat != CRTTIME_INVALID_FORMAT )
// Both FormatNowGetStringA and FormatNowGetStringW end here.