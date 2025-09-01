#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#include "Winspool.h"

#ifndef	CWFORMAS
#define CWFORMAS

class C_WFormas
{
public:
	C_WFormas( );

	 virtual ~C_WFormas();	 	 
	 bool imprimirArchivo( char *cArchivo );
	 void darSeguimiento( char *cText );
	 bool bContinuar;

private:
	char cImpresora[256];
	char cLog[1024];
};
#endif CWFORMAS