#pragma once
#include "stdafx.h"
#include "CRetorno.h"
#include "CEntorno.h"
#import "C:\sys\progx\libcsharp\RESTREB.TLB"

#include <comdef.h>
#include "CTokenSSO.h"
class CSesion
{
private:    
    int static const iscBufferLength = 100000; 
    int idOrigenConfig;
    int iduServicioConfig;
    CEntorno* entorno;  
    CString sEstatus;
    CString sToken;
    void SetSesion();
    void ValidarYEstablecerRespuesta(CString sData);
public:
    CString GetLastToken();    
    CSesion(CEntorno* entorno, int idOrigenConfig, int iduServicioConfig);
    virtual ~CSesion(void);
};