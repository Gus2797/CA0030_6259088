#pragma once
#include "stdafx.h"
#include "sysCapturarAbono.h"
#include "CExcepcion.h"
#include "HTTP_c.h"
#include <include\ArduinoJson.h>
#include "CUtil.h"
#include "CUrlWebService.h"
#include "gnwproto.hpp"
#include "CMaximo.hpp"
#include "CEntorno.h"
#include "CargarDLL.h"

class CContactabilidad
{
private:
    int static const iscWebServiceTelefonos = 70;
    int static const iscFlgModoLocal = 30;
    int static const iscFlgContacta = 248;
    int static const iscIdContacto = 1;
    int static const iscBufferLength = 100000;
    StaticJsonBuffer<iscBufferLength> jsonBuffer;
    bool bEsActiva;
    bool ConsultarContactabilidadEspecifica(int iSubOrigen);
    void EstablecerUrls();
    void SetEsActiva();
    CString GetUrlWebService(int iTipo);
    CUtil util;
    CUrlsMetodos urlsMetodos;
    CEntorno* entorno;
public:
    void EjecutarAppCapturaValidacion();
    CContactabilidad(CEntorno* entornoargs);
    ~CContactabilidad(void);
    bool GetEsSolicitable();
    bool GetEsActiva();
};