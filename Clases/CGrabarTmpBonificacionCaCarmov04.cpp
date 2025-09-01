#include "CGRABARTMPBONIFICACIONCACARMOV04.HPP"
CGrabarTmpBonificacionCaCarmov04::CGrabarTmpBonificacionCaCarmov04(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=32;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_CHAR;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_SMALLINT;
    nSqlTipo[7] = SQL_SMALLINT;
    nSqlTipo[8] = SQL_INTEGER;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_CHAR;
    nSqlTipo[11] = SQL_VARCHAR;
    nSqlTipo[12] = SQL_INTEGER;
    nSqlTipo[13] = SQL_INTEGER;
    nSqlTipo[14] = SQL_CHAR;
    nSqlTipo[15] = SQL_INTEGER;
    nSqlTipo[16] = SQL_CHAR;
    nSqlTipo[17] = SQL_CHAR;
    nSqlTipo[18] = SQL_SMALLINT;
    nSqlTipo[19] = SQL_CHAR;
    nSqlTipo[20] = SQL_INTEGER;
    nSqlTipo[21] = SQL_INTEGER;
    nSqlTipo[22] = SQL_BIGINT;
    nSqlTipo[23] = SQL_CHAR;
    nSqlTipo[24] = SQL_SMALLINT;
    nSqlTipo[25] = SQL_INTEGER;
    nSqlTipo[26] = SQL_INTEGER;
    nSqlTipo[27] = SQL_INTEGER;
    nSqlTipo[28] = SQL_INTEGER;
    nSqlTipo[29] = SQL_INTEGER;
    nSqlTipo[30] = SQL_INTEGER;
	nSqlTipo[31] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_CHAR;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_SSHORT;
    nCTipo[8] = SQL_C_SLONG;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_CHAR;
    nCTipo[11] = SQL_C_CHAR;
    nCTipo[12] = SQL_C_SLONG;
    nCTipo[13] = SQL_C_SLONG;
    nCTipo[14] = SQL_C_CHAR;
    nCTipo[15] = SQL_C_SLONG;
    nCTipo[16] = SQL_C_CHAR;
    nCTipo[17] = SQL_C_CHAR;
    nCTipo[18] = SQL_C_SSHORT;
    nCTipo[19] = SQL_C_CHAR;
    nCTipo[20] = SQL_C_SLONG;
    nCTipo[21] = SQL_C_SLONG;
    nCTipo[22] = SQL_C_SBIGINT;
    nCTipo[23] = SQL_C_CHAR;
    nCTipo[24] = SQL_C_SSHORT;
    nCTipo[25] = SQL_C_SLONG;
    nCTipo[26] = SQL_C_SLONG;
    nCTipo[27] = SQL_C_SLONG;
    nCTipo[28] = SQL_C_SLONG;
    nCTipo[29] = SQL_C_SLONG;
    nCTipo[30] = SQL_C_SLONG;
	nCTipo[31] = SQL_C_SSHORT;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 5;
    nLongitud[3] = 3;
    nLongitud[4] = 5;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    nLongitud[8] = 5;
    nLongitud[9] = 5;
    nLongitud[10] = 3;
    nLongitud[11] = 107;
    nLongitud[12] = 5;
    nLongitud[13] = 5;
    nLongitud[14] = 3;
    nLongitud[15] = 5;
    nLongitud[16] = 3;
    nLongitud[17] = 3;
    nLongitud[18] = 3;
    nLongitud[19] = 17;
    nLongitud[20] = 5;
    nLongitud[21] = 5;
    nLongitud[22] = 9;
    nLongitud[23] = 47;
    nLongitud[24] = 3;
    nLongitud[25] = 5;
    nLongitud[26] = 5;
    nLongitud[27] = 5;
    nLongitud[28] = 5;
    nLongitud[29] = 5;
    nLongitud[30] = 5;
	nLongitud[31] = 3;
    pVar[0] =  clave;
    pVar[1] =  tipomovimiento;
    pVar[2] = &importe;
    pVar[3] =  clientelocalizar;
    pVar[4] = &cliente;
    pVar[5] = &tienda;
    pVar[6] = &ciudad;
    pVar[7] = &caja;
    pVar[8] = &factura;
    pVar[9] = &recibo;
    pVar[10] =  ejercicio;
    pVar[11] = &fecha;
    pVar[12] = &vencidoinicial;
    pVar[13] = &minimoinicial;
    pVar[14] =  anexo;
    pVar[15] = &efectuo;
    pVar[16] =  clavelocal;
    pVar[17] =  flagmovtosupervisor;
    pVar[18] = &cajaoriginal;
    pVar[19] =  ipcarteracliente;
    pVar[20] = &importeventa;
    pVar[21] = &comision;
    pVar[22] = &tarjeta;
    pVar[23] =  nombrecliente;
    pVar[24] = &tipoproducto;
    pVar[25] = &minimototal;
    pVar[26] = &saldototal;
    pVar[27] = &vencidototal;
    pVar[28] = &minimototalfinal;
    pVar[29] = &saldototalfinal;
    pVar[30] = &vencidototalfinal;
	pVar[31] = &iva;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpBonificacionCaCarmov04::~CGrabarTmpBonificacionCaCarmov04()
{
    Commit();
}
    
void CGrabarTmpBonificacionCaCarmov04::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpBonificacionCaCarmov04::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpbonificacioncacarmov");
    return (retorno);
}
BOOL CGrabarTmpBonificacionCaCarmov04::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tipomovimiento, importe, clientelocalizar, cliente, tienda, ciudad, caja, factura, recibo, ejercicio, fecha, vencidoinicial, minimoinicial, anexo, efectuo, clavelocal, flagmovtosupervisor, cajaoriginal, ipcarteracliente, importeventa, comision, tarjeta, nombrecliente, tipoproducto, minimototal, saldototal, vencidototal, minimototalfinal, saldototalfinal, vencidototalfinal, iva) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
