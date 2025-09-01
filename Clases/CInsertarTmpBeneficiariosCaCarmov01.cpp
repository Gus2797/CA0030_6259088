#include "CINSERTARTMPBENEFICIARIOSCACARMOV01.HPP"
CInsertarTmpBeneficiariosCaCarmov01::CInsertarTmpBeneficiariosCaCarmov01(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=24;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_SMALLINT;
    nSqlTipo[7] = SQL_SMALLINT;
    nSqlTipo[8] = SQL_VARCHAR;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_INTEGER;
    nSqlTipo[11] = SQL_CHAR;
    nSqlTipo[12] = SQL_SMALLINT;
    nSqlTipo[13] = SQL_CHAR;
    nSqlTipo[14] = SQL_INTEGER;
    nSqlTipo[15] = SQL_BIGINT;
    nSqlTipo[16] = SQL_CHAR;
    nSqlTipo[17] = SQL_SMALLINT;
    nSqlTipo[18] = SQL_INTEGER;
    nSqlTipo[19] = SQL_INTEGER;
    nSqlTipo[20] = SQL_INTEGER;
    nSqlTipo[21] = SQL_INTEGER;
    nSqlTipo[22] = SQL_INTEGER;
    nSqlTipo[23] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_SSHORT;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_SLONG;
    nCTipo[11] = SQL_C_CHAR;
    nCTipo[12] = SQL_C_SSHORT;
    nCTipo[13] = SQL_C_CHAR;
    nCTipo[14] = SQL_C_SLONG;
    nCTipo[15] = SQL_C_SBIGINT;
    nCTipo[16] = SQL_C_CHAR;
    nCTipo[17] = SQL_C_SSHORT;
    nCTipo[18] = SQL_C_SLONG;
    nCTipo[19] = SQL_C_SLONG;
    nCTipo[20] = SQL_C_SLONG;
    nCTipo[21] = SQL_C_SLONG;
    nCTipo[22] = SQL_C_SLONG;
    nCTipo[23] = SQL_C_SLONG;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 5;
    nLongitud[3] = 5;
    nLongitud[4] = 5;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    nLongitud[8] = 107;
    nLongitud[9] = 5;
    nLongitud[10] = 5;
    nLongitud[11] = 3;
    nLongitud[12] = 3;
    nLongitud[13] = 17;
    nLongitud[14] = 5;
    nLongitud[15] = 9;
    nLongitud[16] = 47;
    nLongitud[17] = 3;
    nLongitud[18] = 5;
    nLongitud[19] = 5;
    nLongitud[20] = 5;
    nLongitud[21] = 5;
    nLongitud[22] = 5;
    nLongitud[23] = 5;
    pVar[0] =  clave;
    pVar[1] =  tipomovimiento;
    pVar[2] = &cliente;
    pVar[3] = &importe;
    pVar[4] = &recibo;
    pVar[5] = &tienda;
    pVar[6] = &ciudad;
    pVar[7] = &caja;
    pVar[8] = &fecha;
    pVar[9] = &folio;
    pVar[10] = &efectuo;
    pVar[11] =  movtoseguro;
    pVar[12] = &cajaoriginal;
    pVar[13] =  ipcarteracliente;
    pVar[14] = &bonificacion;
    pVar[15] = &tarjeta;
    pVar[16] =  nombrecliente;
    pVar[17] = &tipoproducto;
    pVar[18] = &minimototal;
    pVar[19] = &saldototal;
    pVar[20] = &vencidototal;
    pVar[21] = &minimototalfinal;
    pVar[22] = &saldototalfinal;
    pVar[23] = &vencidototalfinal;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CInsertarTmpBeneficiariosCaCarmov01::~CInsertarTmpBeneficiariosCaCarmov01()
{
    Commit();
}
    
void CInsertarTmpBeneficiariosCaCarmov01::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CInsertarTmpBeneficiariosCaCarmov01::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpbeneficiarioscacarmov");
    return (retorno);
}
BOOL CInsertarTmpBeneficiariosCaCarmov01::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tipomovimiento, cliente, importe, recibo, tienda, ciudad, caja, fecha, folio, efectuo, movtoseguro, cajaoriginal, ipcarteracliente, bonificacion, tarjeta, nombrecliente, tipoproducto, minimototal, saldototal, vencidototal, minimototalfinal, saldototalfinal, vencidototalfinal) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
