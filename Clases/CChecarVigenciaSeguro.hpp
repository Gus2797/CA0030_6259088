#ifndef CCHECARVIGENCIASEGURO
#define CCHECARVIGENCIASEGURO
#include "stdafx.h"
#include <RecordSet.HPP>
class CChecarVigenciaSeguro : public CRecordSet 
{
public:
    CChecarVigenciaSeguro(C_ODBC *odbc_ext, const char *select=NULL);
    ~CChecarVigenciaSeguro();
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
    
    char                claveseguro[3];
    char                statusseguro[3];
    SqlTimeStamp        fechavencimiento;
    char                clavenoofrecer[3];
};
#endif CCHECARVIGENCIASEGURO
