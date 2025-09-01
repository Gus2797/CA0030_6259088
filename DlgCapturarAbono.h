// DlgCapturarAbono.h: archivo de encabezado
//
#define PTO_REGTEL_COPPEL           20052
#define FLAGC_AB_CONSIDERANDOCTASVDO        65
#define FLAGC_NOOFRECERCLUB					84
#define FLAGC_FUNCIONALIDAD_ETP				114
#define FLAGC_ENVIAR_TOKEN_PRESTAMOS		150

#pragma once
#include "CapturarAbono.h"
#include "gridcapturarabono.hpp"
#include "afxwin.h"
#include "griddesplegartotal.hpp"
#include "DlgCapturarClienteEtp.h"
#include "DlgCapturarNumEmpleSupervisor.h"
#include "DlgCapturarConvenio.h"
#include "DlgCapturarDatosSeguro.h"
#include "CTmpCaGrabarAbono.hpp"
#include "DlgEncuesta.h"
#include "C_FormasPCL.hpp"
#include "CargarDLL.h"
#include "sysCapturarAbono.h"
//#include "DialogoML.h"
#include "inetmen.hpp"
#include "CSocketx.hpp"
#include "CGrabarTmpSeguroCaCarmov01.hpp"
#include "CGrabarTmpAbonoCrSegurosFija01.hpp"
#include "CGrabarTmpSeguroAutoCaCarmov01.hpp"
#include "CConsultarPolizasNvas01.hpp"
#include "CMaximo.hpp"
#include "CObtenerDatosSeguroAuto.hpp"
#include "CConsultarPlanSeguroAuto.hpp"
#include "CConsultarAbonoSeguro2.hpp"
#include "CReestructuracion.h"
#include "CargarDllCS.h"
#include "COBTENERMENSAJEABONO.HPP"
#include "gnwPlanDeLealtad.h"
#include "Dialog2012.h"
#include "CContactabilidad.h"
#include "CTitularidad.h"
#include "CRespuestaPuenteEntrada.h"
#include "CRespuestaPuenteSalida.h"
#include "CConsultarMensajesCoppelMax.h"
#include "CSesion.h"
#include "CEntorno.h"
#include "CConsumirServicioRest.h"
#include "CConsultarTokenSSO.h"
#include "json\src\json.h"

//Impresiones de AutoSeguro
#define RECIBO_ABONO_POLIZAS				  3
#define IMPRMIR_POLIZA_NUEVA				  0

#define SECCION_1		1
#define SECCION_2		2
#define SECCION_3		3
#define SECCION_4		4
#define SECCION_5		5
#define SECCION_6		6
#define SECCION_7		7

#define TERMICA			1
#define MATRICIAL		2

#define CAPTURA_ABONO							1
#define CLIENTE_ILOCALIZABLE					2
#define EXCLUIRCLIENTEPARASORTEO				3
#define MOSTRAR_SITUACION_ESPECIAL				6
#define INCLUIRCARCLIENTECUENTARESTRUCTURADA	14
#define DESMARCARCLIENTECUENTARESTRUCTURADA		15
#define MARCAR_CLIENTE_LIQUIDO_CUENTA_PERDIDA		18
#define CLIENTE_ABOGADO_EXTERNO                 19
#define CLIENTES_LOCALIZAR_Y_M                  20
#define INCLUIRCLIENTEILOCALIZABLEPARACAPTURA	21
#define INCLUIRCLIENTE_VICITACAMBIO				22
#define CLIENTE_SDO_ACLARACION				    26

//identificador para mensajes
#define MSG_INVITACIONACTUALIZACIONSEGURO	32
#define MSG_BLOQUEOCAMBIOBENEFICIARIOSEGURO	598
#define MSG_BLOQUEOCANCELACIONSEGURO		602
#define MSG_BLOQUEOPAGOAPOYOADICIONAL		603
#define MSG_BLOQUEOSEGUROADICIONALBANCOPPEL	604
//3858
#define MSG_AUTOPROTECCIONNODISPONIBLE		785
#define MSG_CLUBPROTECCIONSALUDDISPONIBLE	783
#define MSG_AREAMENUCLUB					784

//Tipos de cuenta
#define CUENTA_ROPA					0
#define CUENTA_MUEBLES				1
#define CUENTA_SEGURO				2
#define CUENTA_PRESTAMOS			3
#define CUENTA_TAIRE				4
#define CUENTA_BANCOPPEL			5
#define CUENTA_REVOLVENTE			6
#define CUENTA_SEGUROAUTO			7
#define CUENTA_DINEROELECTRONICO	8
#define CUENTA_REESTRUCTURADA		9
#define CUENTA_PLANMOVISTAR			405
#define CUENTA_PLANSALUD			11

#define VALIDACION_HUELLA_CORREOS	                6  
#define VALIDACION_HUELLA_CONTACTABILIDAD	        10 
#define VALIDACION_HUELLA_SITUACIONES_ESPECIALES	14 
#define VALIDACION_HUELLA_ENCUESTAS	                15 

//TITULARIDAD:
#define VALIDACION_BIOMETRIZADA_NO_AUTORIZADA  -1
#define VALIDACION_BIOMETRIZADA_INDEFINIDA      0
#define VALIDACION_BIOMETRIZADA_ADICIONAL       1
#define VALIDACION_BIOMETRIZADA_TITULAR         2
#define VALIDACION_BIOMETRIZADA_GERENTE         1

#define RESPUESTA_CUESTION_NEGATIVA         -1
#define RESPUESTA_CUESTION_INDEFINIDA        0
#define RESPUESTA_CUESTION_POSITIVA          1

//NOMBRES DE LOS REGLONES PARA CELULARES
#define CABECERO_COLUMNA			-1
#define FACTURA						1
#define FECHA_COMPRA				2
#define IMPORTE						3
#define DOMICILIADO					4
#define TIPO_SEGURO					5
#define PLAZO						9
#define SALDO						12
#define BASE						14
#define VENCIDO						15
#define MINIMO						16
#define SALDA_CON					18
#define SU_PAGO_MINIMO				21
#define FECHA_VENCIMIENTO			24
#define FECHA_ACTIVACION			25
#define FECHA_COBERTURA				26
#define MOTOR						27
#define NUMERO_SERIE				29
#define MENSUALIDAD					30
#define POLIZACELULARES				31
#define PLACAS						32


//18890 - Plan de lealtad
#define CARACTERES_CAMPO_INTELIGENTE	320

//38632 - TokenAuth Prestamos-Popup
#define IDU_ORIGEN				1  //Constante para Origen de PopUp Prestamo Personal
#define	IDU_SERVICIO			9  //Constante para Servicio de PopUp Prestamo Personal
#define OPCION_TOKEN_AUTH	    3  //Constante para Opcion de GN290

#define IDU_SERVICIOBRM			6 //Servicio BRM

// SE AÑADE AQUI DEBIDO A COMPLICACIONES DE AÑADIRLO EN EL FLAG.HPP
#define FLAGC_MENSAJE_MORAS			302 // FLAG PARA ACTIVAR MENSAJE MORAS 


#include "CCuentaWeb.hpp"

// TEMPAPSESTRATCOB005
#include <ApiSanaTuDeudaClient.h>
#include <ParametrosApiSanaTuDeuda.h>

// Cuadro de di�logo de CDlgCapturarAbono
class CDlgCapturarAbono : public CDialog2012
{
    // Construcci�n
public:
    CDlgCapturarAbono(CWnd* pParent = NULL);	// Constructor est�ndar
    virtual ~CDlgCapturarAbono(); // destructor est�ndar   

    bool bCargaDatosSorteo;
    long lFlagHuella;
    short static const iScCA0030 = 1;
    short static const iScGN0214 = 2;

    // TEMPAPSESTRATCOB005 - SANA TU DEUDA
    bool bExisteCuentaSolex;
    #define URL_WSSANATUDEUDA       211
    #define FLAGC_SANATUDEUDA       153
    #define MENSAJE_CLIENTE_Z       3579
    #define MENSAJE_CUENTA_SOLEX    3580
    char cUrlSanaTuDeuda[1024];
    ParametrosApiSanaTuDeuda sParametrosSanaTuDeuda;
    ApiSanaTuDeudaClient apiSanaTuDeuda;
    void ValidarClienteSanaTuDeuda();
    CUtil util;

