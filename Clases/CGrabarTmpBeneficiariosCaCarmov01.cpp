#include "CGRABARTMPBENEFICIARIOSCACARMOV01.HPP"
CGrabarTmpBeneficiariosCaCarmov01::CGrabarTmpBeneficiariosCaCarmov01(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=15;
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
    nSqlTipo[14] = SQL_BIGINT;
   
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
    nCTipo[14] = SQL_C_SBIGINT;
 
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
    nLongitud[14] = 9;
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
    pVar[14] = &tarjeta;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpBeneficiariosCaCarmov01::~CGrabarTmpBeneficiariosCaCarmov01()
{
    Commit();
}
    
void CGrabarTmpBeneficiariosCaCarmov01::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpBeneficiariosCaCarmov01::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("cacarmov");
    return (retorno);
}
BOOL CGrabarTmpBeneficiariosCaCarmov01::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tipomovimiento, cliente, importe, recibo, tienda, ciudad, caja, fecha, folio, efectuo, movtoseguro, cajaoriginal, ipcarteracliente, tarjeta) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
