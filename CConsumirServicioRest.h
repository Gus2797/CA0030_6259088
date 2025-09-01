#pragma once
#include "stdafx.h"
#import "C:\sys\progx\libcsharp\RESTREB.TLB"
#include <comdef.h>

class CConsumirServicioRest
{
private:    
    int static const iscBufferLength = 100000; 
   
    CString sRespuesta;
    void CConsumirServicioRest::obtenerRespuesta( CString sUrl, CString sJson, CString sToken );

public:
	CConsumirServicioRest::CConsumirServicioRest( CString sUrl, CString sJson, CString sToken );
    ~CConsumirServicioRest( void );
    CString ObtenerUltimaRespuesta( );
};