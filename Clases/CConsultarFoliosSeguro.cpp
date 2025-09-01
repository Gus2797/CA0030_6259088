#include "CCONSULTARFOLIOSSEGURO.HPP"
CConsultarFoliosSeguro::CConsultarFoliosSeguro(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=2;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SSHORT;
 
    nLongitud[0] = 5;
    nLongitud[1] = 3;
    pVar[0] = &folioseguro;
    pVar[1] = &seguroclub;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarFoliosSeguro::~CConsultarFoliosSeguro()
{
}
    
void CConsultarFoliosSeguro::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
