// Consulta original solicitada:...
//  select * from fun_obtener_puesto(96793929)
    
#ifndef CCONSULTAFACTURASESIONTEMP
#define CCONSULTAFACTURASESIONTEMP
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultaFacturaSesionTemp : public CRecordSet 
{
public:
    CConsultaFacturaSesionTemp(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultaFacturaSesionTemp();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[12];
    int nCTipo[12];
    long nLongitud[12];
    long nLongResp[12];
    void *pVar[12];
    
	long                factura_temp;
    __int64             sesion_temp;
	long				monto_temp;
	char                banco_temp[17];
	char                localforaneo_temp[2];
	__int64				numerocheque_temp;
	char                codautorizacionbanco_temp[9];
	char                tipotarjeta_temp[2];
	short int           idu_banco_temp;
	long				cliente_temp;

};
#endif CCONSULTAFACTURASESIONTEMP
