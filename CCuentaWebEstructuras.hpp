#pragma once
#include <sqltime.hpp>

#define MAX_INDEX 100
#define NUM_CTAS_DETALLE 10

struct SMaestroDetalle
{
	long 	lSaldo,
			lInteresAdicional;

	short	iTipoDeduccion;

	SqlTimeStamp	cFechaUltimaCompra;

	SMaestroDetalle()
	{
		SecureZeroMemory(this, sizeof(SMaestroDetalle) - sizeof(SqlTimeStamp));
		cFechaUltimaCompra.ponerFecha(1, 1, 1900);
	};
};

struct SCuentaPerdidaDetalle
{
	long	lSaldo, 
			lInteresAdicional;

	short	iTipoDeduccion; 

	SqlTimeStamp	cFechaUltimaCompra,
					cFechaDificilCobro;

	SCuentaPerdidaDetalle()
	{
		SecureZeroMemory(this, sizeof(SCuentaPerdidaDetalle) - sizeof(SqlTimeStamp)*2);
		cFechaUltimaCompra.ponerFecha(1, 1, 1900);
		cFechaDificilCobro.ponerFecha(1, 1, 1900);
	};
};

struct CCuentaClienteWeb
{
	int iTipoDeCuenta;  //0 ropa, 1 Muebles, 2 seguros, 3 Prestamos, 4 TiempoAire, 5 Bancoppel, 6 Revolvente

	long lSaldo,
		lBase,
		lVencido,
		lMinimo,
		lSaldaCon,
		lBonificacion,
		lInteresAdicional,
		lInteresAdicionalPrimerMes,
		lFactura,
		lImporteVenta,
		lFolio,
		lPoliza,
		lPolizaAnterior,
		lDineroElectronico,
		lPrecioSeguro,
		lSaldoMesAnterior,
		lSaldoTeorico,
		lSaldaConCorte,
		lInteresSobreCompra,
		lCuentaCandidato;

	short iPlazo,
		iTienda,
		iTipoSeguro,
		iClaveConyugal,
		iCantidadSeguros,
		iCausaCancelacionClub,
		iCvesInBeneficiarios,
		iCiudad,
		iTipoVehiculo,
		iTipoCobertura,
		iModelo,
		iTipoProducto,
		iSeguroVigente,
		iMesesPagados,
		iPorcentajeBonificacion,
		iDiasTranscurridos;

	char cDescripcion[12],
		cClaveSeguro,
		cStatusSeguro,
		cClaveMovimiento,
		cTipoCancelacion,
		cClaveNoOfrecer,
		cSexoAdicional,
		cNombreAdicional[17],
		cApellidoPaternoAdic[17],
		cApellidoMaternoAdic[17],
		cClvOrigen;

	bool bCuentaZ;

	_int64  i64Poliza,
            i64IduAdicional;

	SMaestroDetalle stMaestroDetalle[NUM_CTAS_DETALLE];
	SCuentaPerdidaDetalle stCuentaPerdidaDetalle[NUM_CTAS_DETALLE];

	SqlTimeStamp tFechaVenta,
		        tFechaPrestamo,
				tFechaSaldaCon,
				tFechaVencimiento,
				tFechaUltimaCompra,
				tFechaUltimoMovimiento,
				tFechaCancelacion,
				tFechaNoOfrecer,
				tFechaAfiliacion,
				tFechaCambioBeneficiario,
				tFechaUltimoPago,
				tFechaNacimientoAdicional,
				tFechaActivacion,
				tFechaInicioVigencia,
				tFechaFinVigencia,
				tFechaSaldaConCorte;

