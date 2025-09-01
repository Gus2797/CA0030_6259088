#include "CCONSULTARABONOSEGURO2.HPP"
CConsultarAbonoSeguro2::CConsultarAbonoSeguro2(C_ODBC *odbc_ext, bool bFlagCommit, const char *select) : CRecordSet(odbc_ext)
{
	this->bFlagCommit = bFlagCommit;
    odbc = odbc_ext;
    nCols=7;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_VARCHAR;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 107;
    nLongitud[2] = 107;
    nLongitud[3] = 5;
    nLongitud[4] = 5;
    nLongitud[5] = 3;
    nLongitud[6] = 107;
    pVar[0] = &factura;
    pVar[1] = &fecha;
    pVar[2] = &fechavencimiento;
    pVar[3] = &importe;
    pVar[4] = &folioanterior;
    pVar[5] = &cantidadmeses;
    pVar[6] = &fechanacimiento;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarAbonoSeguro2::~CConsultarAbonoSeguro2()
{
	if( bFlagCommit == true )
    {
		Commit();
	}
}
    
void CConsultarAbonoSeguro2::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarAbonoSeguro2::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("cacarmov");
    return (retorno);
}
BOOL CConsultarAbonoSeguro2::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (factura, fecha, fechavencimiento, importe, folioanterior, cantidadmeses, fechanacimiento) VALUES (?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
