#include "CGRABARTMPCONVENIOCACARMOV03.HPP"
CGrabarTmpConvenioCaCarmov03::CGrabarTmpConvenioCaCarmov03(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=37;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_SMALLINT;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_INTEGER;
    nSqlTipo[7] = SQL_CHAR;
    nSqlTipo[8] = SQL_VARCHAR;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_INTEGER;
    nSqlTipo[11] = SQL_INTEGER;
    nSqlTipo[12] = SQL_CHAR;
    nSqlTipo[13] = SQL_INTEGER;
    nSqlTipo[14] = SQL_CHAR;
    nSqlTipo[15] = SQL_INTEGER;
    nSqlTipo[16] = SQL_INTEGER;
    nSqlTipo[17] = SQL_INTEGER;
    nSqlTipo[18] = SQL_CHAR;
    nSqlTipo[19] = SQL_SMALLINT;
    nSqlTipo[20] = SQL_INTEGER;
    nSqlTipo[21] = SQL_CHAR;
    nSqlTipo[22] = SQL_CHAR;
    nSqlTipo[23] = SQL_CHAR;
    nSqlTipo[24] = SQL_CHAR;
    nSqlTipo[25] = SQL_SMALLINT;
    nSqlTipo[26] = SQL_CHAR;
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
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SSHORT;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_SLONG;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_SLONG;
    nCTipo[11] = SQL_C_SLONG;
    nCTipo[12] = SQL_C_CHAR;
    nCTipo[13] = SQL_C_SLONG;
    nCTipo[14] = SQL_C_CHAR;
    nCTipo[15] = SQL_C_SLONG;
    nCTipo[16] = SQL_C_SLONG;
    nCTipo[17] = SQL_C_SLONG;
    nCTipo[18] = SQL_C_CHAR;
    nCTipo[19] = SQL_C_SSHORT;
    nCTipo[20] = SQL_C_SLONG;
    nCTipo[21] = SQL_C_CHAR;
    nCTipo[22] = SQL_C_CHAR;
    nCTipo[23] = SQL_C_CHAR;
    nCTipo[24] = SQL_C_CHAR;
    nCTipo[25] = SQL_C_SSHORT;
    nCTipo[26] = SQL_C_CHAR;
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
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 5;
    nLongitud[3] = 3;
    nLongitud[4] = 3;
    nLongitud[5] = 3;
    nLongitud[6] = 5;
    nLongitud[7] = 3;
    nLongitud[8] = 107;
    nLongitud[9] = 5;
    nLongitud[10] = 5;
    nLongitud[11] = 5;
    nLongitud[12] = 3;
    nLongitud[13] = 5;
    nLongitud[14] = 3;
    nLongitud[15] = 5;
    nLongitud[16] = 5;
    nLongitud[17] = 5;
    nLongitud[18] = 3;
    nLongitud[19] = 3;
    nLongitud[20] = 5;
    nLongitud[21] = 3;
    nLongitud[22] = 3;
    nLongitud[23] = 3;
    nLongitud[24] = 3;
    nLongitud[25] = 3;
    nLongitud[26] = 17;
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
    pVar[0] =  clave;
    pVar[1] =  tipomovimiento;
    pVar[2] = &cliente;
    pVar[3] = &tienda;
    pVar[4] = &ciudad;
    pVar[5] = &caja;
    pVar[6] = &factura;
    pVar[7] =  ejercicio;
    pVar[8] = &fecha;
    pVar[9] = &recibo;
    pVar[10] = &vencidoinicial;
    pVar[11] = &minimoinicial;
    pVar[12] =  anexo;
    pVar[13] = &efectuo;
    pVar[14] =  clavelocal;
    pVar[15] = &saldoinicial;
    pVar[16] = &saldofinal;
    pVar[17] = &saldocuenta;
    pVar[18] =  flagmovtosupervisor;
    pVar[19] = &plazoconvenio;
    pVar[20] = &importe;
    pVar[21] =  tipoconvenio;
    pVar[22] =  subtipoconvenio;
    pVar[23] =  clientelocalizar;
    pVar[24] =  tiposeguro;
    pVar[25] = &cajaoriginal;
    pVar[26] =  ipcarteracliente;
    pVar[27] = &importeventa;
    pVar[28] = &tarjeta;
    pVar[29] =  nombrecliente;
    pVar[30] = &tipoproducto;
    pVar[31] = &minimototal;
    pVar[32] = &saldototal;
    pVar[33] = &vencidototal;
    pVar[34] = &minimototalfinal;
    pVar[35] = &saldototalfinal;
    pVar[36] = &vencidototalfinal;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpConvenioCaCarmov03::~CGrabarTmpConvenioCaCarmov03()
{
    Commit();
}
    
void CGrabarTmpConvenioCaCarmov03::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpConvenioCaCarmov03::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpconveniocacarmov");
    return (retorno);
}
BOOL CGrabarTmpConvenioCaCarmov03::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tipomovimiento, cliente, tienda, ciudad, caja, factura, ejercicio, fecha, recibo, vencidoinicial, minimoinicial, anexo, efectuo, clavelocal, saldoinicial, saldofinal, saldocuenta, flagmovtosupervisor, plazoconvenio, importe, tipoconvenio, subtipoconvenio, clientelocalizar, tiposeguro, cajaoriginal, ipcarteracliente, importeventa, tarjeta, nombrecliente, tipoproducto, minimototal, saldototal, vencidototal, minimototalfinal, saldototalfinal, vencidototalfinal) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
