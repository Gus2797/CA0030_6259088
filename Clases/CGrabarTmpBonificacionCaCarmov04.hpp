// Consulta original solicitada:...
//  SELECT clave,tipomovimiento,importe,clientelocalizar,cliente,tienda,ciudad,caja,factura,recibo,ejercicio,fecha,vencidoinicial,minimoinicial,anexo,efectuo,clavelocal,flagmovtosupervisor,cajaoriginal,ipcarteracliente,importeventa,comision,tarjeta,nombrecliente,tipoproducto,minimototal,saldototal,vencidototal,minimototalfinal,saldototalfinal,vencidototalfinal FROM tmpbonificacioncacarmov
    
#ifndef CGRABARTMPBONIFICACIONCACARMOV04
#define CGRABARTMPBONIFICACIONCACARMOV04
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarTmpBonificacionCaCarmov04 : public CRecordSet 
{
public:
    CGrabarTmpBonificacionCaCarmov04(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpBonificacionCaCarmov04();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[33];
    int nCTipo[33];
    long nLongitud[33];
    long nLongResp[33];
    void *pVar[33];
    
    char                clave[3];
    char                tipomovimiento[3];
    long                importe;
    char                clientelocalizar[3];
    long                cliente;
    short int           tienda;
    short int           ciudad;
    short int           caja;
    long                factura;
    long                recibo;
    char                ejercicio[3];
    SqlTimeStamp        fecha;
    long                vencidoinicial;
    long                minimoinicial;
    char                anexo[3];
    long                efectuo;
    char                clavelocal[3];
    char                flagmovtosupervisor[3];
    short int           cajaoriginal;
    char                ipcarteracliente[17];
    long                importeventa;
    long                comision;
    _int64              tarjeta;
    char                nombrecliente[47];
    short int           tipoproducto;
    long                minimototal;
    long                saldototal;
    long                vencidototal;
    long                minimototalfinal;
    long                saldototalfinal;
    long                vencidototalfinal;
	short int			iva;
};
#endif CGRABARTMPBONIFICACIONCACARMOV04
