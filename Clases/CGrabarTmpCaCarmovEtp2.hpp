// Consulta original solicitada:...
//   select clave, tipomovimiento, clavelocal, cliente, tienda, ciudad, caja, fecha, importe, recibo, clienteetp, cajaoriginal, ipcarteracliente, efectuo, digito FROM cacarmov
    
#ifndef CGRABARTMPCACARMOVETP2
#define CGRABARTMPCACARMOVETP2
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarTmpCaCarmovEtp2 : public CRecordSet 
{
public:
    CGrabarTmpCaCarmovEtp2(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpCaCarmovEtp2();
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
    char                clavelocal[3];
    long                cliente;
    short int           tienda;
    short int           ciudad;
    short int           caja;
    SqlTimeStamp        fecha;
    long                importe;
    long                recibo;
    long                clienteetp;
    short int           cajaoriginal;
    char                ipcarteracliente[17];
    long                efectuo;
    short int           digito;
};
#endif CGRABARTMPCACARMOVETP2
