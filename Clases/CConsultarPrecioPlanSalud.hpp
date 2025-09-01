// Consulta original solicitada:...
//  select * from fun_crobtenerpreciosplanesseguro('4', '1')
    
#ifndef CCONSULTARPRECIOPLANSALUD
#define CCONSULTARPRECIOPLANSALUD
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarPrecioPlanSalud : public CRecordSet 
{
public:
    CConsultarPrecioPlanSalud(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarPrecioPlanSalud();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[6];
    int nCTipo[6];
    long nLongitud[6];
    long nLongResp[6];
    void *pVar[6];
    
    short int           ioplan;
    double              ipreciodiario;
    double              ipreciomensual;
    double              iprecioanual;
    long                isumaasegurada;
};
#endif CCONSULTARPRECIOPLANSALUD
