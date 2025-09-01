#include "CEJECUTARFUNCIONPGSQL.HPP"
cEjecutarFuncionPgSQL::cEjecutarFuncionPgSQL(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=3;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_SMALLINT;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_LONGVARCHAR;
   
    nCTipo[0] = SQL_C_SSHORT;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_CHAR;
 
    nLongitud[0] = 3;
    nLongitud[1] = 5;
    nLongitud[2] = 20000;
    pVar[0] = &istatus;
    pVar[1] = &iregistrosafectados;
    pVar[2] =  smensaje;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
cEjecutarFuncionPgSQL::~cEjecutarFuncionPgSQL()
{
    //Commit();
}
    
void cEjecutarFuncionPgSQL::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL cEjecutarFuncionPgSQL::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("");
    return (retorno);
}
BOOL cEjecutarFuncionPgSQL::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (istatus, iregistrosafectados, smensaje) VALUES (?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
