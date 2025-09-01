#include "CGenerarImagenImpresion.h"
#include "DlgCapturarAbono.h"

#include "C_Mem.hpp"

#define TOTAL_DETALLES 11			// Total de conceptos que salen impresos en el recibo de abono.
#define LONGITUD_COLUMNA_CTAS 115	// Ancho de las columnas para las cuentas.
#define COLUM_INICIA_ENCABEZADO 640	// Columna donde inicia el nombre
#define MAX_COLUMNAS 1455			// Maximo de columnas por default en el recibo y el recibo tendra mas de 8 cuentas este numero se incrementara.

class CImpresionReciboAbonos
{
public:
	CImpresionReciboAbonos( LPVOID lpImpresion );
	~CImpresionReciboAbonos();


private:
	int iRenglon;		// Este renglon controla el esqueleto del recibo de inicio a fin.
	int iRenglonCta;	// Este renglon controla la impresion de las cuentas del cliente. inicia donde este iRenglonInicialCtas y esta en un ciclo.
	int iColMax;		// Esta variable controla la columna maxima a la cual llegara el recibo. tiene un valor minino de 1300 pix. Si el cliente
						// tiene muchas cuentas se tendra que hacer mas grande.
	int iColIniEncabezado;
	int iConvenios,iAbonoConVencidoFinalImpresion[100];

	CDlgCapturarAbono *lpImpresion;
	CGenerarImpresion *termica;

	CFont cNewFont;
	CFont *pcOldFont;

public:
	void imprimirRecibo();
	bool ObtenerVencido();
	int iFlagCapturoSeguroAdicional,iTotalConv;
	
private:
	void imprimirReciboTermica( char *cArchivoImpresion );
	int obtenerMes( char *cFecha );
	void imprimirEncabezadoTermica( );
	void nombreMes( int iMes, char *cNombreMes );
	void determinaMensajeRecibo( char *cMensaje, int iFlagNoDebe );	
	void calculaAbonoInteres( long lInteresesAdicionales, long lSuPago, long &lAbonoCuenta, long &lAbonoInteres );
	void imprimirCuenta( int iTipoDato, long &lSuAbono,long &lAhoraDebe,long &lVencido,long &lSaldaCon,int &iCtasAImp, int &iRen, bool &bAplicaBonificacion, long &lMontoClubAfiliado, int &iTipoPlanSegClub );
	void imprimirEncabezadoConvenioUnico( );
	void imprimirReciboConvenioTienda( long lTotalImporteConvenio, char *cFecha );
	void imprimirReciboConvenioCliente( long lTotalImporteConvenio, char *cFecha );
	void imprimirReciboConvenioUnico( );	
	int VerificarCuentaBcpl2(char *cadena, char *subcadena);
	void guardarCertificacionAbonos(int i); 
	bool obtenerFechaPrimerAbono(int i); 
	
	void imprimeMensajePromocionDirecta( );
	__int64 buscarFolionuevo(__int64 lFacturaX,long lCliente,long lNumeroRecibo);
	char cMensajeClienteZ[150];
};