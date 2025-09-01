#include "CCONSULTARZONACLIENTE.HPP"
CConsultarZonaCliente::CConsultarZonaCliente(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=3;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SLONG;
 
    nLongitud[0] = 32;
    nLongitud[1] = 27;
    nLongitud[2] = 5;
    pVar[0] =  nombrezona;
    pVar[1] =  municipio;
    pVar[2] = &codigopostal;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarZonaCliente::~CConsultarZonaCliente()
{
    Commit();
}
    
void CConsultarZonaCliente::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarZonaCliente::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crZonas");
    return (retorno);
}
BOOL CConsultarZonaCliente::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (nombrezona, municipio, codigopostal) VALUES (?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
