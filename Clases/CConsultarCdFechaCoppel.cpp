#include "CCONSULTARCDFECHACOPPEL.HPP"
CConsultarCdFechaCoppel::CConsultarCdFechaCoppel(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=3;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_SMALLINT;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_SSHORT;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
 
    nLongitud[0] = 3;
    nLongitud[1] = 22;
    nLongitud[2] = 107;
    pVar[0] = &tienda;
    pVar[1] =  nombreciudad;
    pVar[2] = &fecha;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarCdFechaCoppel::~CConsultarCdFechaCoppel()
{
    Commit();
}
    
void CConsultarCdFechaCoppel::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarCdFechaCoppel::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("gndominio");
    return (retorno);
}
BOOL CConsultarCdFechaCoppel::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (tienda, nombreciudad, fecha) VALUES (?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
