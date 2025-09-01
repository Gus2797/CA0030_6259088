// Consulta original solicitada:...
//  SELECT cliente, statusseguro,fechavencimiento,fechaafiliacion FROM crSeguros 
    
#ifndef COBTENFECHAAFILIACION
#define COBTENFECHAAFILIACION
#include "stdafx.h"
#include <RecordSet.hpp>
class CobtenFechaAfiliacion : public CRecordSet 
{
public:
    CobtenFechaAfiliacion(C_ODBC *odbc_ext, const char *select=NULL);
    ~CobtenFechaAfiliacion();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[5];
    int nCTipo[5];
    long nLongitud[5];
    long nLongResp[5];
    void *pVar[5];
    
    long                cliente;
    char                statusseguro[3];
    SqlTimeStamp        fechavencimiento;
    SqlTimeStamp        fechaafiliacion;
};
#endif COBTENFECHAAFILIACION
