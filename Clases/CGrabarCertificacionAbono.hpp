// Consulta original solicitada:...
//  SELECT estado, mensaje FROM fun_guardarcertificacionbonificaciondiaria(318388421, 518481, 0239, '03', '2017-12-22', '2017-12-22', '18', 7086, 0, 11120, 800, 500, 0,  7086, '108', 3546, '50', 0, 0,  10320, 0);
    
#ifndef CGRABARCERTIFICACIONABONO
#define CGRABARCERTIFICACIONABONO
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarCertificacionAbono : public CRecordSet 
{
public:
    CGrabarCertificacionAbono(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarCertificacionAbono();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];
    
    long                estado;
    char                mensaje[20001];
};
#endif CGRABARCERTIFICACIONABONO
