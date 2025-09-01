// Consulta original solicitada:...
//  SELECT nombreciudad,fecha FROM gndominio
    
#ifndef CCONSULTARCIUDADFECHATIENDA
#define CCONSULTARCIUDADFECHATIENDA
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarCiudadFechaTienda : public CRecordSet 
{
public:
    CConsultarCiudadFechaTienda(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarCiudadFechaTienda();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];
    
    char                nombreciudad[22];
    SqlTimeStamp        fecha;
};
#endif CCONSULTARCIUDADFECHATIENDA
