#include "CCONSULTARPOLIZASSEGUROSDESACTUALIZADOS.HPP"
cConsultarPolizasSegurosDesactualizados::cConsultarPolizasSegurosDesactualizados(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=6;
    odbcRet=TRUE;
    nSqlTipo[0] = SQL_VARCHAR;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_VARCHAR;
    nSqlTipo[3] = SQL_CHAR;
    nSqlTipo[4] = SQL_CHAR;
    nSqlTipo[5] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_CHAR;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_SSHORT;
 
    nLongitud[0] = 87;
    nLongitud[1] = 5;
    nLongitud[2] = 107;
    nLongitud[3] = 4;
    nLongitud[4] = 4;
    nLongitud[5] = 3;
    pVar[0] =  snombreasegurado;
    pVar[1] = &ifolio;
    pVar[2] = &dfechavencimiento;
    pVar[3] =  cstatus;
    pVar[4] =  cempresa;
    pVar[5] = &iflagactualizacion;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
cConsultarPolizasSegurosDesactualizados::~cConsultarPolizasSegurosDesactualizados()
{
}
    
void cConsultarPolizasSegurosDesactualizados::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
 
