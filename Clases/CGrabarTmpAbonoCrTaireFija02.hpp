// Consulta original solicitada:...
//  SELECT cliente,saldo,minimoapagar,interesadicional,fechaultimomovimiento,flagactualizacion,sistema,caja,tienda,interesadicionalprimermes FROM tmpabonocrtaire
    
#ifndef CGRABARTMPABONOCRTAIREFIJA02
#define CGRABARTMPABONOCRTAIREFIJA02
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarTmpAbonoCrTaireFija02 : public CRecordSet 
{
public:
    CGrabarTmpAbonoCrTaireFija02(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpAbonoCrTaireFija02();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[11];
    int nCTipo[11];
    long nLongitud[11];
    long nLongResp[11];
    void *pVar[11];
    
    long                cliente;
    long                saldo;
    long                minimoapagar;
    long                interesadicional;
    SqlTimeStamp        fechaultimomovimiento;
    short int           flagactualizacion;
    short int           sistema;
    short int           caja;
    short int           tienda;
    long                interesadicionalprimermes;
};
#endif CGRABARTMPABONOCRTAIREFIJA02
