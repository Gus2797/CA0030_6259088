#include "CCONSULTARCALLE.HPP"
CConsultarCalle::CConsultarCalle(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=2;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 32;
    pVar[0] = &calle;
    pVar[1] =  nombrecalle;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarCalle::~CConsultarCalle()
{
    Commit();
}
    
void CConsultarCalle::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarCalle::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crcalles");
    return (retorno);
}
BOOL CConsultarCalle::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                           
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (calle, nombrecalle) VALUES (?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
