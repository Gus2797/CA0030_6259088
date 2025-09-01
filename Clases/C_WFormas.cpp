#include "C_WFormas.hpp"
#include <winspool.h>
#include <winsock.h>
#include "C_Mem.hpp"
#include "C_Archiv.hpp"
#include "gnwproto.hpp"
// returns a DEVMODE and DEVNAMES for the printer name specified
BOOL GetPrinterDevice(LPTSTR pszPrinterName, HGLOBAL* phDevNames, HGLOBAL* phDevMode)
{
    // if NULL is passed, then assume we are setting app object's
    // devmode and devnames
    if (phDevMode == NULL || phDevNames == NULL)
        return FALSE;

    // Open printer
    HANDLE hPrinter;
    if (OpenPrinter(pszPrinterName, &hPrinter, NULL) == FALSE)
        return FALSE;

    // obtain PRINTER_INFO_2 structure and close printer
    DWORD dwBytesReturned, dwBytesNeeded;
    GetPrinter(hPrinter, 2, NULL, 0, &dwBytesNeeded);
    PRINTER_INFO_2* p2 = (PRINTER_INFO_2*)GlobalAlloc(GPTR, dwBytesNeeded);
    if (GetPrinter(hPrinter, 2, (LPBYTE)p2, dwBytesNeeded, &dwBytesReturned) == 0) {
       GlobalFree(p2);
       ClosePrinter(hPrinter);
       return FALSE;
    }
    ClosePrinter(hPrinter);

    // Allocate a global handle for DEVMODE
    HGLOBAL  hDevMode = GlobalAlloc(GHND, sizeof(*p2->pDevMode) + p2->pDevMode->dmDriverExtra);
    ASSERT(hDevMode);
    DEVMODE* pDevMode = (DEVMODE*)GlobalLock(hDevMode);
    ASSERT(pDevMode);

    // copy DEVMODE data from PRINTER_INFO_2::pDevMode
	if(memcpy_s(pDevMode, sizeof(DEVMODE), p2->pDevMode, sizeof(*p2->pDevMode) + p2->pDevMode->dmDriverExtra) < 0){;}
    GlobalUnlock(hDevMode);

    // Compute size of DEVNAMES structure from PRINTER_INFO_2's data
    DWORD drvNameLen = strnlen(p2->pDriverName, 255);  // driver name
    DWORD ptrNameLen = strnlen(p2->pPrinterName, 255); // printer name
    DWORD porNameLen = strnlen(p2->pPortName, 255);    // port name

    // Allocate a global handle big enough to hold DEVNAMES.
    HGLOBAL hDevNames = GlobalAlloc(GHND, sizeof(DEVNAMES) + (drvNameLen + ptrNameLen + porNameLen)*sizeof(TCHAR));
    ASSERT(hDevNames);
    DEVNAMES* pDevNames = (DEVNAMES*)GlobalLock(hDevNames);
    ASSERT(pDevNames);

    // Copy the DEVNAMES information from PRINTER_INFO_2
    int tcOffset = sizeof(DEVNAMES)/sizeof(TCHAR);
    ASSERT(sizeof(DEVNAMES) == tcOffset*sizeof(TCHAR));

    pDevNames->wDriverOffset = tcOffset;
	if(memcpy_s((LPTSTR)pDevNames + tcOffset, drvNameLen*sizeof(TCHAR), p2->pDriverName, drvNameLen*sizeof(TCHAR)) < 0){;}
    tcOffset += drvNameLen;

    pDevNames->wDeviceOffset = tcOffset;
	if(memcpy_s((LPTSTR)pDevNames + tcOffset, drvNameLen*sizeof(TCHAR), p2->pPrinterName, ptrNameLen*sizeof(TCHAR)) < 0){;}
    tcOffset += ptrNameLen;

    pDevNames->wOutputOffset = tcOffset;
	if(memcpy_s((LPTSTR)pDevNames + tcOffset, drvNameLen*sizeof(TCHAR), p2->pPortName, porNameLen*sizeof(TCHAR)) < 0){;}
    pDevNames->wDefault = 0;

    GlobalUnlock(hDevNames);
    GlobalFree(p2);   // free PRINTER_INFO_2

    // set the new hDevMode and hDevNames
    *phDevMode = hDevMode;
    *phDevNames = hDevNames;
	free(hDevMode);
	free(hDevNames);

    return TRUE;
}

