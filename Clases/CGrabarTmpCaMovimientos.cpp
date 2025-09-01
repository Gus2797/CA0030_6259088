#include "CGRABARTMPCAMOVIMIENTOS.HPP"
CGrabarTmpCaMovimientos::CGrabarTmpCaMovimientos(C_ODBC *odbc_ext, bool bFlagCommit, const char *select) : CRecordSet(odbc_ext),bFlagCommit(bFlagCommit)
{
	CGrabarTmpCaMovimientos::bFlagCommit = bFlagCommit;
    odbc = odbc_ext;
    nCols=8;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_VARCHAR;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_VARCHAR;
    nSqlTipo[6] = SQL_SMALLINT;
    nSqlTipo[7] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_CHAR;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
    nLongitud[1] = 107;
    nLongitud[2] = 3;
    nLongitud[3] = 5;
    nLongitud[4] = 5;
    nLongitud[5] = 107;
    nLongitud[6] = 3;
    nLongitud[7] = 5;
    pVar[0] = &cliente;
    pVar[1] = &fechaconvenio;
    pVar[2] = &plazoconvenio;
    pVar[3] = &vencido;
    pVar[4] = &saldofinal;
    pVar[5] = &fechacompra;
    pVar[6] = &caja;
    pVar[7] = &empleado;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpCaMovimientos::~CGrabarTmpCaMovimientos()
{
    if( bFlagCommit == true )
	{
		Commit();	
	}
}
    
void CGrabarTmpCaMovimientos::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpCaMovimientos::prepararInsert()
{
	BOOL retorno = FALSE;
    retorno=prepararInsert("caMovimientos");
    return (retorno);
}
BOOL CGrabarTmpCaMovimientos::prepararInsert(const char *nombreTabla)
{
	BOOL retorno = FALSE;
	int i;
	CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
    sqlTxtInsert.Format("INSERT INTO %s (cliente, fechaconvenio, plazoconvenio, vencido, saldofinal, fechacompra, caja, empleado) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
