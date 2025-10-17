#include "stdafx.h"
#include "DlgCapturarAbono.h"
#include "CLogBonificacionDiaria.hpp"

void CDlgCapturarAbono::generarLogBonificax(char *nomfuncion,const char *mensaje, long numCte, long numFactura, char * fechaCompra, int numTienda)
{
	char cTxt[3000] = { 0 };
	
	sprintf_s(cTxt, "SELECT estado, mensaje FROM fun_guardarlogbonificaciondiaria(%d, %d, '%s', '%s', %d, '%s');", numCte, numFactura, mensaje,  fechaCompra,  numTienda, nomfuncion);
	grabarBonificaLog(cTxt);
	
	CLogBonificacionDiaria cLogBonificacionDiaria(&odbc, false);
	if (cLogBonificacionDiaria.Exec(cTxt))
	{
		cLogBonificacionDiaria.activarCols();
		cLogBonificacionDiaria.Leer();
	} else {
		sprintf_s(cTxt, "Error al grabar log fuente[%s]", nomfuncion);
		grabarBonificaLog(cTxt);
	}
}