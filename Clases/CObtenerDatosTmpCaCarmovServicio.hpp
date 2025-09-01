#ifndef COBTENERDATOSTMPCACARMOVSERVICIO
#define COBTENERDATOSTMPCACARMOVSERVICIO
#include "stdafx.h"
#include <RecordSet.HPP>
class CObtenerDatosTmpCaCarmovServicio : public CRecordSet 
{
public:
    CObtenerDatosTmpCaCarmovServicio(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerDatosTmpCaCarmovServicio();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[18];
    int nCTipo[18];
    long nLongitud[18];
    long nLongResp[18];
    void *pVar[18];
    
    char                clave[3];
    short int           tienda;
    short int           ciudad;
    short int           caja;
    long                recibo;
    long                folio;
    long                importe;
    char                cuenta[22];
    long                ruta;
    char                rpu[14];
    char                compania[3];
    char                contrato[24];
    SqlTimeStamp        fechavencimiento;
    char                credito[16];
    _int64              telefono;
    long                efectuo;
	char                tipomovimiento[3];
};
#endif COBTENERDATOSTMPCACARMOVSERVICIO
