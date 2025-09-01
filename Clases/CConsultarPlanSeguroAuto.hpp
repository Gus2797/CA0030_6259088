// Consulta original solicitada:...
// SELECT INITCAP(descripcionseguro) AS descripcionseguro FROM crtiposeguro WHERE tiposeguro = 4 AND fechaalta <= '2020-03-12' ORDER BY fechaalta DESC LIMIT 1;
    
#ifndef CCONSULTARPLANSEGUROAUTO
#define CCONSULTARPLANSEGUROAUTO
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarPlanSeguroAuto : public CRecordSet 
{
public:
    CConsultarPlanSeguroAuto(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarPlanSeguroAuto();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];
    
    char descripcionseguro[101];
};
#endif CCONSULTARPLANSEGUROAUTO
