#include "COBTENERMENSAJEABONO.HPP"
cObtenerMensajeAbono::cObtenerMensajeAbono(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=4;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_VARCHAR;
    nSqlTipo[1] = SQL_VARCHAR;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_CHAR;
 
    nLongitud[0] = 512;
    nLongitud[1] = 512;
    nLongitud[2] = 512;
    nLongitud[3] = 512;
    pVar[0] =  msg1;
    pVar[1] =  msg2;
    pVar[2] =  msg3;
    pVar[3] =  msg4;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
cObtenerMensajeAbono::~cObtenerMensajeAbono()
{
}
    
void cObtenerMensajeAbono::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
