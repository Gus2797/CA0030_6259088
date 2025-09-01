#ifndef CGRABARCRCARMOVX
#define CGRABARCRCARMOVX
#include "stdafx.h"
#include <RecordSet.HPP>
class CGrabarCrCarmovX : public CRecordSet 
{
public:
    CGrabarCrCarmovX(C_ODBC *odbc_ext, bool bFlagCommit = true, const char *select=NULL);
    ~CGrabarCrCarmovX();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[80];
    int nCTipo[80];
    long nLongitud[80];
    long nLongResp[80];
    void *pVar[80];
	bool bFlagCommit;
    
    char                clave[3];
    char                tipomovimiento[3];
    short int           tienda;
    short int           ciudad;
    long                cliente;
    long                clienteetp;
    short int           caja;
    long                recibo;
    long                factura;
    long                importe;
    long                saldoinicial;
    long                saldofinal;
    long                saldocuenta;
    long                vencidoinicial;
    long                minimoinicial;
    long                base;
    SqlTimeStamp        fechasaldacon;
    long                importesaldacon;
    char                tipoconvenio[3];
    char                subtipoconvenio[3];
    short int           plazoconvenio;
    char                ejercicio[3];
    char                clavetdaocob[3];
    char                grabacartera[3];
    char                anexo[3];
    char                clavelocal[3];
    char                clientelocalizar[3];
    char                tiposeguro[3];
    char                flagseguroconyugal[3];
    char                movtoseguro[3];
    char                flagmontoseguro[3];
    char                statusseguro[3];
    short int           causabaja;
    short int           cantidadseguros;
    short int           cantidadsegurosanterior;
    short int           cantidadmeses;
    long                bonificacion;
    short int           mesesvencidos;
    SqlTimeStamp        fechanacimiento;
    short int           edad;
    char                sexo[3];
    char                areaajuste[3];
    SqlTimeStamp        fechaabonoajuste;
    char                claveajuste[4];
    char                ajuste[4];
    short int           tiendaorigen;
    long                numerocontrol;
    long                comision;
    long                clienteremitente;
    char                tipogastoviaje[3];
    long                centro;
    char                flagincluyerecibo[3];
    long                ruta;
    long                folio;
    char                cuenta[22];
    long                iva;
    _int64              telefono;
    char                compania[3];
    char                contrato[24];
    char                credito[17];
    SqlTimeStamp        fechavencimiento;
    SqlTimeStamp        fechavencimientoanterior;
    SqlTimeStamp        fecha;
    long                efectuo;
    short int           cajaoriginal;
    _int64              foliotienda;
    char                rpu[14];
    char                flagmovtosupervisor[3];
    long                interes;
    long                importeventa;
    long                folioanterior;
    short int           digito;
    char                sac[11];
    char                ipcarteracliente[17];
	_int64				fol_sucursal;
	_int64				num_cliente;
	short int           num_movimiento;
	short int           clv_statusmovimiento;
	SqlTimeStamp        fechadocumento;
};
#endif CGRABARCRCARMOVX
