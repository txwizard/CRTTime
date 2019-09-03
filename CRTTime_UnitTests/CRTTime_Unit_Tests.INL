//	CRTTime2_Unit_Tests.INL : Define the implementation of the CRTTime2 unit tests for all character encodings.

int					intNChars;
int		            intCaseIndex;

LPCRT_TIME_BOTH		lpTimeInfo = AllocBytes_WW ( sizeof ( CRT_TIME_BOTH ) );

Unless ( lpTimeInfo )
{
    SetLastError ( CRTTIME_ERR_OUT_OF_MEMORY );
    return CRTTIME_ERR_OUT_OF_MEMORY;
}	// Unless ( lpTimeInfo )

if ( intNChars = _tcsftime ( ( TCHAR * ) &m_achrOutputBuffer_1 ,
                             STRFTIME_OUTBUF_SIZE ,
                             STRFTIME_DEFAULT_LOCAL_FORMAT ,
                             plpcrt_tm_struct ) )
{
    _tprintf ( TEXT ( "Test Time = %s\n\n" ) ,
               ( TCHAR * ) m_achrOutputBuffer_1 );

    LPTSTR lpFormatString = GetStringPointer ( RCDATA_LOOK_IN_STARTUP_PE_FILE,
                                               IDS_TEST_CASE_REPORT ,
                                               RCDATA_HIDE_LENGTH );

    Unless ( lpFormatString )
    {
        m_utpWaitForCarbonUnit->intReturnCode = GetLastError ( );
        _tprintf ( FB_FormatMessage2A ( IDS_ERRHINT_STR_TCR ,
                                        m_utpWaitForCarbonUnit->intReturnCode ,
                                        FB_SCF2_HEXADECIMAL ) );
        return m_utpWaitForCarbonUnit->intReturnCode;
    }	// Unless ( lpFormatString )

    for ( intCaseIndex = ARRAY_FIRST_ELEMENT_SUBSCR;
          intCaseIndex < sizeof ( m_alpszTokenInfo ) / ( sizeof ( TCHAR * ) * TOKEN_PROPERTY_COUNT );	// This resolves to a compile-time constant.
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
                _tprintf ( lpFormatString ,																// Format Control String
                           intCaseIndex + ARRAY_ORDINAL_FROM_SUBSCR ,									// Format Item 1: Case %2i
                           ( TCHAR * ) m_alpszTokenInfo [ intCaseIndex ] [ POS_TOKEN_INTERPRETATION ] ,	// Format Item 2: : %s:
                           ( TCHAR * ) m_alpszTokenInfo [ intCaseIndex ] [ POS_RAW_TOKEN ] ,			// Format Item 3: - Raw Token %s
                           ( TCHAR * ) m_achrOutputBuffer_1 ,											// Format Item 4: = %s - Modified
                           ( TCHAR * ) m_alpszTokenInfo [ intCaseIndex ] [ POS_MODIFIED_TOKEN ] ,		// Format Item 5: Modified Token %s
                           ( TCHAR * ) m_achrOutputBuffer_2 );											// Format Item 6: = %s\n
            }	// TRUE (anticipated outcome) block, if ( intNChars = _tcsftime ( ( TCHAR * ) &m_achrOutputBuffer_2 , STRFTIME_OUTBUF_SIZE , m_alpszTokenInfo [ intCaseIndex ] [ POS_MODIFIED_TOKEN ] , plpcrt_tm_struct ) )
            else
            {
                return CleanupAndReportOutcome  ( TEXT ( "ERROR: CRT _tcsftime Function Error") ,
                                                  &lpFormatString ,
                                                  RETCODE_STRFTIME_ERROR );
            }	// FALSE (unanticipated outcome) block, if ( intNChars = _tcsftime ( ( TCHAR * ) &m_achrOutputBuffer_2 , STRFTIME_OUTBUF_SIZE , m_alpszTokenInfo [ intCaseIndex ] [ POS_MODIFIED_TOKEN ] , plpcrt_tm_struct ) )
        }	// TRUE (anticipated outcome) block, if ( intNChars = _tcsftime ( ( TCHAR * ) &m_achrOutputBuffer_1 , STRFTIME_OUTBUF_SIZE , m_alpszTokenInfo [ intCaseIndex] [ POS_RAW_TOKEN ] , plpcrt_tm_struct ) )
        else
        {
            return CleanupAndReportOutcome ( TEXT ( "ERROR: CRT _tcsftime Function Error "),
                                             &lpFormatString,
                                             RETCODE_STRFTIME_ERROR );
        }	// FALSE (unanticipated outcome) block, if ( intNChars = _tcsftime ( ( TCHAR * ) &m_achrOutputBuffer_1 , STRFTIME_OUTBUF_SIZE , m_alpszTokenInfo [ intCaseIndex] [ POS_RAW_TOKEN ] , plpcrt_tm_struct ) )
    }	// for ( intCaseIndex = ARRAY_FIRST_ELEMENT_SUBSCR; intCaseIndex < sizeof ( m_alpszTokenInfo ) / sizeof ( TCHAR * ); intCaseIndex++ )

    #if !defined ( UNICODE )
    lpFormatString = ( LPTSTR ) FreeBuffer_WW ( lpFormatString );
    #endif	/* #if !defined ( UNICODE ) */

    if ( FormatTimeBoth ( STRFTIME_DEFAULT_LOCAL_FORMAT ,
                          STRFTIME_DEFAULT_UTC_FORMAT ,
                          RCDATA_LOOK_IN_STARTUP_PE_FILE ,
                          lpTimeInfo ) )
    {
        lpFormatString = GetStringPointer ( RCDATA_LOOK_IN_STARTUP_PE_FILE ,
                                            IDS_TIME_PER_FORMATTIMEBOTH ,
                                            RCDATA_HIDE_LENGTH );
        _tprintf ( lpFormatString ,
                   lpTimeInfo->TimeStringLocal ,
                   lpTimeInfo->TimeStringUtc );
    }	// TRUE (anticipated outcome) block, if ( FormatTimeBoth ( STRFTIME_DEFAULT_LOCAL_FORMAT , STRFTIME_DEFAULT_UTC_FORMAT , RCDATA_LOOK_IN_STARTUP_PE_FILE , lpTimeInfo ) )
    else
    {
        m_utpWaitForCarbonUnit->intReturnCode = GetLastError ( );
        lpFormatString = GetStringPointer ( RCDATA_LOOK_IN_STARTUP_PE_FILE ,
                                            IDS_ERRMSG_TIME_BOTH_ERROR ,
                                            RCDATA_HIDE_LENGTH );
        _tprintf ( lpFormatString ,
                   m_utpWaitForCarbonUnit->intReturnCode ,
                   m_utpWaitForCarbonUnit->intReturnCode );
    }	// FALSE (unanticipated outcome) block, if ( FormatTimeBoth ( STRFTIME_DEFAULT_LOCAL_FORMAT , STRFTIME_DEFAULT_UTC_FORMAT , RCDATA_LOOK_IN_STARTUP_PE_FILE , lpTimeInfo ) )

    #if !defined ( UNICODE )
    if ( lpTimeInfo->TimeStringLocal )
    {
        FreeBuffer_WW ( lpTimeInfo->TimeStringLocal );
        lpTimeInfo->TimeStringLocal = NULL;
    }	// if ( lpTimeInfo->TimeStringLocal )

    if ( lpTimeInfo->TimeStringUtc )
    {
        FreeBuffer_WW ( lpTimeInfo->TimeStringUtc );
        lpTimeInfo->TimeStringUtc = NULL;
    }	// if ( lpTimeInfo->TimeStringLocal )

    lpFormatString = ( LPTSTR ) FreeBuffer_WW ( lpFormatString );
    #endif	/*#if !defined ( UNICODE ) */

    lpFormatString = GetStringPointer ( RCDATA_LOOK_IN_STARTUP_PE_FILE ,
                                        IDS_TEST_SET_SUCCEEDED ,
                                        RCDATA_HIDE_LENGTH );

    #if defined ( UNICODE )
    return m_utpWaitForCarbonUnit->intReturnCode;
    #else 
    return CleanupAndReportOutcome ( lpFormatString ,													// The message is in the string.
                                     &lpFormatString ,													// Pass a pointer to the string pointer separately, so that it can be reset.
                                     m_utpWaitForCarbonUnit->intReturnCode );							// Pass the status code to return to the main routine.
    #endif	/* #if defined ( UNICODE ) */
}	// TRUE (anticipated outcome) block, if ( intNChars = _tcsftime ( ( wchar_t * ) &m_achrOutputBuffer_1 , STRFTIME_OUTBUF_SIZE , STRFTIME_DEFAULT_LOCAL_FORMAT , &m_crt_tm_struct ) )
else
{
    _tprintf ( TEXT ( "ERROR: CRT _tcsftime Function Error" ) );
    return RETCODE_STRFTIME_ERROR;
}	// FALSE (unanticipated outcome) block, if ( intNChars = _tcsftime ( ( wchar_t * ) &m_achrOutputBuffer_1 , STRFTIME_OUTBUF_SIZE , STRFTIME_DEFAULT_LOCAL_FORMAT , &m_crt_tm_struct ) )