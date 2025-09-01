// Consulta original solicitada:...
//  SELECT clave, tipomovimiento, cliente, importe, recibo, tienda, ciudad, caja, fecha, folio, efectuo, movtoseguro, cajaoriginal, ipcarteracliente, tarjeta FROM cacarmov
    
#ifndef CGRABARTMPBENEFICIARIOSCACARMOV01
#define CGRABARTMPBENEFICIARIOSCACARMOV01
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarTmpBeneficiariosCaCarmov01 : public CRecordSet 
{
public:
    CGrabarTmpBeneficiariosCaCarmov01(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpBeneficiariosCaCarmov01();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[16];
    int nCTipo[16];
    long nLongitud[16];
    long nLongResp[16];
    void *pVar[16];
    
    char                clave[3];
    char                tipomovimiento[3];
    long                cliente;
    long                importe;
    long                recibo;
    short int           tienda;
    short int           ciudad;
    short int           caja;
    SqlTimeStamp        fecha;
    long                folio;
    long                efectuo;
    char                movtoseguro[3];
    short int           cajaoriginal;
    char                ipcarteracliente[17];
    _int64              tarjeta;
};
#endif CGRABARTMPBENEFICIARIOSCACARMOV01
