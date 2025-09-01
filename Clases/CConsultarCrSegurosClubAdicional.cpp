#include "CCONSULTARCRSEGUROSCLUBADICIONAL.HPP"
CConsultarCrSegurosClubAdicional::CConsultarCrSegurosClubAdicional(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=8;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_SMALLINT;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_VARCHAR;
    nSqlTipo[4] = SQL_VARCHAR;
    nSqlTipo[5] = SQL_VARCHAR;
	nSqlTipo[6] = SQL_SMALLINT;
	nSqlTipo[7] = SQL_VARCHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SSHORT;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_CHAR;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_CHAR;
	nCTipo[6] = SQL_C_SSHORT;
	nCTipo[7] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 3;
    nLongitud[2] = 17;
    nLongitud[3] = 17;
    nLongitud[4] = 17;
    nLongitud[5] = 107;
	nLongitud[6] = 3;
	nLongitud[7] = 107;

    pVar[0] =  &folio;
    pVar[1] =  &cantidadseguros;
    pVar[2] =  nombreadicional;
    pVar[3] =  apellidopaternoadic;
    pVar[4] =  apellidomaternoadic;
    pVar[5] =  &fecnacadic;
	pVar[6] =  &parentescoadic;
	pVar[7] =  &fechavencimiento;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarCrSegurosClubAdicional::~CConsultarCrSegurosClubAdicional()
{
    Commit();
}
    
void CConsultarCrSegurosClubAdicional::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarCrSegurosClubAdicional::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crseguros");
    return (retorno);
}
BOOL CConsultarCrSegurosClubAdicional::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (folio,cantidadseguros,nombreadicional,apellidopaternoadic,apellidomaternoadic,fecnacadic,parentescoadic,fechavencimiento) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
