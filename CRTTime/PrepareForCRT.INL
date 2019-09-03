//	PrepareForCRT.INL : Define the implementation of PrepareForCRT for both character encodings.

    PTCHAR rlpszFormat 			= NULL;

    int    intTokenIndex 		= ARRAY_INVALID_SUBSCRIPT;
    int    intOldTokenLength 	= UNKNOWN_STRING_LENGTH;
    int    intNewTokenLength 	= UNKNOWN_STRING_LENGTH;

    PTCHAR lpTZToken 			= NULL;

    for ( intTokenIndex = ARRAY_FIRST_ELEMENT;
          intTokenIndex < ( int ) m_intTokenTableASize;
          intTokenIndex++ )
    {
        lpTZToken 				= _tcsstr ( plpszFormat ,
                                            m_lpTZAbbrevTokens [ intTokenIndex ] );

        if ( lpTZToken )
        {	// Found a match; break out of the loop.
            break;
        }	// if ( lpTZToken )
    }	// for ( intTokenIndex = ARRAY_FIRST_ELEMENT; intTokenIndex < m_intTokenTableASize; intTokenIndex++ )

    if ( lpTZToken )
    {
        rlpszFormat 			= ( PTCHAR ) AllocTchars_WW ( CRTTIME_NOW_OUTPUT_BUFCAP );

        if ( rlpszFormat )
        {
            intOldTokenLength 	= _tcslen ( m_lpTZAbbrevTokens [ intTokenIndex ] );
            intNewTokenLength 	= _tcslen ( CRTTIME_TZ_ABBREVIATION_TOKEN );
        }	// Anticipated outcome block, if ( rlpszFormat )
    }	// TRUE (The format string contains a TZ token.) block, if ( lpTZToken )
    else
    {	// Since _tcsftime can process the format as is, return a pointer to it. Save the memory allocation and copying for when you really need it.
        rlpszFormat				= ( TCHAR    * ) plpszFormat;
    }	// FALSE (The format string is devoid of TZ tokens.) block, if ( lpTZToken )

    return rlpszFormat;
//	PrepareForCRT