void obtenerIP(char *cIP)
{
	char   cIPTemp[20], cHostTemp[30];
	struct hostent *pHostEnt;
	struct in_addr  **stIp;

	SecureZeroMemory( cHostTemp, sizeof(cHostTemp) );
	SecureZeroMemory( cIPTemp, sizeof(cIPTemp) );	

	gethostname(cHostTemp, sizeof(cHostTemp) );

	pHostEnt = gethostbyname ( cHostTemp ) ;

	if ( pHostEnt != NULL )
	{
		stIp= (struct in_addr **) pHostEnt->h_addr_list;

		//while( *stIp != NULL )
		{
			if(sprintf_s( cIPTemp, "%s", inet_ntoa(**(stIp++)) ) < 0){;}
			if(memcpy_s(cIP, 15, cIPTemp,15) < 0){;}
			cIP[15]=0;
			//m_Lista.AddString( cIPTemp );
		}
	}
}

C_WFormas::~C_WFormas()
{	
	
}

C_WFormas::C_WFormas( ) 
{
	if(sprintf_s( cLog, "C_WFormas: Entra al constructor" ) < 0){;}
	darSeguimiento( cLog );	

	char cNombreImpresora[128] = {0};

	SecureZeroMemory( cLog, sizeof( cLog) );
	SecureZeroMemory( cImpresora, sizeof(cImpresora) );

	int i = 0, iPosicionEncontro = 0;
	CString sNombreImpresora;
	
	bool bConfigurarImp = false;

	DWORD dwNeeded = 0, dwItems = 0;
	LPBYTE lpPrinterInfo = NULL;
	CStringArray szaPrinterArray;

	bContinuar = false;

	EnumPrinters( PRINTER_ENUM_LOCAL, NULL, 2, NULL, 0, &dwNeeded, &dwItems );
	//Enumerating all the printers available in the system

	lpPrinterInfo = new BYTE[dwNeeded];

	if( lpPrinterInfo )
	{
		//Get the data in the BYTE pointer
		if( EnumPrinters( PRINTER_ENUM_LOCAL, NULL, 2, lpPrinterInfo, dwNeeded,&dwNeeded,&dwItems) )
		{
			for( int k = 0; k < (int)dwItems; k++ )
				//Loop through them and add them to the String Array
				szaPrinterArray.Add((((LPPRINTER_INFO_2)lpPrinterInfo) + k )->pPrinterName);
		}
	}

	delete lpPrinterInfo;

	for(int j = 0; j < szaPrinterArray.GetSize(); j++)
	{
		iPosicionEncontro = -1;
		SecureZeroMemory(cNombreImpresora,sizeof(cNombreImpresora));		
		sNombreImpresora = szaPrinterArray[j];		
		if(sprintf_s( cNombreImpresora, "%s", sNombreImpresora ) < 0){;}

		sNombreImpresora.MakeUpper();
		
		iPosicionEncontro = sNombreImpresora.Find("IMPRESORA");		
		if ( iPosicionEncontro >= 0 )
		{
			bConfigurarImp = true;
			if(sprintf_s( cLog, "C_WFormas: Encontro impresora Matricial, bConfigurarImp = %d", bConfigurarImp ) < 0){;}
			darSeguimiento( cLog );			
			
			break;
		}
		else
		{
			iPosicionEncontro = sNombreImpresora.Find("EPSON");
			if ( iPosicionEncontro >= 0 )
			{
				bConfigurarImp = true;
				if(sprintf_s( cLog, "C_WFormas: Encontro impresora Matricial, bConfigurarImp = %d", bConfigurarImp ) < 0){;}
				darSeguimiento( cLog );			
				
				break;
			}
			else 
			{
				iPosicionEncontro = sNombreImpresora.Find("LASER");		
				if ( iPosicionEncontro >= 0 )
				{
					bConfigurarImp = true;
					if(sprintf_s( cLog, "C_WFormas: Encontro impresora Laser, bConfigurarImp = %d", bConfigurarImp ) < 0){;}
					darSeguimiento( cLog );
					break;
				}
			}
		}
	}

	if( bConfigurarImp )
	{
		bContinuar = true;
		if(sprintf_s( cImpresora, "%s", cNombreImpresora ) < 0){;}
	}
	else
	{
		bContinuar = false;
		if(sprintf_s( cLog, "C_WFormas: La impresora Matricial no se encuentra instalada, bConfigurarImp = %d", bConfigurarImp ) < 0){;}
		darSeguimiento( cLog );
	}
}

