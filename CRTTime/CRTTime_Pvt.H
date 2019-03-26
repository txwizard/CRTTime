/*
    ============================================================================

    File Name:          CRTTime_Pvt.H

    Library:            CRTTime2.dll

    Link Library:       CRTTime2.lib

    Synopsis:           Define common private data structures.

    Remarks:            These structures are defined in dllmain.C, and all other
                        routines use one of the two lists.

    Author:             David A. Gray, MBA

    License:            Copyright (C) 2018, David A. Gray. All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    *   Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

    *   Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    *   Neither the name of Simple Soft Services, Inc. nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version Author Synopsis
    ---------- ------- ------ --------------------------------------------------
	2018/06/26 1.0.0.1 DAG    Initial release
	2019/03/25 1.0.0.2 DAG    Implement wrappers that return formatted local and
	                          UTC current time strings via strftime.
	============================================================================
*/

#if !defined ( CRTTime_Pvt_DEFINED )
#define        CRTTime_Pvt_DEFINED

#include ".\targetver.h"
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include ".\CRTTime.H"

#if !defined ( TRAILING_NULL_ALLOWANCE_P6C )
	#undef	TRAILING_NULL_ALLOWANCE_P6C
	#define TRAILING_NULL_ALLOWANCE_P6C	1
#endif	/* #if defined ( TRAILING_NULL_ALLOWANCE_P6C ) */

#if !defined ( __cplusplus )
    #if !defined ( bool )
        typedef int                     bool ;
    #endif  /* #if !defined ( bool ) */

    #if !defined ( BOOK )
        typedef int                     BOOL ;
    #endif  /* #if !defined ( BOOK ) */

    #if !defined ( true )
        #define true                    1
    #endif  /* #if !defined ( true ) */

    #if !defined ( TRUE )
        #define TRUE                    1
    #endif  /* #if !defined ( TRUE ) */

    #if !defined ( false )
        #define false                   0
    #endif  /*  #if !defined ( false ) */

    #if !defined ( FALSE )
        #define FALSE                   0
    #endif  /*  #if !defined ( FALSE ) */
#endif  /* #if !defined ( __cplusplus ) */

//  ----------------------------------------------------------------------------
//  The following block might be overkill, but it makes the values explicit for
//  both 32 and 64 bit configurations.
//  ----------------------------------------------------------------------------

#if defined ( _WIN64 )
    #define ARRAY_FIRST_ELEMENT         0x0000000000000000
    #define ARRAY_INVALID_SUBSCRIPT     -1
    #define ARRAY_NEXT_SUBSCRIPT        0x0000000000000001

	#define CRTTIME_NOW_OUTPUT_BUFCAP	0xff
	#define CRTTIME_NOW_OUTPUT_BUFSIZE	( CRTTIME_NOW_OUTPUT_BUFCAP + TRAILING_NULL_ALLOWANCE_P6C )
	#define CRT_TIME_ERROR              -1
    #define CRT_TIME_CONVERSION_ERROR   0x000000000000000L
    #define CRTTIME_TZ_ABBR_ALLOWANCE   0x0000000000000003  // Allow for two new characters (marker tokens) and a terminal NULL character.

    #define EMPTY_STRING_LENGTH         0x0000000000000000
    #define UNKNOWN_STRING_LENGTH       -1
#else
    #define ARRAY_FIRST_ELEMENT         0x00000000L
    #define ARRAY_INVALID_SUBSCRIPT     -1L
    #define ARRAY_NEXT_SUBSCRIPT        0x00000001L

    #define CRT_TIME_ERROR              -1
    #define CRT_TIME_CONVERSION_ERROR   0x00000000L
	#define CRTTIME_NOW_OUTPUT_BUFCAP	0xff
	#define CRTTIME_NOW_OUTPUT_BUFSIZE	( CRTTIME_NOW_OUTPUT_BUFCAP + TRAILING_NULL_ALLOWANCE_P6C )
    #define CRTTIME_TZ_ABBR_ALLOWANCE   0x00000003L         // Allow for two new characters (marker tokens) and a terminal NULL character.

    #define EMPTY_STRING_LENGTH         0x00000000L
    #define UNKNOWN_STRING_LENGTH       -1L
#endif  /* #if defined ( _WIN64 ) */

#define CRTTIME_ERR_NONE                0x00000000L
#define CRTTIME_ERR_FORMAT_STR_NULL     -1L
#define CRTTIME_ERR_FORMAT_STR_EMPTY    -2L

#define CRTTIME_ERRMSG_NONE             TEXT ( "The function succeeded." )
#define CRTTIME_ERRMSG_FORMAT_STR_NULL  TEXT ( "The time format string pointer is NULL." )
#define CRTTIME_ERRMSG_FORMAT_STR_EMPTY TEXT ( "The format string is empty.")


//  ----------------------------------------------------------------------------
//  The following message string is returned directly to report an out-of-bounds
//  status code.
//  ----------------------------------------------------------------------------

#define CRTTIME_ERRMSG_UNKNOWN_ERROR    TEXT ( "The specified status code is undefined." )
#define CRTTIME_TZ_ABBREVIATION_TOKEN   TEXT ( "^Z^" )

