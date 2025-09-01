#include "CGRABARTMPCRSEGUROS.HPP"
CGrabarTmpCrSeguros::CGrabarTmpCrSeguros(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=7;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_SMALLINT;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SSHORT;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 107;
    nLongitud[3] = 3;
    nLongitud[4] = 3;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    pVar[0] = &cliente;
    pVar[1] = &folio;
    pVar[2] = &fechavencimiento;
    pVar[3] = &cvesinbeneficiarios;
    pVar[4] = &cantidadseguros;
    pVar[5] = &claveconyugal;
    pVar[6] =  claveseguro;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpCrSeguros::~CGrabarTmpCrSeguros()
{
    Commit();
}
    
void CGrabarTmpCrSeguros::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpCrSeguros::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crseguros");
    return (retorno);
}
BOOL CGrabarTmpCrSeguros::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
    sqlTxtInsert.Format("INSERT INTO %s (cliente, folio, fechavencimiento, cvesinbeneficiarios, cantidadseguros, claveconyugal, claveseguro) VALUES (?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
