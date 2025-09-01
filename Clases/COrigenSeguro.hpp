// Consulta original solicitada:...
//  SELECT CASE WHEN TRIM(clv_origenseguro)=''THEN 'C' ELSE clv_origenseguro END::CHAR(1) AS clv_origenseguro  FROM fun_consultarcrseguros(1346695,14025);
    
#ifndef CORIGENSEGURO
#define CORIGENSEGURO
#include "stdafx.h"
#include <RecordSet.hpp>
class COrigenSeguro : public CRecordSet 
{
public:
    COrigenSeguro(C_ODBC *odbc_ext, const char *select=NULL);
    ~COrigenSeguro();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];
    
    char                clv_origenseguro[4];
};
#endif CORIGENSEGURO
