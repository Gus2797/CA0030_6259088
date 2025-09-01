#include "CCONSULTASITUACIONCAUSA.HPP"
CConsultaSituacionCausa::CConsultaSituacionCausa(C_ODBC *odbc_ext, bool bFlagCommit, const char *select) : CRecordSet(odbc_ext)
{
	this->bFlagCommit = bFlagCommit;
    odbc = odbc_ext;
    nCols=3;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
    nLongitud[1] = 2;
    nLongitud[2] = 5;
    pVar[0] = &idsituacion;
    pVar[1] = &clvsituacion;
    pVar[2] = &numcausasituacion;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
    nada001 = 0;                                                              
}
    
    
CConsultaSituacionCausa::~CConsultaSituacionCausa()
{
	if( bFlagCommit == true )
	{
		Commit();
	}
}
    
void CConsultaSituacionCausa::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
