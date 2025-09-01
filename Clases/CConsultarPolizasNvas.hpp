// Consulta original solicitada:...
//  SELECT cliente,factura,digito FROM cacarmov
    
#ifndef CCONSULTARPOLIZASNVAS
#define CCONSULTARPOLIZASNVAS
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarPolizasNvas : public CRecordSet 
{
public:
    CConsultarPolizasNvas(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarPolizasNvas();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[4];
    int nCTipo[4];
    long nLongitud[4];
    long nLongResp[4];
    void *pVar[4];
    
    long                cliente;
    long                factura;
    short int           digito;
};
#endif CCONSULTARPOLIZASNVAS
