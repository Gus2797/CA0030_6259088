#include "CCHECARVIGENCIASEGURO.HPP"
CChecarVigenciaSeguro::CChecarVigenciaSeguro(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=4;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_CHAR;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 107;
    nLongitud[3] = 3;
    pVar[0] =  claveseguro;
    pVar[1] =  statusseguro;
    pVar[2] = &fechavencimiento;
    pVar[3] =  clavenoofrecer;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CChecarVigenciaSeguro::~CChecarVigenciaSeguro()
{
    Commit();
}
    
void CChecarVigenciaSeguro::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CChecarVigenciaSeguro::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crSeguros");
    return (retorno);
}
BOOL CChecarVigenciaSeguro::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (claveseguro, statusseguro, fechavencimiento, clavenoofrecer) VALUES (?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
