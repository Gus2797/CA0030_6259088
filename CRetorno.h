#pragma once
#include "stdafx.h"

class CRetorno
{
private:
    CString sMensaje;
    bool bRetorno;
public:    
    CRetorno(void);
    virtual ~CRetorno(void);
    void SetMensaje(CString sMensaje);
    void SetMensaje(char* cMensaje);
	CString GetMensaje();
    void SetEsExitoso(bool bRetorno);
    bool GetEsExitoso();
    void * Objeto;
};