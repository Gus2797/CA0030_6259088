//#include "CCuentaWeblocal.hpp" //TODO: 09/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA
#include "CCuentaWeb.hpp" //TODO: 09/09/2025, AGREGADO POR GAHL, CARGA DE LA FECHA COMPRA
#include "sysControl.h"
#include "wtienda.hpp"
#include "flags.hpp"

#include "Markup.h"

#include "ccuenta.nsmap"
#include "soapccuentaProxy.h"
//TODO: 05/09/2025, AGREGADO POR MRL, CARGA DE LA FECHA COMPRA - INICIO
#include <vector>
#include <utility>
//TODO: 05/09/2025, AGREGADO POR MRL, CARGA DE LA FECHA COMPRA - FIN

CCuentaWeb::CCuentaWeb( )
{
	//grabarLog( "Inicia CCuenta Web" );
	inicializarVariables();
}

CCuentaWeb::CCuentaWeb( long lCliente, char *cFechaTienda, short iTienda, short iCiudad, char *cIpServidorCartera, char *cIpServidorCCuenta, short iTimeOut )
{
	//grabarLog( "Inicia CCuenta Web" );
	iniciarCCuenta( lCliente, cFechaTienda, iTienda, iCiudad, cIpServidorCartera, cIpServidorCCuenta, iTimeOut );
}

CCuentaWeb::~CCuentaWeb()
{
	//grabarLog( "Termina CCuenta Web" );
}

void CCuentaWeb::iniciarCCuenta( long lCliente, char *cFechaTienda, short iTienda, short iCiudad, char *cIpServidorCartera, char *cIpServidorCCuenta, short iTimeOut )
{
	//grabarLog( "Inicia Funcion iniciarCCuenta" );
	int iAnio = 0, iMes = 0, iDia = 0;

	inicializarVariables();

	CCuentaWeb::lCliente = lCliente;
	CCuentaWeb::iTienda = iTienda;
	CCuentaWeb::iCiudadCoppel = iCiudad;
	CCuentaWeb::iTimeOut = iTimeOut;
	sprintf( CCuentaWeb::cFecha, "%s", cFechaTienda );
	sprintf( CCuentaWeb::cIpServidorCartera, "%s", cIpServidorCartera );
	sprintf( CCuentaWeb::cIpServidorCCuenta, "%s", cIpServidorCCuenta );

	iDia = atoi(CString(cFechaTienda).Mid(8, 2));
	iMes = atoi(CString(cFechaTienda).Mid(5, 2));
	iAnio = atoi(CString(cFechaTienda).Mid(0, 4));

	tFechaCorte.ponerFecha( iDia, iMes, iAnio );
}

void CCuentaWeb::inicializarVariables( )
{
	this->CInfoClienteWeb::CInfoClienteWeb();
	bCandidatoPrestamo = bClienteValido = false;
	bBonificacionPrestamos = bBonificacionP = false;
	lCliente = 0;
	iTienda = iPlazo = iCiudadCoppel = iCuentas = iConvenios = iCuentasActivas = iCuentasActivasMuebles = iCuentasActivasMuebles30 = iCuentasDetalle = 0;
	memset( cIpServidorCartera, 0, sizeof( cIpServidorCartera) );
	memset( cIpServidorCCuenta, 0, sizeof( cIpServidorCCuenta) );
	memset( cFecha, 0, sizeof( cFecha) );
	iCuenta = iConvenio = iCuentaDetalle = -1;
	tFechaCorte.ponerFecha(1, 1, 1900);

	for ( int i = 0; i < MAX_INDEX; i++ )
	{
		memset(&pCuenta[i], 0, sizeof(CCuentaClienteWeb) - (sizeof(SMaestroDetalle)*NUM_CTAS_DETALLE) - (sizeof(SCuentaPerdidaDetalle)*NUM_CTAS_DETALLE) - (sizeof(SqlTimeStamp)*16));
		pCuenta[i].tFechaVenta.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaPrestamo.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaSaldaCon.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaVencimiento.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaUltimaCompra.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaUltimoMovimiento.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaCancelacion.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaNoOfrecer.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaAfiliacion.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaCambioBeneficiario.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaUltimoPago.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaNacimientoAdicional.ponerFecha(1, 1, 1900);
		pCuenta[i].tFechaActivacion.ponerFecha( 1, 1, 1900);
		pCuenta[i].tFechaInicioVigencia.ponerFecha( 1, 1, 1900);
		pCuenta[i].tFechaFinVigencia.ponerFecha( 1, 1, 1900);
		pCuenta[i].tFechaSaldaConCorte.ponerFecha( 1, 1, 1900);
	}
}

//bool CCuentaWeb::leerXML( char *cXml, int iTipoConsulta ) //TODO: 04/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA PASO 3
bool CCuentaWeb::leerXML( char *cXml = "", int iTipoConsulta = CONSULTA_CUENTA ) //TODO: 04/09/2025, AGREGADO POR GAHL, CARGA DE LA FECHA COMPRA
{
	bool bRegresa = true;
	CString sXML, sCampo, sValor;
	//TODO: 04/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - INICIO
	/*CMarkup XML;
	
	sXML.Format("%s", cXml);
	
	XML.SetDoc(sXML);
	
	if ( XML.FindElem( "table" ) )
	{
		while ( XML.FindChildElem("row") )
		{
			if ( XML.IntoElem() )
			{
				while ( XML.FindChildElem( ) )
				{
					sCampo = XML.GetChildTagName();
					sCampo.Trim();
					if(sCampo == TEXTO_DETALLECUENTA)
					{
						iCuentaDetalle++;
						iCuentasDetalle++;
						if ( XML.IntoElem() )
						{
							while ( XML.FindChildElem( ) )
							{
								sCampo = XML.GetChildTagName();
								sCampo.Trim();
								sValor = XML.GetChildData( );
								sValor.Trim();
								obtenerDato(sCampo, sValor, iTipoConsulta ); //TODO: 04/09/2025, GAHL, CARGA DE LA FECHA COMPRA PASO 4
								//TODO: 04/09/2025, GAHL, IMPLEMENTAR LOG POR CADA CAMPO O TODOS LOS CAMPOS QUE SE OCUPEN DEL XML (FECHAVENTA)
							}
						}
						XML.OutOfElem();
					}
					else
					{
						sValor = XML.GetChildData( );
						sValor.Trim();
						obtenerDato(sCampo, sValor, iTipoConsulta ); 
					}
				}
			}
			XML.OutOfElem();
		}
	}*/
	//TODO: 04/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - FIN
	//TODO: 05/09/2025, AGREGADO POR MRL, CARGA DE LA FECHA COMPRA - INICIO
	std::vector<std::pair<CString, CString>> xml;
	
	xml.push_back(std::make_pair("tipocuenta", "1"));
	xml.push_back(std::make_pair("fechaventa", "2025-03-11"));
	xml.push_back(std::make_pair("plazo", "12"));
	xml.push_back(std::make_pair("interessobrecompra", "570"));
	xml.push_back(std::make_pair("importeventa", "2348"));
	xml.push_back(std::make_pair("abonobase", "188"));
	xml.push_back(std::make_pair("saldacon", "1536"));
	xml.push_back(std::make_pair("diastranscurridos", "100"	));
	xml.push_back(std::make_pair("bonificacion", "147"));
	xml.push_back(std::make_pair("porcentajebonificacion", "2580"));
	xml.push_back(std::make_pair("vencido", "187"));
	xml.push_back(std::make_pair("interesadicional", "0"));
	xml.push_back(std::make_pair("saldo", "1683"));
	xml.push_back(std::make_pair("intprimermes", "0"));
	xml.push_back(std::make_pair("factura", "804460"));
	xml.push_back(std::make_pair("tienda", "212"));

	for (auto it: xml) {
		sCampo = it.first;
		sValor = it.second;
		obtenerDato(sCampo, sValor, iTipoConsulta );
	}
	//TODO: 05/09/2025, AGREGADO POR MRL, CARGA DE LA FECHA COMPRA - FIN
	return bRegresa;
}

