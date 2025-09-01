#ifndef CCONSULTARZONACLIENTE
#define CCONSULTARZONACLIENTE
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarZonaCliente : public CRecordSet 
{
public:
    CConsultarZonaCliente(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarZonaCliente();
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
    
    char                nombrezona[32];
    char                municipio[27];
    long                codigopostal;
};
#endif CCONSULTARZONACLIENTE
