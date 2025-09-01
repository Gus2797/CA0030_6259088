// Consulta original solicitada:...
//  SELECT clave,tipomovimiento,cliente,importe,recibo,tienda,ciudad,caja,fecha,folio,efectuo,movtoseguro,cajaoriginal,ipcarteracliente,bonificacion,tarjeta,nombrecliente,tipoproducto,minimototal,saldototal,vencidototal,minimototalfinal,saldototalfinal,vencidototalfinal FROM tmpbeneficiarioscacarmov
    
#ifndef CINSERTARTMPBENEFICIARIOSCACARMOV01
#define CINSERTARTMPBENEFICIARIOSCACARMOV01
#include "stdafx.h"
#include <RecordSet.hpp>
class CInsertarTmpBeneficiariosCaCarmov01 : public CRecordSet 
{
public:
    CInsertarTmpBeneficiariosCaCarmov01(C_ODBC *odbc_ext, const char *select=NULL);
    ~CInsertarTmpBeneficiariosCaCarmov01();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[25];
    int nCTipo[25];
    long nLongitud[25];
    long nLongResp[25];
    void *pVar[25];
    
    char                clave[3];
    char                tipomovimiento[3];
    long                cliente;
    long                importe;
    long                recibo;
    short int           tienda;
    short int           ciudad;
    short int           caja;
    SqlTimeStamp        fecha;
    long                folio;
    long                efectuo;
    char                movtoseguro[3];
    short int           cajaoriginal;
    char                ipcarteracliente[17];
    long                bonificacion;
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
#endif CINSERTARTMPBENEFICIARIOSCACARMOV01
