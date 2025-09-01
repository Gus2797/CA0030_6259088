#include "COBTENERDATOSCACARMOVTEMPORAL.HPP"
CObtenerDatosCacarmovTemporal::CObtenerDatosCacarmovTemporal(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=8;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_SMALLINT;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_BIGINT;
    nSqlTipo[4] = SQL_SMALLINT;
    nSqlTipo[5] = SQL_INTEGER;
	nSqlTipo[6] = SQL_INTEGER;
	nSqlTipo[7] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SSHORT;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SBIGINT;
    nCTipo[4] = SQL_C_SSHORT;
    nCTipo[5] = SQL_C_SLONG;
	nCTipo[6] = SQL_C_SLONG;
	nCTipo[7] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 3;
    nLongitud[2] = 107;
    nLongitud[3] = 9;
    nLongitud[4] = 3;
    nLongitud[5] = 5;
	nLongitud[6] = 5;
	nLongitud[7] = 107;
    pVar[0] = &importe;
    pVar[1] = &cantidadmeses;
    pVar[2] = &fechavencimiento;
    pVar[3] = &fol_sucursal;
    pVar[4] = &cantidadseguros;
    pVar[5] = &folio;
	pVar[6] = &factura;
	pVar[7] = &fechaabonoajuste;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CObtenerDatosCacarmovTemporal::~CObtenerDatosCacarmovTemporal()
{
}
    
void CObtenerDatosCacarmovTemporal::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
