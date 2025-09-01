#ifndef CCONSULTARCATOTALENCUESTA
#define CCONSULTARCATOTALENCUESTA
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarCaTotalEncuesta : public CRecordSet 
{
public:
    CConsultarCaTotalEncuesta(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarCaTotalEncuesta();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];
    
    long                totalencuestarperiodico;
    long                totalencuestaredocta;
};
#endif CCONSULTARCATOTALENCUESTA
