// Consulta original solicitada:...
//  SELECT url FROM urlswebservice WHERE tipo = 7
    
#ifndef CCONSULTARWS
#define CCONSULTARWS
//#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarWS : public CRecordSet 
{
public:
    CConsultarWS(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarWS();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];
    
    char                url[52];
};
#endif CCONSULTARWS
