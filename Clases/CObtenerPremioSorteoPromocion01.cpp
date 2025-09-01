#include "COBTENERPREMIOSORTEOPROMOCION01.HPP"
CObtenerPremioSorteoPromocion01::CObtenerPremioSorteoPromocion01(C_ODBC *odbc_ext, bool bFlagCommit, const char *select) : CRecordSet(odbc_ext)
{
	inicializar( bFlagCommit ) //Vulnerabilidad Use of Uninitialized Variable
	CObtenerPremioSorteoPromocion01::bFlagCommit = bFlagCommit;
    odbc = odbc_ext;
    nCols=6;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_SMALLINT;
    nSqlTipo[3] = SQL_INTEGER;
	nSqlTipo[4] = SQL_SMALLINT;
	nSqlTipo[5] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SSHORT;
    nCTipo[3] = SQL_C_SLONG;
	nCTipo[4] = SQL_C_SSHORT;
	nCTipo[5] = SQL_C_SLONG;
 
    nLongitud[0] = 5;
    nLongitud[1] = 37;
    nLongitud[2] = 3;
    nLongitud[3] = 5;
	nLongitud[4] = 3;
	nLongitud[5] = 5;

    pVar[0] = &boleto;
    pVar[1] =  descripcion;
    pVar[2] = &tipo;
    pVar[3] = &importe;
	pVar[4] = &campana;
	pVar[5] = &foliocupon;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CObtenerPremioSorteoPromocion01::~CObtenerPremioSorteoPromocion01()
{
	if( bFlagCommit == true )
	{
		Commit();
	}
}
    
void CObtenerPremioSorteoPromocion01::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
//Vulnerabilidad Use of Uninitialized Variable
void CObtenerPremioSorteoPromocion01::inicializar(bool bFlagCommit1)
{
	bFlagCommit = bFlagCommit1;
} 

 
BOOL CObtenerPremioSorteoPromocion01::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tdsorteo");
    return (retorno);
}
BOOL CObtenerPremioSorteoPromocion01::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (boleto, descripcion, tipo, importe, campana, foliocupon) VALUES (?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
