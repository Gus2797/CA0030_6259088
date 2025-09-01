#include "CGRABARTMPSEGUROCACARMOV01.HPP"
CGrabarTmpSeguroCaCarmov01::CGrabarTmpSeguroCaCarmov01(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=39;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_CHAR;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_SMALLINT;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_CHAR;
    nSqlTipo[7] = SQL_SMALLINT;
    nSqlTipo[8] = SQL_VARCHAR;
    nSqlTipo[9] = SQL_VARCHAR;
    nSqlTipo[10] = SQL_SMALLINT;
    nSqlTipo[11] = SQL_VARCHAR;
    nSqlTipo[12] = SQL_INTEGER;
    nSqlTipo[13] = SQL_SMALLINT;
    nSqlTipo[14] = SQL_INTEGER;
    nSqlTipo[15] = SQL_INTEGER;
    nSqlTipo[16] = SQL_INTEGER;
    nSqlTipo[17] = SQL_SMALLINT;
    nSqlTipo[18] = SQL_SMALLINT;
    nSqlTipo[19] = SQL_CHAR;
    nSqlTipo[20] = SQL_CHAR;
    nSqlTipo[21] = SQL_INTEGER;
    nSqlTipo[22] = SQL_CHAR;
    nSqlTipo[23] = SQL_CHAR;
    nSqlTipo[24] = SQL_CHAR;
    nSqlTipo[25] = SQL_VARCHAR;
    nSqlTipo[26] = SQL_SMALLINT;
    nSqlTipo[27] = SQL_SMALLINT;
    nSqlTipo[28] = SQL_CHAR;
    nSqlTipo[29] = SQL_INTEGER;
    nSqlTipo[30] = SQL_BIGINT;
    nSqlTipo[31] = SQL_CHAR;
    nSqlTipo[32] = SQL_SMALLINT;
    nSqlTipo[33] = SQL_INTEGER;
    nSqlTipo[34] = SQL_INTEGER;
    nSqlTipo[35] = SQL_INTEGER;
    nSqlTipo[36] = SQL_INTEGER;
    nSqlTipo[37] = SQL_INTEGER;
    nSqlTipo[38] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_SSHORT;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_SSHORT;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_CHAR;
    nCTipo[10] = SQL_C_SSHORT;
    nCTipo[11] = SQL_C_CHAR;
    nCTipo[12] = SQL_C_SLONG;
    nCTipo[13] = SQL_C_SSHORT;
    nCTipo[14] = SQL_C_SLONG;
    nCTipo[15] = SQL_C_SLONG;
    nCTipo[16] = SQL_C_SLONG;
    nCTipo[17] = SQL_C_SSHORT;
    nCTipo[18] = SQL_C_SSHORT;
    nCTipo[19] = SQL_C_CHAR;
    nCTipo[20] = SQL_C_CHAR;
    nCTipo[21] = SQL_C_SLONG;
    nCTipo[22] = SQL_C_CHAR;
    nCTipo[23] = SQL_C_CHAR;
    nCTipo[24] = SQL_C_CHAR;
    nCTipo[25] = SQL_C_CHAR;
    nCTipo[26] = SQL_C_SSHORT;
    nCTipo[27] = SQL_C_SSHORT;
    nCTipo[28] = SQL_C_CHAR;
    nCTipo[29] = SQL_C_SLONG;
    nCTipo[30] = SQL_C_SBIGINT;
    nCTipo[31] = SQL_C_CHAR;
    nCTipo[32] = SQL_C_SSHORT;
    nCTipo[33] = SQL_C_SLONG;
    nCTipo[34] = SQL_C_SLONG;
    nCTipo[35] = SQL_C_SLONG;
    nCTipo[36] = SQL_C_SLONG;
    nCTipo[37] = SQL_C_SLONG;
    nCTipo[38] = SQL_C_SLONG;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
    nLongitud[3] = 5;
    nLongitud[4] = 3;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    nLongitud[8] = 107;
    nLongitud[9] = 107;
    nLongitud[10] = 3;
    nLongitud[11] = 107;
    nLongitud[12] = 5;
    nLongitud[13] = 3;
    nLongitud[14] = 5;
    nLongitud[15] = 5;
    nLongitud[16] = 5;
    nLongitud[17] = 3;
    nLongitud[18] = 3;
    nLongitud[19] = 3;
    nLongitud[20] = 3;
    nLongitud[21] = 5;
    nLongitud[22] = 3;
    nLongitud[23] = 3;
    nLongitud[24] = 3;
    nLongitud[25] = 107;
    nLongitud[26] = 3;
    nLongitud[27] = 3;
    nLongitud[28] = 17;
    nLongitud[29] = 5;
    nLongitud[30] = 9;
    nLongitud[31] = 47;
    nLongitud[32] = 3;
    nLongitud[33] = 5;
    nLongitud[34] = 5;
    nLongitud[35] = 5;
    nLongitud[36] = 5;
    nLongitud[37] = 5;
    nLongitud[38] = 5;
    pVar[0] =  clave;
    pVar[1] =  tipomovimiento;
    pVar[2] =  clavelocal;
    pVar[3] = &cliente;
    pVar[4] = &tienda;
    pVar[5] = &ciudad;
    pVar[6] =  tiposeguro;
    pVar[7] = &caja;
    pVar[8] = &fechavencimiento;
    pVar[9] = &fechavencimientoanterior;
    pVar[10] = &cantidadsegurosanterior;
    pVar[11] = &fecha;
    pVar[12] = &efectuo;
    pVar[13] = &mesesvencidos;
    pVar[14] = &folio;
    pVar[15] = &importe;
    pVar[16] = &recibo;
    pVar[17] = &cantidadseguros;
    pVar[18] = &edad;
    pVar[19] =  sexo;
    pVar[20] =  flagseguroconyugal;
    pVar[21] = &bonificacion;
    pVar[22] =  clientelocalizar;
    pVar[23] =  movtoseguro;
    pVar[24] =  flagmontoseguro;
    pVar[25] = &fechanacimiento;
    pVar[26] = &cantidadmeses;
    pVar[27] = &cajaoriginal;
    pVar[28] =  ipcarteracliente;
    pVar[29] = &importeclub;
    pVar[30] = &tarjeta;
    pVar[31] =  nombrecliente;
    pVar[32] = &tipoproducto;
    pVar[33] = &minimototal;
    pVar[34] = &saldototal;
    pVar[35] = &vencidototal;
    pVar[36] = &minimototalfinal;
    pVar[37] = &saldototalfinal;
    pVar[38] = &vencidototalfinal;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpSeguroCaCarmov01::~CGrabarTmpSeguroCaCarmov01()
{
    Commit();
}
    
void CGrabarTmpSeguroCaCarmov01::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpSeguroCaCarmov01::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpsegurocacarmov");
    return (retorno);
}
BOOL CGrabarTmpSeguroCaCarmov01::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tipomovimiento, clavelocal, cliente, tienda, ciudad, tiposeguro, caja, fechavencimiento, fechavencimientoanterior, cantidadsegurosanterior, fecha, efectuo, mesesvencidos, folio, importe, recibo, cantidadseguros, edad, sexo, flagseguroconyugal, bonificacion, clientelocalizar, movtoseguro, flagmontoseguro, fechanacimiento, cantidadmeses, cajaoriginal, ipcarteracliente, importeclub, tarjeta, nombrecliente, tipoproducto, minimototal, saldototal, vencidototal, minimototalfinal, saldototalfinal, vencidototalfinal) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
