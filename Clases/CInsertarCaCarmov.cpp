#include "CINSERTARCACARMOV.HPP"
CInsertarCaCarmov::CInsertarCaCarmov(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=11;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_CHAR;
    nSqlTipo[7] = SQL_INTEGER;
    nSqlTipo[8] = SQL_VARCHAR;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_SLONG;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_CHAR;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
    nLongitud[3] = 3;
    nLongitud[4] = 5;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 5;
    nLongitud[8] = 107;
    nLongitud[9] = 5;
    nLongitud[10] = 107;
    pVar[0] =  clave;
    pVar[1] =  tipomovimiento;
    pVar[2] = &tienda;
    pVar[3] = &ciudad;
    pVar[4] = &cliente;
    pVar[5] = &caja;
    pVar[6] =  movtoseguro;
    pVar[7] = &folio;
    pVar[8] = &fecha;
    pVar[9] = &efectuo;
    pVar[10] = &fechanacimiento;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CInsertarCaCarmov::~CInsertarCaCarmov()
{
    Commit();
}
    
void CInsertarCaCarmov::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CInsertarCaCarmov::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("cacarmov");
    return (retorno);
}
BOOL CInsertarCaCarmov::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tipomovimiento, tienda, ciudad, cliente, caja, movtoseguro, folio, fecha, efectuo, fechanacimiento) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
