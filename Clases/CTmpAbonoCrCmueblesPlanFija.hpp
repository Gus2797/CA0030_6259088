#ifndef CTMPABONOCRCMUEBLESPLANFIJA
#define CTMPABONOCRCMUEBLESPLANFIJA
#include "stdafx.h"
#include <RecordSet.HPP>
class CTmpAbonoCrCmueblesPlanFija : public CRecordSet 
{
public:
    CTmpAbonoCrCmueblesPlanFija(C_ODBC *odbc_ext, const char *select=NULL);
    ~CTmpAbonoCrCmueblesPlanFija();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[7];
    int nCTipo[7];
    long nLongitud[7];
    long nLongResp[7];
    void *pVar[7];
    
    long                cliente;
    long                factura;
    long                abonosmes;
    short int           caja;
    short int           sistema;
    short int           tienda;
};
#endif CTMPABONOCRCMUEBLESPLANFIJA
