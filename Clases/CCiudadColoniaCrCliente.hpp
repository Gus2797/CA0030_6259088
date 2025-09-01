#ifndef CCIUDADCOLONIACRCLIENTE
#define CCIUDADCOLONIACRCLIENTE
#include "stdafx.h"
#include <RecordSet.HPP>
class CCiudadColoniaCrCliente : public CRecordSet 
{
public:
    CCiudadColoniaCrCliente(C_ODBC *odbc_ext, const char *select=NULL);
    ~CCiudadColoniaCrCliente();
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
    
    short int           ciudad;
    short int           colonia;
};
#endif CCIUDADCOLONIACRCLIENTE
