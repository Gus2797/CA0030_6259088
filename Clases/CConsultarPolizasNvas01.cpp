#include "CCONSULTARPOLIZASNVAS01.HPP"
CConsultarPolizasNvas01::CConsultarPolizasNvas01(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=4;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_SMALLINT;
	nSqlTipo[3] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_SSHORT;
	nCTipo[3] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 3;
	nLongitud[3] = 5;

    pVar[0] = &cliente;
    pVar[1] = &factura;
    pVar[2] = &digito;
	pVar[3] = &folioanterior;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarPolizasNvas01::~CConsultarPolizasNvas01()
{
    Commit();
}
    
void CConsultarPolizasNvas01::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarPolizasNvas01::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("cacarmov");
    return (retorno);
}
BOOL CConsultarPolizasNvas01::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, factura, digito, folioanterior) VALUES (?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
