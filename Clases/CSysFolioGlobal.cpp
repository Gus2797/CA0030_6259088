#include "CSYSFOLIOGLOBAL.HPP"
CSysFolioGlobal::CSysFolioGlobal(C_ODBC *odbc_ext, bool bFlagCommit, const char *select) : CRecordSet(odbc_ext),bFlagCommit(bFlagCommit)
{
    CSysFolioGlobal::bFlagCommit = bFlagCommit;
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_BIGINT;

    nCTipo[0] = SQL_C_SBIGINT;

    nLongitud[0] = 9;
    pVar[0] = &folio;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }
}


CSysFolioGlobal::~CSysFolioGlobal()
{
	if( bFlagCommit == true )
	{
        Commit();
    }
}

void CSysFolioGlobal::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)
    {
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }
    flagInsertar=1;
}

BOOL CSysFolioGlobal::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("SysFolioGlobal");
    return (retorno);
}
BOOL CSysFolioGlobal::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;

    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (folio) VALUES (?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)
    {
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }
    return (retorno);
}
