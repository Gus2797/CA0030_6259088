// Consulta original solicitada:...
//  select departamento, clase, grupo FROM gnconsultargrabarclientepromicion( '9529047', '4', '2011-07-30' )
    
#ifndef CDATOSCRPROMDIRECTAS
#define CDATOSCRPROMDIRECTAS
#include "stdafx.h"
#include <RecordSet.hpp>
class CDatosCrpromdirectas : public CRecordSet 
{
public:
    CDatosCrpromdirectas(C_ODBC *odbc_ext, const char *select=NULL);
    ~CDatosCrpromdirectas();
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
    
    long                departamento;
    long                clase;
    long                grupo;
};
#endif CDATOSCRPROMDIRECTAS
