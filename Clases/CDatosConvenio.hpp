#ifndef CDATOSCONVENIO
#define CDATOSCONVENIO
#include "stdafx.h"
#include <RecordSet.HPP>
class CDatosConvenio : public CRecordSet 
{
public:
    CDatosConvenio(C_ODBC *odbc_ext, const char *select=NULL);
    ~CDatosConvenio();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[7];
    int nCTipo[7];
    long nLongitud[7];
    long nLongResp[7];
    void *pVar[7];
    
    short int           tipoconvenio;
    short int           subtipoconvenio;
    SqlTimeStamp        fechaconvenio;
    short int           plazoconvenio;
    long                importeconvenio;
    long                efectuoconvenio;
};
#endif CDATOSCONVENIO
