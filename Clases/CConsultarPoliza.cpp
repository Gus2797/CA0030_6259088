#include "CCONSULTARPOLIZA.HPP"
CConsultarPoliza::CConsultarPoliza(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_BIGINT;
   
    nCTipo[0] = SQL_C_SBIGINT;
 
    nLongitud[0] = 9;
    pVar[0] = &poliza;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarPoliza::~CConsultarPoliza()
{
    Commit();
}
    
void CConsultarPoliza::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarPoliza::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tdpolizasautoproteccion");
    return (retorno);
}
BOOL CConsultarPoliza::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (poliza) VALUES (?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
