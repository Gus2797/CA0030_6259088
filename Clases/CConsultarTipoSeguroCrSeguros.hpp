#ifndef CCONSULTARTIPOSEGUROCRSEGUROS
#define CCONSULTARTIPOSEGUROCRSEGUROS
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarTipoSeguroCrSeguros : public CRecordSet 
{
public:
    CConsultarTipoSeguroCrSeguros(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarTipoSeguroCrSeguros();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[5];
    int nCTipo[5];
    long nLongitud[5];
    long nLongResp[5];
    void *pVar[5];
    
    SqlTimeStamp        fechavencimiento;
    char                statusseguro[3];
    char                clavenoofrecer[3];
	SqlTimeStamp        fechaultimopago;//15750
};
#endif CCONSULTARTIPOSEGUROCRSEGUROS
