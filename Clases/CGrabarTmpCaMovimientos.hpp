#ifndef CGRABARTMPCAMOVIMIENTOS
#define CGRABARTMPCAMOVIMIENTOS
#include "stdafx.h"
#include <RecordSet.HPP>
class CGrabarTmpCaMovimientos : public CRecordSet 
{
public:
    CGrabarTmpCaMovimientos(C_ODBC *odbc_ext, bool bFlagCommit = true, const char *select=NULL);
    ~CGrabarTmpCaMovimientos();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
	bool				bFlagCommit;
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[9];
    int nCTipo[9];
    long nLongitud[9];
    long nLongResp[9];
    void *pVar[9];
    
    long                cliente;
    SqlTimeStamp        fechaconvenio;
    short int           plazoconvenio;
    long                vencido;
    long                saldofinal;
    SqlTimeStamp        fechacompra;
    short int           caja;
    long                empleado;
};
#endif CGRABARTMPCAMOVIMIENTOS
