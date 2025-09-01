#include "CCONSULTARTIPOSEGUROCRSEGUROS.HPP"
CConsultarTipoSeguroCrSeguros::CConsultarTipoSeguroCrSeguros(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=4;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_VARCHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_CHAR;
	nSqlTipo[3] = SQL_VARCHAR;//15750
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
	nCTipo[3] = SQL_C_CHAR;//15750
 
    nLongitud[0] = 107;
    nLongitud[1] = 3;
    nLongitud[2] = 3;
	nLongitud[3] = 107;//15750
    pVar[0] = &fechavencimiento;
    pVar[1] =  statusseguro;
    pVar[2] =  clavenoofrecer;
	pVar[3] = &fechaultimopago;//15750
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarTipoSeguroCrSeguros::~CConsultarTipoSeguroCrSeguros()
{
    Commit();
}
    
void CConsultarTipoSeguroCrSeguros::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarTipoSeguroCrSeguros::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crSeguros");
    return (retorno);
}
BOOL CConsultarTipoSeguroCrSeguros::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (fechavencimiento, statusseguro, clavenoofrecer, fechaultimopago) VALUES (?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
