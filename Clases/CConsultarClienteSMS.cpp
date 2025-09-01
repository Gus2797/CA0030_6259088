#include "CCONSULTARCLIENTESMS.HPP"
CConsultarClienteSMS::CConsultarClienteSMS(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_SSHORT;
 
    nLongitud[0] = 3;
    pVar[0] = &sumatoria;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
    nada001 = 0;                                                              
}
    
    
CConsultarClienteSMS::~CConsultarClienteSMS()
{
    Commit();
}
    
void CConsultarClienteSMS::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarClienteSMS::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("");
    return (retorno);
}
BOOL CConsultarClienteSMS::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (sumatoria) VALUES (?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
