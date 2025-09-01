// Consulta original solicitada:...
//  select clave, tienda, ciudad, caja, recibo, importe, ruta, folio, cuenta, efectuo, digito, cliente, flagincluyerecibo from tmpcacarmovservicio
    
#ifndef COBTENERRECIBOJAPAC
#define COBTENERRECIBOJAPAC
#include "stdafx.h"
#include <RecordSet.hpp>
class CObtenerReciboJapac : public CRecordSet 
{
public:
    CObtenerReciboJapac(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerReciboJapac();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[14];
    int nCTipo[14];
    long nLongitud[14];
    long nLongResp[14];
    void *pVar[14];
    
    char                clave[3];
    short int           tienda;
    short int           ciudad;
    short int           caja;
    long                recibo;
    long                importe;
    long                ruta;
    long                folio;
    char                cuenta[22];
    long                efectuo;
    short int           digito;
    long                cliente;
    char                flagincluyerecibo[3];
};
#endif COBTENERRECIBOJAPAC
