#include "CTMPABONOCRCMUEBLESPLANFIJA.HPP"
CTmpAbonoCrCmueblesPlanFija::CTmpAbonoCrCmueblesPlanFija(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=6;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_SMALLINT;
    nSqlTipo[5] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SSHORT;
    nCTipo[5] = SQL_C_SSHORT;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 5;
    nLongitud[3] = 3;
    nLongitud[4] = 3;
    nLongitud[5] = 3;
    pVar[0] = &cliente;
    pVar[1] = &factura;
    pVar[2] = &abonosmes;
    pVar[3] = &caja;
    pVar[4] = &sistema;
    pVar[5] = &tienda;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CTmpAbonoCrCmueblesPlanFija::~CTmpAbonoCrCmueblesPlanFija()
{
    Commit();
}
    
void CTmpAbonoCrCmueblesPlanFija::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CTmpAbonoCrCmueblesPlanFija::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("TmpAbonoCrCmueblesPlanFija");
    return (retorno);
}
BOOL CTmpAbonoCrCmueblesPlanFija::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, factura, abonosmes, caja, sistema, tienda) VALUES (?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
