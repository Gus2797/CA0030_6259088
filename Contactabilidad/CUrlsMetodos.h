#pragma once
#include "stdafx.h"
class CUrlsMetodos
{
private:
    CString sTelefonoSolicitar;
    CString sTelefonoCofetel;
    CString sConfirmacionPendientes;
    CString sConfirmacionPendientesTitular;
    CString sCarteraCliente;
    CString sTiendaGnDominio;

public:
    CUrlsMetodos(void)
    {
        this->sTelefonoSolicitar = "http://%s/telefonos/solicitar";
    }
    ~CUrlsMetodos(void)
    {
    }

    void SetTelefonoSolicitar(CString sUrl)
    {
        CString sTmp = this->sTelefonoSolicitar;
        this->sTelefonoSolicitar.Empty();
        this->sTelefonoSolicitar.AppendFormat(sTmp, sUrl);
    }
    CString GetTelefonoSolicitar(int iSuborigen, long lCliente, int iTipoTelefono)
    {
        CString sUrl = this->sTelefonoSolicitar;
        sUrl.AppendFormat("/%d/%ld/%d", iSuborigen, lCliente, iTipoTelefono);
        return sUrl;
    }
};