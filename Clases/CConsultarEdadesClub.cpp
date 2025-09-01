#include "CCONSULTAREDADESCLUB.HPP"
CConsultarEdadesClub::CConsultarEdadesClub(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=3;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_SMALLINT;
    nSqlTipo[1] = SQL_SMALLINT;
	nSqlTipo[2] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_SSHORT;
    nCTipo[1] = SQL_C_SSHORT;
	nCTipo[2] = SQL_C_SSHORT;
 
    nLongitud[0] = 3;
    nLongitud[1] = 3;
	nLongitud[2] = 3;

    pVar[0] = &edadminima;
    pVar[1] = &edadmaxima;
	pVar[2] = &edadmaximaabono;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarEdadesClub::~CConsultarEdadesClub()
{
    Commit();
}
    
void CConsultarEdadesClub::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarEdadesClub::prepararInsert()
{
	BOOL retorno = FALSE;
    retorno=prepararInsert("cat_crseguros");
    return (retorno);
}
BOOL CConsultarEdadesClub::prepararInsert(const char *nombreTabla)
{
	BOOL retorno = FALSE;
	int i;
	CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (edadminima, edadmaxima, edadmaximaabono) VALUES (?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
