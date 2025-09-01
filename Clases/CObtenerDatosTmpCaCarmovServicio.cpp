#include "COBTENERDATOSTMPCACARMOVSERVICIO.HPP"
CObtenerDatosTmpCaCarmovServicio::CObtenerDatosTmpCaCarmovServicio(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=17;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_SMALLINT;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_INTEGER;
    nSqlTipo[6] = SQL_INTEGER;
    nSqlTipo[7] = SQL_CHAR;
    nSqlTipo[8] = SQL_INTEGER;
    nSqlTipo[9] = SQL_CHAR;
    nSqlTipo[10] = SQL_CHAR;
    nSqlTipo[11] = SQL_CHAR;
    nSqlTipo[12] = SQL_VARCHAR;
    nSqlTipo[13] = SQL_CHAR;
    nSqlTipo[14] = SQL_BIGINT;
    nSqlTipo[15] = SQL_INTEGER;
	nSqlTipo[16] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_SSHORT;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SLONG;
    nCTipo[6] = SQL_C_SLONG;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_SLONG;
    nCTipo[9] = SQL_C_CHAR;
    nCTipo[10] = SQL_C_CHAR;
    nCTipo[11] = SQL_C_CHAR;
    nCTipo[12] = SQL_C_CHAR;
    nCTipo[13] = SQL_C_CHAR;
    nCTipo[14] = SQL_C_SBIGINT;
    nCTipo[15] = SQL_C_SLONG;
	nCTipo[16] = SQL_C_CHAR;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
    nLongitud[3] = 3;
    nLongitud[4] = 5;
    nLongitud[5] = 5;
    nLongitud[6] = 5;
    nLongitud[7] = 22;
    nLongitud[8] = 5;
    nLongitud[9] = 14;
    nLongitud[10] = 3;
    nLongitud[11] = 24;
    nLongitud[12] = 107;
    nLongitud[13] = 16;
    nLongitud[14] = 9;
    nLongitud[15] = 5;
	nLongitud[16] = 3;

    pVar[0] =  clave;
    pVar[1] = &tienda;
    pVar[2] = &ciudad;
    pVar[3] = &caja;
    pVar[4] = &recibo;
    pVar[5] = &folio;
    pVar[6] = &importe;
    pVar[7] =  cuenta;
    pVar[8] = &ruta;
    pVar[9] =  rpu;
    pVar[10] =  compania;
    pVar[11] =  contrato;
    pVar[12] = &fechavencimiento;
    pVar[13] =  credito;
    pVar[14] = &telefono;
    pVar[15] = &efectuo;
	pVar[16] =  tipomovimiento;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CObtenerDatosTmpCaCarmovServicio::~CObtenerDatosTmpCaCarmovServicio()
{
    Commit();
}
    
void CObtenerDatosTmpCaCarmovServicio::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CObtenerDatosTmpCaCarmovServicio::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpCaCarmovServicio");
    return (retorno);
}
BOOL CObtenerDatosTmpCaCarmovServicio::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tienda, ciudad, caja, recibo, folio, importe, cuenta, ruta, rpu, compania, contrato, fechavencimiento, credito, telefono, efectuo, tipomovimiento) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
