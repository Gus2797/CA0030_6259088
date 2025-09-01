#ifndef CGRABARTMPCACARMOVSEGURO
#define CGRABARTMPCACARMOVSEGURO
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarTmpCaCarmovSeguro : public CRecordSet 
{
public:
    CGrabarTmpCaCarmovSeguro(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpCaCarmovSeguro();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[15];
    int nCTipo[15];
    long nLongitud[15];
    long nLongResp[15];
    void *pVar[15];
    
    char                clave[3];
    short int           tienda;
    short int           caja;
    long                cliente;
    long                folio;
    short int           cantidadseguros;
    short int           cantidadsegurosanterior;
    long                importe;
    char                nombreadicional[17];
    char                apellidopaternoadic[17];
    char                apellidomaternoadic[17];
    SqlTimeStamp        fecnacadic;
	short int			parentescoadic;
	short int			respuesta;
	short int			consecutivo;

};
#endif CGRABARTMPCACARMOVSEGURO
