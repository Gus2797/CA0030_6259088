#include "CCONSULTARCRSEGUROSFECHAMESDIAVENCE.HPP"
CConsultarCrSegurosFechaMesDiaVence::CConsultarCrSegurosFechaMesDiaVence(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=3;
    odbcRet=TRUE;
    flagInsertar = 0;

    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_VARCHAR;
     
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_CHAR;
    
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 107;

    pVar[0] = &meses;
    pVar[1] = &dias;
    pVar[2] = &fechavencimiento;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarCrSegurosFechaMesDiaVence::~CConsultarCrSegurosFechaMesDiaVence()
{
    Commit();
}
    
void CConsultarCrSegurosFechaMesDiaVence::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarCrSegurosFechaMesDiaVence::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crseguros");
    return (retorno);
}
BOOL CConsultarCrSegurosFechaMesDiaVence::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (meses, dias, fechavencimiento) VALUES (?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
