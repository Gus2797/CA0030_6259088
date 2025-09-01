#include "CCONSULTARPRECIOSEGUROCLUB.HPP"
CConsultarPrecioSeguroClub::CConsultarPrecioSeguroClub(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=4;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_SMALLINT;
	nSqlTipo[3] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_SSHORT;
	nCTipo[3] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 3;
	nLongitud[3] = 32;

    pVar[0] = &precioseguro;
    pVar[1] = &montoseguro;
    pVar[2] = &maximoseguros;
	pVar[3] = planseguro;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarPrecioSeguroClub::~CConsultarPrecioSeguroClub()
{
    Commit();
}
    
void CConsultarPrecioSeguroClub::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarPrecioSeguroClub::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("casegurossys");
    return (retorno);
}
BOOL CConsultarPrecioSeguroClub::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (precioseguro, montoseguro, maximoseguros, planseguro) VALUES (?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