void CCuentaWeb::obtenerDato( CString sCampo, CString sValor, int iTipoConsulta ) //TODO: 04/09/2025, GAHL, CARGA DE LA FECHA COMPRA PASO 5
{
	char cTexto[20] = {0};

	if ( iTipoConsulta == CONSULTA_CUENTA )
	{
		if ( sCampo == TEXTO_TIPOCUENTA || sCampo == TEXTO_NUM_TIPODECUENTA )
		{
			iCuenta ++;
			if ( sCampo == TEXTO_TIPOCUENTA )
			{
				iCuentas ++;
			}			
			pCuenta[iCuenta].iTipoDeCuenta = atoi( sValor );
		}
		else if ( sCampo == TEXTO_SALDO || sCampo == TEXTO_IMP_SALDO )
		{
			pCuenta[iCuenta].lSaldo = atol( sValor );
		}
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - INICIO
		/*else if ( sCampo == TEXTO_SALDOTEORICO || sCampo == TEXTO_IMP_SALDOTEORICO )
		{
			pCuenta[iCuenta].lSaldoTeorico = atol( sValor );
		}*/
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - FIN
		else if ( sCampo == TEXTO_INTERESADICIONAL || sCampo == TEXTO_IMP_INTERESADICIONAL )
		{
			pCuenta[iCuenta].lInteresAdicional = atol( sValor );
		}
		else if ( sCampo == TEXTO_ABONOBASE || sCampo == TEXTO_IMP_ABONOBASE )
		{
			pCuenta[iCuenta].lBase = atol( sValor );
		}
		else if ( sCampo == TEXTO_PLAZO )
		{
			pCuenta[iCuenta].iPlazo = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_VENCIDO || sCampo == TEXTO_IMP_VENCIDO )
		{
			pCuenta[iCuenta].lVencido = atol( sValor );
		}
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - INICIO
		/*else if ( sCampo == TEXTO_MINIMO || sCampo == TEXTO_IMP_MINIMO )
		{
			pCuenta[iCuenta].lMinimo = atol( sValor );
		}*/
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - FIN
		else if ( sCampo == TEXTO_BONIFICACION || sCampo == TEXTO_IMP_BONIFICACION )
		{
			pCuenta[iCuenta].lBonificacion = atol( sValor );
		}
		else if ( sCampo == TEXTO_INTPRIMERMES || sCampo == TEXTO_IMP_INTPRIMERMES )
		{
			pCuenta[iCuenta].lInteresAdicionalPrimerMes = atol( sValor );
		}
		else if ( sCampo == TEXTO_SALDACON || sCampo == TEXTO_IMP_SALDACON )
		{
			pCuenta[iCuenta].lSaldaCon = atol( sValor );
		}
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - INICIO
		/*else if ( sCampo == TEXTO_FECHASALDACON )
		{
			pCuenta[iCuenta].tFechaSaldaCon.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}*/
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - FIN
		else if ( sCampo == TEXTO_FACTURA )
		{
			pCuenta[iCuenta].lFactura = atol( sValor );
		}
		else if ( sCampo == TEXTO_IMPORTEVENTA || sCampo == TEXTO_IMPORTEPRESTAMO )
		{
			pCuenta[iCuenta].lImporteVenta = atol( sValor );
		}
		else if ( sCampo == TEXTO_FECHAVENTA )
		{
			pCuenta[iCuenta].tFechaVenta.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - INICIO
		/*else if ( sCampo == TEXTO_FECHAPRESTAMO )
		{
			pCuenta[iCuenta].tFechaPrestamo.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_DESCRIPCION )
		{
			sprintf( pCuenta[iCuenta].cDescripcion, "%.10s", sValor );
		}*/
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - FIN
		else if ( sCampo == TEXTO_TIENDA )
		{
			pCuenta[iCuenta].iTienda = (short) atoi( sValor );
		}
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - INICIO
		/*else if ( sCampo == TEXTO_FECHAULTCOMPRA )
		{
			pCuenta[iCuenta].tFechaUltimaCompra.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_FECHAULTIMOMOVIMIENTO )
		{
			pCuenta[iCuenta].tFechaUltimoMovimiento.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_CLAVESEGURO )
		{
			if ( sValor == "" )
			{
				pCuenta[iCuenta].cClaveSeguro = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				pCuenta[iCuenta].cClaveSeguro = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_STATUSSEGURO || sCampo == TEXTO_CLV_STATUS)
		{
			if ( sValor == "" )
			{
				pCuenta[iCuenta].cStatusSeguro = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				pCuenta[iCuenta].cStatusSeguro = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_CLAVEMOVIMIENTO )
		{
			if ( sValor == "" )
			{
				pCuenta[iCuenta].cClaveMovimiento = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				pCuenta[iCuenta].cClaveMovimiento = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_TIPOSEGURO || sCampo == TEXTO_IDU_SEGURO )
		{
			pCuenta[iCuenta].iTipoSeguro = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_FOLIO )
		{
			pCuenta[iCuenta].lFolio = atol( sValor );
		}
		else if ( sCampo == TEXTO_CLAVECONYUGAL || sCampo == TEXTO_OPC_TIPOCLIENTE )
		{
			pCuenta[iCuenta].iClaveConyugal = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_CANTIDADSEGUROS || sCampo == TEXTO_IDU_PLAN)
		{
			pCuenta[iCuenta].iCantidadSeguros = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_TIPOCANCELACION )
		{
			if ( sValor == "" )
			{
				pCuenta[iCuenta].cTipoCancelacion = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				pCuenta[iCuenta].cTipoCancelacion = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_CAUSACANCELACIONCLUB )
		{
			pCuenta[iCuenta].iCausaCancelacionClub = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_FECHACANCELACION || sCampo == TEXTO_FEC_CANCELACION )
		{
			pCuenta[iCuenta].tFechaCancelacion.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_CLAVENOOFRECER )
		{
			if ( sValor == "" )
			{
				pCuenta[iCuenta].cClaveNoOfrecer = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				pCuenta[iCuenta].cClaveNoOfrecer = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_FECHANOOFRECER )
		{
			pCuenta[iCuenta].tFechaNoOfrecer.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_FECHAAFILIACION || sCampo == TEXTO_FEC_AFILIACION)
		{
			pCuenta[iCuenta].tFechaAfiliacion.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_FECHACAMBIOBENEFICIARIO )
		{
			pCuenta[iCuenta].tFechaCambioBeneficiario.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_FECHAUTIMOPAGO || sCampo == TEXTO_FEC_ULTIMOABONO )
		{
			pCuenta[iCuenta].tFechaUltimoPago.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_FECHAVENCIMIENTO )
		{
			pCuenta[iCuenta].tFechaVencimiento.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_CVESINBENEFICIARIOS )
		{
			pCuenta[iCuenta].iCvesInBeneficiarios = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_SEXOADICIONAL || sCampo == TEXTO_CLV_SEXO )
		{
			if ( sValor == "" )
			{
				pCuenta[iCuenta].cSexoAdicional = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				pCuenta[iCuenta].cSexoAdicional = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_FECHANACIMIENTOADICIONAL || sCampo == TEXTO_FEC_NACIMIENTO )
		{
			pCuenta[iCuenta].tFechaNacimientoAdicional.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_NOMBREADICIONAL || sCampo == TEXTO_NOM_ADICIONAL )
		{
			sprintf( pCuenta[iCuenta].cNombreAdicional, "%s", sValor );
		}
		else if ( sCampo == TEXTO_APELLIDOPATERNOADIC || sCampo == TEXTO_NOM_APELLIDOPATERNO )
		{
			sprintf( pCuenta[iCuenta].cApellidoPaternoAdic, "%s", sValor );
		}
		else if ( sCampo == TEXTO_APELLIDOMATERNOADIC || sCampo == TEXTO_NOM_APELLIDOMATERNO )
		{
			sprintf( pCuenta[iCuenta].cApellidoMaternoAdic, "%s", sValor );
		}
		else if ( sCampo == TEXTO_POLIZA )
		{
			pCuenta[iCuenta].lPoliza = atol( sValor );
		}
		else if ( sCampo == TEXTO_CIUDAD )
		{
			pCuenta[iCuenta].iCiudad = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_TIPOVEHICULO )
		{
			pCuenta[iCuenta].iTipoVehiculo = (short) atoi( sValor );
		}				
		else if ( sCampo == TEXTO_TIPOCOBERTURA )
		{
			pCuenta[iCuenta].iTipoCobertura = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_MODELO )
		{
			pCuenta[iCuenta].iModelo = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_FECHAACTIVACION )
		{
			pCuenta[iCuenta].tFechaActivacion.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_POLIZAANTERIOR )
		{
			pCuenta[iCuenta].lPolizaAnterior = atol( sValor );
		}
		else if ( sCampo == TEXTO_SALDOALAFECHA )
		{
			pCuenta[iCuenta].lDineroElectronico = atol( sValor );
		}
		else if ( sCampo == TEXTO_FLAG_CUENTA_PERDIDA )
		{
			pCuenta[iCuenta].bCuentaZ = true;
		}
		else if ( sCampo == TEXTO_TIPOPRODUCTO || sCampo == TEXTO_IDU_PARENTESCO )
		{
			pCuenta[iCuenta].iTipoProducto = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_PRECIOSEGUROAUTO )
		{
			pCuenta[iCuenta].lPrecioSeguro = atol( sValor );
		}
		else if ( sCampo == TEXTO_SEGUROAUTOVIGENTE )
		{
			pCuenta[iCuenta].iSeguroVigente = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_MESESPAGADOS )
		{
			pCuenta[iCuenta].iMesesPagados = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_SALDOMESANTERIOR )
		{
			pCuenta[iCuenta].lSaldoMesAnterior = atol( sValor );
		}
		else if ( sCampo == TEXTO_SALDO_DETALLE )
		{
			pCuenta[iCuenta].stMaestroDetalle[iCuentaDetalle].lSaldo = atol( sValor );
		}
		else if ( sCampo == TEXTO_INTERESADICIONAL_DETALLE )
		{
			pCuenta[iCuenta].stMaestroDetalle[iCuentaDetalle].lInteresAdicional = atol( sValor );
		}
		else if ( sCampo == TEXTO_TIPODEDUCCION_DETALLE )
		{
			pCuenta[iCuenta].stMaestroDetalle[iCuentaDetalle].iTipoDeduccion = (short) atol( sValor );
		}
		else if ( sCampo == TEXTO_FECHAULTIMACOMPRA_DETALLE )
		{
			//sprintf(pCuenta[iCuenta].stMaestroDetalle[iCuentaDetalle].cFechaUltimaCompra,"%s", sValor);
			pCuenta[iCuenta].stMaestroDetalle[iCuentaDetalle].cFechaUltimaCompra.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_SALDO_CTA_PERDIDA )
		{
			pCuenta[iCuenta].stCuentaPerdidaDetalle[iCuentaDetalle].lSaldo = atol( sValor );
		}
		else if ( sCampo == TEXTO_INTERESADICIONAL_CTA_PERDIDA )
		{
			pCuenta[iCuenta].stCuentaPerdidaDetalle[iCuentaDetalle].lInteresAdicional = atol( sValor );
		}
		else if ( sCampo == TEXTO_TIPODEDUCCION_CTA_PERDIDA )
		{
			pCuenta[iCuenta].stCuentaPerdidaDetalle[iCuentaDetalle].iTipoDeduccion = (short) atol( sValor );
		}
		else if ( sCampo == TEXTO_FECHAULTIMACOMPRA_CTA_PERDIDA )
		{
			//sprintf(pCuenta[iCuenta].stCuentaPerdidaDetalle[iCuentaDetalle].cFechaUltimaCompra,"%s", sValor);
			pCuenta[iCuenta].stCuentaPerdidaDetalle[iCuentaDetalle].cFechaUltimaCompra.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_FECHADIFICILCOBRO_CTA_PERDIDA )
		{
			//sprintf(pCuenta[iCuenta].stCuentaPerdidaDetalle[iCuentaDetalle].cFechaDificilCobro,"%s", sValor);
			pCuenta[iCuenta].stCuentaPerdidaDetalle[iCuentaDetalle].cFechaDificilCobro.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_FOL_POLIZA )
		{
			pCuenta[iCuenta].i64Poliza = _atoi64( sValor );
		}
		else if ( sCampo == TEXTO_IDU_ADICIONAL )
		{
			pCuenta[iCuenta].i64IduAdicional = _atoi64( sValor );
		}
		else if ( sCampo == TEXTO_CLV_ORIGEN )
		{
			if ( sValor == "" )
			{
				pCuenta[iCuenta].cClvOrigen = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				pCuenta[iCuenta].cClvOrigen = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_FEC_INICIOVIGENCIA )
		{
			pCuenta[iCuenta].tFechaInicioVigencia.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_FEC_FINVIGENCIA )
		{
			pCuenta[iCuenta].tFechaFinVigencia.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_SALDACONCORTE )
		{
			pCuenta[iCuenta].lSaldaConCorte = atol( sValor );
		}*/
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - FIN
		else if ( sCampo == TEXTO_PORCENTAJEBONIFICACION )
		{
			pCuenta[iCuenta].iPorcentajeBonificacion = (short) atoi( sValor );
		}
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - INICIO
		/*else if ( sCampo == TEXTO_FECHASALDACONCORTE )
		{
			pCuenta[iCuenta].tFechaSaldaConCorte.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}*/
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - FIN
		else if ( sCampo == TEXTO_INTERESSOBRECOMPRA )
		{
			pCuenta[iCuenta].lInteresSobreCompra = atol( sValor );
		}
		else if ( sCampo ==  TEXTO_DIASTRANSCURRIDOS)
		{
			pCuenta[iCuenta].iDiasTranscurridos = atoi( sValor );
		}
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - INICIO
		/*else if ( sCampo ==  TEXTO_CUENTACANDIDATA || sCampo == TEXTO_CTECANDIDATOMORA)
		{
			pCuenta[iCuenta].lCuentaCandidato = atoi( sValor );
		}*/
		//TODO: 05/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - FIN
	}
	//TODO: 04/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - INICIO
	/*else if ( iTipoConsulta == CONSULTA_DATOS )
	{
		if ( sCampo == TEXTO_NOMBRE )
		{
			sprintf( cNombre, "%s", sValor );

			if ( !sValor.IsEmpty() && sValor != "-1" )
			{
				bClienteValido = true;
			}
		}
		else if ( sCampo == TEXTO_APELLIDOPATERNO )
		{
			sprintf( cApellidoPaterno, "%s", sValor );
		}
		else if ( sCampo == TEXTO_APELLIDOMATERNO )
		{
			sprintf( cApellidoMaterno, "%s", sValor );
		}
		else if ( sCampo == TEXTO_TELEFONOCLIENTE )
		{
			i64TelefonoCliente = _atoi64( sValor );
		}
		else if ( sCampo == TEXTO_PEDIRTELEFONO )
		{
			iPedirTelefono = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_CIUDAD_CLIENTE )
		{
			iCiudad = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_COLONIA )
		{
			iColonia = atoi( sValor );
		}
		else if ( sCampo == TEXTO_CALLE )
		{
			lCalle = atol( sValor );
		}
		else if ( sCampo == TEXTO_CASA )
		{
			lCasa = atol( sValor );
		}
		else if ( sCampo == TEXTO_RUMBO )
		{
			if ( sValor == "" )
			{
				cRumbo = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				cRumbo = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_COMPLEMENTO )
		{
			sprintf( cComplemento, "%s", sValor );
		}
		else if ( sCampo == TEXTO_UHC )
		{
			if ( sValor = "1" )
			{
				bBanderaUHC = true;
			}
			else
			{
				bBanderaUHC = false;
			}
		}
		else if ( sCampo == TEXTO_NUMDEPTOINTERIOR )
		{
			sprintf( cNumDeptoOInterior, "%s", sValor );
		}
		else if ( sCampo == TEXTO_TELEFONOCELULAR )
		{
			i64TelefonoCelular = _atoi64( sValor ); 
		}
		else if ( sCampo == TEXTO_CASAPREF )
		{
			sprintf( cTexto, "%s", sValor );
			cCasaPREF = cTexto[0];
		}
		else if ( sCampo == TEXTO_FECHANACIMIENTO )
		{
			tFechaNacimiento.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_EDOCIVIL )
		{
			if ( sValor == "" )
			{
				cEstadoCivil = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				cEstadoCivil = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_SEXO )
		{
			if ( sValor == "" )
			{
				cSexo = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				cSexo = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_SITUACIONESPECIAL )
		{
			if ( sValor == "" )
			{
				cSituacionEspecial = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				cSituacionEspecial = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_CAUSASITESPECIAL )
		{
			iCausaSituacionEspecial = (short) atoi( sValor );
		}
		else if( sCampo == TEXTO_IDSITUACIONESPECIAL )
		{
			iIdSituacion = (short) atoi( sValor );
		}
		else if( sCampo == TEXTO_IDMOTIVO)
		{
			iIdmotivo = (short) atoi( sValor );
		}
		else if( sCampo == TEXTO_IDPERSONA)
		{
			iIdpersona = (short) atoi( sValor );
		}
		else if( sCampo == TEXTO_DESRIPCIONCUENTAS)
		{
			sprintf( cDesCuentas, "%.255s", sValor );
		}
		else if ( sCampo == TEXTO_PUNTUALIDAD )
		{
			sprintf( cTexto, "%s", sValor );
			cPuntualidad = cTexto[0];
		}
		else if ( sCampo == TEXTO_INGRESOMENSUAL )
		{
			iIngresoMensual = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_LIMITECREDITO )
		{
			iLimiteDeCredito = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_REPOSICIONDETARJETA )
		{
			iReposicionDeTarjeta = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_FLAGDESCUENTOESPECIAL )
		{
			iFlagDescuentoEspecial = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_FLAGHUELLA )
		{
			iFlagHuella = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_LUGARTRABAJO )
		{
			sprintf( cLugarDeTrabajo, "%s", sValor );
		}
		else if ( sCampo == TEXTO_CIUDADTRABAJO )
		{
			iCiudadTrabajo = atoi( sValor );
		}
		else if ( sCampo == TEXTO_COLONIATRABAJO )
		{
			iColoniaTrabajo = atoi( sValor );
		}
		else if ( sCampo == TEXTO_CALLETRABAJO )
		{
			lCalleTrabajo = atol( sValor );
		}
		else if ( sCampo == TEXTO_CASATRABAJO )
		{
			lCasaTrabajo = atol( sValor );
		}
		else if ( sCampo == TEXTO_NUMDEPTOINTERIORTRAB )
		{
			sprintf( cNumDeptoOInteriorTrabajo, "%s", sValor );
		}
		else if ( sCampo == TEXTO_TELEFONOTRABAJO )
		{
			i64TelefonoTrabajo = _atoi64( sValor );
		}
		else if ( sCampo == TEXTO_EXTENSION )
		{
			iExtension = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_NOMBREREFERENCIA1 )
		{
			sprintf( cNombreReferencia, "%s", sValor );
		}
		else if ( sCampo == TEXTO_APELLIDOPATERNOREFERENCIA1 )
		{
			sprintf( cApellidoPaternoReferencia, "%s", sValor );
		}
		else if ( sCampo == TEXTO_APELLIDOMATERNOREFERENCIA1 )
		{
			sprintf( cApellidoMaternoReferencia, "%s", sValor );
		}
		else if ( sCampo == TEXTO_TELEFONOREFERENCIA1 )
		{
			i64TelefonoReferencia = _atoi64( sValor );
		}
		else if ( sCampo == TEXTO_FECHAALTA )
		{
			tFechaAlta.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_GRUPOSEMAFOROCN )
		{
			iFlagGrupoSemaforoCN = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_STATUSAFORE )
		{
			iStatusAfore = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_SUBPUNTUALIDAD )
		{
			sprintf( cTexto, "%s", sValor );
			cSubPuntualidad = cTexto[0];
		}
		else if ( sCampo == TEXTO_CORREO )
		{
			sprintf( cCorreo, "%s", sValor );
		}
	}
	else if ( iTipoConsulta == CONSULTA_DOMICILIO ) 
	{
		if ( sCampo == TEXTO_NUMEROCALLE )
		{
			domicilio.lCalle = atol( sValor );
		}
		else if ( sCampo == TEXTO_NOMBRECALLE )
		{
			sprintf( domicilio.cNombreCalle, "%s", sValor );
		}
		else if ( sCampo == TEXTO_NUMEROCASA )
		{
			domicilio.lCasa = atol( sValor );
		}
		else if ( sCampo == TEXTO_NUMERCIUDAD )
		{
			domicilio.iCiudad = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_NOMBRECIUDAD )
		{
			sprintf( domicilio.cNombreCiudad, "%s", sValor );
		}
		else if ( sCampo == TEXTO_NUMEROZONA )
		{
			domicilio.iColonia = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_NOMBREZONA )
		{
			sprintf( domicilio.cNombreZona, "%s", sValor );
		}
		else if ( sCampo == TEXTO_POBLACION )
		{
			sprintf( domicilio.cPoblacion, "%s", sValor );
		}
		else if ( sCampo == TEXTO_NUMEROESTADO )
		{
			domicilio.iEstado = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_NOMBREESTADO )
		{
			sprintf( domicilio.cNombreEstado, "%s", sValor );
		}
		else if ( sCampo == TEXTO_MUNICIPIO )
		{
			sprintf( domicilio.cMunicipio, "%s", sValor );
		}
		else if ( sCampo == TEXTO_PLANOCOORDENADAS )
		{
			sprintf( domicilio.cPlanoCoordenadas, "%s", sValor );
		}
		else if ( sCampo == TEXTO_RUMBOZONA )
		{
			sprintf( domicilio.cRumboZona, "%s", sValor );
		}
		else if ( sCampo == TEXTO_COMPLEMENTO )
		{
			sprintf( domicilio.cComplemento, "%s", sValor );
		}
		else if ( sCampo == TEXTO_CODIGOPOSTAL )
		{
			domicilio.lCodigopostal = atol( sValor );
		}
		else if ( sCampo == TEXTO_DESCRIPCIONUHCMANZANA )
		{
			sprintf( domicilio.cDescripcionUhcManzana, "%s", sValor );
		}
		else if ( sCampo == TEXTO_DESCRIPCIONUHCOTROS )
		{
			sprintf( domicilio.cDescripcionUhcOtros, "%s", sValor );
		}
		else if ( sCampo == TEXTO_DESCRIPCIONUHCANDADOR )
		{
			sprintf( domicilio.cDescripcionUhcandador, "%s", sValor );
		}
		else if ( sCampo == TEXTO_DESCRIPCIONUHCETAPA )
		{
			sprintf( domicilio.cDescripcionUhcEtapa, "%s", sValor );
		}
		else if ( sCampo == TEXTO_DESCRIPCIONUHCLOTE )
		{
			sprintf( domicilio.cDescripcionUhcLote, "%s", sValor );
		}
		else if ( sCampo == TEXTO_DESCRIPCIONUHCEDIFICIO )
		{
			sprintf( domicilio.cDescripcionUhcEdificio, "%s", sValor );
		}
		else if ( sCampo == TEXTO_DESCRIPCIONUHCENTRADA )
		{
			sprintf( domicilio.cDescripcionUhcEntrada, "%s", sValor );
		}
		else if ( sCampo == TEXTO_CALLEUNIDADHABITACIONAL )
		{
			domicilio.lCalleUnidadHabitacional = atol( sValor );
		}
		else if ( sCampo == TEXTO_CASAUNIDADHABITACIONAL )
		{
			domicilio.lCasaUnidadHabitacional = atol( sValor );
		}
		else if ( sCampo == TEXTO_RUMBO )
		{
			if ( sValor == "" )
			{
				domicilio.cRumbo = ' ';
			}
			else
			{
				sprintf( cTexto, "%s", sValor );
				domicilio.cRumbo = cTexto[0];
			}
		}
		else if ( sCampo == TEXTO_NUMDEPTOINTERIOR )
		{
			sprintf( cNumDeptoOInterior, "%s", sValor );
		}		
		else if ( sCampo == TEXTO_NUMDEPTOINTERIORTRAB )
		{
			sprintf( cNumDeptoOInteriorTrabajo, "%s", sValor );
		}
	}
	else if ( iTipoConsulta == CONSULTA_LINEACREDITO ) 
	{
		if ( sCampo == TEXTO_LINEADECREDITOTOPE )
		{
			lineaCredito.lLineadeCreditoTope = atol( sValor );
		}
		else if ( sCampo == TEXTO_LINEADECREDITOREAL )
		{
			lineaCredito.lLineadeCreditoReal = atol( sValor );
		}
		else if ( sCampo == TEXTO_FECHALINEADECREDITOTOPE )
		{
			lineaCredito.tFechaLineadeCreditoTope.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_FECHALINEADECREDITOREAL )
		{
			lineaCredito.tFechaLineadeCreditoReal.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_NIVELLINEACREDITOTOPE )
		{
			lineaCredito.iNivelLineaCreditoTope = atol( sValor );
		}
		else if ( sCampo == TEXTO_NIVELLINEACREDITOREAL )
		{
			lineaCredito.iNivelLineaCreditoReal = atol( sValor );
		}
		else if ( sCampo == TEXTO_FLAGCREDITOCLIENTEESP )
		{
			lineaCredito.iFlagCreditoClienteEsp = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_MARGENCREDITO )
		{
			lineaCredito.lMargenCredito = atol( sValor );
		}
		else if ( sCampo == TEXTO_SALDOCLIENTE )
		{
			lineaCredito.lSaldoCliente = atol( sValor );
		}
		else if ( sCampo == TEXTO_LINEAREALCREDITO )
		{
			lineaCredito.lImporteLineaRealCredito = atol( sValor );
		}
	}
	else if ( iTipoConsulta == CONSULTA_PARAMETRICOS ) 
	{
		if ( sCampo == TEXTO_PARCELULARES )
		{
			parametricos.iParametricoCelulares = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_MODELOCELULARES )
		{
			sprintf( cTexto, "%s", sValor );
			parametricos.cModeloCelulares = cTexto[0];
		}
		else if ( sCampo == TEXTO_PARALTORIESGO )
		{
			parametricos.iParametricoAltoRiesgo = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_PARPRESTAMO )
		{
			parametricos.iParametricoPrestamo = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_FECHAPRIMERCOMPRA )
		{
			parametricos.tFechaPrimerCompra.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_PREPUNTAJEALTORIESGO )
		{
			parametricos.iPrePuntajeAltoRiesgo = atoi( sValor );
		}
		else if ( sCampo == TEXTO_PAGOULTIMOSDOCEMESES )
		{
			parametricos.iPagoUltimosDoceMeses = atoi( sValor );
		}
		else if ( sCampo == TEXTO_PUNTAJEFINALAJUSTADO )
		{
			parametricos.iPuntajeFinalAjustado = atoi( sValor );
		}
	}
	else if ( iTipoConsulta == CONSULTA_TOTALES ) 
	{
		if ( sCampo == TEXTO_IMP_SALDO )
		{
			totalesCuenta.lSaldoTotal = atol( sValor );
		}
		else if ( sCampo == TEXTO_IMP_INTERESADICIONAL )
		{
			totalesCuenta.lIntAdicTotal = atol( sValor );
		}
		else if ( sCampo == TEXTO_IMP_ABONOBASE )
		{
			totalesCuenta.lBaseTotal = atol( sValor );
		}
		else if ( sCampo == TEXTO_IMP_VENCIDO )
		{
			totalesCuenta.lVencidoTotal = atol( sValor );
		}
		else if ( sCampo == TEXTO_IMP_MINIMO )
		{
			totalesCuenta.lMinimoTotal = atol( sValor );
		}
		else if ( sCampo == TEXTO_IMP_BONIFICACION )
		{
			totalesCuenta.lBonificacionTotal = atol( sValor );
		}
		else if ( sCampo == TEXTO_IMP_INTPRIMERMES )
		{
			totalesCuenta.lInteresAdicionalPrimerMes = atol( sValor );
		}
		else if ( sCampo == TEXTO_IMP_SALDACON )
		{
			totalesCuenta.lSaldaConTotal = atol( sValor );
		}
		else if ( sCampo == TEXTO_IMP_SALDOTEORICO )
		{
			totalesCuenta.lSaldoTeoricoTotal = atol( sValor );
		}
		else if ( sCampo == TEXTO_IMP_SALDACONCORTE )
		{
			totalesCuenta.lSaldaConCorteTotal = atol( sValor );
		}
		else if ( sCampo == TEXTO_CTECANDIDATOMORA )
		{
			totalesCuenta.lCienteCandidato = atol( sValor );
		}
	}
	else if ( iTipoConsulta == CONSULTA_CANDIDATOPRESTAMO ) 
	{
		if ( sCampo == TEXTO_PLAZO )
		{
			iPlazo = (short) atoi( sValor );

			switch ( iPlazo )
			{
				case 12:
					prestamos.iPlazo12 = 12;
					break;

				case 18:
					prestamos.iPlazo18 = 18;
					break;

				case 24:
					prestamos.iPlazo24 = 24;
					break;
			}
		}
		else if ( sCampo == TEXTO_PRESTAMO )
		{
			switch ( iPlazo )
			{
				case 12:
					prestamos.lImporte12 = atol( sValor );
					break;

				case 18:
					prestamos.lImporte18 = atol( sValor );
					break;

				case 24:
					prestamos.lImporte24 = atol( sValor );
					break;
			}
		}
		else if ( sCampo == TEXTO_PRESTAMOMINIMO )
		{
			switch ( iPlazo )
			{
				case 12:
					prestamos.lImporteMinimo12 = atol( sValor );
					break;

				case 18:
					prestamos.lImporteMinimo18 = atol( sValor );
					break;

				case 24:
					prestamos.lImporteMinimo24 = atol( sValor );
					break;
			}
		}
		else if ( sCampo == TEXTO_PUNTOS_INICIALES )
		{
			prestamos.iPuntosIniciales = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_PUNTAJE_FINAL )
		{
			prestamos.iPuntajeFinal = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_FACTOR_PRESTAMO )
		{
			prestamos.iFactorPrestamo = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_GRUPO )
		{
			sprintf( prestamos.cGrupo, "%s", sValor );
		}
		else if ( sCampo == TEXTO_ID_RECHAZO )
		{
			prestamos.iIdRechazo = (short) atoi( sValor );

			if ( prestamos.iIdRechazo == 0 )
			{
				bCandidatoPrestamo = true;
			}
		}
		else if ( sCampo == TEXTO_MENSAJE )
		{
			sprintf( prestamos.cMensaje, "%s", sValor );
		}
		else if ( sCampo == TEXTO_PUNTOS_ANTIGUEDAD )
		{
			prestamos.iPuntosAntiguedad = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_PUNTOS_CONSUMO )
		{
			prestamos.iPuntosConsumo = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_PUNTOS_PARPRESTAMO )
		{
			prestamos.iPuntosParPrestamo = (short) atoi( sValor );
		}
	}
	else if ( iTipoConsulta == CONSULTA_CONVENIOS )
	{
		if ( sCampo == TEXTO_TIPOCUENTA )
		{
			iConvenios ++;
			iConvenio ++;
			convenios[iConvenio].iTipoCuenta = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_DESCRIPCION )
		{
			sprintf( convenios[iConvenio].cDescripcion, "%s", sValor );
		}
		else if ( sCampo == TEXTO_FACTURA )
		{
			convenios[iConvenio].lFactura = atol( sValor );
		}
		else if ( sCampo == TEXTO_TIPOCONVENIO )
		{
			convenios[iConvenio].iTipoConvenio = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_SUBTIPOCONVENIO )
		{
			convenios[iConvenio].iSubTipoConvenio = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_FECHACONVENIO )
		{
			convenios[iConvenio].tFechaConvenio.ponerFecha( atoi( sValor.Mid(8, 2) ), atoi( sValor.Mid(5, 2) ), atoi( sValor.Mid(0,4) ) );
		}
		else if ( sCampo == TEXTO_PLAZOCONVENIO )
		{
			convenios[iConvenio].iPlazoConvenio = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_IMPORTECONVENIO )
		{
			convenios[iConvenio].lImporteConvenio = atol( sValor );
		}
		else if ( sCampo == TEXTO_EFECTUOCONVENIO )
		{
			convenios[iConvenio].lEfectuoConvenio = atol( sValor );
		}
		else if ( sCampo == TEXTO_FLAG_CUENTA_PERDIDA )
		{
			convenios[iConvenio].bCuentaZ = true;
		}
	}
	else if ( iTipoConsulta == CONSULTA_CUENTASACTIVAS )
	{
		if ( sCampo == TEXTO_CUENTASACTIVAS )
		{
			iCuentasActivas = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_CUENTASACTIVASMUEBLES )
		{
			iCuentasActivasMuebles = (short) atoi( sValor );
		}
		else if ( sCampo == TEXTO_CUENTASACTIVASMUEBLES30 )
		{
			iCuentasActivasMuebles30 = (short) atoi( sValor );
		}
	}
	else if ( iTipoConsulta == CONSULTA_AUMENTOLRC )
	{
		if ( sCampo == TEXTO_PUNTAJE_FINALLRC )
		{
			aumentolrc.iPuntajeFinal =  (short) atoi( sValor );
		}
	}
	else if ( iTipoConsulta == SIMULACION_REESTRUCTURA)
	{
		if(  sCampo == TEXTO_IMP_SALDO12) 
		{
			sInfoReestructura.lImp_saldo12 = (long) atoi( sValor );
		}
		if(  sCampo == TEXTO_IMP_ABONOBASE12) 
		{
			sInfoReestructura.lImp_abonobase12 = (long) atoi( sValor );
		}
		if(  sCampo == TEXTO_IMP_SALDO18) 
		{
			sInfoReestructura.lImp_saldo18 = (long) atoi( sValor );
		}
		if(  sCampo == TEXTO_IMP_ABONOBASE18) 
		{
			sInfoReestructura.lImp_abonobase18 = (long) atoi( sValor );
		}
		if(  sCampo == TEXTO_IMP_SALDO24) 
		{
			sInfoReestructura.lImp_saldo24 = (long) atoi( sValor );
		} 
		if(  sCampo == TEXTO_IMP_ABONOBASE24) 
		{
			sInfoReestructura.lImp_abonobase24 = (long) atoi( sValor );
		}
		if( sCampo == TEXTO_ES_CANDIDATO) 
		{
			sInfoReestructura.iEsCandidato = (short int) atoi( sValor );
		}
		if(  sCampo == TEXTO_PRODUCTO_REESTRUCTURA) 
		{
			 sInfoReestructura.iProductoReestructura  = (short int) atoi( sValor );
		}
		if( sCampo == TEXTO_PAGO_CONDICIONADO) 
		{
			sInfoReestructura.iPagoCondicionado = (short int) atoi( sValor );
		}
		if(sCampo ==  TEXTO_IMP_SALDOFINANCIADO)
		{
			sInfoReestructura.lImp_saldofinanciado = (long) atoi( sValor);
		}
		if(sCampo ==  TEXTO_ABONO_DESBLOQUEO)
		{
			sInfoReestructura.iAbonosDesbloqueo = (short int) atoi( sValor);
		}
		if(sCampo ==  TEXTO_TIENE_PORCENTAJE)
		{
			sInfoReestructura.iTienePorcentaje = (short int) atoi( sValor);
		}
	}
	else if ( iTipoConsulta == CONSULTA_BONIFICACIONPRESTAMO )
	{
		if( sCampo == TEXTO_BONIFICACIONPRESTAMO) 
		{
			CBonificacionPrestamo.lbonificacion = (long) atoi( sValor );
		}
		if( sCampo == TEXTO_INTERES_BONIFICACIONPRESTAMO) 
		{
			CBonificacionPrestamo.linteres = (long) atoi( sValor );
		}
		if( sCampo == TEXTO_PORCENTAJE_BONIFICACIONPRESTAMO) 
		{
			CBonificacionPrestamo.llPorcentaje = (long) atoi( sValor );
		}
		if( sCampo == TEXTO_ESTADO_BONIFICACIONPRESTAMO) 
		{
			CBonificacionPrestamo.estado = (short int) atoi( sValor );

			if(CBonificacionPrestamo.estado == 0)
			{
				bBonificacionP = true;
			}
			else 
			{
				bBonificacionP = false;
			}
		}
		if( sCampo == TEXTO_MENSAJE_BONIFICACIONPRESTAMO) 
		{
			sprintf( CBonificacionPrestamo.mensaje, "%s", sValor );
		}
	}*/
	//TODO: 04/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - FIN
}

void CCuentaWeb::leerCliente( )
{
	int iSoap = 0;
	ns2__leerClienteCoppelResponse response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerCliente" );
	
	iSoap = ws.leerClienteCoppel(lCliente, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_DATOS );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerDomicilio( )
{
	int iSoap = 0;
	ns2__leerDomicilioClienteResponse response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerDomicilio" );
	
	iSoap = ws.leerDomicilioCliente(lCliente, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_DOMICILIO  );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerTienda( )
{
	int iSoap = 0;
	ns2__leerCuentasClienteResponse response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerTienda" );
	
	iSoap = ws.leerCuentasCliente(lCliente, cFecha, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_CUENTA );

		//Se llenan los totales para no ocupar llamar al metodo leerTotales 
		totalesCuenta.lSaldoTotal = pCuenta[iCuenta].lSaldo;
		totalesCuenta.lIntAdicTotal = pCuenta[iCuenta].lInteresAdicional;
		totalesCuenta.lBaseTotal = pCuenta[iCuenta].lBase;
		totalesCuenta.lVencidoTotal = pCuenta[iCuenta].lVencido;
		totalesCuenta.lMinimoTotal = pCuenta[iCuenta].lMinimo;
		totalesCuenta.lBonificacionTotal = pCuenta[iCuenta].lBonificacion;
		totalesCuenta.lInteresAdicionalPrimerMes = pCuenta[iCuenta].lInteresAdicionalPrimerMes;
		totalesCuenta.lSaldaConTotal = pCuenta[iCuenta].lSaldaCon;
		totalesCuenta.lSaldoTeoricoTotal = pCuenta[iCuenta].lSaldoTeorico;
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerTienda01( ) //TODO: 04/09/2025, GAHL, CARGA DE LA FECHA COMPRA PASO 1
{
	//TODO: 01/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - INICIO
	/*int iSoap = 0;
	ns2__leerCuentasCliente01Response response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerTienda" );
	
	iSoap = ws.leerCuentasCliente01(lCliente, cFecha, cIpServidorCartera, response);
	
	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_CUENTA ); //TODO: 04/09/2025, GAHL, CARGA DE LA FECHA COMPRA PASO 2
		totalesCuenta.lSaldoTotal = pCuenta[iCuenta].lSaldo;
		totalesCuenta.lIntAdicTotal = pCuenta[iCuenta].lInteresAdicional;
		totalesCuenta.lBaseTotal = pCuenta[iCuenta].lBase;
		totalesCuenta.lVencidoTotal = pCuenta[iCuenta].lVencido;
		totalesCuenta.lMinimoTotal = pCuenta[iCuenta].lMinimo;
		totalesCuenta.lBonificacionTotal = pCuenta[iCuenta].lBonificacion;
		totalesCuenta.lInteresAdicionalPrimerMes = pCuenta[iCuenta].lInteresAdicionalPrimerMes;
		totalesCuenta.lSaldaConTotal = pCuenta[iCuenta].lSaldaCon;
		totalesCuenta.lSaldoTeoricoTotal = pCuenta[iCuenta].lSaldoTeorico;
		totalesCuenta.lCienteCandidato = pCuenta[iCuenta].lCuentaCandidato;
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}*/
//TODO: 01/09/2025, CODIGO ORIGINAL COMENTADO POR GAHL, CARGA DE LA FECHA COMPRA - FIN
//TODO: 05/09/2025, AGREGADO POR GAHL, CARGA DE LA FECHA COMPRA - INICIO
	leerXML();
//TODO: 05/09/2025, AGREGADO POR GAHL, CARGA DE LA FECHA COMPRA - FIN
}

void CCuentaWeb::leerCuenta( char *cCuenta)
{
	int iSoap = 0;
	ns2__leerCuentaClienteResponse response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerCuenta" );

	iSoap = ws.leerCuentaCliente(lCliente, cFecha, cCuenta, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_CUENTA );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerCuenta01( char *cCuenta)
{
	int iSoap = 0;
	ns2__leerCuentaCliente01Response response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerCuenta" );

	iSoap = ws.leerCuentaCliente01(lCliente, cFecha, cCuenta, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_CUENTA );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerDatos( char *cDato, int iTipoConsulta )
{
	int iSoap = 0;
	ns2__leerDatosClienteResponse response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerDatos" );

	iSoap = ws.leerDatosCliente(lCliente, cDato, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, iTipoConsulta );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerTotales( )
{
	int iSoap = 0;
	ns2__leerImportesTotalesClienteResponse response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerTotales" );

	iSoap = ws.leerImportesTotalesCliente(lCliente, cFecha, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_TOTALES );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerTotales01( )
{
	int iSoap = 0;
	ns2__leerImportesTotalesCliente01Response response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerTotales" );

	iSoap = ws.leerImportesTotalesCliente01(lCliente, cFecha, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_TOTALES );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerLineaCredito( )
{
	//grabarLog( "Inicia Funcion leerLineaCredito" );
	leerDatos( "2", CONSULTA_LINEACREDITO );
	leerMargenCredito( );
}

void CCuentaWeb::leerParametricos( )
{
	//grabarLog( "Inicia Funcion leerParametricos" );
	leerDatos( "3", CONSULTA_PARAMETRICOS );
}

bool CCuentaWeb::leerCandidatoPrestamo( )
{
	int iSoap = 0;
	ns2__leerImporteCandidatosPrestamosResponse response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerCandidatoPrestamo" );

	iSoap = ws.leerImporteCandidatosPrestamos(lCliente, cFecha, iTienda, iCiudadCoppel, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_CANDIDATOPRESTAMO );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}

	return bCandidatoPrestamo;
}

void CCuentaWeb::leerMargenCredito( )
{
	int iSoap = 0;
	ns2__leerMargenCreditoResponse response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerMargenCredito" );

	iSoap = ws.leerMargenCredito(lCliente, cFecha, iTienda, iCiudadCoppel, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_LINEACREDITO );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerConvenios( )
{
	int iSoap = 0;
	ns2__leerConveniosResponse response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerConvenios" );

	iSoap = ws.leerConvenios(lCliente, cFecha, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_CONVENIOS );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerConvenios01( )
{
	int iSoap = 0;
	ns2__leerConvenios01Response response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerConvenios01" );

	iSoap = ws.leerConvenios01(lCliente, cFecha, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_CONVENIOS );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerCuentasActivas( )
{
	int iSoap = 0;
	ns2__leerCantidadCuentasActivasResponse response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	//grabarLog( "Inicia Funcion leerCuentasActivas" );

	iSoap = ws.leerCantidadCuentasActivas(lCliente, cFecha, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_CUENTASACTIVAS );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerCandidatoAumentoLRC( )
{
	int iSoap = 0;
	ns2__leerCandidatosAumentoLRCResponse response;
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );

	iSoap = ws.leerCandidatosAumentoLRC(lCliente, cFecha, iTienda, iCiudadCoppel, cIpServidorCartera, response);

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_AUMENTOLRC );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}

}

void CCuentaWeb::simularReestructuracion()
{
	int iSoap = 0;
	ns2__simularReestructuracionResponse response; 
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );
	
	iSoap = ws.simularReestructuracion(lCliente, cFecha, cIpServidorCartera, response);//poner el metodo del ws

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, SIMULACION_REESTRUCTURA );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::leerBonificacionPrestamos( char *cDias, char *cInteresprestamo, char *cIplazo, char *cFechaPrestamo)
{
	int iSoap = 0;
	ns2__leerBonificacionPrestamosResponse response; 
	ccuentaProxy ws( cIpServidorCCuenta, 20534, iTimeOut );
	
	iSoap = ws.leerBonificacionPrestamos(cDias, cInteresprestamo, cIplazo, cFechaPrestamo, cIpServidorCartera, response);//poner el metodo del ws

	if( iSoap == SOAP_OK )
	{
		leerXML( response.datos->Respuesta, CONSULTA_BONIFICACIONPRESTAMO );
	}
	else
	{
		char cError[2049] = {0};

		sprintf( cError, ws.obtenerError() );
		grabarLog( cError );

		if ( iSoap == SOAP_EOF )
		{
			mostrarError( ERROR_DE_TIMEOUT );
		}
		else
		{
			mostrarError( atoi(cError) );
		}
	}
}

void CCuentaWeb::grabarLog( char *cTexto )
{
	char sArch[80]={0};
	char cTextoGrabar[512]={0};
	CTime tFecha = CTime::GetCurrentTime();

	sprintf(sArch, "C:\\sys\\mem\\CCuentaWeb%02d%02d.log", tFecha.GetMonth(), tFecha.GetDay() );
	
	sprintf( cTextoGrabar, "%04d-%02d-%02d %02d:%02d:%02d %s\n", tFecha.GetYear(), tFecha.GetMonth(), tFecha.GetDay(), tFecha.GetHour(), tFecha.GetMinute(), tFecha.GetSecond(), cTexto);
	C_Archivo arch( sArch, &cTextoGrabar, sizeof( cTextoGrabar ) );
	arch.posicionar( (long)0, BASE_FINAL);
	arch.grabar( cTextoGrabar, (unsigned int) strlen(cTextoGrabar) );
}

void CCuentaWeb::mostrarError( int iError )
{
	switch ( iError )
	{
		case ERROR_DE_TIMEOUT:
			AfxMessageBox( "Error de enlace" );
			grabarLog( "Error de enlace" );
			break;

		case ERROR_CONEXION:
			AfxMessageBox( "Error al abrir conexion a la cartera" );
			grabarLog( "Error al abrir conexion a la cartera" );
			break;

		case ERROR_CRCUENTACTE:
			AfxMessageBox( "Error al obtener cuenta del cliente" );
			grabarLog( "Error al obtener cuenta del cliente" );
			break;

		case NO_HAY_DATOS_CRCUENTACTE:
			AfxMessageBox( "Error al obtener datos del cliente" );
			grabarLog( "Error al obtener datos del cliente" );
			break;

		case NO_EXISTE_CTE:
			AfxMessageBox( "No existe el cliente" );
			grabarLog( "No existe el cliente" );
			break;

		case ERROR_CRCUENTADOM:
			AfxMessageBox( "Error al obtener domicilio del cliente" );
			grabarLog( "Error al obtener domicilio del cliente" );
			break;

		case NO_HAY_DATOS_CRCUENTADOM:
			AfxMessageBox( "Error al leer domicilio del cliente" );
			grabarLog( "Error al leer domicilio del cliente" );
			break;

		case ERROR_PUNTUALIDAD:
			AfxMessageBox( "Error al obtener puntualidad del cliente" );
			grabarLog( "Error al obtener puntualidad del cliente" );
			break;

		case ERROR_CRCUENTATOTALCTA:
			AfxMessageBox( "Error al obtener cuentas del cliente" );
			grabarLog( "Error al obtener cuentas del cliente" );
			break;

		case NO_HAY_DATOS_CRCUENTATOTALCTA:
			AfxMessageBox( "Error al leer cuentas del cliente" );
			grabarLog( "Error al leer cuentas del cliente" );
			break;

		case ERROR_CRCUENTATOTALES:
			AfxMessageBox( "Error al obtener saldos totales del cliente" );
			grabarLog( "Error al obtener saldos totales del cliente" );
			break;

		case NO_HAY_DATOS_CRCUENTATOTALES:
			AfxMessageBox( "Error al leer saldos totales del cliente" );
			grabarLog( "Error al leer saldos totales del cliente" );
			break;

		case ERROR_CRCUENTATOTALESCTASPERDIDAS:
			AfxMessageBox( "Error al obtener cuentas perdidas del cliente" );
			grabarLog( "Error al obtener cuentas perdidas del cliente" );
			break;

		case ERROR_CRCUENTALEERCUENTA:
			AfxMessageBox( "Error al leer cuenta del cliente" );
			grabarLog( "Error al leer cuenta del cliente" );
			break;

		case NO_HAY_DATOS_CRCUENTALEERCUENTA:
			AfxMessageBox( "Error al leer cuenta del cliente" );
			grabarLog( "Error al leer cuenta del cliente" );
			break;

		case ERROR_CRCUENTACANDIDATOPREST:
			AfxMessageBox( "Error al obtener parametrico de prestamos" );
			grabarLog( "Error al obtener parametrico de prestamos" );
			break;

		case NO_HAY_DATOS_CRCUENTACANDIDATOPREST:
			AfxMessageBox( "Error al leer parametrico de prestamos" );
			grabarLog( "Error al leer parametrico de prestamos" );
			break;

		case ERROR_CRCUENTAMARGENCREDITO:
			AfxMessageBox( "Error al obtener margen de cr�dito" );
			grabarLog( "Error al obtener margen de cr�dito" );
			break;

		case NO_HAY_DATOS_CRCUENTAMARGENCREDITO:
			AfxMessageBox( "Error al leer margen de cr�dito" );
			grabarLog( "Error al leer margen de cr�dito" );
			break;

		case ERROR_FUN_CRCUENTALEERCONVENIOS:
			AfxMessageBox( "Error al obtener convenios" );
			grabarLog( "Error al obtener convenios" );
			break;

		case NO_HAY_DATOS_FUN_CRCUENTALEERCONVENIOS:
			AfxMessageBox( "Error al leer convenios" );
			grabarLog( "Error al leer convenios" );
			break;

		case ERROR_FUN_CPCUENTALEERCONVENIOS:
			AfxMessageBox( "Error al obtener convenios cuenta perdida" );
			grabarLog( "Error al obtener convenios cuenta perdida" );
			break;

		case NO_HAY_DATOS_FUN_CPCUENTALEERCONVENIOS:
			AfxMessageBox( "Error al leer convenios cuenta perdida" );
			grabarLog( "Error al leer convenios cuenta perdida" );
			break;

		case ERROR_FUN_CROBTENERCANTIDADESCUENTAS:
			AfxMessageBox( "Error al obtener cantidad cuentas" );
			grabarLog( "Error al obtener cantidad cuentas" );
			break;

		case NO_HAY_DATOS_FUN_CROBTENERCANTIDADESCUENTAS:
			AfxMessageBox( "Error al leer cantidad cuentas" );
			grabarLog( "Error al leer cantidad cuentas" );
			break;

		case ERROR_FECHA_INVALIDA:
			AfxMessageBox( "La fecha recibida es invalida" );
			grabarLog( "La fecha recibida es invalida" );
			break;
	
		case ERROR_CRCANDIDATOAUMENTOLRC:
			AfxMessageBox( "Error al obtener puntaje para aumento lrc" );
			grabarLog( "Error al obtener puntaje para aumento lrc" );
			break;

		case NO_HAY_DATOS_CRCANDIDATOAUMENTOLRC:
			AfxMessageBox( "Error al leer candidato aumento lrc" );
			grabarLog( "Error al leer candidato aumento lrc" );
			break;

		default:
			AfxMessageBox( "Error no definido" );
			grabarLog( "Error no definido" );
			break;
	}
}