#include "CRESPUESTAPUENTEENTRADA.H"
CRespuestaPuenteEntrada::CRespuestaPuenteEntrada(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols = 1;
    odbcRet = TRUE;
    nSqlTipo[0] = SQL_INTEGER;

    nCTipo[0] = SQL_C_SLONG;

    nLongitud[0] = 5;
    pVar[0] = &lResultado;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }
}

CRespuestaPuenteEntrada::~CRespuestaPuenteEntrada() {}

void CRespuestaPuenteEntrada::activarCols()
{
    int i;
    for (i = 0; i < nCols; i++)
    {
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }
}
