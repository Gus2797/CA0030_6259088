// Consulta original solicitada:...
//  select des_registroEntrada as cEntrada, des_registrosalida as cSalida from
//  fun_obtenerctlrespuestapuente('GN0133',13::SMALLINT,55::SMALLINT,'1')

#ifndef CRESPUESTAPUENTESALIDA
#define CRESPUESTAPUENTESALIDA
#include "stdafx.h"
#include <RecordSet.hpp>
class CRespuestaPuenteSalida : public CRecordSet
{
public:
    CRespuestaPuenteSalida(C_ODBC *odbc_ext, const char *select = NULL);
    ~CRespuestaPuenteSalida();
    void activarCols();

    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];

    char cEntrada[20001];
    char cSalida[20001];
};
#endif CRESPUESTAPUENTESALIDA