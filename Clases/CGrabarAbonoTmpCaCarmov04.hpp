// Consulta original solicitada:...
//  SELECT clave,cliente,tienda,ciudad,caja,ejercicio,factura,fecha,recibo,vencidoinicial,minimoinicial,efectuo,tipomovimiento,importe,saldocuenta,saldoinicial,saldofinal,base,edad,fechasaldacon,importesaldacon,clientelocalizar,tiposeguro,cajaoriginal,ipcarteracliente,flagmovtosupervisor,tipoconvenio,importeventa,comision,tarjeta,nombrecliente,tipoproducto,minimototal,saldototal,vencidototal,minimototalfinal,saldototalfinal,vencidototalfinal FROM  tmpabonocacarmov
    
#ifndef CGRABARABONOTMPCACARMOV04
#define CGRABARABONOTMPCACARMOV04
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarAbonoTmpCaCarmov04 : public CRecordSet 
{
public:
    CGrabarAbonoTmpCaCarmov04(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarAbonoTmpCaCarmov04();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[41];
    int nCTipo[41];
    long nLongitud[41];
    long nLongResp[41];
    void *pVar[41];
    
    char                clave[3];
    long                cliente;
    short int           tienda;
    short int           ciudad;
    short int           caja;
    char                ejercicio[3];
    long                factura;
    SqlTimeStamp        fecha;
    long                recibo;
    long                vencidoinicial;
    long                minimoinicial;
    long                efectuo;
    char                tipomovimiento[3];
    long                importe;
    long                saldocuenta;
    long                saldoinicial;
    long                saldofinal;
    long                base;
    short int           edad;
    SqlTimeStamp        fechasaldacon;
    long                importesaldacon;
    char                clientelocalizar[3];
    char                tiposeguro[3];
    short int           cajaoriginal;
    char                ipcarteracliente[17];
    char                flagmovtosupervisor[3];
    char                tipoconvenio[3];
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
	short int           plazoconvenio;
	short int           iva;
};
#endif CGRABARABONOTMPCACARMOV04
