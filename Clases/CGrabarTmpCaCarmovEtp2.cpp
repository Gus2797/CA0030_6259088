#include "CGRABARTMPCACARMOVETP2.HPP"
CGrabarTmpCaCarmovEtp2::CGrabarTmpCaCarmovEtp2(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=15;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_CHAR;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_SMALLINT;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_SMALLINT;
    nSqlTipo[7] = SQL_VARCHAR;
    nSqlTipo[8] = SQL_INTEGER;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_INTEGER;
    nSqlTipo[11] = SQL_SMALLINT;
    nSqlTipo[12] = SQL_CHAR;
    nSqlTipo[13] = SQL_INTEGER;
    nSqlTipo[14] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_SSHORT;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_SLONG;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_SLONG;
    nCTipo[11] = SQL_C_SSHORT;
    nCTipo[12] = SQL_C_CHAR;
    nCTipo[13] = SQL_C_SLONG;
    nCTipo[14] = SQL_C_SSHORT;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
    nLongitud[3] = 5;
    nLongitud[4] = 3;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 107;
    nLongitud[8] = 5;
    nLongitud[9] = 5;
    nLongitud[10] = 5;
    nLongitud[11] = 3;
    nLongitud[12] = 17;
    nLongitud[13] = 5;
    nLongitud[14] = 3;
    pVar[0] =  clave;
    pVar[1] =  tipomovimiento;
    pVar[2] =  clavelocal;
    pVar[3] = &cliente;
    pVar[4] = &tienda;
    pVar[5] = &ciudad;
    pVar[6] = &caja;
    pVar[7] = &fecha;
    pVar[8] = &importe;
    pVar[9] = &recibo;
    pVar[10] = &clienteetp;
    pVar[11] = &cajaoriginal;
    pVar[12] =  ipcarteracliente;
    pVar[13] = &efectuo;
    pVar[14] = &digito;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpCaCarmovEtp2::~CGrabarTmpCaCarmovEtp2()
{
    Commit();
}
    
void CGrabarTmpCaCarmovEtp2::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpCaCarmovEtp2::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("cacarmov");
    return (retorno);
}
BOOL CGrabarTmpCaCarmovEtp2::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tipomovimiento, clavelocal, cliente, tienda, ciudad, caja, fecha, importe, recibo, clienteetp, cajaoriginal, ipcarteracliente, efectuo, digito) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
