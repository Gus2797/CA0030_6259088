#include "COBTENERSITUACIONREGLACLIENTE.HPP"
CObtenerSituacionReglaCliente::CObtenerSituacionReglaCliente(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_LONGVARCHAR;
   
    nCTipo[0] = SQL_C_CHAR;
 
    nLongitud[0] = 20000;
    pVar[0] =  ccadenasituacion;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CObtenerSituacionReglaCliente::~CObtenerSituacionReglaCliente()
{
}
    
void CObtenerSituacionReglaCliente::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
