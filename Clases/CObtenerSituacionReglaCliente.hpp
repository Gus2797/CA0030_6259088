// Consulta original solicitada:...
//  select ccadenasituacion from fun_obtenersituacionclienteregla(3, 1, 2, 1346695)
    
#ifndef COBTENERSITUACIONREGLACLIENTE
#define COBTENERSITUACIONREGLACLIENTE
#include "stdafx.h"
#include <RecordSet.hpp>
class CObtenerSituacionReglaCliente : public CRecordSet 
{
public:
    CObtenerSituacionReglaCliente(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerSituacionReglaCliente();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];
    
    char                ccadenasituacion[20001];
};
#endif COBTENERSITUACIONREGLACLIENTE
