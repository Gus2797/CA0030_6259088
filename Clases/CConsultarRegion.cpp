#include "CCONSULTARREGION.HPP"
CConsultarRegion::CConsultarRegion(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_CHAR;
    
    nCTipo[0] = SQL_C_CHAR;
    
    nLongitud[0] = 16;

    pVar[0] =  bodegamueblesnacional;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}

CConsultarRegion::~CConsultarRegion()
{
}
    
void CConsultarRegion::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
