#include "CGRABARTMPABONOCRCROPADETALLE.HPP"
CGrabarTmpAbonoCrCropaDetalle::CGrabarTmpAbonoCrCropaDetalle(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=8;
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
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_SSHORT;
    nCTipo[6] = SQL_C_SSHORT;
    nCTipo[7] = SQL_C_SSHORT;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 5;
    nLongitud[3] = 5;
    nLongitud[4] = 107;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    pVar[0] = &num_cliente;
    pVar[1] = &imp_saldo;
    pVar[2] = &imp_interesadicional;
    pVar[3] = &idu_tipodeduccion;
    pVar[4] = &fec_ultimomovto;
    pVar[5] = &num_sistema;
    pVar[6] = &num_caja;
    pVar[7] = &num_tienda;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CGrabarTmpAbonoCrCropaDetalle::~CGrabarTmpAbonoCrCropaDetalle()
{
    Commit();
}
    
void CGrabarTmpAbonoCrCropaDetalle::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CGrabarTmpAbonoCrCropaDetalle::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tmp_carteraropadetalle");
    return (retorno);
}
BOOL CGrabarTmpAbonoCrCropaDetalle::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (num_cliente, imp_saldo, imp_interesadicional, idu_tipodeduccion, fec_ultimomovto, num_sistema, num_caja, num_tienda) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
