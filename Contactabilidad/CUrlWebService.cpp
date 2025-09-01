#include "CURLWEBSERVICE.H"
CUrlWebService::CUrlWebService(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols = 4;
    odbcRet = TRUE;
    nSqlTipo[0] = SQL_VARCHAR;
    nSqlTipo[1] = SQL_SMALLINT;
    nSqlTipo[2] = SQL_CHAR;
    nSqlTipo[3] = SQL_INTEGER;

    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_SSHORT;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SLONG;

    nLongitud[0] = 87;
    nLongitud[1] = 3;
    nLongitud[2] = 202;
    nLongitud[3] = 5;
    pVar[0] = cUrl;
    pVar[1] = &iTipo;
    pVar[2] = cDescripcion;
    pVar[3] = &iKeyx;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }
}

CUrlWebService::~CUrlWebService() {}

void CUrlWebService::activarCols()
{
    int i;
    for (i = 0; i < nCols; i++)
    {
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }
}
