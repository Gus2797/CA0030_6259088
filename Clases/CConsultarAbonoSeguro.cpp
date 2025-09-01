#include "CCONSULTARABONOSEGURO.HPP"
CConsultarAbonoSeguro::CConsultarAbonoSeguro(C_ODBC *odbc_ext, bool bFlagCommit, const char *select) : CRecordSet(odbc_ext)
{
	this->bFlagCommit = bFlagCommit;
    odbc = odbc_ext;
    nCols=5;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_VARCHAR;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
    nLongitud[1] = 107;
    nLongitud[2] = 107;
    nLongitud[3] = 5;
    nLongitud[4] = 5;
    pVar[0] = &factura;
    pVar[1] = &fecha;
    pVar[2] = &fechavencimiento;
    pVar[3] = &importe;
    pVar[4] = &folioanterior;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarAbonoSeguro::~CConsultarAbonoSeguro()
{
	if( bFlagCommit == true )
    {
		Commit();
	}
}
    
void CConsultarAbonoSeguro::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarAbonoSeguro::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("cacarmov");
    return (retorno);
}
BOOL CConsultarAbonoSeguro::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (factura, fecha, fechavencimiento, importe, folioanterior) VALUES (?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
