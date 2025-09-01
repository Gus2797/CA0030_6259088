#include "CACTUALIZAREMPLEADOMOVSMS.HPP"
CActualizarEmpleadoMovSMS::CActualizarEmpleadoMovSMS(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=0;
    odbcRet=TRUE;
    flagInsertar = 0;
   
 
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CActualizarEmpleadoMovSMS::~CActualizarEmpleadoMovSMS()
{
    Commit();
}
    
void CActualizarEmpleadoMovSMS::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CActualizarEmpleadoMovSMS::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("");
    return (retorno);
}
BOOL CActualizarEmpleadoMovSMS::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s () VALUES ()",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
