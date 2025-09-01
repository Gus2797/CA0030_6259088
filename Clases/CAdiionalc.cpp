#include "CADIIONALC.HPP"
CAdiional::CAdiional(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols = 2;
    odbcRet = TRUE;
    nSqlTipo[0] = SQL_BIGINT;
    nSqlTipo[1] = SQL_LONGVARCHAR;

    nCTipo[0] = SQL_C_SBIGINT;
    nCTipo[1] = SQL_C_CHAR;

    nLongitud[0] = 9;
    nLongitud[1] = 20000;
    pVar[0] = &poliza2;
    pVar[1] = nombreadicional;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }
}


CAdiional::~CAdiional()
{
}

void CAdiional::activarCols()
{
    int i;
    for (i = 0; i < nCols; i++)
    {
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }
}

