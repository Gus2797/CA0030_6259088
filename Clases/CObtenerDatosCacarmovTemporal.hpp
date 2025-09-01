// Consulta original solicitada:...
//  SELECT importe,cantidadmeses,fechavencimiento,fol_sucursal as idu_adicional,cantidadseguros,folio FROM mov_cacarmovtemporal
    
#ifndef COBTENERDATOSCACARMOVTEMPORAL
#define COBTENERDATOSCACARMOVTEMPORAL
#include "stdafx.h"
#include <RecordSet.hpp>
class CObtenerDatosCacarmovTemporal : public CRecordSet 
{
public:
    CObtenerDatosCacarmovTemporal(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerDatosCacarmovTemporal();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[9];
    int nCTipo[9];
    long nLongitud[9];
    long nLongResp[9];
    void *pVar[9];
    
    long                importe;
    short int           cantidadmeses;
    SqlTimeStamp        fechavencimiento;
    _int64              fol_sucursal;
    short int           cantidadseguros;
    long                folio;
	long                factura;
	SqlTimeStamp        fechaabonoajuste;
};
#endif COBTENERDATOSCACARMOVTEMPORAL
