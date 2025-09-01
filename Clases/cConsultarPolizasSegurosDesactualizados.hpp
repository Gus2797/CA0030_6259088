// Consulta original solicitada:...
//  SELECT * FROM fun_consultarPolizasSegurosDesactualizados(178115827,0,'0');
    
#ifndef CCONSULTARPOLIZASSEGUROSDESACTUALIZADOS
#define CCONSULTARPOLIZASSEGUROSDESACTUALIZADOS
#include "stdafx.h"
#include <RecordSet.hpp>
class cConsultarPolizasSegurosDesactualizados : public CRecordSet 
{
public:
    cConsultarPolizasSegurosDesactualizados(C_ODBC *odbc_ext, const char *select=NULL);
    ~cConsultarPolizasSegurosDesactualizados();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[7];
    int nCTipo[7];
    long nLongitud[7];
    long nLongResp[7];
    void *pVar[7];
    
    char                snombreasegurado[87];
    long                ifolio;
    SqlTimeStamp        dfechavencimiento;
    char                cstatus[4];
    char                cempresa[4];
    short int           iflagactualizacion;
};
#endif CCONSULTARPOLIZASSEGUROSDESACTUALIZADOS