	// POP UP
	long CDlgCapturarAbono::InvitacionPrestamoPopUp( int iTienda, int  iCaja, int iCiudad, long lCliente, long lCajero, int iInvitacion, int iTitular, short iSistema );
	bool CDlgCapturarAbono::GenerarTokenSSO( long lCliente, short iTienda, short iCaja, short iSistema, long lEmpleado, char* cIpTiendaNumero);
	CConsumirServicioRest* consumirServicio;	
    CSesion* sesion;
    CEntorno* entorno;
    int iscIdOrigenConfig, iscIduServicioConfig;
	int iscIdOrigenPrestamo, iscIduServicioPrestamo, iFlagBRMPrestamoClienteN;
	CString sToken;
	CString sLeyenda;
	//Metodo para obtener token authentication
	bool CDlgCapturarAbono::GenerarToken(char *cIpTiendaLocal , int iTienda , int iSistema , int iCaja , int iServicio , char *cNombreServicio , int iOpcion);

	//BRM
	struct sConsumoBRM
	{
		int impMaxPrestar_p12;
		int impMaxPrestar_p18;
		int impMaxPrestar_p24;
		CString des_estatus;
	};

	//BRM Pop Up
	bool leerCandidatoPrestamoBRM(long lCliente);
	void mostrarPopUpPrestamoPersonal();
	long leerCandidatoPrestamoCCuenta(CString sServer, int iTienda, long lEmpleado, int iCaja, int iMuestra, long lCliente, int iSistema);
	void limpiarFolioRezagado(bool bTipoEjecucion); //***** 6267707 Cajas/Legado no hay registro en tdcheques ni en SOA *****
	void eliminarRegistroTemporalSesionTarjetaIniciarProcesoFacturacion(); //***** 6267707 Cajas/Legado no hay registro en tdcheques ni en SOA *****
	sConsumoBRM consumoBRM;
	int iEstatusApi;


    /*****/
    //Progc *Coppel
    //Variables
	string jsonConvenios;
    int iPorcentajeUtilizado, iCantidadCuentaMuebles;
    char cPuntualidadAsterisco[3], cSubPuntualidadAsterisco[3], cSituacionEspecialAsterisco, FolioClubMovSMS[9];
    int iCausaSituacionEspecialAsterisco;
    long lVencidoTiempoAireAsterisco, lAbonoBaseTiempoAireAsterisco;
    int iTotalConv;//Se agrego..
    int iFlag_Reestructuracion;
    int iflag_descuentomoracliente;
    bool bFlag_GuardoHit, bClienteReestructurado, bMostrarReestructura, bMostrarMensajeReestructura;
    CString inoTienda;
    short iDiaUltimoPago, iMesUltimoPago, iAnioUltimoPago;//15750
    __int64 i64Cliente;
    CString  cFechadominio, cFechaAfiliacion;
    short iFlagNoOfrecer, iFlagNoEnviarSMS;
    struct AutoSeguro
    {
        short int iCiudadTienda,
            iDiaActual,
            iMesActual,
            iAnioActual,
            iModelo,
            iMarca,
            iLinea,
            iTipoUso,
            iTipoVehiculo,
            iTipoCobertura,
            iMesesAsegurados,
            iTipoSeguro,
            iGastosDeAsistenciaLegal,
            iTipoCovertura,
            iFlagPoliza;

        _int64 iDaniosTerceros,
            iGastosMedicos,
            iPolizaCompleta,
            iPolizaAnterior;

        long lCliente,
            lPrimaNeta,
            lExcedente,
            lDerechoDePoliza,
            lPrimaTotal,
            lSuPago,
            lEntrego,
            lCambio,
            lPoliza,
            lRecibo,
            lIdAseguradora,
            lUdi,
            lPrimaAntesDeIva,
            lPrimaNetaAnual,
            lExcedenteAnual,
            lDerechoPolizaAnual,
            lPrimaAntesDeIvaAnual,
            lPrimaTotalAnual,
            lUdiDespuesDeIva,
            lExcedenteDespuesDeIva,
            lDerechoDePolizaDespuesDeIva,
            lUdiaAnual,
            lUdiDespuesDeIvaAnual,
            lExcedenteDespuesDeIvaAnual,
            lDerechoDePolizaDespuesDeIvaAnual;

        char cNombre[30],
            cApePaterno[30],
            cApeMaterno[30],
            cSexo,
            cTipoUso[21],
            cMarca[21],
            cLinea[31],
            cTipoVehiculo[21],
            cPlaca[11],
            cNumSerie[21],
            cConfNumSerie[21],
            cAsistenciaLegal[16],
            cClaveAmis[10],
            cDescripcionMarca[25],
            cDescripcionLinea[35];

        AutoSeguro()
        {
            SecureZeroMemory(this, sizeof(AutoSeguro));
        }
    };


	//TODO 
	//JOHN
	// MORAS
	int ConsultarImporteMoratorio();


    //Funciones
    void fnLlamarCcuenta();

	//Inicio monedas CoppelMax
	void MostrarAbonosPuntualesCoppelMax();
	void OcultarAbonosPuntualesCoppelMax();
	//Fin monedas CoppelMax

	void getDineroElectMin(); // Se obtiene el dinero electronico minimo para imprimir ticket de abonos puntuales
	void validaGanador();
	void replaceString(char *message, CString find, CString replace, char *newMessage);
    /***/

    bool validarClick(int nTmpFocus);
    void asignarFoco();
    bool validarControl(char *cCadena);
    bool validarControles();
    void menuCajas(int iOpcion);
    int desplegarDatosCliente();
    void inicializarCaptura();
    int tiposDeEtp();
    int checarSituacionEspecial(int &iSituacion, short iCausaSituacion);
    int capturarConvenio();
    void capturarDatosSeguro();
	void capturarDatosSeguroMotos(int iColX);
	void capturarDatosSeguroCelulares(int iColX);
    bool obtenerNombreFechaNacimientoCliente();
    void unionNombrex(char *cCampo, char *cTexto, int &iInicio, int iTotal);
    void checarParentesco(char *cValorParent, int iParentesco);
    void iniciarHoja(C_FormasPCL &hoja);
    void finHoja(C_FormasPCL &hoja);
    bool imprimirPolizaSeguroClub(int iCont, int iConyugal);
    long obtenerMontoSeguroClub(int iCantSeguros);
    bool obtenerDatosBeneficiarios(int iConyugal);
    bool imprimirReciboCajas(char *cImagen, long &lImporteServicio);
    bool consultaFechaAfiliacionTitular();
    void calculaAbonoInteres(long lInteresesAdicionales, long lSuPago, long &lAbonoCuenta, long &lAbonoInteres);
    bool checarPagos(int iCuentas);//alvaro

