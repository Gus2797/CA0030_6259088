// Consulta original solicitada:...
//  select fecha,domiciliocompleto,expedicion from gndominio
    
#ifndef CFECHADIRECCIONCOPPEL
#define CFECHADIRECCIONCOPPEL
#include "stdafx.h"
#include <RecordSet.hpp>
class CFechaDireccionCoppel : public CRecordSet 
{
public:
    CFechaDireccionCoppel(C_ODBC *odbc_ext, const char *select=NULL);
    ~CFechaDireccionCoppel();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[4];
    int nCTipo[4];
    long nLongitud[4];
    long nLongResp[4];
    void *pVar[4];
    
    SqlTimeStamp        fecha;
    char                domiciliocompleto[202];
    char                expedicion[52];
};
#endif CFECHADIRECCIONCOPPEL
