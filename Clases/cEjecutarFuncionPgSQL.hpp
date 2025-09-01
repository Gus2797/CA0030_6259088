// Consulta original solicitada:...
//  select istatus,iRegistrosAfectados,smensaje  from fun_crrespaldarsegurocliente(1346695,14025,'11','1',1027);
    
#ifndef CEJECUTARFUNCIONPGSQL
#define CEJECUTARFUNCIONPGSQL
#include "stdafx.h"
#include <RecordSet.hpp>
class cEjecutarFuncionPgSQL : public CRecordSet 
{
public:
    cEjecutarFuncionPgSQL(C_ODBC *odbc_ext, const char *select=NULL);
    ~cEjecutarFuncionPgSQL();
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
    
    short int           istatus;
    long                iregistrosafectados;
    char                smensaje[20001];
};
#endif CEJECUTARFUNCIONPGSQL
