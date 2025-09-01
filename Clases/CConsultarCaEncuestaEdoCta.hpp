#ifndef CCONSULTARCAENCUESTAEDOCTA
#define CCONSULTARCAENCUESTAEDOCTA
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarCaEncuestaEdoCta : public CRecordSet 
{
public:
    CConsultarCaEncuestaEdoCta(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarCaEncuestaEdoCta();
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
    
    long                status;
    SqlTimeStamp        fecha;
    long                totaledoscta;
    long                keyx;
};
#endif CCONSULTARCAENCUESTAEDOCTA
