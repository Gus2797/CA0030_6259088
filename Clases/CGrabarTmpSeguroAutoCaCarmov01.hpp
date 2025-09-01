// Consulta original solicitada:...
//  SELECT clave,tipomovimiento,tienda,ciudad,cliente,caja,recibo,factura,folioanterior,importe,saldoinicial,tiposeguro,cantidadmeses,fecha,fechavencimiento,fechavencimientoanterior,fechanacimiento,efectuo,tipovehiculo,fechaactivacioncancelar,polizaanteriorcancelar,importeventacancelar,fechaventacancelar,clavelocal,clientelocalizar,ipcarteracliente,tarjeta,nombrecliente,tipoproducto,minimototal,saldototal,vencidototal,minimototalfinal,saldototalfinal,vencidototalfinal,IdPoliza FROM tmpseguroautocacarmov
    
#ifndef CGRABARTMPSEGUROAUTOCACARMOV01
#define CGRABARTMPSEGUROAUTOCACARMOV01
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarTmpSeguroAutoCaCarmov01 : public CRecordSet 
{
public:
    CGrabarTmpSeguroAutoCaCarmov01(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpSeguroAutoCaCarmov01();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[37];
    int nCTipo[37];
    long nLongitud[37];
    long nLongResp[37];
    void *pVar[37];
    
    char                clave[3];
    char                tipomovimiento[3];
    short int           tienda;
    short int           ciudad;
    long                cliente;
    short int           caja;
    long                recibo;
    long                factura;
    long                folioanterior;
    long                importe;
    long                saldoinicial;
    char                tiposeguro[3];
    short int           cantidadmeses;
    SqlTimeStamp        fecha;
    SqlTimeStamp        fechavencimiento;
    SqlTimeStamp        fechavencimientoanterior;
    SqlTimeStamp        fechanacimiento;
    long                efectuo;
    char                tipovehiculo[3];
    SqlTimeStamp        fechaactivacioncancelar;
    long                polizaanteriorcancelar;
    long                importeventacancelar;
    SqlTimeStamp        fechaventacancelar;
    char                clavelocal[3];
    char                clientelocalizar[3];
    char                ipcarteracliente[17];
    _int64              tarjeta;
    char                nombrecliente[47];
    short int           tipoproducto;
    long                minimototal;
    long                saldototal;
    long                vencidototal;
    long                minimototalfinal;
    long                saldototalfinal;
    long                vencidototalfinal;
    long                idpoliza;
};
#endif CGRABARTMPSEGUROAUTOCACARMOV01
