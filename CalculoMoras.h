#pragma once
#include "stdafx.h"

class CCalculoMoras
{
public:
	CCalculoMoras(void);
	~CCalculoMoras(void);
	
	CString sFechaActual;
	char cSql[100];
	int iAnioActual ,iMesActual,iDiaActual, iImpMoras;
	long lCliente, lImpMoras; 

	int CalcularMoras(float fVenciodo, float fInteres, float fBase);
};