	CCuentaClienteWeb()
	{
		SecureZeroMemory(this, sizeof(CCuentaClienteWeb) - (sizeof(SMaestroDetalle)*NUM_CTAS_DETALLE) - (sizeof(SCuentaPerdidaDetalle)*NUM_CTAS_DETALLE) - (sizeof(SqlTimeStamp)*16));
		tFechaVenta.ponerFecha(1, 1, 1900);
		tFechaPrestamo.ponerFecha(1, 1, 1900);
		tFechaSaldaCon.ponerFecha(1, 1, 1900);
		tFechaVencimiento.ponerFecha(1, 1, 1900);
		tFechaUltimaCompra.ponerFecha(1, 1, 1900);
		tFechaUltimoMovimiento.ponerFecha(1, 1, 1900);
		tFechaCancelacion.ponerFecha(1, 1, 1900);
		tFechaNoOfrecer.ponerFecha(1, 1, 1900);
		tFechaAfiliacion.ponerFecha(1, 1, 1900);
		tFechaCambioBeneficiario.ponerFecha(1, 1, 1900);
		tFechaUltimoPago.ponerFecha(1, 1, 1900);
		tFechaNacimientoAdicional.ponerFecha(1, 1, 1900);
		tFechaActivacion.ponerFecha( 1, 1, 1900);
		tFechaInicioVigencia.ponerFecha( 1, 1, 1900);
		tFechaFinVigencia.ponerFecha( 1, 1, 1900);
		tFechaSaldaConCorte.ponerFecha( 1, 1, 1900);
	};

};

struct CInfoClienteWeb
{
	char    cNombre[17],
	        cApellidoPaterno[17],
	        cApellidoMaterno[17],
			cSexo,
			cEstadoCivil;
	int	    iCiudad,
	        iColonia;
	long    lCalle,
	        lCasa;
	char    cRumbo,
	        cComplemento[32];
	bool    bBanderaUHC;
	short   iUHCManzana,
		    iUHCOtros,
		    iUHCAndador,
		    iUHCEtapa,
		    iUHCLote,
		    iUHCEdificio,
		    iUHCEntrada;
	char    cCasaPREF;

	short   iIngresoMensual;
	char    cSituacionEspecial,
	        cPuntualidad;
	short   iLimiteDeCredito,
	        iReposicionDeTarjeta;
	char    cNumDeptoOInterior[6];
	_int64  i64TelefonoCelular;
	char    cLugarDeTrabajo[22];
	int     iCiudadTrabajo,
	        iColoniaTrabajo;
	long    lCalleTrabajo,
	        lCasaTrabajo;
	char    cNumDeptoOInteriorTrabajo[6];
	short   iExtension;
	char    cNombreReferencia[17],
	        cApellidoMaternoReferencia[17],
		    cApellidoPaternoReferencia[17];

	short   iCausaSituacionEspecial,
			iIdSituacion,
			iIdmotivo,
			iIdpersona;
			
	char	cDesCuentas[256];
	       
	short	iFlagHuella,
			iFlagDescuentoEspecial,
			iFlagGrupoSemaforoCN,
			iCuentasActivas,
			iCuentasActivasMuebles,
			iCuentasActivasMuebles30;

	short iStatusAfore;
	char  cSubPuntualidad;

	short iPedirTelefono;

	_int64  i64TelefonoCliente,
			i64TelefonoTrabajo,
			i64TelefonoReferencia;

	char	cCorreo[258];

	SqlTimeStamp    tFechaAlta;
	SqlTimeStamp    tFechaNacimiento;

	CInfoClienteWeb()
	{
		SecureZeroMemory(this, sizeof(CInfoClienteWeb)-(sizeof(SqlTimeStamp)*2));
		tFechaAlta.ponerFecha(1, 1, 1900);
		tFechaNacimiento.ponerFecha(1, 1, 1900);
	};
};

struct CDomicilioWeb
{
	long lCalle,
		lCasa;
	
	short iCiudad,
		iColonia,
		iEstado;

	char cNombreCalle[22],
		cNombreCiudad[22],
		cNombreZona[32],
		cPoblacion[27],
		cNombreEstado[27],
		cMunicipio[27],
		cPlanoCoordenadas[7],
		cRumboZona[33],
		cComplemento[32],
		cRumbo;

    long lCodigopostal;

    char cDescripcionUhcManzana[32],
		cDescripcionUhcOtros[32],
		cDescripcionUhcandador[32],
		cDescripcionUhcEtapa[32],
		cDescripcionUhcLote[32],
		cDescripcionUhcEdificio[32],
		cDescripcionUhcEntrada[32];

    long lCalleUnidadHabitacional,
		lCasaUnidadHabitacional;

	CDomicilioWeb()
	{
        SecureZeroMemory(this, sizeof(CDomicilioWeb));
	};

};

