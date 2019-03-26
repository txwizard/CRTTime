//	CRTTime2_Unit_Tests.INL : Define the implementation of the CRTTime2 unit tests for all character encodings.

size_t				intNChars;
size_t              intCaseIndex;

if ( intNChars = _tcsftime ( ( TCHAR * ) &m_achrOutputBuffer_1 ,
	                           STRFTIME_OUTBUF_SIZE ,
	                           STRFTIME_DEFAULT_FORMAT ,
	                           plpcrt_tm_struct ) )
{
	_tprintf ( TEXT ( "Test Time = %s\n\n" ) ,
		       ( TCHAR * ) m_achrOutputBuffer_1 );

	for ( intCaseIndex = ARRAY_FIRST_ELEMENT_SUBSCR;
		  intCaseIndex < sizeof ( m_alpszTokenInfo ) / ( sizeof ( TCHAR * ) * TOKEN_PROPERTY_COUNT );
		  intCaseIndex++ )
	{
		if ( intNChars = _tcsftime2 ( ( TCHAR * ) &m_achrOutputBuffer_1 ,
			                          STRFTIME_OUTBUF_SIZE ,
			                          ( TCHAR * ) m_alpszTokenInfo [ intCaseIndex ] [ POS_RAW_TOKEN ] ,
			                          plpcrt_tm_struct ) )
		{
			if ( intNChars = _tcsftime2 ( ( TCHAR * ) &m_achrOutputBuffer_2 ,
				                          STRFTIME_OUTBUF_SIZE ,
				                          ( TCHAR * ) m_alpszTokenInfo [ intCaseIndex ] [ POS_MODIFIED_TOKEN ] ,
				                          plpcrt_tm_struct ) )
			{
				_tprintf ( TEXT ( "Case %2d: %s:\n\n         Raw Token:      %s  = %s\n         Modified Token: %s = %s\n\n" ) ,		// Format Control String
					       intCaseIndex + ARRAY_ORDINAL_FROM_SUBSCR ,																	// Format Item 1 = Case %2i
					       ( TCHAR * ) m_alpszTokenInfo [ intCaseIndex ] [ POS_TOKEN_INTERPRETATION ] ,									// Format Item 2 = : %s:
					       ( TCHAR * ) m_alpszTokenInfo [ intCaseIndex ] [ POS_RAW_TOKEN ] ,											// Format Item 3 = - Raw Token %s
					       ( TCHAR * ) m_achrOutputBuffer_1 ,																			// Format Item 4 =  = %s - Modified
					       ( TCHAR * ) m_alpszTokenInfo [ intCaseIndex ] [ POS_MODIFIED_TOKEN ] ,										// Format Item 5 = Modified Token %s
					       ( TCHAR * ) m_achrOutputBuffer_2 );																			// Format Item 6 = = %s\n
			}	// TRUE (anticipated outcome) block, if ( intNChars = _tcsftime ( ( TCHAR * ) &m_achrOutputBuffer_2 , STRFTIME_OUTBUF_SIZE , m_alpszTokenInfo [ intCaseIndex ] [ POS_MODIFIED_TOKEN ] , plpcrt_tm_struct ) )
			else
			{
				_tprintf ( TEXT ( "ERROR: CRT _tcsftime Function Error" ) );
				return RETCODE_STRFTIME_ERROR;
			}	// FALSE (unanticipated outcome) block, if ( intNChars = _tcsftime ( ( TCHAR * ) &m_achrOutputBuffer_2 , STRFTIME_OUTBUF_SIZE , m_alpszTokenInfo [ intCaseIndex ] [ POS_MODIFIED_TOKEN ] , plpcrt_tm_struct ) )
		}	// TRUE (anticipated outcome) block, if ( intNChars = _tcsftime ( ( TCHAR * ) &m_achrOutputBuffer_1 , STRFTIME_OUTBUF_SIZE , m_alpszTokenInfo [ intCaseIndex] [ POS_RAW_TOKEN ] , plpcrt_tm_struct ) )
		else
		{
			_tprintf ( TEXT ( "ERROR: CRT _tcsftime Function Error" ) );
			return RETCODE_STRFTIME_ERROR;
		}	// FALSE (unanticipated outcome) block, if ( intNChars = _tcsftime ( ( TCHAR * ) &m_achrOutputBuffer_1 , STRFTIME_OUTBUF_SIZE , m_alpszTokenInfo [ intCaseIndex] [ POS_RAW_TOKEN ] , plpcrt_tm_struct ) )
	}	// for ( intCaseIndex = ARRAY_FIRST_ELEMENT_SUBSCR; intCaseIndex < sizeof ( m_alpszTokenInfo ) / sizeof ( TCHAR * ); intCaseIndex++ )

	return EXIT_SUCCESS;
}	// TRUE (anticipated outcome) block, if ( intNChars = _tcsftime ( ( wchar_t * ) &m_achrOutputBuffer_1 , STRFTIME_OUTBUF_SIZE , STRFTIME_DEFAULT_FORMAT , &m_crt_tm_struct ) )
else
{
	_tprintf ( TEXT ( "ERROR: CRT _tcsftime Function Error" ) );
	return RETCODE_STRFTIME_ERROR;
}	// FALSE (unanticipated outcome) block, if ( intNChars = _tcsftime ( ( wchar_t * ) &m_achrOutputBuffer_1 , STRFTIME_OUTBUF_SIZE , STRFTIME_DEFAULT_FORMAT , &m_crt_tm_struct ) )