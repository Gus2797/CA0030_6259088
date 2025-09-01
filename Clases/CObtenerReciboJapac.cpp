#include "COBTENERRECIBOJAPAC.HPP"
CObtenerReciboJapac::CObtenerReciboJapac(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=13;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_SMALLINT;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_INTEGER;
    nSqlTipo[6] = SQL_INTEGER;
    nSqlTipo[7] = SQL_INTEGER;
    nSqlTipo[8] = SQL_CHAR;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_SMALLINT;
    nSqlTipo[11] = SQL_INTEGER;
    nSqlTipo[12] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_SSHORT;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SLONG;
    nCTipo[6] = SQL_C_SLONG;
    nCTipo[7] = SQL_C_SLONG;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_SSHORT;
    nCTipo[11] = SQL_C_SLONG;
    nCTipo[12] = SQL_C_CHAR;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
    nLongitud[3] = 3;
    nLongitud[4] = 5;
    nLongitud[5] = 5;
    nLongitud[6] = 5;
    nLongitud[7] = 5;
    nLongitud[8] = 22;
    nLongitud[9] = 5;
    nLongitud[10] = 3;
    nLongitud[11] = 5;
    nLongitud[12] = 3;
    pVar[0] =  clave;
    pVar[1] = &tienda;
    pVar[2] = &ciudad;
    pVar[3] = &caja;
    pVar[4] = &recibo;
    pVar[5] = &importe;
    pVar[6] = &ruta;
    pVar[7] = &folio;
    pVar[8] =  cuenta;
    pVar[9] = &efectuo;
    pVar[10] = &digito;
    pVar[11] = &cliente;
    pVar[12] =  flagincluyerecibo;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CObtenerReciboJapac::~CObtenerReciboJapac()
{
    Commit();
}
    
void CObtenerReciboJapac::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CObtenerReciboJapac::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpcacarmovservicio");
    return (retorno);
}
BOOL CObtenerReciboJapac::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tienda, ciudad, caja, recibo, importe, ruta, folio, cuenta, efectuo, digito, cliente, flagincluyerecibo) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
