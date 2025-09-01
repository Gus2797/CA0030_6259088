// Consulta original solicitada:...
//  SELECT clave,tipomovimiento,clavelocal,cliente,tienda,ciudad,tiposeguro,caja,fechavencimiento,fechavencimientoanterior,cantidadsegurosanterior,fecha,efectuo,mesesvencidos,folio,importe,recibo,cantidadseguros,edad,sexo,flagseguroconyugal,bonificacion,clientelocalizar,movtoseguro,flagmontoseguro,fechanacimiento,cantidadmeses,cajaoriginal,ipcarteracliente,importeclub,tarjeta,nombrecliente,tipoproducto,minimototal,saldototal,vencidototal,minimototalfinal,saldototalfinal,vencidototalfinal FROM tmpsegurocacarmov
    
#ifndef CGRABARTMPSEGUROCACARMOV01
#define CGRABARTMPSEGUROCACARMOV01
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarTmpSeguroCaCarmov01 : public CRecordSet 
{
public:
    CGrabarTmpSeguroCaCarmov01(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpSeguroCaCarmov01();
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
    char                clavelocal[3];
    long                cliente;
    short int           tienda;
    short int           ciudad;
    char                tiposeguro[3];
    short int           caja;
    SqlTimeStamp        fechavencimiento;
    SqlTimeStamp        fechavencimientoanterior;
    short int           cantidadsegurosanterior;
    SqlTimeStamp        fecha;
    long                efectuo;
    short int           mesesvencidos;
    long                folio;
    long                importe;
    long                recibo;
    short int           cantidadseguros;
    short int           edad;
    char                sexo[3];
    char                flagseguroconyugal[3];
    long                bonificacion;
    char                clientelocalizar[3];
    char                movtoseguro[3];
    char                flagmontoseguro[3];
    SqlTimeStamp        fechanacimiento;
    short int           cantidadmeses;
    short int           cajaoriginal;
    char                ipcarteracliente[17];
    long                importeclub;
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
#endif CGRABARTMPSEGUROCACARMOV01
