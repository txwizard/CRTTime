// FormatTimeCleanup.C : Define FormatTimeCleanup, an internal utility function.
//

#include ".\CRTTime_Pvt.H"

LPVOID	  __stdcall FormatTimeCleanup
(
        LPCVOID * prlpFormattedTime,
        LPCVOID   pFormat,
        LPCVOID * plpszFormatString,
        CBOOL     pfDiscardFomrattetTime
)
{
    if ( pFormat != plpszFormatString )
    {	// plpszFormatString points to a locally allocated buffer that's about to go out of scope.
		* plpszFormatString		= FreeBuffer_WW ( plpszFormatString );
    }	// if ( pFormat != plpszFormatString )

    if ( pfDiscardFomrattetTime )
    {
        if ( prlpFormattedTime )
        {	// Discard the buffer before it goes out of scope.
			* prlpFormattedTime = FreeBuffer_WW ( prlpFormattedTime );
        }	// if ( prlpFormattedTime )

        return NULL;
    }	// TRUE (The function failed.) block, if ( pfDiscardFomrattetTime )
    else
    {
        return prlpFormattedTime;
    }	// FALSE (The function succeeded.) block, if ( pfDiscardFomrattetTime )
}	// FormatTimeCleanup