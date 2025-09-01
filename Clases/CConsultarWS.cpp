#include "CCONSULTARWS.hpp"
CConsultarWS::CConsultarWS(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_CHAR;
 
    nLongitud[0] = 52;
    pVar[0] =  url;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarWS::~CConsultarWS()
{
}
    
void CConsultarWS::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
