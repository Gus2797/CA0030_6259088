// Consulta original solicitada:...
//  SELECT factura,fecha,fechavencimiento,importe,folioanterior FROM cacarmov WHERE recibo = 3108 AND caja = 1 AND clv = 'G' AND tiposeguro = '3'
    
#ifndef CCONSULTARABONOSEGURO
#define CCONSULTARABONOSEGURO
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarAbonoSeguro : public CRecordSet 
{
public:
    CConsultarAbonoSeguro(C_ODBC *odbc_ext,bool bFlagCommit = true, const char *select=NULL);
    ~CConsultarAbonoSeguro();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[6];
    int nCTipo[6];
    long nLongitud[6];
    long nLongResp[6];
    void *pVar[6];
	bool bFlagCommit;
    
    long                factura;
    SqlTimeStamp        fecha;
    SqlTimeStamp        fechavencimiento;
    long                importe;
    long                folioanterior;
};
#endif CCONSULTARABONOSEGURO
