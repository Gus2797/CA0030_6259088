#ifndef CCONSULTARCLAVECONYUGALCRSEGUROS
#define CCONSULTARCLAVECONYUGALCRSEGUROS
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarClaveConyugalCrSeguros : public CRecordSet 
{
public:
    CConsultarClaveConyugalCrSeguros(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarClaveConyugalCrSeguros();
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
    
    short int           claveconyugal;
};
#endif CCONSULTARCLAVECONYUGALCRSEGUROS
