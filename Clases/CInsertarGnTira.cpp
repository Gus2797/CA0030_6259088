#include "CINSERTARGNTIRA.HPP"
CInsertarGnTira::CInsertarGnTira(C_ODBC *odbc_ext, bool bFlagCommit, const char *select) : CRecordSet(odbc_ext),bFlagCommit(bFlagCommit)
{
	CInsertarGnTira::bFlagCommit = bFlagCommit;
    odbc = odbc_ext;
    nCols=11;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_SMALLINT;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_INTEGER;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_LONGVARCHAR;
    nSqlTipo[7] = SQL_INTEGER;
    nSqlTipo[8] = SQL_INTEGER;
    nSqlTipo[9] = SQL_INTEGER;
    nSqlTipo[10] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_SSHORT;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SLONG;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_SLONG;
    nCTipo[8] = SQL_C_SLONG;
    nCTipo[9] = SQL_C_SLONG;
    nCTipo[10] = SQL_C_CHAR;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
    nLongitud[3] = 3;
    nLongitud[4] = 5;
    nLongitud[5] = 3;
    nLongitud[6] = 100000;
    nLongitud[7] = 5;
    nLongitud[8] = 5;
    nLongitud[9] = 5;
    nLongitud[10] = 107;
    pVar[0] = &status;
    pVar[1] =  area;
    pVar[2] = &tipo;
    pVar[3] = &caja;
    pVar[4] = &folio;
    pVar[5] = &tipoimpresora;
    pVar[6] =  documento;
    pVar[7] = &tamanio;
    pVar[8] = &empleadoefectuo;
    pVar[9] = &empleadocancelo;
    pVar[10] = &fecha;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CInsertarGnTira::~CInsertarGnTira()
{
    if( bFlagCommit == true )
	{
		Commit();
	}
}
    
void CInsertarGnTira::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CInsertarGnTira::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("gntira");
    return (retorno);
}
BOOL CInsertarGnTira::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (status, area, tipo, caja, folio, tipoimpresora, documento, tamanio, empleadoefectuo, empleadocancelo, fecha) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
