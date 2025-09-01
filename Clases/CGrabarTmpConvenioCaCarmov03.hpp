// Consulta original solicitada:...
//  SELECT clave,tipomovimiento,cliente,tienda,ciudad,caja,factura,ejercicio,fecha,recibo,vencidoinicial,minimoinicial,anexo,efectuo,clavelocal,saldoinicial,saldofinal,saldocuenta,flagmovtosupervisor,plazoconvenio,importe,tipoconvenio,subtipoconvenio,clientelocalizar,tiposeguro,cajaoriginal,ipcarteracliente,importeventa,tarjeta,nombrecliente,tipoproducto,minimototal,saldototal,vencidototal,minimototalfinal,saldototalfinal,vencidototalfinal FROM tmpconveniocacarmov
    
#ifndef CGRABARTMPCONVENIOCACARMOV03
#define CGRABARTMPCONVENIOCACARMOV03
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarTmpConvenioCaCarmov03 : public CRecordSet 
{
public:
    CGrabarTmpConvenioCaCarmov03(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpConvenioCaCarmov03();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[38];
    int nCTipo[38];
    long nLongitud[38];
    long nLongResp[38];
    void *pVar[38];
    
    char                clave[3];
    char                tipomovimiento[3];
    long                cliente;
    short int           tienda;
    short int           ciudad;
    short int           caja;
    long                factura;
    char                ejercicio[3];
    SqlTimeStamp        fecha;
    long                recibo;
    long                vencidoinicial;
    long                minimoinicial;
    char                anexo[3];
    long                efectuo;
    char                clavelocal[3];
    long                saldoinicial;
    long                saldofinal;
    long                saldocuenta;
    char                flagmovtosupervisor[3];
    short int           plazoconvenio;
    long                importe;
    char                tipoconvenio[3];
    char                subtipoconvenio[3];
    char                clientelocalizar[3];
    char                tiposeguro[3];
    short int           cajaoriginal;
    char                ipcarteracliente[17];
    long                importeventa;
    _int64              tarjeta;
    char                nombrecliente[47];
    short int           tipoproducto;
    long                minimototal;
    long                saldototal;
    long                vencidototal;
    long                minimototalfinal;
    long                saldototalfinal;
    long                vencidototalfinal;
};
#endif CGRABARTMPCONVENIOCACARMOV03
