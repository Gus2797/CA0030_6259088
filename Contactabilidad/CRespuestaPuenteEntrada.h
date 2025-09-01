// Consulta original solicitada:...
//  SELECT fun_grabarctlrespuestapuente as lResultado FROM fun_grabarctlrespuestapuente('GN0133', 13::SMALLINT,
//  55::SMALLINT,'1', '{}', '{}')

#ifndef CRESPUESTAPUENTEENTRADA
#define CRESPUESTAPUENTEENTRADA
#include "stdafx.h"
#include <RecordSet.hpp>
class CRespuestaPuenteEntrada : public CRecordSet
{
public:
    CRespuestaPuenteEntrada(C_ODBC *odbc_ext, const char *select = NULL);
    ~CRespuestaPuenteEntrada();
    void activarCols();

    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];

    long lResultado;
};
#endif CRESPUESTAPUENTEENTRADA
