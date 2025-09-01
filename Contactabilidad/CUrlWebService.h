#ifndef CURLWEBSERVICE
#define CURLWEBSERVICE
#include "stdafx.h"
#include <RecordSet.hpp>
class CUrlWebService : public CRecordSet
{
public:
    CUrlWebService(C_ODBC *odbc_ext, const char *select = NULL);
    ~CUrlWebService();
    void activarCols();

    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[5];
    int nCTipo[5];
    long nLongitud[5];
    long nLongResp[5];
    void *pVar[5];

    char cUrl[87];
    short int iTipo;
    char cDescripcion[202];
    long iKeyx;
};
#endif CURLWEBSERVICE