    int obtenerNumeroSeguros();
    void seguroReactivado();
    bool grabarCuentasPerdidas();
    /***Se agrego para guardar los abonos  */
    bool grabarConvenioCacarmov();//Se agrego para los convenio..
    bool grabarAbonoCacarmov();//Se agrego para los abonos..
    bool grabarAbonoSegCacarmov();//se agrego para seguros..
    bool grabarAbonoInteCacarmov();//Se agrefo para intereser..
    bool grabarAbonoSegurosCacarmov();
	bool grabarAbonoSegurosCarmovX();
	bool ValidarExisteConvenio();
    void ObtenerTipoConvenio(int Registros);
    bool ValidarConvenioUnico(int AbonoBase, int Vencido, int Pago, bool bflg_candconvunico);
    bool ObtenerMesAnio();
	int getPlazoMaximo();
    /*********************************************************/
    bool buscarNombreColonia(int &iCiudadCliente, long &lColoniaCliente, char *cNombreColonia);
    bool pedirEncuesta();
    int menuSiNoNose();
    void checarTipoEncuesta();
    void checarEncuestas();
    bool buscarClienteCrCliente(int &iCiudadCliente, long &lZonaCliente);
    bool grabarEncuesta(int iFlag);
    long totalEncuestar();
    bool obtenerDatosGnDominio();
    int buscarClienteEncuestado(int iTipo);
    int actualizarTablaCaEncuestaCliente();
    bool incrementarTablaCaEncuesta();
    void pedirPago();
    int obtenerMes(char *cFechaVencimiento);
    long obtenerTotalImporteConvenios();
    long obtenerMontoSeguro();
    void desplegarPaginaSeguros(int iFlagReactivo, int iFlagIncrementa, int iColumna, CDlgCapturarDatosSeguro &dlgCapturarDatosSeguro, int iFlagAfiliar);
    bool obtenerFlag(char cArea, int iTipo, int &iFlag);
    bool recibirPagoCa(void);
    void darVolanteMuebles(void);
    void darVolanteRopa(void);
    void compactarImpresion(C_FormasPCL &hoja);
    void encabezadoReciboCajas(C_FormasPCL &hoja);
    void encabezadoTalonCajas(C_FormasPCL &hoja, int iPagina, int iContadorSeguros);
    void imprimirTotales(C_FormasPCL &hoja, long &lUstedDebia, int iContadorSeguros, int iFlagAnexo);
    void imprimirImportesRecibo(C_FormasPCL &hoja, int iLinea, long &lUstedDebia, long &lSuAbono, long &lAhoraDebe,
        long &lAbonoTotal, long &lInteresTotal, long &lDebeTotal, long &lVencidoTotal, long &lSaldaConTotal,
        __int64 lFactura, char *cDescripcion, int iDiaVenta, int iMesVenta, int AnioVenta, long lSaldo,
        long lSuPago, long lInteresesAdicionales, long lVencidoGrid, long lSaldaConGrid, long lInteresAdiconalGrid, long lInteresMesUno);
    void fechaSaldaCon(int &iDiaS, int &iMesS, int &iAnioS);
    void obtenerDatosCrCropa(int &iDb1, int &iDb2, int &iDb3, int &iDb4, int &iDb5, char *cTexto, int &iInts);
    void determinaMensajeRecibo(char *cMensaje, int iFlagNoDebe);
    void verificarVigenciaSeguros(int iCuenta1, int iCuenta2, int iCuenta3, int iContadorSeguros, C_FormasPCL &hoja, int iIndicadorSeguro, int iFlag);
    void imprimirSeguroVencido(int iCuenta1, int iCuenta2, int iCuenta3, C_FormasPCL &hoja, int &iIndicadorSeguro, int k);
    void imprimirSeguroVigente(int iCuenta1, int iCuenta2, int iCuenta3, C_FormasPCL &hoja, int &iIndicadorSeguro, int k, int iFlag, int iContadorSeguros);
    void imprimirDescuentoConyugal();
    int obtenerClaveConyugalCrSeguros(long lFolio);
    int checarSiTieneConvenioUnico(void);
    void imprimirReciboConvenioUnico(C_FormasPCL &hoja);
    void imprimirReciboConvenioUnicoxx(C_FormasPCL &hoja, long lNumEmpleado);
    bool crearTablaTemporal();
    bool subirDatosTablaTemporal();
    bool grabarAbono();
    void buscarSeguroClub(void);
    bool grabarAbonoTablasTemporales(short &iError);
    int  menuAyudaAbonos();
    void desplegarSaldarCuenta();
    void desplegarPagoMinimoCuenta();
    void desplegarSaldarTodasCuentas();
    void desplegarPagoMinimoCuentas();
    int calcularMorasCliente();
	void iniciarCapturaConvenio(std::string jsonString);
	void setJsonConvenios(std::string jsonString);
	void registraConvenio();
	int getTipoCuenta(char *cCuenta);
	void limpiarConvenios();
    void calculadora();

    void actualizarPuntualidad();

    //nuevo
    bool grabarClienteEtpTemporal(long lSuPago);
    bool grabarCaMovimientosTemporal(int iPlazoConvenio, long lVencido, long lEmpleado,
        long lSaldo, long lSuPago, long lAbonoInteres, long lBonificacion,
        int iDiaVenta, int iMesVenta, int iAnioVenta,
        int iDiaConvenio, int iMesConvenio, int iAnioConvenio);
    bool grabarEficienciaCajeraTemporal(long lEmpleado, long lSaldo, long lSuPago, long lSaldaCon, long lVencido, int iDiaConvenio, int iMesConvenio, int iPlazoConvenio);
    bool grabarAbonoCaCarmovTemporal(char cClave, char *cEjercicio, long lFactura, long lVencido, long lMinimo, long lEmpleado,
        char *cTipoMovimiento, long lAbonoCuenta, long lSaldoNuevo, long lSaldo,
        long lImporteSaldaCon, long lSaldoFinal, char *cClienteLocalizar,
        long lFechaSaldaCon, long lImporteVenta, long lComision, int iTipoProducto, long lMinimoTotal, long lSaldoTotal, long lVencidoTotal, long lMinimoTotalFinal, long lSaldoTotalFinal, long lVencidoTotalFinal, long lBase, short iFlagCuentaPerdida, long lSaldoFinalRopa, long lSaldoFinalTasa0, long lSaldoDetalladoRopa, long lSaldoDetalladoTasa0);
    int checarVigenciaConvenio(int iDia, int iMes, int iPlazo);
    int calcularEjercicio(int iAnioVenta);
    void calcularAbonoInteres(long &lAbonoCuenta, long &lAbonoInteres, long lSuPago, long lInteresAdicional);
    long calcularSaldoNuevo(long lSaldo, long lInteresAdicional, long lSuPago, long lBonificacion, long lSaldaCon);
    long obtenerFechaSaldaCon(long lFactura, int iDiaVentaTabla, int iMesVentaTabla, int iAnioVentaTabla);
    long grabarAbonoInteresCaCarmovTemporal(long lFactura, char *cClaveCuenta, int iFlagSupervisor, long lAbonoInteres, long iAbonoCuenta,
        long lSaldo, long lInteresAdicional, long lSuPago, long lBonificacion, long lSaldaCon,
        char *cStatus, char *cLocalizar, int iAnioVenta, long lVencido, long lMinimo, bool &bContinuar, long lImporteVenta, long lComision, long iInteresPrimerMes, int iTipoProducto, long lMinimoTotal, long lSaldoTotal, long lVencidoTotal, long lMinimoTotalFinal, long lSaldoTotalFinal, long lVencidoTotalFinal, long lAbonoInteresesRopa, long lSaldoDetalladoRopa, long lAbonoInteresesTasa0, long lSaldoDetalladoTasa0, long imp_descuento);
    bool grabarConvenioCaCarmovTemporal(long lFactura, char *cClaveCuenta, long lSuPago, int iPlazoConvenio,
        long lEmpleadoMicro, long lImporteConvenio, int iFlagSupervisor, char *cStatus,
        long lMinimo, long lSaldo, int iAnioVenta, long lVencido, int iTipoConvenio, int iSubTipoConvenio, long lImporteVenta, int iTipoProducto, long lMinimoTotal, long lSaldoTotal, long lVencidoTotal, long lMinimoTotalFinal, long lSaldoTotalFinal, long lVencidoTotalFinal);

    bool grabarBonificacionCaCarmovTemporal(long lFactura, char *cClaveCuenta, long lBonificacion,
        long lVencido, long lMinimo, long lEmpleadoMicro, int iFlagSupervisor,
        char *cStatus, int iAnioVenta, char *cClienteLocalizar, long lImporteVenta, long lComision, int iTipoProducto, long lMinimoTotal, long lSaldoTotal, long lVencidoTotal, long lMinimoTotalFinal, long lSaldoTotalFinal, long lVencidoTotalFinal, long lBonificacionRopa, long lBonificacionTasa0);
    bool grabarBeneficiariosCaCarmovTemporal(long lNumeroBeneficiarios, long lEmpleadoMicro, int iTipoProducto, long lMinimoTotal, long lSaldoTotal, long lVencidoTotal, long lMinimoTotalFinal, long lSaldoTotalFinal, long lVencidoTotalFinal);

