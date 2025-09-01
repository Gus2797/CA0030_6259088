#include "CCONSULTARPLANSEGUROAUTO.HPP"
CConsultarPlanSeguroAuto::CConsultarPlanSeguroAuto(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_LONGVARCHAR;
   
    nCTipo[0] = SQL_C_CHAR;
 
    nLongitud[0] = 100;
    pVar[0] =  descripcionseguro;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarPlanSeguroAuto::~CConsultarPlanSeguroAuto()
{
}
    
void CConsultarPlanSeguroAuto::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
