#include "CGRABARTMPCRCMUEBLES.HPP"
CGrabarTmpCrCmuebles::CGrabarTmpCrCmuebles(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=5;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 5;
    nLongitud[3] = 5;
    nLongitud[4] = 107;
    pVar[0] = &cliente;
    pVar[1] = &factura;
    pVar[2] = &saldo;
    pVar[3] = &interesadicional;
    pVar[4] = &fechaultimomovimiento;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpCrCmuebles::~CGrabarTmpCrCmuebles()
{
    Commit();
}
    
void CGrabarTmpCrCmuebles::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpCrCmuebles::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("CrCmuebles");
    return (retorno);
}
BOOL CGrabarTmpCrCmuebles::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, factura, saldo, interesadicional, fechaultimomovimiento) VALUES (?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