    int checarFinalDeMes(int &iMes1, int &iMes2, int &iMes3, int &iMes4, int &iMes5, int &iMes6, int &iMes7, int &iMes8, int &iMes9,
        int &iMes10, int &iMes11, int &iMes12);
    bool grabarSeguroCaCarmovTemporal(int iDiaVencimiento, int iMesVencimiento, int iAnioVencimiento, int iCantidadSeguros, long lSuPago, int iCantidadAnteriorSeguros,
        int iDiaVencimientoAnterior, int iMesVencimientoAnterior, int iAnioVencimientoAnterior, char *cClaveCuenta, char *cStatusCuenta, int iFlagConyugal, int iNumeroMeses, long lFactura, int iTipoProducto, long lMinimoTotal, long lSaldoTotal, long lVencidoTotal, long lMinimoTotalFinal, long lSaldoTotalFinal, long lVencidoTotalFinal, int iGraboAdicional);
    bool incrementarFolioCajas();
    bool grabarTmpClienteEtpCaCarmov(char *cFolioTiendaTxt);
    bool grabarTmpCaEficienciaCajeras();
    bool grabarTmpAbonoCaCarmov(char *cFolioTiendaTxt);
    bool grabarTmpCaMovimientos();
    bool grabarTmpAbonoInteresCaCarmov(char *cFolioTiendaTxt);
    bool grabarTmpConvenioCaCarmov(char *cFolioTiendaTxt);
    bool grabarTmpBonificacionCaCarmov(char *cFolioTiendaTxt);
    bool grabarTmpSeguroCaCarmov(char *cFolioTiendaTxt);
    bool grabarTemporalCarteraPrestamos(long lSaldoNuevo, long lAbonoInteres, long lAbonoCuenta, long lSuPago, char *cStatus, long lFactura, long lInteresCalculado);
    bool grabarTemporalCarteraBancoppel(long lSaldoNuevo, long lAbonoInteres, long lAbonoCuenta, long lSuPago, long lFactura, long lInteresCalculado);
    bool grabarTemporalCarteraRopa(long lSuPago, char *cStatus, long lInteresAdicional, long lAbonoInteres, long lSaldoNuevo, long lInteresPrimerMes);
    bool grabarTemporalCarteraTiempoAire(long lSuPago, char *cStatus, long lInteresAdicional, long lAbonoInteres, long lSaldoNuevo, long lInteresPrimerMes);
    bool grabarTemporalCarteraRevolvente(long lSuPago, char *cStatus, long lInteresAdicional, long lAbonoInteres, long lSaldoNuevo, long lInteresPrimerMes);
    bool grabarTemporalCarteraMuebles(long lSupago, long lFactura, char *cStatus, long lAbonoInteres, long lSaldoNuevo, long lInteresPrimerMes);
    bool grabarTemporalCarteraPlanes(long lSuPago, long lFactura);
    bool grabarTemporalCarteraSeguro(long lFactura, int iDiaVencimiento, int iMesVencimiento, int iAnioVencimiento, char *cClave, int iNumeroSeguros, int &iGraboAdicional);
    bool grabarTmpCrPrestamo();
    bool grabarTmpCrcDeudaBancoppel();
    bool grabarTmpCrCmuebles();
    bool grabarTmpCrCropa();
    bool grabarTmpCrTaire();
    bool grabarTmpCrSeguros();
    bool grabarCambioSitCte();
    bool grabarTmpCrCRevolvente();
    bool crearTablasTemporalesTienda();
    bool incrementarAcumuladoMonetarioCajas();
    bool consultarAcumuladoMonetarioCajas();
    void menuSegurosDeVida();
    void datosSeguro(long &lFolio1, long &lFolio2, int &iCantSeguro1, int &iCantSeguro2, int &iFlagConyugal1, int &iFlagConyugal2, int &iFolio1, int &iFolio2);
    bool grabarPagoServicio();
    void imprimirReciboPagoServicios(char *cImagen, long lImporteServicio);
    bool consultarImportePagoServicio(char *cClave, long &lImporteServicio);
    bool consultarCuentasPagoServicio(char *cClave, int &iCuentasServicio, char * cTipo);
    void imprimirImportePagoServicio(C_FormasPCL &hoja, int iLinea, long lImporte);
    void imprimirPagoServicios(C_FormasPCL &hoja, int &iLinea, int &iPagina, int iContadorSeguros, char *cClave, long &iUstedDebiaServicio, char *cConstante, long &lImporteServicio, long &lSuPagoServicio, long &lReciboServicio, int iFlagAnexo, long &lAcumuladoServicio, char *cTipo);

    void consultarImporteTotalPagoServicio(long &lImporteTotalServicio);
    int checarClaveGerente();

    // peticion 16596
    void cargarCampanasDE();

    //peticion 19589 CRTP
    void cargarCoppelRecompensa(int flag);
    //
// Menu Seguro Club
    void menuSegurosClub();
    bool consultarAdicional();
    void ventaClubProteccion();
    void ventaClubProteccionAdicional();
    bool tieneSeguroClub(char &cStatusSeguro, char &cTipoCan, char &cClaveNoOfrecer, long &lFolioSeguro, bool &bCteSeguro);
    void borrarSeguroClub(int iClave);
    void borrarSeguroClubCancelado(int iClave);
    void clubBeneficiarios();
    void clubDocumentacion();
    bool clubCancelacion();
    int consultarCuotaAdicionales(bool bNuevos);
    int consultarCuotaAdicionalesPS();
    void consultarCrSegurosFechaMesVence();
    bool consultarCrSegurosFechaVenceTit();
    bool imprimirPolizaSeguroClubAdicional(int iFlagImpresoraTermica);
    bool obtenerDatosBeneficiarioAdicional(int iFolioAdicional);
    short obtenerRespuestaPolizaAdicional(short iConsecutivo);
    bool grabarSeguroCaCarmovTemporalAdicional(CGrabarTmpSeguroCaCarmov01 &tmpAdicionales);
    bool grabarTemporalCarteraSeguroAdicional(CGrabarTmpAbonoCrSegurosFija01 &tmpCrSeguros);
    bool grabarTmpCacarMovSeguros();
    bool borrarTemporalesSeguroAdicional(bool bBorrar = false);
    bool imprimirReciboSeguroClubAdicional(C_FormasPCL &hoja, char * cRespuesta2, int iRenglon, int iContadorSeguros, int iFlagAnexo, int &iPagina, int &iLinea);
    void imprimirTotalesAdicional(C_FormasPCL &hoja, int iFlagAnexo, int iRenglon);
    int checarCuentaSegurosClub();
    int checarCuentaSegurosClubSMS();
    bool validarNumeroCliente(char *cTextoMsj);
    void cargarMerca360();

    bool obtenerDatosTablaTmpParaGrid();
    bool grabarTmpTdbeneficiariosaTdBeneficiarios();
    void inicializar();
    long obtenerTotalAbonoCuentasPagoServicio(long &lTotal);
    bool incrementarFolioSysFolioGlobal(__int64 &i64FolioTienda);
    bool borrarPagoServicio();
    void borrarCuentaSeguroClubGrid();
    void ponerCuentaSeguroClubGrid();
    long checarVigenciaSeguro(int iCantidadSeguros, long lTotalMinimo, long lCuotaX, long lCuotaPS, long lTotalMinimoSeguros);
    int vencidoSeguro(int iDiaVencSeg, int iMesVencSeg, int iAnioVencSeg);
    int checarCorteCajas();
    void procesoCierreCajas();
    void menuOperacionesVarias();
    long obtenerFacturaSeguroCancelado();
    bool obtenerPolizaSeguro(long &lPoliza, int iTipo);
    void obtenerMes(int iMes, char *cNomMes);
    bool datosDeCliente(int &iCasa, int &iColonia, int &iCalle, int &iCiudad, long &lCodigoPostal, char *cNombreCalle, char *cNombreZona, char *cNombreCiudad);
    bool decrementarFolioCajas();
    bool decrementarFolioSeguroCajas();
    bool decrementarFolioRecibo();
    bool borrarDatosTemporalesFijas();
    void obtenerDatosAdicional(long lFolioSeguro, char *cNombre, char *cApellidoPat, char *cApellidoMat, short &iParentesco, short &iDiaNac, short &iMesNac, short &iAnioNac);

    bool GrabarCarmovx();

    bool verificarUltimoRecibo();

    void checarEncuestaEdosCtas();
    void actualizarTablaCaEncuestaEdosCtas();
    long lFolioGrabarAbono;
    void encabezadoTalonCajasServicio(C_FormasPCL &hoja, int iPagina, int iContadorSeguros, long lReciboServicio);
    void totalesRecibo(C_FormasPCL &hoja, int iPagina, int iLinea,
        long lAcumuladoServicio, int iFlagServicio,
        long &lUstedDebiaServicio, int iContadorSeguros, int iFlagAnexo,
        int iFlagNoDebeServicio, int iCuenta1, int iCuenta2, int iCuenta3, int iIndicadorSeguro, long lAbonoTotalServicio,
        long lInteresTotalServicio, long lDebeTotalServicio, long lVencidoTotalServicio, long lSaldaConTotalServicio,
        long lSuPagoServicio, long lEntregoServicio, long lReciboServicio);

    //////////////////////************************************----------------------------
    void pagoAbonosPlanMovistar();
    long lTotalGlobalServicios;
    //////////////////////************************************----------------------------

    bool consultarFolioCajas();
    bool tieneSeguroClubConyugal(char &cStatusSeguro, char &cTipoCan, char &cClaveNoOfrecer, long &lFolioSeguro);

    bool verificarEmpleadoTdClaves(long lEmpleado, int &iEncontro);

    void obtenerTotalServicio(char cClave, int iCaja, long &lTotalServicio);
    void obtenerTotalGlobalServicio(int iCaja, long &lTotalGlobalServicio);
    void obtenerFolioServicio(long &lRecibo, char cClave, char cTipo);

