//	CRTTimeErrMsg.INL : Define the ANSI and wide character implementations of CRTTimeErrMsg.

if ( pintErrorCode > ARRAY_FIRST_ELEMENT )
{
	return CRTTIME_ERRMSG_NONE;
}
else if ( pintErrorCode == ARRAY_FIRST_ELEMENT )
{
	return ( PTCHAR ) CRTTIME_ERRMSG_FORMAT_STR_EMPTY;
}
else if ( abs ( pintErrorCode ) < sizeof ( m_lpDLLErrMsgs ) / sizeof ( TCHAR * ) )
{
	return ( PTCHAR ) m_lpDLLErrMsgs [ abs ( pintErrorCode ) ];
}	// TRUE (anticipated outcome) block, if ( pintErrorCode > ARRAY_FIRST_ELEMENT && pintErrorCode < sizeof ( m_lpDLLErrMsgs ) / sizeof ( TCHAR * ) )
else
{
	return ( PTCHAR ) CRTTIME_ERRMSG_UNKNOWN_ERROR;
}	// FALSE (unanticipated outcome) block, if ( pintErrorCode > ARRAY_FIRST_ELEMENT && pintErrorCode < sizeof ( m_lpDLLErrMsgs ) / sizeof ( TCHAR * ) )