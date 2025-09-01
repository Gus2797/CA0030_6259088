#include "CCONSULTARCRSEGUROSCLUB.HPP"
CConsultarCrSegurosClub::CConsultarCrSegurosClub(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=6;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_CHAR;
    nSqlTipo[4] = SQL_CHAR;
    nSqlTipo[5] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_CHAR;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_CHAR;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 5;
    nLongitud[3] = 3;
    nLongitud[4] = 3;
    nLongitud[5] = 107;
    pVar[0] =  claveseguro;
    pVar[1] =  statusseguro;
    pVar[2] = &folio;
    pVar[3] =  tipocancelacion;
    pVar[4] =  clavenoofrecer;
    pVar[5] = &fechavencimiento;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarCrSegurosClub::~CConsultarCrSegurosClub()
{
    Commit();
}
    
void CConsultarCrSegurosClub::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarCrSegurosClub::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crseguros");
    return (retorno);
}
BOOL CConsultarCrSegurosClub::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (claveseguro, statusseguro, folio, tipocancelacion, clavenoofrecer, fechavencimiento) VALUES (?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