    //Actualizar PLANTEL
    bool grabarTmpCrCmueblesPlanes();
    int  obtenerClaveConyugalCrSegurosAf(long lCliente);
    int  desplegarDatosClienteEtp();
    bool abrirConexionCuentaPerdida();
    void mostrarMensajeTarjetaBanco();
    void mostrarMovtosCliente();
    int checarHoraInvitacion();
    void obtenerFechaCartera();
    //void mostrarMensajeAutorizacionPrestamo();
	void validarPopUpPrestamoPersonal();
    int tiposDeEtp2();
    bool LeerTarjeta(int iOpcion, char *cTextoMsj);

    bool bCambioStatusAfore;
    int iFlagMsjAfore;
    int iTiempoMensaje;

    bool validarCaja();
    bool imprimirClausulaClub(C_FormasPCL &xHoja, int iClub, int iEstaEnfermo);
    bool imprimirNotaImportante(C_FormasPCL &xHoja, int iCont);
    void procesoGrabarGnTira(int iTipoImpresora);

    bool obtenerFlagImpresora(int &iFlagImpresoraTermica);

    //SeguroAutoProteccionCoppel
    bool capturarAbonoSeguroAuto(long lPoliza);
    bool capturarVentaSeguroAuto();
    CString obtenerPlanSeguroAuto(int iTipoSeguro);
    long obtenerCostoSeguroAuto(int iTipoSeguro, int iTipovehiculo, int iNumMeses);
    bool buscarSegurosAuto();
    bool grabarSeguroAutoCaCarmovTemporal(long lImporte, long lPrimaMes, int iFlagPoliza, long lPoliza, int iNumMeses,
        int iDiaVen, int iMesVen, int iAnioVen,
        int iDiaVAnt, int iMesVAnt, int iAnioVAnt,
        int iDiaVigencia, int iMesVigencia, int iAnioVigencia,
        int iTipoProducto, long lMinimoTotal, long lSaldoTotal, long lVencidoTotal, long lMinimoTotalFinal, long lSaldoTotalFinal, long lVencidoTotalFinal,
        int iTipovehiculo, int iDiaActi, int iMesActi, int iAnioActi, long lPolizaanteriorcancelar, long lImporteventacancelar,
        int iDiaVenta, int iMesVenta, int iAnioVenta);
    bool grabarTmpSeguroAutoCaCarmov();
    bool grabarTmpCrSegurosAuto();
    void revizarImprimirPolizaSeguroAuto(int iTipoRecibo);
    void imprimirPoliza(long lCliente, long lPoliza, int IdAseguradora, int iTipoRecibo);
    void ponerAcentoMayusculas(char *cCadena);
    void consultarEncuesta();
    void pedirEncuestaCat();
    long consultarIdAseguradora(long lFolio);
    long obtenerNumeroPoliza(int iModo);
    __int64 buscarFolionuevo(__int64 lFacturaX, long lCliente, long lNumeroRecibo);
    bool grabarCaSegurosAutoProteccion(long lFactura, long lFolioAnterior, int iImporte, int iCantidadMeses, SqlTimeStamp fechavencimiento, SqlTimeStamp fechaactivacion);
    bool obtenerDatosSeguroAuto(char *cMensaje, long lFactura, long lFolioAnterior, int importe);
    __int64 obtenerPolizaXML(long);
    bool obtenerFechaSaldaCon(int &iAnioSaldaCon, int &iMesSaldaCon, int &iDiaSaldaCon);

    //SitEsp
    bool ValidarSituacionEspecial(long lCliente, int iReglaConsulta, int iProcesoConsulta, int iArea);
    bool ConsultaMarcarSituacionEspecial(int iReglaConsulta, int iProcesoConsulta, char *cSituacionEspecial, int &iIdSituacion);
    bool grabarCrearSituacionEspecialArray(char *cJsonPostLocal, char *cMensaje);
    void obtenerSituacionEspecialRegla(int iArea, int iRegla, int iProceso, long lCliente);
    void MostrarSituacionesEnOpcion();
    bool validarTieneSitEspCliente();
    bool ConsultarPuerto(int &iPuerto);
    void tituloMostrar();
    void ModificarClienteLocalizar();

    //9923-->Club de proteccion familiar
    int llamarModuloMigracion(long lFolioSegAMigrar = 0L);
    int llamarModuloPagoApoyoAdicional();
    bool realizarProcesoCambioPolizaSeguro(long lPolizaAnterior, long lPolizaNueva);
    void generarXMLBeneficiarios(long lFolio, char *cXml);
    int llamarModuloReimpresionPolizasSeguros();
    bool validarComplementoCliente(short iTipoSeguro, int &iFlagMesRegalado);
    int CargarMensajesInvitacion();
    int  obtenerOrigenSeguro();

    //12612 Seguros Vida
    int llamarModuloSegurosVida();
    char cIpServidorControl[22];


    // Prestamos a clientes nuevos
    short validaFlagPrestamoCteN(long lNumCliente);

    /******** CAPTURA DE CORREOS *******/
    CString sCliente;
    int iFlagConsultaSC3;
    void consultarInfoEmpleadoOperacion(long lnumeroEmpleadoOperador, long &centroEmpleado);
    void validaCandidato(int &iprocesocomprobante, int &iNumAdicional_, int iNumSistema, int  &iImprimeComprobantes, long &lnota, long &LImporte, long lCentro);
    void consultarOrigenSubOrigen(long &Origen, long &subOrigen);
    void imprimirConfirmacionCorreo(char *cArea, long &lFactura, int iNumSistema, CString &opcionImpresion, int &iTipoProcesoComprobante, CString &sNumCliente);
    void capturaDeDatosEcommerce(bool &bGrabo, bool &bConsultaSorteo, int &iTipoProcesoComprobante,
        int &iImprimeComprobantes);
    /**********************************/
    //15750
    short ValidarCandidatoClub(CString Estatus, CString clavenoofrecer, CString FechaVencido);

    CUGCell m_cell;
    //VARIABLES GLOBLAES
    int iControles, iFlagMovimiento, iSituacionEspecial,
        iFlagCorte, iFlagDomiciliacionCuentas, iFlagConsultaDomiciliacion,
        iDiaEncuesta, iMesEncuesta, iAnioEncuesta, iFlagPeriodico, iFlagBanorte,
        iFlagEdoCuenta, iFlag30Dias, iTipoEncuesta,
        iFlagReactivo, iFlagNuevo, iFlagConvenioTerminado, iFlagVolante, iFlagPago,
        iFlagTdaConEstacionamiento,
        iDiaBonificacionRopa, iMesBonificacionRopa, iAnioBonificacionRopa, iFlagGraboAbono,
        iFlagCapturoBeneficiariosClub, iContador, iRegresa,
        iFlagAbonoInteres, iFlagConvenio, iFlagBonificacion, iFlagSeguro, iFlagBeneficiarios,
        iFlagClienteEtp, iFlagAbono, iFlagMovimientos, iFlagEficienciaCajera, iFlagTerminacion,
        iFlagCrPrestamo, iFlagCrRopa, iFlagCrMuebles, iFlagCrSeguro, iFlagSegAfirme, iFlagCrTaire, iFlagCrCRevolvente,
        iFlagServicio, iFlagMesUltimoMovimiento,
        iFlagCapturoServicio, iMarcaSeguroClub, iFlagExisteEncuesta, iFlagMensajeAfore, iFlagCapturaBeneficiario,
        iCasa, iColonia, iCalle, iCiudad, iClub,
        iCtaPerdida, iFlagInvitacionBanco,
        iFlagSeguroAdicional, iFlagTieneSeguroAdicional, iFlagEncuestaCat,
        iFlagSeguroAuto, iFlagCapturarTelefonos, iPedirTelefonos, iFlagAsteriscoCoppel, iFlagPromocionDirecta, iColumnaClub,
        iFlagTimeOutCCuenta, iTotalConvenio, imesesparaconvunico, iFlagContactoEfectivo, iFlagImpresionCuentasPerdidas,
        iFlagMenuDomiciliacionDeRopa, iFlagMenuDomiciliacionDeMuebles, iFlagCampoInteligentePL, iFlagCertificacionBonidicacion,iFlagTdaConCubrebocas,iFlagETP,iFlagPopUp,
		flagCuentasSeguros, iFlagSanaTuDeuda;
                            //TEMPAPSESTRATCOB005

	//VARIABLES SEGURO CELULARES
	int  iFlagSeguroCelulares;

