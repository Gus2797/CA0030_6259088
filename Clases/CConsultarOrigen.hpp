// Consulta original solicitada:...
//  select iorigen, isuborigen from fun_consultarorigensuborigencorreo(1);
    
#ifndef CCONSULTARORIGEN
#define CCONSULTARORIGEN
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarOrigen : public CRecordSet 
{
public:
    CConsultarOrigen(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarOrigen();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];
    
    long                iorigen;
    long                isuborigen;
};
#endif CCONSULTARORIGEN
