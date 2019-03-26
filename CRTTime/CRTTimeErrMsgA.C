//	CRTTimeErrMsgA.C : Define the ANSI implementation of _CRTTimeErrMsg.

#undef UNICODE
#undef _UNICODE
#define CRTTIME_DLLERRMAP_ANSI

#include "CRTTime_Pvt.H"

PTCHAR LIBSPEC_CRTTIME2_API CRTTimeErrMsgA ( int pintErrorCode )
{
	#include ".\CRTTimeErrMsg.INL"
}	// CRTTimeErrMsgA