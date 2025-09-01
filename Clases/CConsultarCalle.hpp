#ifndef CCONSULTARCALLE
#define CCONSULTARCALLE
//#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarCalle : public CRecordSet 
{
public:
    CConsultarCalle(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarCalle();
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
    
    long                calle;
    char                nombrecalle[32];
};
#endif CCONSULTARCALLE
