#include "CREESTRUCTURADAL.HPP"

CReestructuraDAL::CReestructuraDAL(C_ODBC *odbc_ext) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    odbcRet = TRUE;
    flagInsertar = 0;
}

CReestructuraDAL::~CReestructuraDAL()
{
    Commit();
}

bool CReestructuraDAL::esProsectoRestructura(int cMoras, char cPuntualidad, int cCiudad, char cSitEspecial)
{
    this->nCols = 1;

    nSqlTipo[0] = SQL_INTEGER;
    nCTipo[0] = SQL_C_SLONG;
    nLongitud[0] = 5;
    pValor[0] = &esCliente;

    CString sSql;

    sSql.Format("select fun_esCandidatoReestructura(%d,'%c',%d,'%c') AS esCliente", cMoras, cPuntualidad, cCiudad, cSitEspecial);
    odbcRet = Exec(sSql);
    if (odbcRet)
    {
        activarCols();
        return true;
    }

    return false;
}

void CReestructuraDAL::activarCols()
{
    int i = 0;
    for (; i < nCols; i++)
    {
        Activar(i, nCTipo[i], pValor[i], nLongitud[i], &nLongResp[i]);
    }
}


bool CReestructuraDAL::guardaHitReestructura(int iTienda, int iCaja, long lEmpleado, int iAbono, int iOpcFinaliza)
{
    this->nCols = 1;

    CString sSql;
    sSql.Format("select fun_guardahitreestructura('%d','%d','%ld','0','0','0','%d','%d')", iTienda, iCaja, lEmpleado, iAbono, iOpcFinaliza);
    odbcRet = Exec(sSql);

    if (odbcRet)
    {
        return true;
    }

    return false;
}

bool CReestructuraDAL::ValidaFormalizoReestructura(long lCliente)
{
    this->nCols = 1;

    nSqlTipo[0] = SQL_INTEGER;
    nCTipo[0] = SQL_C_SLONG;
    nLongitud[0] = 5;
    pValor[0] = &iFormalizo;
    CString sSql;

    sSql.Format("select fun_validaclienteformalizoreest(%ld) as iFormalizo", lCliente);
    odbcRet = Exec(sSql);
    if (odbcRet)
    {
        activarCols();
        return true;
    }

    return false;
}

bool CReestructuraDAL::ValidaTestigoReestructura(long lCliente)
{
    this->nCols = 1;

    nSqlTipo[0] = SQL_INTEGER;
    nCTipo[0] = SQL_C_SLONG;
    nLongitud[0] = 5;
    pValor[0] = &iClienteTestigo;
    CString sSql;

    sSql.Format("select fun_validatestigoreestructura(%ld)", lCliente);
    odbcRet = Exec(sSql);
    if (odbcRet)
    {
        activarCols();
        return true;
    }

    return false;
}
