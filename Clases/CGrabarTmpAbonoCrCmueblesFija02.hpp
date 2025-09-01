// Consulta original solicitada:...
//  SELECT cliente,factura,saldo,interesadicional,fechaultimomovimiento,caja,sistema,tienda,interesadicionalprimermes FROM tmpabonocrcmuebles
    
#ifndef CGRABARTMPABONOCRCMUEBLESFIJA02
#define CGRABARTMPABONOCRCMUEBLESFIJA02
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarTmpAbonoCrCmueblesFija02 : public CRecordSet 
{
public:
    CGrabarTmpAbonoCrCmueblesFija02(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpAbonoCrCmueblesFija02();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[10];
    int nCTipo[10];
    long nLongitud[10];
    long nLongResp[10];
    void *pVar[10];
    
    long                cliente;
    long                factura;
    long                saldo;
    long                interesadicional;
    SqlTimeStamp        fechaultimomovimiento;
    short int           caja;
    short int           sistema;
    short int           tienda;
    long                interesadicionalprimermes;
};
#endif CGRABARTMPABONOCRCMUEBLESFIJA02
