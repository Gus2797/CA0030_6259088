#include "COBTENERCONSUMODELINEA.HPP"
CObtenerConsumoDeLinea::CObtenerConsumoDeLinea(C_ODBC *odbc_ext, bool bFlagCommit, const char *select) : CRecordSet(odbc_ext)
{
	this->bFlagCommit = bFlagCommit;
    odbc = odbc_ext;
    nCols=5;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SSHORT;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 3;
    nLongitud[3] = 3;
    nLongitud[4] = 3;
    pVar[0] = &iexcesocompra;
    pVar[1] = &ilimitedecredito;
    pVar[2] = &iflagclientejoven;
    pVar[3] = &iporcentajecompra;
    pVar[4] = &limporteclientejoven;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CObtenerConsumoDeLinea::~CObtenerConsumoDeLinea()
{
	if( bFlagCommit == true )
	{
		Commit();	//Modifico Ricardo Rojo
	}
}
    
void CObtenerConsumoDeLinea::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
