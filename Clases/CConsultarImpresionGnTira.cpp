#include "CCONSULTARIMPRESIONGNTIRA.HPP"
CConsultarImpresionGnTira::CConsultarImpresionGnTira(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_CHAR;
 
    nLongitud[0] = 300000;
    pVar[0] =  documento;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarImpresionGnTira::~CConsultarImpresionGnTira()
{
}
    
void CConsultarImpresionGnTira::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
