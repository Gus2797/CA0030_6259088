#ifndef CBUSCARCLIENTEENCUESTADO
#define CBUSCARCLIENTEENCUESTADO
#include "stdafx.h"
#include <RecordSet.HPP>
class CBuscarClienteEncuestado : public CRecordSet 
{
public:
    CBuscarClienteEncuestado(C_ODBC *odbc_ext, const char *select=NULL);
    ~CBuscarClienteEncuestado();
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
    
    char                tipo[3];
    long                cliente;
    SqlTimeStamp        fecha;
};
#endif CBUSCARCLIENTEENCUESTADO
