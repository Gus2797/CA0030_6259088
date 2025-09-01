#ifndef CCONSULTARREGION
#define CCONSULTARREGION
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarRegion : public CRecordSet 
{
public:
    CConsultarRegion(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarRegion();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];
    
    char                bodegamueblesnacional[16];

};
#endif CCONSULTARREGION