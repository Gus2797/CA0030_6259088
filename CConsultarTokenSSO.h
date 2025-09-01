#pragma once
#include "afxwin.h"

class CConsultarTokenSSO
{
    // Construccion
public:
    CConsultarTokenSSO(void);	// Constructor estandar
    virtual ~CConsultarTokenSSO(); // destructor estandar  

	CString consultarTokenSSO(short iIdSistema, short iIdServicio, short iOpcion, CString sNombreServicio, char* cIPServidorTiendaNumero, short iTienda, short iCaja);
};