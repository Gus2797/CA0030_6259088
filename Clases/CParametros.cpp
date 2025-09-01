#include "CPARAMETROS.HPP"
CParametros::CParametros(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=8;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_SMALLINT;
    nSqlTipo[1] = SQL_SMALLINT;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_CHAR;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_SMALLINT;
    nSqlTipo[7] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_SSHORT;
    nCTipo[1] = SQL_C_SSHORT;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_SSHORT;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
    nLongitud[3] = 3;
    nLongitud[4] = 12;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    pVar[0] = &iminutospregunta;
    pVar[1] = &iopcionstatusafore;
    pVar[2] = &idiasencuestasolicitud;
    pVar[3] = &imesesencuestanocotiza;
    pVar[4] =  cdescmes;
    pVar[5] = &iedadcliente;
    pVar[6] = &iopcinvitacionaforecontado;
    pVar[7] = &iopcinvitacionesaforecliente;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CParametros::~CParametros()
{
    Commit();
}
    
void CParametros::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CParametros::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("");
    return (retorno);
}
BOOL CParametros::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (iminutospregunta, iopcionstatusafore, idiasencuestasolicitud, imesesencuestanocotiza, cdescmes, iedadcliente, iopcinvitacionaforecontado, iopcinvitacionesaforecliente) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
