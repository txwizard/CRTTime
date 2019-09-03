// FormatNowGetString.INL : Define both implementations of the current time
//                          format string loader.
//
//                          Both FormatNowGetStringA.C and FormatNowGetStringW.C
//                          include this file as their body.

// LPTSTR    __stdcall FormatNowGetString ( const void *    pFormat , const HMODULE phDllhModule )

	if ( pFormat != CRTTIME_INVALID_FORMAT )
	{
		//	--------------------------------------------------------------------
		//	The following block is the most efficient way to compensate for the
		//	different address lengths of 32-bit and 64-bit machine addresses. It
		//	uses preprocessor symbols defined by the Microsoft Visual C++
		//	compiler.
		//	--------------------------------------------------------------------

		#if ( defined ( _M_ARM ) || defined ( _M_IX86 ) )
		unsigned int uintResourceID = ( unsigned int ) pFormat;
		#elif ( defined ( _M_ARM64 ) || defined ( _M_X64 ) )
		unsigned __int64 uintResourceID = ( unsigned __int64 ) pFormat;
		#else	/* Neither #if ( defined ( _M_ARM ) || defined ( _M_IX86 ) ), nor #elif ( defined ( _M_ARM64 ) || defined ( _M_X64 ) ) is TRUE. */
		#error Platform cannot be determined because all of the following are UNdefined: _M_ARM, _M_IX86, _M_ARM64 _M_X64.
		#endif	/* #if ( defined ( _M_ARM ) || defined ( _M_IX86 ) ) AND #elif ( defined ( _M_ARM64 ) || defined ( _M_X64 ) ) */

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
					              ( unsigned int ) uintResourceID ,
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
									 ( unsigned int ) uintResourceID ,
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