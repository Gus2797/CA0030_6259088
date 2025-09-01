#ifndef CCONSULTARCRSEGUROSFECHAMESDIAVENCE
#define CCONSULTARCRSEGUROSFECHAMESDIAVENCE
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarCrSegurosFechaMesDiaVence : public CRecordSet 
{
public:
    CConsultarCrSegurosFechaMesDiaVence (C_ODBC *odbc_ext, const char *select=NULL);    
	~CConsultarCrSegurosFechaMesDiaVence();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[4];
    int nCTipo[4];
    long nLongitud[4];
    long nLongResp[4];
    void *pVar[4];

    long                meses;
    long                dias;    
    SqlTimeStamp        fechavencimiento;
};
#endif CCONSULTARCRSEGUROSFECHAMESDIAVENCE