struct CParametricosWeb
{
	short int   iParametricoCelulares;
	char		cModeloCelulares;
	short int	iParametricoAltoRiesgo,
				iParametricoPrestamo;
	int			iPrePuntajeAltoRiesgo,
				iPagoUltimosDoceMeses,
				iPuntajeFinalAjustado;
	SqlTimeStamp   tFechaPrimerCompra;
	
	CParametricosWeb()
	{
        SecureZeroMemory(this, sizeof(CParametricosWeb) - sizeof(SqlTimeStamp));
		tFechaPrimerCompra.ponerFecha(1, 1, 1900);
	};
};

struct CLineaCreditoWeb
{
	long lLineadeCreditoTope,
		lLineadeCreditoReal,
		lMargenCredito,
		lSaldoCliente,
		lImporteLineaRealCredito;
	int iNivelLineaCreditoReal,
		iNivelLineaCreditoTope;  
	short int iFlagCreditoClienteEsp;
	SqlTimeStamp tFechaLineadeCreditoReal,
                tFechaLineadeCreditoTope;

	CLineaCreditoWeb()
	{
		SecureZeroMemory(this, sizeof(CLineaCreditoWeb)-(sizeof(SqlTimeStamp)*2) );
		tFechaLineadeCreditoReal.ponerFecha(1, 1, 1900);
        tFechaLineadeCreditoTope.ponerFecha(1, 1, 1900);
	};
};

struct CCuentaTotalesWeb
{
	long lSaldoTotal,
		lVencidoTotal,
		lMinimoTotal,
		lSaldaConTotal,
		lBaseTotal,
		lIntAdicTotal,		
	    lInteresAdicionalPrimerMes,
		lBonificacionTotal,
		lSaldoTeoricoTotal,
		lSaldaConCorteTotal,
		lCienteCandidato;

	CCuentaTotalesWeb( )
	{
		SecureZeroMemory( this, sizeof( CCuentaTotalesWeb ) );
	};
};

struct CPrestamosWeb
{
	short iPlazo12,
		iPlazo18,
		iPlazo24,
		iPuntosIniciales, 
		iPuntajeFinal, 
		iFactorPrestamo, 
		iIdRechazo,
		iPuntosAntiguedad,
		iPuntosConsumo,
		iPuntosParPrestamo;

	long lImporte12,
		lImporteMinimo12,
		lImporte18,
		lImporteMinimo18,
		lImporte24,
		lImporteMinimo24;

	char cGrupo[3],
		cMensaje[512];

	CPrestamosWeb( )
	{
		SecureZeroMemory( this, sizeof( CPrestamosWeb ) );
	};
};

struct CConveniosWeb
{
	short iTipoCuenta,
		iTipoConvenio,
		iSubTipoConvenio,
		iPlazoConvenio;

	char cDescripcion[12];

	long lFactura, 
		lImporteConvenio,
		lEfectuoConvenio;

	bool bCuentaZ;

	SqlTimeStamp tFechaConvenio;

	CConveniosWeb( )
	{
		SecureZeroMemory( this, sizeof( CConveniosWeb ) - sizeof(SqlTimeStamp) );
		tFechaConvenio.ponerFecha(1, 1, 1900);
	};
};


struct CAumentoLRCWeb
{
	short iPuntajeFinal;

	CAumentoLRCWeb( )
	{
		SecureZeroMemory( this, sizeof( CAumentoLRCWeb ) );
	};
};

struct SInfoReestructura
{
	long    lNumCliente,
			lImp_saldo12,
            lImp_abonobase12,
			lImp_saldo18,
            lImp_abonobase18,
			lImp_saldo24,
            lImp_abonobase24,
			lImp_saldofinanciado;

	short int iEsCandidato,
		iPagoCondicionado,
		iProductoReestructura,
		iAbonosDesbloqueo,
		iTienePorcentaje;

	SInfoReestructura( )
	{
		SecureZeroMemory( this, sizeof( SInfoReestructura ) );
	};
};

struct CBonificacionPrestamo
{
	long lbonificacion,
		 linteres,
		 llPorcentaje;

	short int estado;

	char mensaje[100];

	CBonificacionPrestamo( )
	{
		SecureZeroMemory( this, sizeof( CBonificacionPrestamo ) );
	};
};