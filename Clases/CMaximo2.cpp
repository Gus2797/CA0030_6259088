#include "CMAXIMO2.HPP"
CMaximo2::CMaximo2(C_ODBC *odbc_ext, bool bFlagCommit ,const char *select) : CRecordSet(odbc_ext)
{
    this->bFlagCommit = bFlagCommit;
	odbc = odbc_ext;
    nCols=2;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
	nSqlTipo[1] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
	nCTipo[1] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
	nLongitud[1] = 5;
    pVar[0] = &Total;
	pVar[1] = &Total2;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CMaximo2::~CMaximo2()
{
	if( bFlagCommit == true )
	{
		Commit();	//Modifico Ricardo Rojo
	}
}
    
void CMaximo2::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CMaximo2::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("muinvent");
    return (retorno);
}
BOOL CMaximo2::prepararInsert(const char *nombreTabla)
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
