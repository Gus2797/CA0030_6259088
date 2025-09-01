#pragma once
#include "stdafx.h"
#include "stdio.h"
#include "CUrlsMetodos.h"
class CEntorno
{
private:

public:
    int iSuborigen;
    int iTienda;
    int iCaja;
    int iSistema;
    long lEmpleado;
    long lCliente;
    CString sIpTienda;
    CString sAppName;
    CEntorno(void)
    {
        this->iSuborigen = 0;
        this->iTienda = 0;
        this->iCaja = 0;
        this->sIpTienda = "";
        this->lCliente = 0;
        this->iSistema = 0;
        this->lEmpleado = 0;
        this->sAppName = "";
    }

    virtual ~CEntorno(void)
    {
    }
    CString GetJson()
    {
        CString sRetorno = "";
        CString sFormat =
            "{\"iSuborigen\":%d,\"iTienda\":%d,\"iCaja\":%d,\"sIpTienda\":\"%s\","
            " \"lCliente\":%ld, \"iSistema\":%d, \"lEmpleado\":%ld, \"sAppName\":\"%s\"}";
        sRetorno.AppendFormat(sFormat, iSuborigen, iTienda, iCaja, sIpTienda, lCliente,
            iSistema, lEmpleado, sAppName);
        return sRetorno;
    }
};