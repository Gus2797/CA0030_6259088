// Consulta original solicitada:...
//  SELECT precioseguro, montoseguro, maximoseguros FROM fun_consultarPlanesSeguroClub( '20', '3', '1', '1' )
    
#ifndef CCONSULTARPRECIOSEGUROCLUB
#define CCONSULTARPRECIOSEGUROCLUB
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarPrecioSeguroClub : public CRecordSet 
{
public:
    CConsultarPrecioSeguroClub(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarPrecioSeguroClub();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[5];
    int nCTipo[5];
    long nLongitud[5];
    long nLongResp[5];
    void *pVar[5];
    
    long                precioseguro;
    long                montoseguro;
    short int           maximoseguros;
	char                planseguro[32];
};
#endif CCONSULTARPRECIOSEGUROCLUB
