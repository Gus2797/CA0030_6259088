#include "CINSERTARHORAMENSAJE.HPP"
CInsertarHoraMensaje::CInsertarHoraMensaje(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=4;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_SMALLINT;
    nSqlTipo[1] = SQL_SMALLINT;
    nSqlTipo[2] = SQL_SMALLINT;
	nSqlTipo[3] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_SSHORT;
    nCTipo[1] = SQL_C_SSHORT;
    nCTipo[2] = SQL_C_SSHORT;
	nCTipo[3] = SQL_C_SSHORT;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
	nLongitud[3] = 3;
    pVar[0] = &caja;
    pVar[1] = &hora;
    pVar[2] = &minuto;
	pVar[3] = &tiempomensaje;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CInsertarHoraMensaje::~CInsertarHoraMensaje()
{
    Commit();
}
    
void CInsertarHoraMensaje::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CInsertarHoraMensaje::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("cainvitacionafore");
    return (retorno);
}
BOOL CInsertarHoraMensaje::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (caja, hora, minuto, tiempomensaje) VALUES (?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
