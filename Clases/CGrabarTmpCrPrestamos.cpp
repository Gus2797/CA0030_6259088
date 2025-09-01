#include "CGRABARTMPCRPRESTAMOS.HPP"
CGrabarTmpCrPrestamos::CGrabarTmpCrPrestamos(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=7;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_SMALLINT;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_INTEGER;
    nSqlTipo[6] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SSHORT;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SLONG;
    nCTipo[6] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 3;
    nLongitud[2] = 5;
    nLongitud[3] = 5;
    nLongitud[4] = 5;
    nLongitud[5] = 5;
    nLongitud[6] = 107;
    pVar[0] = &cliente;
    pVar[1] = &tienda;
    pVar[2] = &factura;
    pVar[3] = &interesadicional;
    pVar[4] = &saldoactual;
    pVar[5] = &importeultimomovimiento;
    pVar[6] = &fechaultimomovimiento;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpCrPrestamos::~CGrabarTmpCrPrestamos()
{
    Commit();
}
    
void CGrabarTmpCrPrestamos::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpCrPrestamos::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("CrPrestamos");
    return (retorno);
}
BOOL CGrabarTmpCrPrestamos::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, tienda, factura, interesadicional, saldoactual, importeultimomovimiento, fechaultimomovimiento) VALUES (?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
