#include "CCONSULTARPRECIOPLANSALUD.HPP"
CConsultarPrecioPlanSalud::CConsultarPrecioPlanSalud(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=5;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_SMALLINT;
    nSqlTipo[1] = SQL_FLOAT;
    nSqlTipo[2] = SQL_FLOAT;
    nSqlTipo[3] = SQL_FLOAT;
    nSqlTipo[4] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_SSHORT;
    nCTipo[1] = SQL_C_DOUBLE;
    nCTipo[2] = SQL_C_DOUBLE;
    nCTipo[3] = SQL_C_DOUBLE;
    nCTipo[4] = SQL_C_SLONG;
 
    nLongitud[0] = 3;
    nLongitud[1] = 5;
    nLongitud[2] = 5;
    nLongitud[3] = 5;
    nLongitud[4] = 5;
    pVar[0] = &ioplan;
    pVar[1] = &ipreciodiario;
    pVar[2] = &ipreciomensual;
    pVar[3] = &iprecioanual;
    pVar[4] = &isumaasegurada;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarPrecioPlanSalud::~CConsultarPrecioPlanSalud()
{
}
    
void CConsultarPrecioPlanSalud::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
