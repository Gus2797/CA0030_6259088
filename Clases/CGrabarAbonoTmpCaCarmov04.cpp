#include "CGRABARABONOTMPCACARMOV04.HPP"
CGrabarAbonoTmpCaCarmov04::CGrabarAbonoTmpCaCarmov04(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=40;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_SMALLINT;
    nSqlTipo[5] = SQL_CHAR;
    nSqlTipo[6] = SQL_INTEGER;
    nSqlTipo[7] = SQL_VARCHAR;
    nSqlTipo[8] = SQL_INTEGER;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_INTEGER;
    nSqlTipo[11] = SQL_INTEGER;
    nSqlTipo[12] = SQL_CHAR;
    nSqlTipo[13] = SQL_INTEGER;
    nSqlTipo[14] = SQL_INTEGER;
    nSqlTipo[15] = SQL_INTEGER;
    nSqlTipo[16] = SQL_INTEGER;
    nSqlTipo[17] = SQL_INTEGER;
    nSqlTipo[18] = SQL_SMALLINT;
    nSqlTipo[19] = SQL_VARCHAR;
    nSqlTipo[20] = SQL_INTEGER;
    nSqlTipo[21] = SQL_CHAR;
    nSqlTipo[22] = SQL_CHAR;
    nSqlTipo[23] = SQL_SMALLINT;
    nSqlTipo[24] = SQL_CHAR;
    nSqlTipo[25] = SQL_CHAR;
    nSqlTipo[26] = SQL_CHAR;
    nSqlTipo[27] = SQL_INTEGER;
    nSqlTipo[28] = SQL_INTEGER;
    nSqlTipo[29] = SQL_BIGINT;
    nSqlTipo[30] = SQL_CHAR;
    nSqlTipo[31] = SQL_SMALLINT;
    nSqlTipo[32] = SQL_INTEGER;
    nSqlTipo[33] = SQL_INTEGER;
    nSqlTipo[34] = SQL_INTEGER;
    nSqlTipo[35] = SQL_INTEGER;
    nSqlTipo[36] = SQL_INTEGER;
    nSqlTipo[37] = SQL_INTEGER;
	nSqlTipo[38] = SQL_SMALLINT;
	nSqlTipo[39] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SSHORT;
    nCTipo[5] = SQL_C_CHAR;
    nCTipo[6] = SQL_C_SLONG;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_SLONG;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_SLONG;
    nCTipo[11] = SQL_C_SLONG;
    nCTipo[12] = SQL_C_CHAR;
    nCTipo[13] = SQL_C_SLONG;
    nCTipo[14] = SQL_C_SLONG;
    nCTipo[15] = SQL_C_SLONG;
    nCTipo[16] = SQL_C_SLONG;
    nCTipo[17] = SQL_C_SLONG;
    nCTipo[18] = SQL_C_SSHORT;
    nCTipo[19] = SQL_C_CHAR;
    nCTipo[20] = SQL_C_SLONG;
    nCTipo[21] = SQL_C_CHAR;
    nCTipo[22] = SQL_C_CHAR;
    nCTipo[23] = SQL_C_SSHORT;
    nCTipo[24] = SQL_C_CHAR;
    nCTipo[25] = SQL_C_CHAR;
    nCTipo[26] = SQL_C_CHAR;
    nCTipo[27] = SQL_C_SLONG;
    nCTipo[28] = SQL_C_SLONG;
    nCTipo[29] = SQL_C_SBIGINT;
    nCTipo[30] = SQL_C_CHAR;
    nCTipo[31] = SQL_C_SSHORT;
    nCTipo[32] = SQL_C_SLONG;
    nCTipo[33] = SQL_C_SLONG;
    nCTipo[34] = SQL_C_SLONG;
    nCTipo[35] = SQL_C_SLONG;
    nCTipo[36] = SQL_C_SLONG;
    nCTipo[37] = SQL_C_SLONG;
	nCTipo[38] = SQL_C_SSHORT;
	nCTipo[39] = SQL_C_SSHORT;
 
    nLongitud[0] = 3;
    nLongitud[1] = 5;
    nLongitud[2] = 3;
    nLongitud[3] = 3;
    nLongitud[4] = 3;
    nLongitud[5] = 3;
    nLongitud[6] = 5;
    nLongitud[7] = 107;
    nLongitud[8] = 5;
    nLongitud[9] = 5;
    nLongitud[10] = 5;
    nLongitud[11] = 5;
    nLongitud[12] = 3;
    nLongitud[13] = 5;
    nLongitud[14] = 5;
    nLongitud[15] = 5;
    nLongitud[16] = 5;
    nLongitud[17] = 5;
    nLongitud[18] = 3;
    nLongitud[19] = 107;
    nLongitud[20] = 5;
    nLongitud[21] = 3;
    nLongitud[22] = 3;
    nLongitud[23] = 3;
    nLongitud[24] = 17;
    nLongitud[25] = 3;
    nLongitud[26] = 3;
    nLongitud[27] = 5;
    nLongitud[28] = 5;
    nLongitud[29] = 9;
    nLongitud[30] = 47;
    nLongitud[31] = 3;
    nLongitud[32] = 5;
    nLongitud[33] = 5;
    nLongitud[34] = 5;
    nLongitud[35] = 5;
    nLongitud[36] = 5;
    nLongitud[37] = 5;
	nLongitud[38] = 3;
	nLongitud[39] = 3;
    pVar[0] =  clave;
    pVar[1] = &cliente;
    pVar[2] = &tienda;
    pVar[3] = &ciudad;
    pVar[4] = &caja;
    pVar[5] =  ejercicio;
    pVar[6] = &factura;
    pVar[7] = &fecha;
    pVar[8] = &recibo;
    pVar[9] = &vencidoinicial;
    pVar[10] = &minimoinicial;
    pVar[11] = &efectuo;
    pVar[12] =  tipomovimiento;
    pVar[13] = &importe;
    pVar[14] = &saldocuenta;
    pVar[15] = &saldoinicial;
    pVar[16] = &saldofinal;
    pVar[17] = &base;
    pVar[18] = &edad;
    pVar[19] = &fechasaldacon;
    pVar[20] = &importesaldacon;
    pVar[21] =  clientelocalizar;
    pVar[22] =  tiposeguro;
    pVar[23] = &cajaoriginal;
    pVar[24] =  ipcarteracliente;
    pVar[25] =  flagmovtosupervisor;
    pVar[26] =  tipoconvenio;
    pVar[27] = &importeventa;
    pVar[28] = &comision;
    pVar[29] = &tarjeta;
    pVar[30] =  nombrecliente;
    pVar[31] = &tipoproducto;
    pVar[32] = &minimototal;
    pVar[33] = &saldototal;
    pVar[34] = &vencidototal;
    pVar[35] = &minimototalfinal;
    pVar[36] = &saldototalfinal;
    pVar[37] = &vencidototalfinal;
	pVar[38] = &plazoconvenio;
	pVar[39] = &iva;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarAbonoTmpCaCarmov04::~CGrabarAbonoTmpCaCarmov04()
{
    Commit();
}
    
void CGrabarAbonoTmpCaCarmov04::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarAbonoTmpCaCarmov04::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpabonocacarmov");
    return (retorno);
}
BOOL CGrabarAbonoTmpCaCarmov04::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, cliente, tienda, ciudad, caja, ejercicio, factura, fecha, recibo, vencidoinicial, minimoinicial, efectuo, tipomovimiento, importe, saldocuenta, saldoinicial, saldofinal, base, edad, fechasaldacon, importesaldacon, clientelocalizar, tiposeguro, cajaoriginal, ipcarteracliente, flagmovtosupervisor, tipoconvenio, importeventa, comision, tarjeta, nombrecliente, tipoproducto, minimototal, saldototal, vencidototal, minimototalfinal, saldototalfinal, vencidototalfinal, plazoconvenio, iva) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
