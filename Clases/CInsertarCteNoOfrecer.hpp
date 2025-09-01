// Consulta original solicitada:...
//  select respuesta from fun_grabar_tmp_ctesnoofrecerclub(206580649)
    
#ifndef CINSERTARCTENOOFRECER
#define CINSERTARCTENOOFRECER
#include "stdafx.h"
#include <RecordSet.hpp>
class CInsertarCteNoOfrecer : public CRecordSet 
{
public:
    CInsertarCteNoOfrecer(C_ODBC *odbc_ext, const char *select=NULL);
    ~CInsertarCteNoOfrecer();
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
    
    long                respuesta;
};
#endif CINSERTARCTENOOFRECER
