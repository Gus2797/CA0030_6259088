#include "CConsultarClaveConyugalCrSeguros.HPP"
CConsultarClaveConyugalCrSeguros::CConsultarClaveConyugalCrSeguros(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=1;
    odbcRet=TRUE;
    flagInsertar = 0;    

    nSqlTipo[0] = SQL_SMALLINT;
       
    nCTipo[0] = SQL_C_SSHORT;
     
    nLongitud[0] = 3;
    
    pVar[0] = &claveconyugal;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
CConsultarClaveConyugalCrSeguros::~CConsultarClaveConyugalCrSeguros()
{
    Commit();
}
    
void CConsultarClaveConyugalCrSeguros::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarClaveConyugalCrSeguros::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("CrSeguros");
    return (retorno);
}

BOOL CConsultarClaveConyugalCrSeguros::prepararInsert(const char *nombreTabla)
{
	BOOL retorno = FALSE;
	int i;
	CString sqlTxtInsert;
    
    if (flagInsertar==0) activarCols();
	
	sqlTxtInsert.Format("INSERT INTO %s (claveconyugal) VALUES (?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
