#include "CGRABARTMPABONOCRSEGUROSFIJA.HPP"
CGrabarTmpAbonoCrSegurosFija::CGrabarTmpAbonoCrSegurosFija(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=10;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_SMALLINT;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_CHAR;
    nSqlTipo[7] = SQL_SMALLINT;
    nSqlTipo[8] = SQL_SMALLINT;
    nSqlTipo[9] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SSHORT;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_SSHORT;
    nCTipo[8] = SQL_C_SSHORT;
    nCTipo[9] = SQL_C_SSHORT;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 107;
    nLongitud[3] = 3;
    nLongitud[4] = 3;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    nLongitud[8] = 3;
    nLongitud[9] = 3;
    pVar[0] = &cliente;
    pVar[1] = &folio;
    pVar[2] = &fechavencimiento;
    pVar[3] = &cvesinbeneficiarios;
    pVar[4] = &cantidadseguros;
    pVar[5] = &claveconyugal;
    pVar[6] =  claveseguro;
    pVar[7] = &caja;
    pVar[8] = &sistema;
    pVar[9] = &tienda;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpAbonoCrSegurosFija::~CGrabarTmpAbonoCrSegurosFija()
{
    Commit();
}
    
void CGrabarTmpAbonoCrSegurosFija::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpAbonoCrSegurosFija::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("TmpAbonoCrSegurosFija");
    return (retorno);
}
BOOL CGrabarTmpAbonoCrSegurosFija::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, folio, fechavencimiento, cvesinbeneficiarios, cantidadseguros, claveconyugal, claveseguro, caja, sistema, tienda) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
