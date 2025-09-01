// Consulta original solicitada:...
//  select * from fun_obtener_puesto(96793929)
    
#ifndef CCONSULTATDCHEQUESESION
#define CCONSULTATDCHEQUESESION
#include "stdafx.h"
#include <RecordSet.hpp>
CCONSULTATDCHEQUESESION
class CConsultatdchequesesion : public CRecordSet 
{
public:
    CConsultatdchequesesion(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultatdchequesesion();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[1];
    int nCTipo[1];
    long nLongitud[1];
    long nLongResp[1];
    void *pVar[1];
    
	long   captura;
  

};
#endif CCONSULTATDCHEQUESESION