    short iSistema, iTotalCuentas, iSegurosAdicionales, iDiaActual, iMesActual, iAnioActual, iSegurosAfirme, iTipoSeguro, iEdad,
        iFlagCapturoSeguroAdicional, iSegurosAdicionalesNuevos, iNumMesesAdicional;
    int iFoliosSegurosAdicionales[16], iFoliosAfirme[5], iFoliosSegurosActual[16];
    bool bConvenioUnicoCandidato, bProvieneDatos_OtraArea;

    //SitEsp
    int iRegla, iProceso, iIdSituacion;
    short iCausaSituacion;
    char cSituacionEspecial[3], cJsonPost[1024];
    bool bErrorWS, bFlagSituacionesInformativas, bTieneSitEsp, bAplicaAsteriscoSitEsp, bCliente_Abogado_Externo;
    char cSituacionEspecialesMandar[1024], cSituacioEspecial[5];

    short iDiaNacimiento, iEdadCliente, iMesNacimiento, iAnioNacimiento, iCajaOriginal, iCajaActual, iDiaVencimientoCPS, iMesVencimientoCPS, iAnioVencimientoCPS, iDiaVencimientoCPF, iMesVencimientoCPF, iAnioVencimientoCPF;
    int iFoco, iFlagSupervisor, iSituacion, iParentesco1, iParentesco2, iParentesco3, iParentesco4,
        iPorcentaje1, iPorcentaje2, iPorcentaje3, iCiudadGnDominio, iSiTieneSeguroClub, iPorcentaje4,
        iFlagComproSeguro, iFlagCapturoBeneficiariosClubNuevo, iNumeroMeses,
        iCuentasAgua, iCuentasSofol, iCuentasTelefono, iMesConvenio, iRegresaDll,
        iCuentasPredial, iCuentasGas, iCuentasMegacable, iCuentasNextel, iFlagMesRegalado,
        iCuentasAlestra, iCuentasCfe, iCuentasAxtel,
        iFlagCteForaneo, iFlagCapturaSurpervisor, iConyugal, iFlagDespliegaDatosZ,
        iPesosUnidadCredito, iFlagPago60Restructurado, iOpcionSeleccionada, iCuentasCablemas, iFlagMesRegaladoCPS;

    bool ShiftTab, bBanderaTieneClub, bBanderaSeguroConyugal, bBanderaSeguroVigente, bPagodeServicios, bFlagCuponCajas;
    bool bTieneSeguroAfirme, bTienePlantel, bClienteCandidato, bCteSeguro, bCandidatoCPVenta;
    short iTipoConvenio, iSubTipoConvenio, iPlazoConvenio;
    long lTotal30Dias, lTotalEdosCta, lNumeroGerente, lPagoTotal, lDineroCoppel,
        lPagoCliente, lImporteConvenios, lClienteEtp, lSaldaConAnteriorX, lNumeroRecibo,
        lEmpleadoSupervisor, lTotalSaldaCon, lMargenCredDisponible,
        lMargenCompleto, lNumeroConexion, lTotalEncuestar, lTotalAPagar, lCodigoPostal, lCiudadColoniaCte, lpreImporte;
    long lClienteDlg, lClienteMaximo, lFolioBeneficiario, lSalarioMinimo,
        lAcumulado, lAcumuladoMonetario, lConsultaAcumulado,
        lZonaEncuestado, lTelefonoEncuestado, lBaseCcuenta, lClienteLocalizar, lSaldoTmp, lAbonoTotalTmp, lCuotaClub, lCuotaPlan;
    char cFechaConvenio[10], cNombreCiudad[25], cTarjeta[18];
    char cIpServidorCredito[17], cNombre[20], cApellidoMaterno[20], cApellidoPaterno[20], cNombreAsegurado[35],
        cNombreBeneficiario1[20], cApPatBeneficiario1[20], cApMatBeneficiario1[20],
        cNombreBeneficiario2[20], cApPatBeneficiario2[20], cApMatBeneficiario2[20],
        cNombreBeneficiario3[20], cApPatBeneficiario3[20], cApMatBeneficiario3[20],
        cNombreBeneficiario4[20], cApPatBeneficiario4[20], cApMatBeneficiario4[20],
        cPuntualidad[3], cTipoEtp[3], cClaveA[3], cSexoCliente[3], cFechaMovimiento[25],
        cLocal[3], cFechaNacimiento[25], cIpServidorCartera[20], cIpServidorPlanes[22],
        cIpServidorCFE[22], cIpServidorTelmex[22], cIpServidorCentral[22], cIPServidorTiendaNumero[22];
    __int64 lTelefono1, lTelefono2, lTelefono3;
    int iMesNacimiento1, iMesNacimiento2, iMesNacimiento3, iAnioNacimiento1, iAnioNacimiento2, iAnioNacimiento3, iDiaNacimiento1, iDiaNacimiento2, iDiaNacimiento3;

    char cNombreEncuestado[20], cNombreConyuge[35], cApellidoMaternoEncuestado[20], cApellidoPaternoEncuestado[20], cNomMes[5],
        cNombrec[20], cApPaternoc[20], cApMaternoc[20], cPermiso[40], cFechaVigencia[27], cPoliza[22];
    char cSitEsp[3];
    char cTelefonoGnDominio[12];
    char cDomicilioCompleto[205], cExpedicion[55];
    char cSexo, cOcupacion[25], cMonto[10], cConceptoCta[20];
    //clv_situacion guadara pCuentaCliente.cSituacionEspecial y num_causasituacion pCuentaCliente.iCausaSituacionEspecial 
    //esto con el fin de usarlo para los calculos del pase al 100,estos se llenaran al momento de generar los movimientos
    /**************************************************************/
    char clv_situacion[3];
    //Se agrego para validar si los convenios son Validos/invalidos
    short iConConvenio, iTipoCtaConv;
    int iImporteTotalConv, iAbonoBaseTotalConv, iImporteMinimoConv, iVencidoTotalConv, iTarjetaConv, iTotalAbonos;
    int ianio, imes, iNumCandidatoUnico, iflg_candconvunico, iAbonoBaseTotalInicial, lSaldoCtaTicket, lVencidoFinalTicket, iContadorRegistros;
    //Guardar la puntualidad de abonoSegutos..
    int iTotalAbonoSeg;
    /********************************************************************/
        //Guardar la puntualidad de intereses..
    int iTotalAbonoInte;

    /********************************************************************/

    CString sNombreCliente, sApellidoPaterno, sApellidoMaterno;
    char sFechaActivacion[10], sFechaVencimiento[10], sFechaVencimientoAnterior[10];
    CString datosCliente, jsonImporte;

    // Variables para el consumo del sericio de Club de proteccion Mercadotecnia 360
	CString  datosClientes360, cNombreCliente360, cNumRecibo360,cTipoMovimiento360, cClave360;
	/*****************************************************************************/

    int iTiendaDlg, iCajaDlg, lEmpleadoDlg, iMuestraMsg, iRespuesta, iFlagDatosSeguro, iFlagMensajeHuella;
	int flagLlamaCRTP;

    bool bTieneSeguroAuto;

    int iTeclaAnterior, iFinLinea, iTipoImpresora;

    long lGteHuella, lNumeroConsulta, lPoliza;

    char cNombreSucursal[22], cDomicilio[22];

    long lKeyxEncuesta, lKeyxEdoCtas; //Keyx de las tablas de Encuestas
    long lTotalEncPeriodico, lTotalEncEdoCta; // Tabla caTotalEncuestar
    int iFlagAutoGteCargo; // Activo.. Se graba la autorizacion de gtes en cargos a ctes.
    int iStatusAfore; // Status del mensaje de afore tomado de la crcliente por el ccuenta.
    int iStatusAforeNvo;
    int iFlagTiendaLocal, iFlagSorteoBoletoPremios;
    char cFechaMasActualCte[20];
    char cEncabezado[85], cParrafo1[260], cParrafo2[210], cParrafo3[156], cParrafo4[40], cEstCivil[3];
    char cFechaTienda[12];

    bool grabarTdAutorizacionHuellas();
    void imprimirReferenciaJapac(C_FormasPCL &hoja, int iLinea);
    int iFlagJapac;

    int iTipoEtpFicha; //0 = Estacionamiento, 1= Ficha deposito (Men� ETP)

    bool bFlagSalirXCaja;
    short iRespuestaPoliza;

    int iBuscarCliente;

    __int64 i64TelefonoCelular, i64TelefonoCliente;
    int iMostrarEncuestaCat, iCiudadCliente;
    bool bPromocion;

