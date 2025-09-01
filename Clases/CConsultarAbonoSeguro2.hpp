// Consulta original solicitada:...
//  SELECT factura,fecha,fechavencimiento,importe,folioanterior, cantidadmeses, fechanacimiento FROM cacarmov   WHERE recibo=740159
    
#ifndef CCONSULTARABONOSEGURO2
#define CCONSULTARABONOSEGURO2
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarAbonoSeguro2 : public CRecordSet 
{
public:
    CConsultarAbonoSeguro2(C_ODBC *odbc_ext,bool bFlagCommit = true, const char *select=NULL);
    ~CConsultarAbonoSeguro2();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[8];
    int nCTipo[8];
    long nLongitud[8];
    long nLongResp[8];
    void *pVar[8];
	bool bFlagCommit;
    
    long                factura;
    SqlTimeStamp        fecha;
    SqlTimeStamp        fechavencimiento;
    long                importe;
    long                folioanterior;
    short int           cantidadmeses;
    SqlTimeStamp        fechanacimiento;
};
#endif CCONSULTARABONOSEGURO2
