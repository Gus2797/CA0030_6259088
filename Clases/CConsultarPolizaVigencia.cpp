#include "CCONSULTARPOLIZAVIGENCIA.HPP"
CConsultarPolizaVigencia::CConsultarPolizaVigencia(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=2;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
 
    nLongitud[0] = 22;
    nLongitud[1] = 27;
    pVar[0] =  foliopoliza;
    pVar[1] =  fechavigencia;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarPolizaVigencia::~CConsultarPolizaVigencia()
{
}
    
void CConsultarPolizaVigencia::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
