#include "CRESPUESTAPUENTESALIDA.H"
CRespuestaPuenteSalida::CRespuestaPuenteSalida(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols = 2;
    odbcRet = TRUE;
    nSqlTipo[0] = SQL_LONGVARCHAR;
    nSqlTipo[1] = SQL_LONGVARCHAR;

    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;

    nLongitud[0] = 20000;
    nLongitud[1] = 20000;
    pVar[0] = cEntrada;
    pVar[1] = cSalida;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }
}

CRespuestaPuenteSalida::~CRespuestaPuenteSalida() {}

void CRespuestaPuenteSalida::activarCols()
{
    int i;
    for (i = 0; i < nCols; i++)
    {
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }
}
