#include "CCONSULTAFACTURASESIONTEMP.HPP"
CConsultaFacturaSesionTemp::CConsultaFacturaSesionTemp(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=10;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_BIGINT;
	nSqlTipo[2] = SQL_INTEGER;
	nSqlTipo[3] = SQL_VARCHAR;
	nSqlTipo[4] = SQL_VARCHAR;
	nSqlTipo[5] = SQL_BIGINT;
	nSqlTipo[6] = SQL_VARCHAR;
	nSqlTipo[7] = SQL_VARCHAR;
	nSqlTipo[8] = SQL_SMALLINT;
	nSqlTipo[9] = SQL_INTEGER;

    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SBIGINT;
	nCTipo[2] = SQL_C_SLONG;
	nCTipo[3] = SQL_C_CHAR;
	nCTipo[4] = SQL_C_CHAR;
	nCTipo[5] = SQL_C_SBIGINT;
    nCTipo[6] = SQL_C_CHAR;
	nCTipo[7] = SQL_C_CHAR;
	nCTipo[8] = SQL_C_SSHORT;
	nCTipo[9] = SQL_C_SLONG;

    nLongitud[0] = 5;
    nLongitud[1] = 9;
	nLongitud[2] = 5;
	nLongitud[3] = 17;
	nLongitud[4] = 2;
	nLongitud[5] = 9;
	nLongitud[6] = 9;
	nLongitud[7] = 2;
	nLongitud[8] = 3;
	nLongitud[9] = 5;

    pVar[0] = &factura_temp;
    pVar[1] = &sesion_temp;
	pVar[2] = &monto_temp;
	pVar[3] = &banco_temp;
	pVar[4] = &localforaneo_temp;
	pVar[5] = &numerocheque_temp;
	pVar[6] = &codautorizacionbanco_temp;
	pVar[7] = &tipotarjeta_temp;
	pVar[8] = &idu_banco_temp;
	pVar[9] = &cliente_temp;
                                                   
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultaFacturaSesionTemp::~CConsultaFacturaSesionTemp()
{
}
    
void CConsultaFacturaSesionTemp::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