#if defined ( UNICODE )
	#define RCDATA_INPLACE_POINTER		0
#else
	#define RCDATA_BUFFER_CAPACITY		255
	#define RCDATA_BUFFER_SIZE			( RCDATA_BUFFER_CAPACITY + TRAILING_NULL_ALLOWANCE_P6C )
#endif	/* #if defined ( UNICODE ) */

#if defined ( __cplusplus )
extern "C" {
#endif /* #if defined ( __cplusplus ) */
    #if defined ( CRTTIME_DLLMAIN )
               const char    * m_lpTZAbbrevTokensA [ ] = {
                               TZ_TOKEN_ABBREV_MODIFIER_N_1 ,
                               TZ_TOKEN_ABBREV_MODIFIER_N_2 ,
                               TZ_TOKEN_ABBREV_MODIFIER_N_3 ,
                               TZ_TOKEN_ABBREV_MODIFIER_N_4 ,

                               TZ_ABBREV_TOKEN_N_1 ,
                               TZ_ABBREV_TOKEN_N_2 ,
                               TZ_ABBREV_TOKEN_N_3 ,
                               TZ_ABBREV_TOKEN_N_4 };

               const wchar_t * m_lpTZAbbrevTokensW [ ] = {
                               TZ_TOKEN_ABBREV_MODIFIER_W_1 ,
                               TZ_TOKEN_ABBREV_MODIFIER_W_2 ,
                               TZ_TOKEN_ABBREV_MODIFIER_W_3 ,
                               TZ_TOKEN_ABBREV_MODIFIER_W_4 ,

                               TZ_ABBREV_TOKEN_W_1 ,
                               TZ_ABBREV_TOKEN_W_2 ,
                               TZ_ABBREV_TOKEN_W_3 ,
                               TZ_ABBREV_TOKEN_W_4 };

               const size_t    m_intTokenTableASize = sizeof ( m_lpTZAbbrevTokensA ) / sizeof ( char    * );
               const size_t    m_intTokenTableWSize = sizeof ( m_lpTZAbbrevTokensW ) / sizeof ( wchar_t * );

			         HMODULE   m_lpDllhModule		= NULL;
			         HANDLE	   m_hProcHeap			= NULL;
    #else
	    extern       size_t    m_intTokenTableASize;
        extern       size_t    m_intTokenTableWSize;

        extern       char    * m_lpTZAbbrevTokensA [ ];
        extern       wchar_t * m_lpTZAbbrevTokensW [ ];
		
		extern       HMODULE   m_lpDllhModule;
		extern       HANDLE	   m_hProcHeap;
    #endif  // #if defined ( CRTTIME2_DLLMAIN )

    #if defined ( CRTTIME_DLLERRMAP_ANSI )
        static const char    * m_lpDLLErrMsgs [ ] = {
            CRTTIME_ERRMSG_NONE ,
            CRTTIME_ERRMSG_FORMAT_STR_NULL ,
            CRTTIME_ERRMSG_FORMAT_STR_EMPTY };
    #endif  /* #if defined ( CRTTIME_DLLERRMAP_ANSI ) */

    #if defined ( CRTTIME_DLLERRMAP_WIDE )
        static const wchar_t * m_lpDLLErrMsgs [ ] = {
            CRTTIME_ERRMSG_NONE ,
            CRTTIME_ERRMSG_FORMAT_STR_NULL ,
            CRTTIME_ERRMSG_FORMAT_STR_EMPTY };
    #endif  /* #if defined ( CRTTIME_DLLERRMAP_WIDE ) */

    size_t    __stdcall AbbreviateTZNameA   ( char    *       plpszDest );
    size_t    __stdcall AbbreviateTZNameW   ( wchar_t *       plpszDest );

	LPTSTR    __stdcall FormatNowGetStringA ( const void *    pFormat , const HMODULE phDllhModule );
	LPTSTR    __stdcall FormatNowGetStringW ( const void *    pFormat , const HMODULE phDllhModule );

    char    * __stdcall PrepareForCRTA      ( const char    * plpszFormat );
    wchar_t * __stdcall PrepareForCRTW      ( const wchar_t * plpszFormat );
#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */

#if defined ( _UNICODE )
    #define AbbreviateTZName            AbbreviateTZNameW
	#define FormatNowGetString			FormatNowGetStringW
    #define PrepareForCRT               PrepareForCRTW
    #define m_lpTZAbbrevTokens          m_lpTZAbbrevTokensW
    #define m_intTokenTableSize         m_intTokenTableWSize
#else
    #define AbbreviateTZName            AbbreviateTZNameA
	#define FormatNowGetString			FormatNowGetStringA
    #define PrepareForCRT               PrepareForCRTA
    #define m_lpTZAbbrevTokens          m_lpTZAbbrevTokensA
    #define m_intTokenTableSize         m_intTokenTableASize
#endif  /* #if defined ( _UNICODE ) */
#endif  /* CRTTime_Pvt_DEFINED */