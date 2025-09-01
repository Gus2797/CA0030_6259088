#include "CGRABARTMPSEGUROAUTOCACARMOV01.HPP"
CGrabarTmpSeguroAutoCaCarmov01::CGrabarTmpSeguroAutoCaCarmov01(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=36;
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
    nSqlTipo[11] = SQL_CHAR;
    nSqlTipo[12] = SQL_SMALLINT;
    nSqlTipo[13] = SQL_VARCHAR;
    nSqlTipo[14] = SQL_VARCHAR;
    nSqlTipo[15] = SQL_VARCHAR;
    nSqlTipo[16] = SQL_VARCHAR;
    nSqlTipo[17] = SQL_INTEGER;
    nSqlTipo[18] = SQL_CHAR;
    nSqlTipo[19] = SQL_VARCHAR;
    nSqlTipo[20] = SQL_INTEGER;
    nSqlTipo[21] = SQL_INTEGER;
    nSqlTipo[22] = SQL_VARCHAR;
    nSqlTipo[23] = SQL_CHAR;
    nSqlTipo[24] = SQL_CHAR;
    nSqlTipo[25] = SQL_CHAR;
    nSqlTipo[26] = SQL_BIGINT;
    nSqlTipo[27] = SQL_CHAR;
    nSqlTipo[28] = SQL_SMALLINT;
    nSqlTipo[29] = SQL_INTEGER;
    nSqlTipo[30] = SQL_INTEGER;
    nSqlTipo[31] = SQL_INTEGER;
    nSqlTipo[32] = SQL_INTEGER;
    nSqlTipo[33] = SQL_INTEGER;
    nSqlTipo[34] = SQL_INTEGER;
    nSqlTipo[35] = SQL_INTEGER;
   
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
    nCTipo[11] = SQL_C_CHAR;
    nCTipo[12] = SQL_C_SSHORT;
    nCTipo[13] = SQL_C_CHAR;
    nCTipo[14] = SQL_C_CHAR;
    nCTipo[15] = SQL_C_CHAR;
    nCTipo[16] = SQL_C_CHAR;
    nCTipo[17] = SQL_C_SLONG;
    nCTipo[18] = SQL_C_CHAR;
    nCTipo[19] = SQL_C_CHAR;
    nCTipo[20] = SQL_C_SLONG;
    nCTipo[21] = SQL_C_SLONG;
    nCTipo[22] = SQL_C_CHAR;
    nCTipo[23] = SQL_C_CHAR;
    nCTipo[24] = SQL_C_CHAR;
    nCTipo[25] = SQL_C_CHAR;
    nCTipo[26] = SQL_C_SBIGINT;
    nCTipo[27] = SQL_C_CHAR;
    nCTipo[28] = SQL_C_SSHORT;
    nCTipo[29] = SQL_C_SLONG;
    nCTipo[30] = SQL_C_SLONG;
    nCTipo[31] = SQL_C_SLONG;
    nCTipo[32] = SQL_C_SLONG;
    nCTipo[33] = SQL_C_SLONG;
    nCTipo[34] = SQL_C_SLONG;
    nCTipo[35] = SQL_C_SLONG;
 
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
    nLongitud[11] = 3;
    nLongitud[12] = 3;
    nLongitud[13] = 107;
    nLongitud[14] = 107;
    nLongitud[15] = 107;
    nLongitud[16] = 107;
    nLongitud[17] = 5;
    nLongitud[18] = 3;
    nLongitud[19] = 107;
    nLongitud[20] = 5;
    nLongitud[21] = 5;
    nLongitud[22] = 107;
    nLongitud[23] = 3;
    nLongitud[24] = 3;
    nLongitud[25] = 17;
    nLongitud[26] = 9;
    nLongitud[27] = 47;
    nLongitud[28] = 3;
    nLongitud[29] = 5;
    nLongitud[30] = 5;
    nLongitud[31] = 5;
    nLongitud[32] = 5;
    nLongitud[33] = 5;
    nLongitud[34] = 5;
    nLongitud[35] = 5;
    pVar[0] =  clave;
    pVar[1] =  tipomovimiento;
    pVar[2] = &tienda;
    pVar[3] = &ciudad;
    pVar[4] = &cliente;
    pVar[5] = &caja;
    pVar[6] = &recibo;
    pVar[7] = &factura;
    pVar[8] = &folioanterior;
    pVar[9] = &importe;
    pVar[10] = &saldoinicial;
    pVar[11] =  tiposeguro;
    pVar[12] = &cantidadmeses;
    pVar[13] = &fecha;
    pVar[14] = &fechavencimiento;
    pVar[15] = &fechavencimientoanterior;
    pVar[16] = &fechanacimiento;
    pVar[17] = &efectuo;
    pVar[18] =  tipovehiculo;
    pVar[19] = &fechaactivacioncancelar;
    pVar[20] = &polizaanteriorcancelar;
    pVar[21] = &importeventacancelar;
    pVar[22] = &fechaventacancelar;
    pVar[23] =  clavelocal;
    pVar[24] =  clientelocalizar;
    pVar[25] =  ipcarteracliente;
    pVar[26] = &tarjeta;
    pVar[27] =  nombrecliente;
    pVar[28] = &tipoproducto;
    pVar[29] = &minimototal;
    pVar[30] = &saldototal;
    pVar[31] = &vencidototal;
    pVar[32] = &minimototalfinal;
    pVar[33] = &saldototalfinal;
    pVar[34] = &vencidototalfinal;
    pVar[35] = &idpoliza;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpSeguroAutoCaCarmov01::~CGrabarTmpSeguroAutoCaCarmov01()
{
    Commit();
}
    
void CGrabarTmpSeguroAutoCaCarmov01::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpSeguroAutoCaCarmov01::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpseguroautocacarmov");
    return (retorno);
}
BOOL CGrabarTmpSeguroAutoCaCarmov01::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tipomovimiento, tienda, ciudad, cliente, caja, recibo, factura, folioanterior, importe, saldoinicial, tiposeguro, cantidadmeses, fecha, fechavencimiento, fechavencimientoanterior, fechanacimiento, efectuo, tipovehiculo, fechaactivacioncancelar, polizaanteriorcancelar, importeventacancelar, fechaventacancelar, clavelocal, clientelocalizar, ipcarteracliente, tarjeta, nombrecliente, tipoproducto, minimototal, saldototal, vencidototal, minimototalfinal, saldototalfinal, vencidototalfinal, idpoliza) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
