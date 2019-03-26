//	CRTTimeErrMsgW.C : Define the ANSI implementation of _CRTTimeErrMsg.

#define CRTTIME_DLLERRMAP_WIDE

#include "CRTTime_Pvt.H"

PTCHAR LIBSPEC_CRTTIME2_API CRTTimeErrMsgW ( int pintErrorCode )
{
	#include ".\CRTTimeErrMsg.INL"
}	// CRTTimeErrMsgW