#include "CCONSULTARCATOTALENCUESTA.HPP"
CConsultarCaTotalEncuesta::CConsultarCaTotalEncuesta(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=2;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    pVar[0] = &totalencuestarperiodico;
    pVar[1] = &totalencuestaredocta;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarCaTotalEncuesta::~CConsultarCaTotalEncuesta()
{
    Commit();
}
    
void CConsultarCaTotalEncuesta::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarCaTotalEncuesta::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("catotalencuestar");
    return (retorno);
}
BOOL CConsultarCaTotalEncuesta::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (totalencuestarperiodico, totalencuestaredocta) VALUES (?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
