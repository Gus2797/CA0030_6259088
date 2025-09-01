#include "CNOMBRECOLONIACRZONAS.HPP"
CNombreColoniaCrZonas::CNombreColoniaCrZonas(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
 
    nLongitud[0] = 32;
    pVar[0] =  nombrezona;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CNombreColoniaCrZonas::~CNombreColoniaCrZonas()
{
    Commit();
}
    
void CNombreColoniaCrZonas::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CNombreColoniaCrZonas::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crZonas");
    return (retorno);
}
BOOL CNombreColoniaCrZonas::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (nombrezona) VALUES (?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
