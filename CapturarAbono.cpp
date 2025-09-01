/* --------------------------------------------------------------------
    Fecha    :17-01-06 05:10pm  ( dd-mm-aa )
    Elabor¢  :Joel Armando Arana Garcia
    Solicit¢ :Lic. Jos‚ G. Mendoza
    Actividad:Captura de Abonos.
   --------------------------------------------------------------------*/

   // CapturarAbono.cpp : Defines the initialization routines for the DLL.
   //

#include "stdafx.h"
#include <afxdllx.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE CapturarAbonoDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    // Remove this if you use lpReserved
    UNREFERENCED_PARAMETER(lpReserved);

    if (dwReason == DLL_PROCESS_ATTACH)
    {
        TRACE0("CapturarAbono.DLL Initializing!\n");

        // Extension DLL one-time initialization
        if (!AfxInitExtensionModule(CapturarAbonoDLL, hInstance))
            return 0;

        // Insert this DLL into the resource chain
        // NOTE: If this Extension DLL is being implicitly linked to by
        //  an MFC Regular DLL (such as an ActiveX Control)
        //  instead of an MFC application, then you will want to
        //  remove this line from DllMain and put it in a separate
        //  function exported from this Extension DLL.  The Regular DLL
        //  that uses this Extension DLL should then explicitly call that
        //  function to initialize this Extension DLL.  Otherwise,
        //  the CDynLinkLibrary object will not be attached to the
        //  Regular DLL's resource chain, and serious problems will
        //  result.

		//Correcion de vulnerabilidad Memory Leak
		bool bLibera = false;
		CDynLinkLibrary *LinkLibrary = new CDynLinkLibrary(CapturarAbonoDLL);

		if (bLibera == true)
		{
			free(LinkLibrary);
		}

    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        TRACE0("CapturarAbono.DLL Terminating!\n");

        // Terminate the library before destructors are called
        AfxTermExtensionModule(CapturarAbonoDLL);
    }
    return 1;   // ok
}
