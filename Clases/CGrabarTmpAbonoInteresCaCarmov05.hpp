// Consulta original solicitada:...
//  SELECT  clave,tipomovimiento,tienda,ciudad,cliente,caja,recibo,factura,importe,saldoinicial,saldofinal,saldocuenta,clientelocalizar,flagmovtosupervisor,clavelocal,vencidoinicial,minimoinicial,anexo,ejercicio,fecha,efectuo,tiposeguro,edad,cajaoriginal,ipcarteracliente,importeventa,comision,base,tarjeta,nombrecliente,tipoproducto,minimototal,saldototal,vencidototal,minimototalfinal,saldototalfinal,vencidototalfinal from tmpabonointerescacarmov
    
#ifndef CGRABARTMPABONOINTERESCACARMOV05
#define CGRABARTMPABONOINTERESCACARMOV05
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarTmpAbonoInteresCaCarmov05 : public CRecordSet 
{
public:
    CGrabarTmpAbonoInteresCaCarmov05(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpAbonoInteresCaCarmov05();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[40];
    int nCTipo[40];
    long nLongitud[40];
    long nLongResp[40];
    void *pVar[40];
    
    char                clave[3];
    char                tipomovimiento[3];
    short int           tienda;
    short int           ciudad;
    long                cliente;
    short int           caja;
    long                recibo;
    long                factura;
    long                importe;
    long                saldoinicial;
    long                saldofinal;
    long                saldocuenta;
    char                clientelocalizar[3];
    char                flagmovtosupervisor[3];
    char                clavelocal[3];
    long                vencidoinicial;
    long                minimoinicial;
    char                anexo[3];
    char                ejercicio[3];
    SqlTimeStamp        fecha;
    long                efectuo;
    char                tiposeguro[3];
    short int           edad;
    short int           cajaoriginal;
    char                ipcarteracliente[17];
    long                importeventa;
    long                comision;
    long                base;
    _int64              tarjeta;
    char                nombrecliente[47];
    short int           tipoproducto;
    long                minimototal;
    long                saldototal;
    long                vencidototal;
    long                minimototalfinal;
    long                saldototalfinal;
    long                vencidototalfinal;
	short int           plazoconvenio;
	short int           iva;
};
#endif CGRABARTMPABONOINTERESCACARMOV05
