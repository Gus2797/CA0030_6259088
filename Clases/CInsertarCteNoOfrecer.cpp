#include "CINSERTARCTENOOFRECER.HPP"
CInsertarCteNoOfrecer::CInsertarCteNoOfrecer(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
    pVar[0] = &respuesta;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CInsertarCteNoOfrecer::~CInsertarCteNoOfrecer()
{
    Commit();
}
    
void CInsertarCteNoOfrecer::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CInsertarCteNoOfrecer::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("");
    return (retorno);
}
BOOL CInsertarCteNoOfrecer::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (respuesta) VALUES (?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