    short iEdadMinimaClub, iEdadMaximaClub, iEdadMaximaClubAdicional, iEdadMaximaAbonoClub, iEdadMaximaAbonoClubAdic, iCambioPlanSeguroClub;

    //9923--> PARA CLUB DE PROTECCION FAMILIAR
    int iSegurosBancoppel, iSegurosDesactualizadosCoppel, iSegurosDesactualizadosBanCoppel, iFlagPermiteCancelarSeguros, iFlagPermiteSeguroAdicionalBancoppel, iFlagApoyoAdicionalPF;
    char cMensaje[1026];
    short iTipoSeguroPF;
    long lFolioNuevo, lFolioAnterior;

    //3858 --> Plan de Salud
    //Estructuras
    struct STCambioPlanes
    {
        long	lFolioPoliza;
        int		iIduAdicional;
        int		iIduPlan;
        long	lSumaAsegurada;
        long	lImporte;
        char	cFechaInicial[10];
        char	cFechaFinal[10];
        long	lRecibo;
        long	lFolioPolizaAnterior;
    };
    STCambioPlanes *stCambioPlanes;

    struct STDatosCertificacion
    {
        int     iCliente,
            iFactura,
            iTienda,
            iCaja,
            iPlazo,
            iContado,
            iIsc,
            iCredito,
            iAbonoBase,
            iAbono,
            iAbonoInteres,
            iSaldaCon,
            iDiasTranscurridos,
            iBonificacion,
            iPorcBonificacion,
            iSaldoVencido,
            iInteresAdicional,
            iSaldoAnterior,
            iSaldoDespues,
            iBonificacionCorte,
            iSaldaConCorte,
            iTipoCuenta,
			iInteresadicionalPrimerMesc;

        char 	cFechaCompra[10],
            cFechaApartir[10],
            cFechaSaldaConCorte[10],
            cFechaMovto[10];
    };
    STDatosCertificacion stDatosCertificacion[100];

    //Variables
    short iEdadMinimaPlan, iEdadMaximaPlan, iColumnaPlan, iPlanAdicionales, iPlanVigente, iMaxAdicionales;
    bool bBanderaTienePlan, bCandidatoSeguro, bCandidatoPSVenta, bCandidatoPSAbono, bTieneDatosEnTemporales, bTieneVencidoPlan, bSobrePasaEdadMaxima, bErrorProcesoPS;
    int iFlagPlandeSalud, iFlagTienePlanAdicional, iDiasVencidosPS, iSumaAseguradaPlan, iCambiosDePlan, iFlagMarcadoCandidatosCPF;
    __int64 i64PolizasPlanActual[16];
    char cConexion[40];
    int iReciboAux;

    //Funciones
    bool consultarEdadesPlanSalud(short iTipoSeguro);
    void consultarPrecioPlanSalud(long &lPrecioPlanSaludM, long &lPrecioPlanSaludD, long &lPrecioPlanSaludA, short iPlan, short iTipoSeguro);
    int consultarSumaAseguradaPlanSalud(short iPlan, short iTipoSeguro);
    void consultarMaxAdicionales(short iTipoSeguro);
    void obtenerIduConexion();
    void cargarVentaSegurosGenerales(int iTipoForma);
    void cargarAbonosCambiosDePlanSegurosGenerales();
    void borrarTemporalesPlan();
    bool grabarCacarmovPlan();
    bool grabarTdBeneficiariosPlan();
    bool grabarCarmovxPlan();
    bool grabarMaeCrSeguros();
    void compararEdadCliente();
    int imprimirPolizaCambioPlan(int indice);
    bool grabarMaeBeneficiariosSeguro();
    void consultarNombrePlan(char *cNomPlan, short iPlan, short iTipoSeguro);
    bool grabarCandidatoPlan();

    // PARA IMPRIMIR LA PROMOCION DE *COPPEL
    int iFlagAbonoTA;

    bool verificarPromocionAsteriscoCoppel();
    bool verificarPromocionesMesActual();
    void imprimirPromocionAsteriscoCoppel(C_FormasPCL &hoja, int iSistema);
    void marcarFlagPromocionTA(long lNumeroRecibo);
    bool ValidarHabilitarCambioBeneficiarioSeguro();
    void ConsultarCatalogoMensajeTienda(int iNumeroMensaje, char *cMensajeConsulta);

    void imprimirPolizaSeguroClubTermica(long lFolio, short iSeguros, short iTipoSeguro, short iRespuesta, short iEdad, short iCambioPlan);

    // Promocion Directa
    bool consultarPromocionDirecta();
    bool mensajePromocionDirecta(int iFlagImpresoraTermica);
    void imprimirMensajePromoDirectaCajas(C_FormasPCL &hoja);
    bool obtenerCiudadCandidata();
    bool ConsultaFlagImpresion();
    void ImpresionasteriscoCoppel();
    long lDepartamento, lClase, lGrupo;

    short iFlagDescuentoEspecial;
    void cargarSorteos();//bool &bEsTitular,char * cSql, bool &bProcesoHuella, long &lClienteLista, long &iFlagCausa, long &iFlagCausa2, int &iFlagRecaptura   );
    void cargarDatosSorteoNuevo(long lFlagHuella);
    bool validarSituacionEspecialEmpleados(bool &bClienteEsEmpleado);
    bool EsCampaniaSorteoEncontrada();

    void menuSegurosCoppel();
    void cargarVentaSeguroAutoProteccion();
    void menuClubDeProteccionSalud(); //3858
    bool consultarEdadesSeguroClub(short iTipoSeguro);
    bool consultarPrecioSeguroClub(long &lPrecioSeguroClub, short iSeguros, short iTipoSeguro, short iEdadAdicional = 0);
    bool consultarMontoSeguroClub(long &lMontoSeguroClub, short iSeguros, short iTipoSeguro, short iEdadAdicional = 0);
    bool obtenerPreciosSegurosAdicionales(long &lPrecioSeguroClub);
    bool consultarMaximoSegurosClubAdicional(short &iMaximoSeguros, short iSeguros, short iTipoSeguro, short iEdadAdicional);
    void consultarMensajeSeguro();
    bool grabarBeneficiariosCartera();
    bool grabarBeneficiariosCartera(long lFolio);
    bool funVerificarFoco(long lCampo);
    void grabarLog(char *cTexto);
	void grabarLogBeneficiarios(char *cTexto); 
    bool fObtenerParametrosEncuesta();
    bool fun_obtenerdescripcionestatus();
    void fValidarStatusAfore();
    void consultarMensaje(short, char*);
    bool desplegarEncuestaPC();
    bool grabarTmpCarteraRopaDetalle(long lSuPago, long lAbonoRopa, long lAbonoTasa0, char *cStatus, long lBonificacionRopa, long lBonificacionTasa0, long lAbonoInteresesRopa, long lAbonoInteresesTasa0, long lSaldaCon);
    bool obtenerDistrubuccionAbonoRopa(long lSaldoTotal, long lTotalIntereses, long lTotalAbono, long lBonificacion);
    bool grabarTmpCrCropaDetalle();
    void capturarDatosClientesIlocalizables();

    void sumarDias(short iDiasASumar, short &iDia, short &iMes, short &iAnio);
    int diasTranscurridos(char *cFechaActual, short iDia, short iMes, short iAnio);

    short iSeguroVigente;
    long lImporteAdicionalesNuevos;
    char cPlanSeguroClub[32], cMensajeSeguro[1026], cIpServidorCCuentaWeb[20];

    short iPlazoRopa, iCausaSituacionEspecial;
    int iIdSituacionEspecial;

    //DOMICILIACION
    int iFlagDomiciliacion;
    char CuentasDomiciliadas[21 * MAX_INDEX];
    void ObtenerEstatusDomiciliacionCuenta(CCuentaWeb *pCuentaCliente);
    void ImprimirEstatusDomiciliacion(int iColumna, int iRegistro);
    void CargarMenuDomiciliacion();
    //Tasa 0
    long lSaldoRopa, lSaldoTasa0, lInteresesRopa, lInteresesTasa0, lAbonoRopa, lAbonoTasa0, lAbonoInteresesRopa, lAbonoInteresesTasa0, lBonificacionRopa, lBonificacionTasa0;
    int iTipoDeduccionRopa, iTipoDeduccionTasa0, iTotalCuentasDetalle;

    // Peticion 19180
    int VerificarCuentaBcpl(char *cadena, char *subcadena);

