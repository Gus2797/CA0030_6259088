#pragma once
#include "stdafx.h"
class CExcepcion
{
private:
    CString sMensaje;
    CExcepcion* innerExcepcion;
    CString GetTraza(CString sTab) {
        CString sTraza = "->";
        sTraza.AppendFormat("%s", this->sMensaje);
        if (this->innerExcepcion != NULL)
        {
            sTab.Append(sTab);
            sTraza.AppendFormat("\r\n%s%s", sTab, innerExcepcion->GetTraza(sTab));
        }
        return sTraza;
    }
public:
    CExcepcion(CString sMensaje)
    {
        this->sMensaje = sMensaje;
        this->innerExcepcion = NULL;
    }
    CExcepcion(CString sMensaje, CExcepcion* innerExcepcion)
    {
        this->sMensaje = sMensaje;
        this->innerExcepcion = innerExcepcion;
    }
    ~CExcepcion(void) {}
    CString  GetTraza() {
        CString sTab = "  ";
        return GetTraza(sTab);
    }
};