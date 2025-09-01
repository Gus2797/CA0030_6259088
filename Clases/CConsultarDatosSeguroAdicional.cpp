#include "CCONSULTARDATOSSEGUROADICIONAL.HPP"
CConsultarDatosSeguroAdicional::CConsultarDatosSeguroAdicional(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=2;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_SMALLINT;
    nSqlTipo[1] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_SSHORT;
    nCTipo[1] = SQL_C_CHAR;
 
    nLongitud[0] = 3;
    nLongitud[1] = 107;
    pVar[0] = &cantidadseguros;
    pVar[1] = &fecnacadic;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarDatosSeguroAdicional::~CConsultarDatosSeguroAdicional()
{
    Commit();
}
    
void CConsultarDatosSeguroAdicional::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarDatosSeguroAdicional::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpcacarmovseguros");
    return (retorno);
}
BOOL CConsultarDatosSeguroAdicional::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cantidadseguros, fecnacadic) VALUES (?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
