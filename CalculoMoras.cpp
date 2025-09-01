#include "CalculoMoras.h"
#include "DlgCapturarAbono.h"
#include "Cmaximo.hpp"

#include <iostream>
#include <ctime>
#include <sstream>
#include <afx.h> 

CCalculoMoras::CCalculoMoras( )
{	
	
}


CCalculoMoras::~CCalculoMoras(void)
{

}

int CCalculoMoras::CalcularMoras( float fVencido, float fInteres, float fBase)
{
	iImpMoras = 0;

	if(fBase > 0)
	{
		iImpMoras = ((fVencido - fInteres)/fBase) + 0.999999;
	}

	return iImpMoras;
}