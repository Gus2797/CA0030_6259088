// Consulta original solicitada:...
//  SELECT cliente,factura,digito FROM cacarmov
    
#ifndef CCONSULTARPOLIZASNVAS01
#define CCONSULTARPOLIZASNVAS01
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarPolizasNvas01 : public CRecordSet 
{
public:
    CConsultarPolizasNvas01(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarPolizasNvas01();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[5];
    int nCTipo[5];
    long nLongitud[5];
    long nLongResp[5];
    void *pVar[5];
    
    long                cliente;
    long                factura;
    short int           digito;
	long				folioanterior;
};
#endif CCONSULTARPOLIZASNVAS01
