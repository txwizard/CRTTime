//  ============================================================================
//  CRTTime2_Unit_Tests.H: Declare functions that implement the unit tests, and
//                         define arrays of string constants.
//
//  Strangely, this compiler treats -1 and 0xffffffff differetnly. Go figure.
//
//  ----------------------------------------------------------------------------
//  Revision History
//  ----------------------------------------------------------------------------
//
//  Date       Version By  Synopsis
//  ---------- ------- --- -----------------------------------------------------
//  2018/06/25 1.0.0.1 DAG This program was created and tested.
//
//  2019/03/22 1.0.0.1 DAG This program was re-created essentially from scratch,
//                         and its helper functions moved into a library.
//
//	2019/07/26 1.0.0.3 DAG Implement a separate default format string for UTC
//	                       time, STRFTIME_DEFAULT_UTC_FORMAT, rename the
//						   original STRFTIME_DEFAULT_LOCAL_FORMAT, and move both
//						   into this library header, where they belong, and fix
//                         the misnamed function WaitForCarbonUnit, which was
//                         corrected in NativeConssoleAppAids, version 1.0.0.5,
//                         released 2019/04/09, nine days after this project got
//                         pushed to the back burner.
//  ============================================================================

#if !defined ( CRTTIME_UNIT_TESTS_DEFINED )
#define        CRTTIME_UNIT_TESTS_DEFINED

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
	#pragma once
#endif  /* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

#include "..\CRTTime\targetver.h"

#include <stdio.h>                      // Declare standard file and stream I/O routines.

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>					// Windows Header Files

#include "..\CRTTime\CRTTime.H"			// Declare CRTTime functions under test.
#include <NativeConssoleAppAids.h>		// Declare console application helper functions from a library.

#include <TcharMacros_WW.H>             // Define my character string sizing and processing macros.
#include <MathMacros_WW.H>              // Define my array math constants and computation macros.

//  ----------------------------------------------------------------------------
//  The following block might be overkill, but it makes the values explicit for
//  both 32 and 64 bit configurations.
//  ----------------------------------------------------------------------------

#if defined ( _WIN64 )
    #define ARRAY_FIRST_ELEMENT_SUBSCR  0x0000000000000000
    #define ARRAY_INVALID_SUBSCRIPT     0xffffffffffffffff
    #define ARRAY_ORDINAL_FROM_SUBSCR   0x0000000000000001

    #define CONSOLE_INPUT_BUFFER_SIZE   0x0000000000000064

    #define CRT_TIME_ERROR              -1
    #define CRT_TIME_CONVERSION_ERROR   0x0000000000000000

    #define POS_RAW_TOKEN               0x0000000000000000
    #define POS_MODIFIED_TOKEN          0x0000000000000001
    #define POS_TOKEN_INTERPRETATION    0x0000000000000002
    #define POS_FLAG_INTERPRETATION     0x0000000000000003

    #define RETCODE_STRFTIME_ERROR      0x00000000000000FF

    #define STRFTIME_OUTBUF_SIZE        0x0000000000000040

    #define TOKEN_PROPERTY_COUNT        0x0000000000000004
#else
    #define ARRAY_FIRST_ELEMENT_SUBSCR  0x00000000L
    #define ARRAY_INVALID_SUBSCRIPT     0xffffffffL
    #define ARRAY_ORDINAL_FROM_SUBSCR   0x00000001L

    #define CONSOLE_INPUT_BUFFER_SIZE   0x00000064L

    #define CRT_TIME_ERROR              -1
    #define CRT_TIME_CONVERSION_ERROR   0x00000000L

    #define POS_RAW_TOKEN               0x00000000L
    #define POS_MODIFIED_TOKEN          0x00000001L
    #define POS_TOKEN_INTERPRETATION    0x00000002L
    #define POS_FLAG_INTERPRETATION     0x00000003L

    #define RETCODE_STRFTIME_ERROR      0x000000FFL

    #define STRFTIME_OUTBUF_SIZE        0x00000040L

    #define TOKEN_PROPERTY_COUNT        0x00000004L
#endif  /* #if defined ( _WIN64 ) ) */

#define STRFTIME_OUTPUT_MAX_CHARS       ( STRFTIME_OUTBUF_SIZE - 1 )


