// Consulta original solicitada:...
//  select cMensaje from  fun_obtenerdescripcionestatus('1','1')
    
#ifndef CDESCRIPCION
#define CDESCRIPCION
#include "stdafx.h"
#include <RecordSet.hpp>
class CDescripcion : public CRecordSet 
{
public:
    CDescripcion(C_ODBC *odbc_ext, const char *select=NULL);
    ~CDescripcion();
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
    
    char                cmensaje[54];
};
#endif CDESCRIPCION
