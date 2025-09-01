#include "CConsultarGnVigenciaPromocion.hpp"
CConsultarGnVigenciaPromocion::CConsultarGnVigenciaPromocion(C_ODBC *odbc_ext, bool bFlagCommit, const char *select) : CRecordSet(odbc_ext),bFlagCommit(bFlagCommit)
{
	CConsultarGnVigenciaPromocion::bFlagCommit = bFlagCommit;
    odbc = odbc_ext;
    nCols=3;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_SMALLINT;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_SMALLINT;
    
   
    nCTipo[0] = SQL_C_SSHORT;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SSHORT;    
 
    nLongitud[0] = 3;
    nLongitud[1] = 2;
    nLongitud[2] = 3;
    

    pVar[0] = &campana;
    pVar[1] =  tipocampana;
    pVar[2] = &prioridad;    
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarGnVigenciaPromocion::~CConsultarGnVigenciaPromocion()
{
	if( bFlagCommit == true )
	{
		Commit();
	}
}
    
void CConsultarGnVigenciaPromocion::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarGnVigenciaPromocion::prepararInsert()
{
	BOOL retorno = FALSE;
    retorno=prepararInsert("gnvigenciapromocion");
    return (retorno);
}
BOOL CConsultarGnVigenciaPromocion::prepararInsert(const char *nombreTabla)
{
	BOOL retorno = FALSE;
	int i;
	CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (campana, tipocampana, prioridad) VALUES (?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
