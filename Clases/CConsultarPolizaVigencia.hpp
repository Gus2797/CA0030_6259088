// Consulta original solicitada:...
//  select foliopoliza,fechavigencia from gndominio
    
#ifndef CCONSULTARPOLIZAVIGENCIA
#define CCONSULTARPOLIZAVIGENCIA
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarPolizaVigencia : public CRecordSet 
{
public:
    CConsultarPolizaVigencia(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarPolizaVigencia();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];
    
    char                foliopoliza[22];
    char                fechavigencia[27];
};
#endif CCONSULTARPOLIZAVIGENCIA
