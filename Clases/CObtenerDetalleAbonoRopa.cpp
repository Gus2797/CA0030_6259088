#include "COBTENERDETALLEABONOROPA.HPP"
CObtenerDetalleAbonoRopa::CObtenerDetalleAbonoRopa(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=6;
    odbcRet=TRUE;
	nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_INTEGER;
	nSqlTipo[4] = SQL_INTEGER;
	nSqlTipo[5] = SQL_INTEGER;

   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SLONG;
	nCTipo[4] = SQL_C_SLONG;
	nCTipo[5] = SQL_C_SLONG;

 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 5;
    nLongitud[3] = 5;
	nLongitud[4] = 5;
	nLongitud[5] = 5;

    pVar[0] = &abonoRopa;
    pVar[1] = &abonoTasa0;
    pVar[2] = &abonoInteresRopa;
    pVar[3] = &abonoInteresTasa0;
	pVar[4] = &bonificacionRopa;
	pVar[5] = &bonificacionTasa0;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
CObtenerDetalleAbonoRopa::~CObtenerDetalleAbonoRopa()
{
}
    
void CObtenerDetalleAbonoRopa::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
