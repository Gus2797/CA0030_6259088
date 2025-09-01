#include "CGRABARTMPABONOCRREVOLVENTE.HPP"
CGrabarTmpAbonoCrRevolvente::CGrabarTmpAbonoCrRevolvente(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=10;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_VARCHAR;
    nSqlTipo[5] = SQL_SMALLINT;
    nSqlTipo[6] = SQL_SMALLINT;
    nSqlTipo[7] = SQL_SMALLINT;
    nSqlTipo[8] = SQL_SMALLINT;
    nSqlTipo[9] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_SSHORT;
    nCTipo[8] = SQL_C_SSHORT;
    nCTipo[9] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 5;
    nLongitud[3] = 5;
    nLongitud[4] = 107;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    nLongitud[8] = 3;
    nLongitud[9] = 5;
    pVar[0] = &cliente;
    pVar[1] = &saldo;
    pVar[2] = &minimoapagar;
    pVar[3] = &interesadicional;
    pVar[4] = &fechaultimomovimiento;
    pVar[5] = &flagactualizacion;
    pVar[6] = &sistema;
    pVar[7] = &caja;
    pVar[8] = &tienda;
    pVar[9] = &interesadicionalprimermes;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpAbonoCrRevolvente::~CGrabarTmpAbonoCrRevolvente()
{
    Commit();
}
    
void CGrabarTmpAbonoCrRevolvente::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpAbonoCrRevolvente::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmpabonocrcrevolvente");
    return (retorno);
}
BOOL CGrabarTmpAbonoCrRevolvente::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, saldo, minimoapagar, interesadicional, fechaultimomovimiento, flagactualizacion, sistema, caja, tienda, interesadicionalprimermes) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
