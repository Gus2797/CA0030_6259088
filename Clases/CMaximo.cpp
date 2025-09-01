#include "CMAXIMO.HPP"
CMaximo::CMaximo(C_ODBC *odbc_ext, bool bFlagCommit ,const char *select) : CRecordSet(odbc_ext)
{
    this->bFlagCommit = bFlagCommit;
	odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
    pVar[0] = &Total;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CMaximo::~CMaximo()
{
	if( bFlagCommit == true )
	{
		Commit();	//Modifico Ricardo Rojo
	}
}
    
void CMaximo::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CMaximo::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("muinvent");
    return (retorno);
}
BOOL CMaximo::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (Total) VALUES (?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
