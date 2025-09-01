#include "CCONSULTARCIUDADFECHATIENDA.HPP"
CConsultarCiudadFechaTienda::CConsultarCiudadFechaTienda(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=2;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
 
    nLongitud[0] = 22;
    nLongitud[1] = 107;
    pVar[0] =  nombreciudad;
    pVar[1] = &fecha;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarCiudadFechaTienda::~CConsultarCiudadFechaTienda()
{
    Commit();
}
    
void CConsultarCiudadFechaTienda::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarCiudadFechaTienda::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("gndominio");
    return (retorno);
}
BOOL CConsultarCiudadFechaTienda::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (nombreciudad, fecha) VALUES (?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
