

#include "CCONSULTATDCHEQUESESION.HPP"
CConsultatdchequesesion::CConsultatdchequesesion(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_INTEGER;

    nCTipo[0] = SQL_C_SLONG;

    nLongitud[0] = 5;
    nLongitud[1] = 5;
	
    pVar[0] = &captura;
                                   
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultatdchequesesion::~CConsultatdchequesesion()
{
}
    
void CConsultatdchequesesion::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
