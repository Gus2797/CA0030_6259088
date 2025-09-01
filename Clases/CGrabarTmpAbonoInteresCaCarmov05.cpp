#include "CGRABARTMPABONOINTERESCACARMOV05.HPP"
CGrabarTmpAbonoInteresCaCarmov05::CGrabarTmpAbonoInteresCaCarmov05(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=39;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_INTEGER;
    nSqlTipo[7] = SQL_INTEGER;
    nSqlTipo[8] = SQL_INTEGER;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_INTEGER;
    nSqlTipo[11] = SQL_INTEGER;
    nSqlTipo[12] = SQL_CHAR;
    nSqlTipo[13] = SQL_CHAR;
    nSqlTipo[14] = SQL_CHAR;
    nSqlTipo[15] = SQL_INTEGER;
    nSqlTipo[16] = SQL_INTEGER;
    nSqlTipo[17] = SQL_CHAR;
    nSqlTipo[18] = SQL_CHAR;
    nSqlTipo[19] = SQL_VARCHAR;
    nSqlTipo[20] = SQL_INTEGER;
    nSqlTipo[21] = SQL_CHAR;
    nSqlTipo[22] = SQL_SMALLINT;
    nSqlTipo[23] = SQL_SMALLINT;
    nSqlTipo[24] = SQL_CHAR;
    nSqlTipo[25] = SQL_INTEGER;
    nSqlTipo[26] = SQL_INTEGER;
    nSqlTipo[27] = SQL_INTEGER;
    nSqlTipo[28] = SQL_BIGINT;
    nSqlTipo[29] = SQL_CHAR;
    nSqlTipo[30] = SQL_SMALLINT;
    nSqlTipo[31] = SQL_INTEGER;
    nSqlTipo[32] = SQL_INTEGER;
    nSqlTipo[33] = SQL_INTEGER;
    nSqlTipo[34] = SQL_INTEGER;
    nSqlTipo[35] = SQL_INTEGER;
    nSqlTipo[36] = SQL_INTEGER;
	nSqlTipo[37] = SQL_SMALLINT;
	nSqlTipo[38] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_SLONG;
    nCTipo[7] = SQL_C_SLONG;
    nCTipo[8] = SQL_C_SLONG;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_SLONG;
    nCTipo[11] = SQL_C_SLONG;
    nCTipo[12] = SQL_C_CHAR;
    nCTipo[13] = SQL_C_CHAR;
    nCTipo[14] = SQL_C_CHAR;
    nCTipo[15] = SQL_C_SLONG;
    nCTipo[16] = SQL_C_SLONG;
    nCTipo[17] = SQL_C_CHAR;
    nCTipo[18] = SQL_C_CHAR;
    nCTipo[19] = SQL_C_CHAR;
    nCTipo[20] = SQL_C_SLONG;
    nCTipo[21] = SQL_C_CHAR;
    nCTipo[22] = SQL_C_SSHORT;
    nCTipo[23] = SQL_C_SSHORT;
    nCTipo[24] = SQL_C_CHAR;
    nCTipo[25] = SQL_C_SLONG;
    nCTipo[26] = SQL_C_SLONG;
    nCTipo[27] = SQL_C_SLONG;
    nCTipo[28] = SQL_C_SBIGINT;
    nCTipo[29] = SQL_C_CHAR;
    nCTipo[30] = SQL_C_SSHORT;
    nCTipo[31] = SQL_C_SLONG;
    nCTipo[32] = SQL_C_SLONG;
    nCTipo[33] = SQL_C_SLONG;
    nCTipo[34] = SQL_C_SLONG;
    nCTipo[35] = SQL_C_SLONG;
    nCTipo[36] = SQL_C_SLONG;
	nCTipo[37] = SQL_C_SSHORT;
	nCTipo[38] = SQL_C_SSHORT;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
    nLongitud[3] = 3;
    nLongitud[4] = 5;
    nLongitud[5] = 3;
    nLongitud[6] = 5;
    nLongitud[7] = 5;
    nLongitud[8] = 5;
    nLongitud[9] = 5;
    nLongitud[10] = 5;
    nLongitud[11] = 5;
    nLongitud[12] = 3;
    nLongitud[13] = 3;
    nLongitud[14] = 3;
    nLongitud[15] = 5;
    nLongitud[16] = 5;
    nLongitud[17] = 3;
    nLongitud[18] = 3;
    nLongitud[19] = 107;
    nLongitud[20] = 5;
    nLongitud[21] = 3;
    nLongitud[22] = 3;
    nLongitud[23] = 3;
    nLongitud[24] = 17;
    nLongitud[25] = 5;
    nLongitud[26] = 5;
    nLongitud[27] = 5;
    nLongitud[28] = 9;
    nLongitud[29] = 47;
    nLongitud[30] = 3;
    nLongitud[31] = 5;
    nLongitud[32] = 5;
    nLongitud[33] = 5;
    nLongitud[34] = 5;
    nLongitud[35] = 5;
    nLongitud[36] = 5;
	nLongitud[37] = 3;
	nLongitud[38] = 3;
    pVar[0] =  clave;
    pVar[1] =  tipomovimiento;
    pVar[2] = &tienda;
    pVar[3] = &ciudad;
    pVar[4] = &cliente;
    pVar[5] = &caja;
    pVar[6] = &recibo;
    pVar[7] = &factura;
    pVar[8] = &importe;
    pVar[9] = &saldoinicial;
    pVar[10] = &saldofinal;
    pVar[11] = &saldocuenta;
    pVar[12] =  clientelocalizar;
    pVar[13] =  flagmovtosupervisor;
    pVar[14] =  clavelocal;
    pVar[15] = &vencidoinicial;
    pVar[16] = &minimoinicial;
    pVar[17] =  anexo;
    pVar[18] =  ejercicio;
    pVar[19] = &fecha;
    pVar[20] = &efectuo;
    pVar[21] =  tiposeguro;
    pVar[22] = &edad;
    pVar[23] = &cajaoriginal;
    pVar[24] =  ipcarteracliente;
    pVar[25] = &importeventa;
    pVar[26] = &comision;
    pVar[27] = &base;
    pVar[28] = &tarjeta;
    pVar[29] =  nombrecliente;
    pVar[30] = &tipoproducto;
    pVar[31] = &minimototal;
    pVar[32] = &saldototal;
    pVar[33] = &vencidototal;
    pVar[34] = &minimototalfinal;
    pVar[35] = &saldototalfinal;
    pVar[36] = &vencidototalfinal;
	pVar[37] = &plazoconvenio;
	pVar[38] = &iva;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpAbonoInteresCaCarmov05::~CGrabarTmpAbonoInteresCaCarmov05()
{
    Commit();
}
    
void CGrabarTmpAbonoInteresCaCarmov05::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpAbonoInteresCaCarmov05::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpabonointerescacarmov");
    return (retorno);
}
BOOL CGrabarTmpAbonoInteresCaCarmov05::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tipomovimiento, tienda, ciudad, cliente, caja, recibo, factura, importe, saldoinicial, saldofinal, saldocuenta, clientelocalizar, flagmovtosupervisor, clavelocal, vencidoinicial, minimoinicial, anexo, ejercicio, fecha, efectuo, tiposeguro, edad, cajaoriginal, ipcarteracliente, importeventa, comision, base, tarjeta, nombrecliente, tipoproducto, minimototal, saldototal, vencidototal, minimototalfinal, saldototalfinal, vencidototalfinal, plazoconvenio, iva) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
