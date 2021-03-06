// dllmain..C : Defines the entry point for the DLL application.

#define CRTTIME_DLLMAIN
#include "CRTTime_Pvt.H"

BOOL APIENTRY DllMain ( HMODULE phModule,
                        DWORD   pul_reason_for_call,
                        LPVOID  plpReserved
                      )
{
    switch ( pul_reason_for_call )
    {
		case DLL_PROCESS_ATTACH:
			m_lpDllhModule	= phModule;
			m_hProcHeap		= GetProcessHeap ( );
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }	// switch ( pul_reason_for_call )
    
	return TRUE;
}	// BOOL APIENTRY DllMain