    //18890:::Plan De Lealtad
    CPlanDeLealtad * objPlanDeLealtad;
    int iFlagRegistroPL, iFlagInvitacionPL;
    void MostrarControlesPlanLealtad();
    CPlanDeLealtad::SDatosCliente sClientePL;
    bool buscarClientePlanLealtad(char * cCadena);
    bool validarLevantarSC3();
    bool validarNumeroPL(CString sDato);
    void ValidarCaracteresCI();
    bool caracteresNoPermitidos(unsigned char cChar);
    char cOpcionPL[52];
    bool bLevantarSC3;

    //**********Peticion 18841**************
    int iFlagMoratorioCaja, iFlagMoratorioRopa, iFlagMoratorioMuebles, iFlagMoratorioGeneral, iCandidatoAprobado, iSumaInteresMoratorio,
        iMaxInteresValido, iFlagPrioridadMSJ, iAplicoDescuento, prc_descuento, imp_totaldescuento, mostroMensajeMora, iCandidatoConvenioMora, iFlagPrioridadMsjConvenio, idu_huellamora, num_gerentemora;
    char cJsonPostDescuentos[1500], urlservice[512];
    long lSaldoDetalladoTasa0, lSaldoDetalladoRopa;

	//TO DO MORAS
	int iFlagMoras;

    bool grabartmpClienteCandidatomoratorio(char *cJsonPostLocal, int Opcion, char *cMetodo);
    void CargarCA0230();
    void grabarMovimientoDescuentoMoratorio();
    bool GrabarTdAutorizacionHuellas03();
    //void GrabarContadorBitacoraDescMor();
    void MensajeReestructuraDescuentoMora();
    bool obtenerurlService(int iTipo, char *curl);

	//PET-20275
	void iniciarMovimientoOperacion();
	void terminarMovimientoOperacion();
	CString sFechaHoraInicioOperacion;

	//Peticion 29504 - Consumo Servicio Abonos Puntuales y Dinero Electronico
	bool ConsultaClienteCoppelRecompensaTuPuntualidad();
	bool ConsultarSaldoDineroElectronicoCliente(bool iRefreshDineroElectronico);
	bool bMostroMonedas;
	bool bMostroDineroElectronico;
	bool bMostrarMensajeGenerico;
	int iflagCoppelRecompensaTuPuntualidad; 
	int iflagDineroElectronico;
	int iflagNuevoMonederoElectronico;
	int iflagGanador;
	int iflagTicketsCoppelMax;
	int iCorteActual;
	int iCorteLogica;
	int iDineroElectronico;
	int iSaldoDineroElectronicoCuenta;
	int iDineroElecMin;
	short iValorAbonosPuntuales;
	void ConsultarValorAbonosPuntuales(short &iValorAbonosPuntuales);
	int iMonedasTicket;

	// FALG MENU INICIAL
	int iFlagMenuInicial;
	int iOpcionSeleccionadaMenuInicial;


    struct SRecibeDatosWSDescuentoMora
    {
        int iImporteinteresmsj, Grabocacarmov;
        int clv_Error;
        char cMensaje[1024]; //9
    };
    struct SRecibeDatosDescuentoAplicado
    {
        int num_gerentemora;
        int idu_huellamora;
        int imp_pagominmora;
        int foliofacmora;
        int imp_pagomintotalmora;
        int imp_descuentomora;
        char des_facturamora[30]; //9
    };

	//2161: AFOREValidacionesMensajes
	void inviteMensajeAfore();
	void obtenerRegion(char *cRegion);

	//37569 : SSO
	//CString consultarTokenSSO(short iIdSistema, short iIdServicio, short iOpcion, CString sNombreServicio);
	//CString sToken;
	CConsultarTokenSSO cTokenSSO;
	bool ErrorToken;

    /************************************* ESTRUCTURAS *************************************/
    AutoSeguro autoSeguro;

    // Datos del cuadro de di�logo
    enum { IDD = IDD_DLGCAPTURARABONO };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementaci�n
protected:
    //HICON m_hIcon;

    // Funciones de asignaci�n de mensajes generadas
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    //afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    GridCapturarAbono m_grid;
    CEdit m_cliente;
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    CStatic m_apellidoPaterno;
    CStatic m_apellidoMaterno;
    CStatic m_nombre;
    CStatic m_puntualidad2;
    GridDesplegarTotal m_grid2;
    CStatic m_mensaje;
    CStatic m_flecha;
    afx_msg void OnEnSetfocusCliente();

    CStatic m_barra;
    CStatic m_mensaje1;

    CStatic m_edad;
    CStatic m_msgMinimo;
    CStatic m_msgminimo2;
    CStatic m_msgminimo3;
    CStatic m_asteriscocoppel;
    CStatic m_intMesUno;
	CStatic m_dineroElectronico;
	CStatic m_leyendaAclaracion;
	Json::Value obj;
private:
    void GuardaHit(long lAbono);
    void MensajeReestructura();
    CStatic m_msgCandidatoReestructura;
    CString cJsonParams;
    CString cJsonConfiguracion;
    CString cJsonReestructura;
    CString cFechaNacimientoCliente;
    int iLevantoReestructura;
    int iFlagReestructuraDisponible;
    bool bFormalizo;
    bool bValidarMontoDesbloqueo;
    int iTestigo;

    // ########################### CONTROL UNIFICADO DE PREGUNTAS DE TITULARIDAD Y HUELLAS ###########################
    short iBiometrizadoCliente; // no asignado = 0 // adicional = 1 // titular = 2
    short iBiometrizadoGerente; // 1 = correcto  -1 incorrecto
    short iTipoCuestion;  // no asignado = 0 // adicional o titular = 1
    int iNumeroAdicional;                         
    // ############### Se prefiere su uso con GetSetTipoBiometrizado y/o GetSetCuestionTitular #######################

    //Impresion termica

    int iRenglon;		// Este renglon controla el esqueleto del recibo de inicio a fin.
    int iRenglonCta;	// Este renglon controla la impresion de las cuentas del cliente. inicia donde este iRenglonInicialCtas y esta en un ciclo.
    int iColMax;		// Esta variable controla la columna maxima a la cual llegara el recibo. tiene un valor minino de 1300 pix. Si el cliente
                        // tiene muchas cuentas se tendra que hacer mas grande.
    int iColIniEncabezado;
    int iConvenios, iAbonoConVencidoFinalImpresion[100];
    int iFlagImpresoraTermica;
    char cArchivoImpresion[40];

    CGenerarImpresion *termica;

    CFont cNewFont;
    CFont *pcOldFont;

    void imprimirReciboTermica();
    void terminarReciboTermica();
    void imprimirEncabezadoTermica();
    void nombreMes(int iMes, char *cNombreMes);
    void determinaMensajeReciboTermica(char *cMensaje, int iFlagNoDebe);
    void imprimirCuenta(int iTipoDato, long &lSuAbono, long &lAhoraDebe, long &lVencido, long &lSaldaCon, int &iCtasAImp, int &iRen, bool &bAplicaBonificacion, long &lMontoClubAfiliado, int &iTipoPlanSegClub);
    void imprimirEncabezadoConvenioUnico();
    void imprimirReciboConvenioTienda(long lTotalImporteConvenio, char *cFecha);
    void imprimirReciboConvenioCliente(long lTotalImporteConvenio, char *cFecha);
    void imprimirReciboConvenioUnico();
    int VerificarCuentaBcpl2(char *cadena, char *subcadena);
    void guardarCertificacionAbonos(int i);
    bool obtenerFechaPrimerAbono(int i);

    void imprimeMensajePromocionDirecta();
    char cMensajeClienteZ[150];

    void imprimirRecibo();
    bool ObtenerVencido();

    //CImpresiones
    void imprimirMensajeInvitacionBancoppel();
    void ImprimirMensajeActualizarDatos();
	void ImprimirTicketGanadorCoppelMax(int dineroGenerado);
	void ImprimirTicketAbonoCoppelMax();
	bool ConsultarMensajeCoppelMax(list<string> &lsMensajes, int tipoProceso);
	string SepararMiles(int valor);

    void IniciarContactabilidad();
    void EjecutarProcesoSituacionesEspeciales();
    short GetSetTipoBiometrizado(int iProcesoEjecutor);
    int GetIdSuborigen(short iComponente, int iNumSistema);
    short GetSetCuestionTitular();

public:
    CStatic m_mensaje2;
    CStatic m_mensaje3;
    CEdit m_correo;
    CEdit m_celular;
    CStatic m_lblCorreo;
    CStatic m_lblCelular;
    afx_msg void OnEnChangeCliente();
	//afx_msg void OnStnClickedLeyendaAclaracionsdo();
	//afx_msg void OnStnClickedEdad();
};