#if defined ( __cplusplus )
extern "C" {
#endif /* #if defined ( __cplusplus ) */

#if defined ( __cplusplus )
    #if defined ( _DEBUG )
        #pragma message ( __FILE__ ": CPP variable __cplusplus is defined." )
    #endif  /* #if defined ( _DEBUG ) */
#else
    #if defined ( _DEBUG )
        #pragma message ( __FILE__ ": CPP variable __cplusplus is UNdefined." )
    #endif  /* #if defined ( _DEBUG ) */

    #if !defined ( bool )
        #if defined ( _DEBUG )
            #pragma message ( __FILE__ ": CPP variable bool is UNdefined. Make it so." )
        #endif  /* #if defined ( _DEBUG ) */

        typedef int                     bool ;
    #endif  /* #if !defined ( bool ) */

    #if !defined ( BOOK )
        #if defined ( _DEBUG )
            #pragma message ( __FILE__ ": CPP variable BOOK is UNdefined. Make it so." )
        #endif  /* #if defined ( _DEBUG ) */

        typedef int                     BOOK ;
    #endif  /* #if !defined ( BOOK ) */

    #if !defined ( true )
        #if defined ( _DEBUG )
            #pragma message ( __FILE__ ": CPP variable true is UNdefined. Make it so." )
        #endif  /* #if defined ( _DEBUG ) */

        #define true                    1
    #endif  /* #if !defined ( true ) */

    #if !defined ( TRUE )
        #if defined ( _DEBUG )
            #pragma message ( __FILE__ ": CPP variable TRUE is UNdefined. Make it so." )
        #endif  /* #if defined ( _DEBUG ) */

        #define TRUE                    1
    #endif  /* #if !defined ( TRUE ) */

    #if !defined ( false )
        #if defined ( _DEBUG )
            #pragma message ( __FILE__ ": CPP variable false is UNdefined. Make it so." )
        #endif  /* #if defined ( _DEBUG ) */

        #define false                   0
    #endif  /*  #if !defined ( false ) */

    #if !defined ( FALSE )
        #if defined ( _DEBUG )
            #pragma message ( __FILE__ ": CPP variable FALSE is UNdefined. Make it so." )
        #endif  /*      #if defined ( _DEBUG ) */

        #define FALSE                   0
    #endif  /*  #if !defined ( FALSE ) */
#endif  /* #if defined ( __cplusplus ) */

//  ----------------------------------------------------------------------------
//  Other than the first being composed of ANSI characters and the second being
//  composed of wide characters, the following two arrays are identical.
//
//  Each table is a two-dimensional array of pointers to character strings. Each
//  column represents a column of data about the substitution tokens supported
//  by the strftime2 family of functions, which extend the strftime functions by
//  explicitly supporting time zone abbreviations. The four POS_* subscripts
//  defined above index the inner subscripts (the column numbers), while a plain
//  loop iterates the outer subscript (the row numbers).
//  ----------------------------------------------------------------------------

#if defined ( CRTTIME_UNIT_TESTS_MAIN )
    #if defined ( _DEBUG )
        #pragma message ( __FILE__ ": CPP variable CRTTIME_UNIT_TESTS_MAIN is defined. Define two strftime output buffers." )
    #endif  /* #if defined ( _DEBUG ) */

    wchar_t         m_achrOutputBuffer_1 [ STRFTIME_OUTBUF_SIZE ];
    wchar_t         m_achrOutputBuffer_2 [ STRFTIME_OUTBUF_SIZE ];
#else
    #if defined ( _DEBUG )
        #pragma message ( __FILE__ ": CPP variable CRTTIME2_UNIT_TESTS_MAIN is UNdefined." )
    #endif  /* #if defined ( _DEBUG ) */

    #if defined CRTTIME_UNIT_TESTS_HELPERS
        #if defined ( _DEBUG )
            #pragma message ( __FILE__ ": CPP variable CRTTIME_UNIT_TESTS_HELPERS is defined. Do nothing." )
        #endif  /* #if defined ( _DEBUG ) */
    #else
        #if defined ( _DEBUG )
            #pragma message ( __FILE__ ": CPP variable CRTTIME_UNIT_TESTS_HELPERS is UNdefined. Create strftime2 string tables." )
        #endif  /* #if defined ( _DEBUG ) */

        extern wchar_t         m_achrOutputBuffer_1 [ STRFTIME_OUTBUF_SIZE ];
        extern wchar_t         m_achrOutputBuffer_2 [ STRFTIME_OUTBUF_SIZE ];

        #if defined (_UNICODE )
            #if defined ( _DEBUG )
                #pragma message ( __FILE__ ": CPP variable _UNICODE is defined. Create Unicode strftime2 string table." )
            #endif  /* #if defined ( _DEBUG ) */

            const wchar_t * m_alpszTokenInfoW [ ] [ 4 ] = {
                { L"%a" , L"%#a" , L"Abbreviated weekday name"                                                                                                      , L"# flag is ignored." } ,
                { L"%A" , L"%#A" , L"Full weekday name"                                                                                                             , L"# flag is ignored." } ,
                { L"%b" , L"%#b" , L"Abbreviated month name"                                                                                                        , L"# flag is ignored." } ,
                { L"%B" , L"%#B" , L"Full month nam"                                                                                                                , L"# flag is ignored." } ,
                { L"%c" , L"%#c" , L"Date and time representation appropriate for locale"                                                                           , L"Long date and time representation, appropriate for current locale. For example: \"Tuesday, March 14, 1995, 12:41:29\"." } ,
                { L"%d" , L"%#d" , L"Day of month as decimal number (01 – 31)"                                                                                      , L"Remove leading zeros (if any)." } ,
                { L"%H" , L"%#H" , L"Hour in 24-hour format (00 – 23)"                                                                                              , L"Remove leading zeros (if any)." } ,
                { L"%I" , L"%#I" , L"Hour in 12-hour format (01 – 12)"                                                                                              , L"Remove leading zeros (if any)." } ,
                { L"%j" , L"%#j" , L"Day of year as decimal number (001 – 366)"                                                                                     , L"Remove leading zeros (if any)." } ,
                { L"%m" , L"%#m" , L"Month as decimal number (01 – 12)"                                                                                             , L"Remove leading zeros (if any)." } ,
                { L"%M" , L"%#M" , L"Minute as decimal number (00 – 59)"                                                                                            , L"Remove leading zeros (if any)." } ,
                { L"%p" , L"%#p" , L"Current locale's A.M./P.M. indicator for 12-hour clock"                                                                        , L"# flag is ignored." } ,
                { L"%S" , L"%#S" , L"Second as decimal number (00 – 59)"                                                                                            , L"Remove leading zeros (if any)." } ,
                { L"%U" , L"%#U" , L"Week of year as decimal number, with Sunday as first day of week (00 – 53)"                                                    , L"Remove leading zeros (if any)." } ,
                { L"%t" , L"%#t" , L"Time Zone Abbreviation"                                                                                                        , L"# flag is ignored." } ,
                { L"%T" , L"%#T" , L"Time Zone Abbreviation"                                                                                                        , L"# flag is ignored." } ,
                { L"%W" , L"%#W" , L"Week of year as decimal number, with Monday as first day of week (00 – 53)"                                                    , L"Remove leading zeros (if any)." } ,
                { L"%w" , L"%#w" , L"Weekday as decimal number (0 – 6; Sunday is 0)"                                                                                , L"Remove leading zeros (if any)." } ,
                { L"%x" , L"%#x" , L"Date representation for current locale"                                                                                        , L"Long date representation, appropriate to current locale. For example: \"Tuesday, March 14, 1995\"." } ,
                { L"%X" , L"%#X" , L"Time representation for current locale"                                                                                        , L"# flag is ignored." } ,
                { L"%y" , L"%#y" , L"Year without century, as decimal number (00 – 99)"                                                                             , L"Remove leading zeros (if any)." } ,
                { L"%Y" , L"%#Y" , L"Year with century, as decimal number"                                                                                          , L"Remove leading zeros (if any)." } ,
                { L"%z" , L"%#z" , L"Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown"    , L"# flag is ignored." } ,
                { L"%Z" , L"%#Z" , L"Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown"    , L"# flag is ignored." } ,
                { L"%%" , L"%#%" , L"Percent sign (The doubled percent sign behaves in the standard way to suppress the default intepretation of the % character.)" , L"# flag is ignored." } };
            #define m_alpszTokenInfo    m_alpszTokenInfoW
        #else   /* TRUE block, #if defined (_UNICODE ) */
            #if defined ( _DEBUG )
                #pragma message ( __FILE__ ": CPP variable _UNICODE is UNdefined. Create ANSI strftime2 string table." )
            #endif  /* #if defined ( _DEBUG ) */

            const char * m_alpszTokenInfoA [ ] [ 4 ] = {
                { "%a" , "%#a" , "Abbreviated weekday name"                                                                                                      , "# flag is ignored." } ,
                { "%A" , "%#A" , "Full weekday name"                                                                                                             , "# flag is ignored." } ,
                { "%b" , "%#b" , "Abbreviated month name"                                                                                                        , "# flag is ignored." } ,
                { "%B" , "%#B" , "Full month nam"                                                                                                                , "# flag is ignored." } ,
                { "%c" , "%#c" , "Date and time representation appropriate for locale"                                                                           , "Long date and time representation, appropriate for current locale. For example: \"Tuesday, March 14, 1995, 12:41:29\"." } ,
                { "%d" , "%#d" , "Day of month as decimal number (01 – 31)"                                                                                      , "Remove leading zeros (if any)." } ,
                { "%H" , "%#H" , "Hour in 24-hour format (00 – 23)"                                                                                              , "Remove leading zeros (if any)." } ,
                { "%I" , "%#I" , "Hour in 12-hour format (01 – 12)"                                                                                              , "Remove leading zeros (if any)." } ,
                { "%j" , "%#j" , "Day of year as decimal number (001 – 366)"                                                                                     , "Remove leading zeros (if any)." } ,
                { "%m" , "%#m" , "Month as decimal number (01 – 12)"                                                                                             , "Remove leading zeros (if any)." } ,
                { "%M" , "%#M" , "Minute as decimal number (00 – 59)"                                                                                            , "Remove leading zeros (if any)." } ,
                { "%p" , "%#p" , "Current locale's A.M./P.M. indicator for 12-hour clock"                                                                        , "# flag is ignored." } ,
                { "%S" , "%#S" , "Second as decimal number (00 – 59)"                                                                                            , "Remove leading zeros (if any)." } ,
                { "%U" , "%#U" , "Week of year as decimal number, with Sunday as first day of week (00 – 53)"                                                    , "Remove leading zeros (if any)." } ,
                { "%t" , "%#t" , "Time Zone Abbreviation"                                                                                                        , "# flag is ignored." } ,
                { "%T" , "%#T" , "Time Zone Abbreviation"                                                                                                        , "# flag is ignored." } ,
                { "%W" , "%#W" , "Week of year as decimal number, with Monday as first day of week (00 – 53)"                                                    , "Remove leading zeros (if any)." } ,
                { "%w" , "%#w" , "Weekday as decimal number (0 – 6; Sunday is 0)"                                                                                , "Remove leading zeros (if any)." } ,
                { "%x" , "%#x" , "Date representation for current locale"                                                                                        , "Long date representation, appropriate to current locale. For example: \"Tuesday, March 14, 1995\"." } ,
                { "%X" , "%#X" , "Time representation for current locale"                                                                                        , "# flag is ignored." } ,
                { "%y" , "%#y" , "Year without century, as decimal number (00 – 99)"                                                                             , "Remove leading zeros (if any)." } ,
                { "%Y" , "%#Y" , "Year with century, as decimal number"                                                                                          , "Remove leading zeros (if any)." } ,
                { "%z" , "%#z" , "Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown"    , "# flag is ignored." } ,
                { "%Z" , "%#Z" , "Either the time-zone name or time zone abbreviation, depending on registry settings; no characters if time zone is unknown"    , "# flag is ignored." } ,
                { "%%" , "%#%" , "Percent sign (The doubled percent sign behaves in the standard way to suppress the default intepretation of the % character.)" , "# flag is ignored." } };
            #define m_alpszTokenInfo    m_alpszTokenInfoA
        #endif  /* FALSE block, #if defined (_UNICODE ) */
    #endif  /* #if defined CRTTIME_UNIT_TESTS_HELPERS */
#endif  /* #if defined ( CRTTIME2_UNIT_TESTS_MAIN ) */

int     __stdcall CRTTime2_ANSI_Unit_Tests    ( const struct tm *           plpcrt_tm_struct );
int     __stdcall CRTTime2_Unicode_Unit_Tests ( const struct tm *           plpcrt_tm_struct );
#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */
#endif  /*  #if !defined ( CRTTIME_UNIT_TESTS_DEFINED ) */