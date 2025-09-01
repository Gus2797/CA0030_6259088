// Consulta original solicitada:...
//  SELECT * FROM cagrabartmpsegurocacarmov09('12345','1','123456','99','11','1346695','1','2015-01-30')
    
#ifndef CCONSULTARFOLIOSSEGURO
#define CCONSULTARFOLIOSSEGURO
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarFoliosSeguro : public CRecordSet 
{
public:
    CConsultarFoliosSeguro(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarFoliosSeguro();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];
    
    long                folioseguro;
    short int           seguroclub;
};
#endif CCONSULTARFOLIOSSEGURO
