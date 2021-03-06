// CRTTime2_Unit_Tests.C : Defines the entry point for the console application.
//

#undef UNICODE
#undef _UNICODE
#define _MBCS

#define CRTTIME_UNIT_TESTS_MAIN

#include ".\CRTTime_Unit_Tests.H"


int main ( int argc , char* argv [ ] )
{
	//	----------------------------------------------------------------------------
	//	Bake these into the code, so that they get initialized.
	//	----------------------------------------------------------------------------

	static time_t		m_crt_time_t_struct;
	static int			m_intNChars;
	static struct tm	m_crt_tm_struct;								// The structure keyword is required because I'm compiling as straight C.

	       TCHAR *		lpszProgramName = ShowProgramInfo ( TRUE );

		   LPTSTR       lpFormattedStartTimeLocal	= FormatNowLocal ( STRFTIME_DEFAULT_LOCAL_FORMAT ,
				                                                       NULL );

			if ( lpFormattedStartTimeLocal == NULL )
				return GetLastError ( );

		   LPTSTR       lpFormattedStartTimeUTC		= FormatNowUTC   ( STRFTIME_DEFAULT_UTC_FORMAT ,
				                                                       NULL );

		   if ( lpFormattedStartTimeUTC == NULL )
			   return GetLastError ( );

		   _tprintf ( "\nExecution start time = %s (%s)\n\n" ,
			          lpFormattedStartTimeLocal ,
			          lpFormattedStartTimeUTC );

			m_hProcHeap = GetProcessHeap ( );

			Unless ( HeapFree ( m_hProcHeap , 
					            HEAP_ALL_FLAGS_OFF ,
							    lpFormattedStartTimeLocal ) )
				return GetLastError ( );

			Unless ( HeapFree ( m_hProcHeap , 
					            HEAP_ALL_FLAGS_OFF ,
						   	    lpFormattedStartTimeUTC ) )
				return GetLastError ( );
	
			Unless ( m_utpWaitForCarbonUnit = ( LPCRTWaitForCarbonUnit )  AllocBytes_WW ( sizeof ( CRTWaitForCarbonUnit ) ) )
				return CRTTIME_ERR_OUT_OF_MEMORY;

			if ( time ( ( time_t * ) &m_crt_time_t_struct ) > CRT_TIME_ERROR )
			{
				if ( ( errno = _localtime64_s ( &m_crt_tm_struct , &m_crt_time_t_struct ) ) == CRT_TIME_CONVERSION_ERROR )
				{	// A buffer of wchar_t is safe to cast to the shorter char type.
					if ( m_intNChars = _tcsftime ( ( char * ) &m_achrOutputBuffer_1 ,
												   STRFTIME_OUTBUF_SIZE ,
												   STRFTIME_DEFAULT_LOCAL_FORMAT ,
												   &m_crt_tm_struct ) )
					{
						printf ( "%s begin at %s\n\n" ,
								 lpszProgramName ,
								 ( char * ) m_achrOutputBuffer_1 );

						m_crt_tm_struct.tm_hour		= 2;
						m_crt_tm_struct.tm_isdst	= 1;
						m_crt_tm_struct.tm_mday		= 4;
						m_crt_tm_struct.tm_min		= 7;
						m_crt_tm_struct.tm_mon		= 5;
						m_crt_tm_struct.tm_sec		= 9;
						m_crt_tm_struct.tm_wday		= 1;
						m_crt_tm_struct.tm_yday		= 154;

						m_utpWaitForCarbonUnit->intReturnCode = CRTTime2_ANSI_Unit_Tests ( &m_crt_tm_struct );

						if ( !m_utpWaitForCarbonUnit->intReturnCode )
						{
							m_utpWaitForCarbonUnit->intReturnCode = CRTTime2_Unicode_Unit_Tests ( &m_crt_tm_struct );
						}	// if ( !m_utpWaitForCarbonUnit->intReturnCode )
					}	// TRUE (anticipated outcome) block, if ( m_intNChars = _tcsftime ( ( wchar_t * ) &m_achrOutputBuffer_1 , STRFTIME_OUTBUF_SIZE , STRFTIME_DEFAULT_LOCAL_FORMAT , &m_crt_tm_struct ) )
					else
					{
						printf ( "ERROR: CRT _tcsftime Function Error" );
						m_utpWaitForCarbonUnit->intReturnCode = RETCODE_STRFTIME_ERROR;
					}	// FALSE (unanticipated outcome) block, if ( m_intNChars = _tcsftime ( ( wchar_t * ) &m_achrOutputBuffer_1 , STRFTIME_OUTBUF_SIZE , STRFTIME_DEFAULT_LOCAL_FORMAT , &m_crt_tm_struct ) )
				}	// TRUE (anticipated outcome) block, if ( ( errno = _localtime64_s ( &m_crt_tm_struct , &m_crt_time_t_struct ) ) == CRT_TIME_CONVERSION_ERROR )
				else
				{
					printf ( "ERROR: CRT _localtime64_s Function Error, status code = 0x%04X (%i decimal)" ,
							 errno ,
							 errno );
					m_utpWaitForCarbonUnit->intReturnCode = errno;
				}	// FALSE (unanticipated outcome) block, if ( ( errno = _localtime64_s ( &m_crt_tm_struct , &m_crt_time_t_struct ) ) == CRT_TIME_CONVERSION_ERROR )
			}	// TRUE (anticipated outcome) block, if ( time ( ( time_t * ) &m_crt_time_t_struct ) > CRT_TIME_ERROR )
			else
			{
				printf ( "ERROR: CRT Time Function Error" );
				m_utpWaitForCarbonUnit->intReturnCode = CRT_TIME_ERROR;
			}	// FALSE (unanticipated outcome) block, if ( time ( ( time_t * ) &m_crt_time_t_struct ) > CRT_TIME_ERROR )

			return WaitForCarbonUnit ( m_utpWaitForCarbonUnit );
}   // int main ( int argc , char* argv [ ] )