// Consulta original solicitada:...
//  SELECT clave, conceptocuenta, tienda, factura, fechacompra, importe, diapago, fechavencimiento, fechaultimomovimiento, fechasaldacon, fechaconvenio, empleadoconvenio, plazoconvenio, importeconvenio, saldo, interesadicional, base, vencido, minimo, saldacon, bonificacion, supago, numeroseguros, numeromeses, flagconyugal, fechavencimientoanterior, saldaconanteriormuebles, tipoconvenio, flagcapturoconvenio, status, cantidadanteriorseguros, subtipoconvenio, interesprimermes, tipoproducto, minimototal, saldototal, vencidototal, minimototalfinal, saldototalfinal, vencidototalfinal FROM tmpcagrabarabono
    
#ifndef CTMPCAGRABARABONO
#define CTMPCAGRABARABONO
#include "stdafx.h"
#include <RecordSet.hpp>
class CTmpCaGrabarAbono : public CRecordSet 
{
public:
    CTmpCaGrabarAbono(C_ODBC *odbc_ext, const char *select=NULL);
    ~CTmpCaGrabarAbono();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[43];
    int nCTipo[43];
    long nLongitud[43];
    long nLongResp[43];
    void *pVar[43];
    
    char                clave[3];
    char                conceptocuenta[12];
    short int           tienda;
    long                factura;
    SqlTimeStamp        fechacompra;
    long                importe;
    short int           diapago;
    SqlTimeStamp        fechavencimiento;
    SqlTimeStamp        fechaultimomovimiento;
    SqlTimeStamp        fechasaldacon;
    SqlTimeStamp        fechaconvenio;
    long                empleadoconvenio;
    short int           plazoconvenio;
    long                importeconvenio;
    long                saldo;
    long                interesadicional;
    long                base;
    long                vencido;
    long                minimo;
    long                saldacon;
    long                bonificacion;
    long                supago;
    short int           numeroseguros;
    short int           numeromeses;
    short int           flagconyugal;
    SqlTimeStamp        fechavencimientoanterior;
    long                saldaconanteriormuebles;
    short int           tipoconvenio;
    short int           flagcapturoconvenio;
    char                status[3];
    short int           cantidadanteriorseguros;
    short int           subtipoconvenio;
    long                interesprimermes;
    short int           tipoproducto;
    long                minimototal;
    long                saldototal;
    long                vencidototal;
    long                minimototalfinal;
    long                saldototalfinal;
    long                vencidototalfinal;
	short int           flagcuentaperdida;
	long				descuento;
};
#endif CTMPCAGRABARABONO
