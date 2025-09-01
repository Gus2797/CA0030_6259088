#pragma once
#include "stdafx.h"

class CTokenSSO
{
public:    
    int iTienda;
    CString sIpTienda;
    int iIduOrigen;
    int iIduServicio;
    int iSistema;
    int iCaja;

    CTokenSSO(void)
    {
        iTienda=0;
        sIpTienda.Empty();
        iIduOrigen=0;
        iIduServicio=0;
        iSistema=0;
        iCaja=0;
    }
    ~CTokenSSO(void)
    {
    }
    CString GetJson()
    {        
        CString sJSonVal="";
        CString sJSonAttr ="{";
        sJSonAttr+=_T("\"Tienda\" : %d, ");
        sJSonAttr+=_T("\"IpTienda\" : \"%s\", ");
        sJSonAttr+=_T("\"IduOrigen\" : %d, ");
        sJSonAttr+=_T("\"IduServicio\" : %d,");
        sJSonAttr+=_T("\"NumeroSistema\" : %d,");
        sJSonAttr+=_T("\"Caja\" : %d");
        sJSonAttr+=_T("}");
        sJSonVal.Format(sJSonAttr
            ,iTienda
            ,sIpTienda            
            ,iIduOrigen
            ,iIduServicio
            ,iSistema
            ,iCaja);
        return sJSonVal;
        return "";
    }
};