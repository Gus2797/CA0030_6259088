#include "CCHECARENCUESTA2.HPP"
CChecarEncuesta2::CChecarEncuesta2(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=6;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_VARCHAR;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SLONG;
 
    nLongitud[0] = 107;
    nLongitud[1] = 5;
    nLongitud[2] = 5;
    nLongitud[3] = 3;
    nLongitud[4] = 5;
    nLongitud[5] = 5;
    pVar[0] = &fecha;
    pVar[1] = &total30dias;
    pVar[2] = &totaledoscta;
    pVar[3] = &status;
    pVar[4] = &totalencuestar;
    pVar[5] = &keyx;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CChecarEncuesta2::~CChecarEncuesta2()
{
    Commit();
}
    
void CChecarEncuesta2::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CChecarEncuesta2::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("caencuesta");
    return (retorno);
}
BOOL CChecarEncuesta2::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (fecha, total30dias, totaledoscta, status, totalencuestar, keyx) VALUES (?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
