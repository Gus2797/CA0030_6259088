#include "CGRABARTMPABONOCRPRESTAMOSFIJA.HPP"
CGrabarTmpAbonoCrPrestamosFija::CGrabarTmpAbonoCrPrestamosFija(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=9;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_SMALLINT;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_INTEGER;
    nSqlTipo[6] = SQL_VARCHAR;
    nSqlTipo[7] = SQL_SMALLINT;
    nSqlTipo[8] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SSHORT;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SLONG;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_SSHORT;
    nCTipo[8] = SQL_C_SSHORT;
 
    nLongitud[0] = 5;
    nLongitud[1] = 3;
    nLongitud[2] = 5;
    nLongitud[3] = 5;
    nLongitud[4] = 5;
    nLongitud[5] = 5;
    nLongitud[6] = 107;
    nLongitud[7] = 3;
    nLongitud[8] = 3;
    pVar[0] = &cliente;
    pVar[1] = &tienda;
    pVar[2] = &factura;
    pVar[3] = &interesadicional;
    pVar[4] = &saldoactual;
    pVar[5] = &importeultimomovimiento;
    pVar[6] = &fechaultimomovimiento;
    pVar[7] = &caja;
    pVar[8] = &sistema;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpAbonoCrPrestamosFija::~CGrabarTmpAbonoCrPrestamosFija()
{
    Commit();
}
    
void CGrabarTmpAbonoCrPrestamosFija::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpAbonoCrPrestamosFija::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("TmpAbonoCrPrestamosFija");
    return (retorno);
}
BOOL CGrabarTmpAbonoCrPrestamosFija::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, tienda, factura, interesadicional, saldoactual, importeultimomovimiento, fechaultimomovimiento, caja, sistema) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
