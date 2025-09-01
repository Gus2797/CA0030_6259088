#include "CCONSULTARCAENCUESTAEDOCTA.HPP"
CConsultarCaEncuestaEdoCta::CConsultarCaEncuestaEdoCta(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=4;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_VARCHAR;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
    nLongitud[1] = 107;
    nLongitud[2] = 5;
    nLongitud[3] = 5;
    pVar[0] = &status;
    pVar[1] = &fecha;
    pVar[2] = &totaledoscta;
    pVar[3] = &keyx;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarCaEncuestaEdoCta::~CConsultarCaEncuestaEdoCta()
{
    Commit();
}
    
void CConsultarCaEncuestaEdoCta::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarCaEncuestaEdoCta::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("caencuestaedocta");
    return (retorno);
}
BOOL CConsultarCaEncuestaEdoCta::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (status, fecha, totaledoscta, keyx) VALUES (?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
