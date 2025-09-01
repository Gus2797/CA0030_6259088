#include "CCONSULTARDESCRIPCIONCLUB.HPP"
CConsultarDescripcionClub::CConsultarDescripcionClub(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=3;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_SMALLINT;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_LONGVARCHAR;
   
    nCTipo[0] = SQL_C_SSHORT;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_CHAR;
 
    nLongitud[0] = 3;
    nLongitud[1] = 5;
    nLongitud[2] = 2000;
    pVar[0] = &idu_modulopolizaclub;
    pVar[1] = &idu_mensajepolizaclub;
    pVar[2] =  desc_mensaje;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarDescripcionClub::~CConsultarDescripcionClub()
{
}
    
void CConsultarDescripcionClub::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
