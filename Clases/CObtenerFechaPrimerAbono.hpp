// Consulta original solicitada:...
//  SELECT diapago, mespago, aniopago FROM gncalculardiadepago( '0', '31', '12', '2011');
    
#ifndef COBTENERFECHAPRIMERABONO
#define COBTENERFECHAPRIMERABONO
#include "stdafx.h"
#include <RecordSet.hpp>
class CObtenerFechaPrimerAbono : public CRecordSet 
{
public:
    CObtenerFechaPrimerAbono(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerFechaPrimerAbono();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[4];
    int nCTipo[4];
    long nLongitud[4];
    long nLongResp[4];
    void *pVar[4];
    
    long                diapago;
    long                mespago;
    long                aniopago;
};
#endif COBTENERFECHAPRIMERABONO
