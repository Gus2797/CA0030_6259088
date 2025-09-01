#include "CFECHACOPPEL.HPP"
CFechaCoppel::CFechaCoppel(C_ODBC *odbc_ext, bool bFlagCommit, const char *select) : CRecordSet(odbc_ext),bFlagCommit(bFlagCommit)
{
    CFechaCoppel::bFlagCommit = bFlagCommit;
	odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_CHAR;
 
    nLongitud[0] = 107;
    pVar[0] = &fecha;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CFechaCoppel::~CFechaCoppel()
{
	if ( bFlagCommit == true )
	{
		Commit();
	}
}
    
void CFechaCoppel::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CFechaCoppel::prepararInsert()
{
BOOL retorno = FALSE;

    retorno=prepararInsert("gnDominio");
	//retorno=prepararInsert("soclientesupervisar");
    return (retorno);
}
BOOL CFechaCoppel::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (fecha) VALUES (?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