bool C_WFormas::imprimirArchivo( char *cArchivo )
{
	bool bRegresa = false;
	if(sprintf_s( cLog, "C_WFormas::imprimirArchivo: Entra a imprimir archivo" ) < 0){;}
	darSeguimiento( cLog );	
	
	HANDLE hPrinter;
	DOC_INFO_1 DocInfo;

	DocInfo.pDatatype = "RAW";
	DocInfo.pDocName = "ReciboAbonos";
	DocInfo.pOutputFile = NULL;
	
	DWORD written;
	long lTamanoArchivo = 0;

	C_Archivo archImg;
	archImg.abrir( cArchivo, LEER_SOLAMENTE );
	lTamanoArchivo = _filelength( archImg.fp );

	if( lTamanoArchivo > 0  )
	{
		int iLeido = 0;
		C_Mem mImgX( lTamanoArchivo + 100 );
		SecureZeroMemory( mImgX.buffer, lTamanoArchivo + 100 );
		iLeido = _read( archImg.fp, mImgX.buffer, (unsigned int)lTamanoArchivo );

		if(OpenPrinter(cImpresora, &hPrinter, NULL))
		{
			if(StartDocPrinter(hPrinter,1,(LPBYTE)&DocInfo))
			{
				if(StartPagePrinter(hPrinter))
				{
					if( WritePrinter(hPrinter, mImgX.buffer, iLeido, &written) )
					{
						bRegresa = true;
					}
					else
					{
						AfxMessageBox("Error al Imprimir");
						if(sprintf_s( cLog, "C_WFormas::imprimirArchivo: Error al Imprimir" ) < 0){;}
						darSeguimiento( cLog );	
					}
				}
				else
				{
					AfxMessageBox("Error al Iniciar Pagina");
					if(sprintf_s( cLog, "C_WFormas::imprimirArchivo: Error al Iniciar Pagina" ) < 0){;}
					darSeguimiento( cLog );	
				}
			}
			else
			{
				AfxMessageBox("Error al Iniciar Documento");
				if(sprintf_s( cLog, "C_WFormas::imprimirArchivo: Error al Iniciar Documento" ) < 0){;}
				darSeguimiento( cLog );	
			}
		}
		else
		{
			AfxMessageBox("Error al Configurar Impresora");
			if(sprintf_s( cLog, "C_WFormas::imprimirArchivo: Error al Configurar Impresora" ) < 0){;}
			darSeguimiento( cLog );	
		}

		EndPagePrinter(hPrinter);
		EndDocPrinter(hPrinter);		
		ClosePrinter(hPrinter);
	}
	archImg.cerrar();

	return bRegresa;
}

void C_WFormas::darSeguimiento( char *cTexto )
{
	char sArch[80]={0};
	char cTextoGrabar[2048]={0};
	CTime tFecha = CTime::GetCurrentTime();

	if(sprintf_s(sArch, "C:\\sys\\mem\\CapturarAbonos%02d%02d.log", tFecha.GetMonth(), tFecha.GetDay() ) < 0){;}
	
	if(sprintf_s( cTextoGrabar, "%04d-%02d-%02d %02d:%02d:%02d %s\n", tFecha.GetYear(), tFecha.GetMonth(), tFecha.GetDay(), tFecha.GetHour(), tFecha.GetMinute(), tFecha.GetSecond(), cTexto) < 0){;}
	C_Archivo arch( sArch, &cTextoGrabar, sizeof( cTextoGrabar ) );
	arch.posicionar( (long)0, BASE_FINAL);
	arch.grabar( cTextoGrabar, (unsigned int) strnlen(cTextoGrabar, sizeof(cTextoGrabar)) );
}