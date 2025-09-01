#pragma once
#include "CCuentaWebEstructuras.hpp"
#include "gnwproto.hpp"

class CCuentaWeb :public CInfoClienteWeb
{
public:	
	CCuentaWeb( long lCliente, char *cFechaTienda, short iTienda, short iCiudad, char *cIpServidorCartera, char *cIpServidorCCuenta, short iTimeOut = 0 );
	CCuentaWeb( );

	~CCuentaWeb( );

private:
	void grabarLog( char *cTexto );

public:
	CCuentaClienteWeb pCuenta[MAX_INDEX];

	bool bClienteValido, bBonificacionP;
	short iCuentas, iConvenios, iCuentasActivas, iCuentasActivasMuebles, iCuentasActivasMuebles30, iCuentasDetalle;

	SqlTimeStamp tFechaCorte;

	CDomicilioWeb domicilio;
	CLineaCreditoWeb lineaCredito;
	CParametricosWeb parametricos;
	CCuentaTotalesWeb totalesCuenta;
	CPrestamosWeb prestamos;
	CConveniosWeb convenios[MAX_INDEX];
	CAumentoLRCWeb aumentolrc;
	SInfoReestructura sInfoReestructura;
	CBonificacionPrestamo CBonificacionPrestamo;

	void iniciarCCuenta( long lCliente, char *cFechaTienda, short iTienda, short iCiudad, char *cIpServidorCartera, char *cIpServidorCCuenta, short iTimeOut = 0 );
	void leerCliente( );
	void leerDomicilio( );
	void leerTienda( );
	void leerCuenta( char *cCuenta );
	void leerTotales( );
	void leerTienda01( );
	void leerCuenta01( char *cCuenta );
	void leerTotales01( );
	void leerLineaCredito( );
	void leerParametricos( );
	bool leerCandidatoPrestamo( );
	void leerMargenCredito( );
	void leerConvenios( );
	void leerConvenios01( );
	void leerCuentasActivas( );
	void leerCandidatoAumentoLRC( );
	void simularReestructuracion( );
	void leerBonificacionPrestamos( char *cDias, char *cInteresprestamo, char *cIplazo, char *cFechaPrestamo );

private:
	char cIpServidorCartera[17], cIpServidorCCuenta[17], cFecha[12];
	long lCliente;

	short iCuenta, iTienda, iCiudadCoppel, iPlazo, iConvenio, iTimeOut, iCuentaDetalle;
	bool bCandidatoPrestamo, bBonificacionPrestamos;

	void inicializarVariables( );
	bool leerXML( char *cXml, int iTipoConsulta );
	void obtenerDato( CString sCampo, CString sValor, int iTipoConsulta );
	void leerDatos( char *cDato, int iTipoConsulta );
	void mostrarError( int iError );
};