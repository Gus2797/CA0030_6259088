#include "CGRABARTMPCACARMOVSEGURO.HPP"
CGrabarTmpCaCarmovSeguro::CGrabarTmpCaCarmovSeguro(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=15;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_SMALLINT;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_SMALLINT;
    nSqlTipo[7] = SQL_INTEGER;
    nSqlTipo[8] = SQL_CHAR;
    nSqlTipo[9] = SQL_CHAR;
    nSqlTipo[10] = SQL_CHAR;
    nSqlTipo[11] = SQL_VARCHAR;
	nSqlTipo[12] = SQL_SMALLINT;	
	nSqlTipo[13] = SQL_SMALLINT;	
	nSqlTipo[14] = SQL_SMALLINT;	
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_SSHORT;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_SLONG;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_CHAR;
    nCTipo[10] = SQL_C_CHAR;
    nCTipo[11] = SQL_C_CHAR;
	nCTipo[12] = SQL_C_SSHORT;	
	nCTipo[13] = SQL_C_SSHORT;	
	nCTipo[14] = SQL_C_SSHORT;	
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
    nLongitud[3] = 5;
    nLongitud[4] = 5;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 5;
    nLongitud[8] = 17;
    nLongitud[9] = 17;
    nLongitud[10] = 17;
    nLongitud[11] = 107;
	nLongitud[12] = 3;
	nLongitud[13] = 3;
	nLongitud[14] = 3;

    pVar[0] =  clave;
    pVar[1] =  &tienda;
    pVar[2] =  &caja;
    pVar[3] =  &cliente;
    pVar[4] =  &folio;
    pVar[5] =  &cantidadseguros;
    pVar[6] =  &cantidadsegurosanterior;
    pVar[7] =  &importe;
    pVar[8] =  nombreadicional;
    pVar[9] =  apellidopaternoadic;
    pVar[10] =  apellidomaternoadic;
    pVar[11] =  &fecnacadic;
	pVar[12] =  &parentescoadic;
	pVar[13] =  &respuesta;
	pVar[14] =  &consecutivo;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpCaCarmovSeguro::~CGrabarTmpCaCarmovSeguro()
{
    Commit();
}
    
void CGrabarTmpCaCarmovSeguro::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpCaCarmovSeguro::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpcacarmovseguros");
    return (retorno);
}
BOOL CGrabarTmpCaCarmovSeguro::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (clave, tienda, caja, cliente, folio, cantidadseguros, cantidadsegurosanterior, importe, nombreadicional, apellidopaternoadic, apellidomaternoadic, fecnacadic, parentescoadic, respuesta, consecutivo ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
