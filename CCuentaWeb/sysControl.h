#pragma once


#include "conecta.hpp"
#include "general.hpp"


//Definicion de errores
#define ERROR_DE_TIMEOUT							0	//Error de timeout.
#define ERROR_CONEXION								-1	//Error al abrir conexion a la cartera.
#define ERROR_CRCUENTACTE							-2	//Error al ejecutar la Funcion fun_crCuentaLeerCliente.
#define NO_HAY_DATOS_CRCUENTACTE					-3 	//no regresa datos la Funcion fun_crCuentaLeerCliente.
#define NO_EXISTE_CTE								-4	//No Existe el Cliente
#define ERROR_CRCUENTADOM							-5 	//Error al Ejecutar la Funcion fun_crCuentaLeerDomicilio
#define NO_HAY_DATOS_CRCUENTADOM					-6	//No regresa datos la Funcion fun_crCuentaLeerDomicilio
#define ERROR_PUNTUALIDAD							-7	//Error al consultar Puntualidad del Cliente
#define ERROR_CRCUENTATOTALCTA						-8	//Error al Ejecutar la Funcion fun_crCuentaLeerTotalCuentas
#define NO_HAY_DATOS_CRCUENTATOTALCTA				-9	//No regresa datos la funcion fun_crCuentaLeerTotalCuentas
#define ERROR_CRCUENTATOTALES						-10	//Error al Ejecutar la funcion fun_crcuentatotales
#define NO_HAY_DATOS_CRCUENTATOTALES				-11	//No regresa datos la funcion fun_crcuentatotales
#define ERROR_CRCUENTATOTALESCTASPERDIDAS			-12	//Error al Ejecutar la funcion fun_cpcuentatotalesPerdidas
#define ERROR_CRCUENTALEERCUENTA					-13	//Error al Ejecutar la Funcion fun_crCuentaLeerCuenta
#define NO_HAY_DATOS_CRCUENTALEERCUENTA				-14	//No regresa datos la funcion fun_crCuentaLeerCuenta
#define ERROR_CRCUENTACANDIDATOPREST				-15	//Error al consultar la Funcion fun_crCuentaCandidatoPrestamo
#define NO_HAY_DATOS_CRCUENTACANDIDATOPREST			-16	//No regresa datos la Funcion fun_crCuentaCandidatoPrestamo
#define ERROR_CRCUENTAMARGENCREDITO					-17	//Error al consultar la Funcion fun_crCuentaMargenCredito
#define NO_HAY_DATOS_CRCUENTAMARGENCREDITO			-18	//No regresa datos la Funcion fun_crCuentaMargenCredito
#define ERROR_FUN_CRCUENTALEERCONVENIOS				-19	//Error al consultar la Funcion fun_crCuentaLeerConvenios
#define NO_HAY_DATOS_FUN_CRCUENTALEERCONVENIOS		-20	//No regresa datos la Funcion fun_crCuentaLeerConvenios
#define ERROR_FUN_CPCUENTALEERCONVENIOS				-21	//Error al consultar la Funcion fun_cpCuentaLeerConvenios
#define NO_HAY_DATOS_FUN_CPCUENTALEERCONVENIOS		-22	//No regresa datos la Funcion fun_cpCuentaLeerConvenios
#define ERROR_FUN_CROBTENERCANTIDADESCUENTAS		-23	//Error al consultar la Funcion fun_crObtenerCantidadesCuentas
#define NO_HAY_DATOS_FUN_CROBTENERCANTIDADESCUENTAS	-24	//No regresa datos la Funcion fun_crObtenerCantidadesCuentas
#define ERROR_FECHA_INVALIDA						-25	//Fecha Invalida
#define ERROR_CRCANDIDATOAUMENTOLRC					-26	//Error al consultar la Funcion fun_crcandidatoaumentolrc
#define NO_HAY_DATOS_CRCANDIDATOAUMENTOLRC			-27	//No regresa datos la Funcion fun_crcandidatoaumentolrc
#define ERROR_CRSIMULACIONREESTRUCTURA				-28	//Error al consultar la Funcion fun_calculareestructuracion
#define NO_HAY_DATOS_CRSIMULACIONREESTRUCTURA		-29	//No regresa datos la Funcion fun_calculareestructuracion

//Definicion de tipo de consulta
#define CONSULTA_CUENTA					 0
#define CONSULTA_DATOS					 1
#define CONSULTA_DOMICILIO				 2
#define CONSULTA_LINEACREDITO			 3
#define CONSULTA_PARAMETRICOS			 4
#define CONSULTA_TOTALES				 5
#define CONSULTA_CANDIDATOPRESTAMO		 6
#define CONSULTA_CONVENIOS				 7
#define CONSULTA_CUENTASACTIVAS			 8
#define CONSULTA_AUMENTOLRC				 9
#define SIMULACION_REESTRUCTURA			10
#define CONSULTA_BONIFICACIONPRESTAMO	11

#define TEXTO_TIPOCUENTA				"tipocuenta"
#define TEXTO_SALDO						"saldo"
#define TEXTO_INTERESADICIONAL			"interesadicional"
#define TEXTO_ABONOBASE					"abonobase"
#define TEXTO_PLAZO					 	"plazo" //PRESTAMO
#define TEXTO_VENCIDO					"vencido"
#define TEXTO_MINIMO					"minimo"
#define TEXTO_BONIFICACION				"bonificacion"
#define TEXTO_INTPRIMERMES				"intprimermes"
#define TEXTO_SALDACON					"saldacon"
#define TEXTO_FECHASALDACON				"fechasaldacon"
#define TEXTO_FACTURA					"factura"
#define TEXTO_IMPORTEVENTA				"importeventa"
#define TEXTO_FECHAVENTA				"fechaventa"
#define TEXTO_FECHAPRESTAMO				"fechaprestamo"
#define TEXTO_DESCRIPCION				"descripcion"
#define TEXTO_TIENDA					"tienda"
#define TEXTO_FECHAULTCOMPRA			"fechaultcompra"
#define TEXTO_FECHAULTIMOMOVIMIENTO		"fechaultimomovimiento"
#define TEXTO_TIPOPRODUCTO				"tipoproducto"
#define TEXTO_IMPORTEPRESTAMO			"importeprestamo"
#define TEXTO_SALDOMESANTERIOR			"saldomesanterior"
#define TEXTO_SALDOTEORICO				"saldoteorico"
#define TEXTO_SALDACONCORTE				"saldaconcorte"
#define TEXTO_PORCENTAJEBONIFICACION	"porcentajebonificacion"
#define TEXTO_FECHASALDACONCORTE		"fechasaldaconcorte"
#define TEXTO_INTERESSOBRECOMPRA		"interessobrecompra"
#define TEXTO_DIASTRANSCURRIDOS			"diastranscurridos"

//TEXTOes para las Cuentas de Seguros
#define TEXTO_CLAVESEGURO				"claveseguro"
#define TEXTO_STATUSSEGURO				"statusseguro"
#define TEXTO_CLAVEMOVIMIENTO			"clavemovimiento"
#define TEXTO_TIPOSEGURO				"tiposeguro"
#define TEXTO_FOLIO						"folio"
#define TEXTO_CLAVECONYUGAL				"claveconyugal"
#define TEXTO_CANTIDADSEGUROS			"cantidadseguros"
#define TEXTO_TIPOCANCELACION			"tipocancelacion"
#define TEXTO_CAUSACANCELACIONCLUB		"causacancelacionclub"
#define TEXTO_FECHACANCELACION			"fechacancelacion"
#define TEXTO_CLAVENOOFRECER			"clavenoofrecer"
#define TEXTO_FECHANOOFRECER			"fechanoofrecer"
#define TEXTO_FECHAAFILIACION			"fechaafiliacion"
#define TEXTO_FECHACAMBIOBENEFICIARIO	"fechacambiobeneficiario"
#define TEXTO_FECHAUTIMOPAGO			"fechaultimopago"
#define TEXTO_FECHAVENCIMIENTO			"fechavencimiento" //Tambien se usa para Seguros de Auto
#define TEXTO_CVESINBENEFICIARIOS		"cvesinbeneficiarios"
#define TEXTO_SEXOADICIONAL				"sexoadicional"
#define TEXTO_FECHANACIMIENTOADICIONAL	"fechanacimientoadicional"
#define TEXTO_NOMBREADICIONAL			"nombreadicional"
#define TEXTO_APELLIDOPATERNOADIC		"apellidopaternoadic"
#define TEXTO_APELLIDOMATERNOADIC		"apellidomaternoadic"

//TEXTOes para Seguros de Auto
#define TEXTO_POLIZA			"poliza"
#define TEXTO_CIUDAD			"ciudad"
#define TEXTO_TIPOVEHICULO		"tipovehiculo"
#define TEXTO_TIPOCOBERTURA		"tipocobertura"
#define TEXTO_MODELO			"modelo"
#define TEXTO_FECHAACTIVACION	"fechaactivacion"
#define TEXTO_POLIZAANTERIOR	"polizaanterior"
#define TEXTO_PRECIOSEGUROAUTO	"precio"
#define TEXTO_SEGUROAUTOVIGENTE	"segurovigente"
#define TEXTO_MESESPAGADOS		"mesespagados"

//TEXTOes para Dinero Electronico
#define TEXTO_SALDOALAFECHA	"saldoalafecha"
//descuento moratorio
#define TEXTO_CUENTACANDIDATA	"cuentacandidata"

//TEXTO para cuentas de seguros

#define TEXTO_IDU_SEGURO			"idu_seguro"
#define TEXTO_FOL_POLIZA			"fol_poliza"
#define TEXTO_IDU_ADICIONAL			"idu_adicional"
#define TEXTO_IDU_PLAN				"idu_plan"
#define TEXTO_CLV_STATUS			"clv_estatus"
#define TEXTO_CLV_ORIGEN			"clv_origen"
#define TEXTO_OPC_TIPOCLIENTE		"opc_tipocliente"
#define TEXTO_FEC_AFILIACION		"fec_afiliacion"
#define TEXTO_FEC_INICIOVIGENCIA	"fec_iniciovigencia"
#define TEXTO_FEC_FINVIGENCIA		"fec_finvigencia"
#define TEXTO_FEC_ULTIMOABONO		"fec_ultimoabono"
#define TEXTO_FEC_CANCELACION		"fec_cancelacion"
#define TEXTO_NOM_ADICIONAL			"nom_adicional"
#define TEXTO_NOM_APELLIDOPATERNO	"nom_apellidopaterno"
#define TEXTO_NOM_APELLIDOMATERNO	"nom_apellidomaterno"
#define TEXTO_FEC_NACIMIENTO		"fec_nacimiento"
#define TEXTO_IDU_PARENTESCO		"idu_parentesco"
#define TEXTO_CLV_SEXO				"clv_sexo"


//TEXTO para totales de las cuentas
#define TEXTO_NUM_TIPODECUENTA		"num_tipodecuenta"
#define TEXTO_IMP_SALDO				"imp_saldo"
#define TEXTO_IMP_INTERESADICIONAL	"imp_interesadicional"
#define TEXTO_IMP_ABONOBASE			"imp_abonobase"
#define TEXTO_IMP_VENCIDO			"imp_vencido"
#define TEXTO_IMP_MINIMO			"imp_minimo"
#define TEXTO_IMP_BONIFICACION		"imp_bonificacion"
#define TEXTO_IMP_INTPRIMERMES		"imp_intprimermes"
#define TEXTO_IMP_SALDACON			"imp_saldacon"
#define TEXTO_IMP_SALDOTEORICO		"imp_saldoteorico"
#define TEXTO_IMP_SALDACONCORTE		"imp_saldaconcorte"

#define TEXTO_FLAG_CUENTA_PERDIDA	"flagcuentaperdida"

//descuento moratorio
#define TEXTO_CTECANDIDATOMORA  	"clientecandidato"


//Datos del cliente
#define TEXTO_NOMBRE						"nombre"
#define TEXTO_APELLIDOPATERNO				"apellidopaterno"
#define TEXTO_APELLIDOMATERNO				"apellidomaterno"
#define TEXTO_TELEFONOCLIENTE				"telefonocliente"
#define TEXTO_PEDIRTELEFONO					"pedirtelefono"
#define TEXTO_CIUDAD_CLIENTE				"ciudad"
#define TEXTO_COLONIA						"colonia"
#define TEXTO_CALLE							"calle"
#define TEXTO_CASA							"casa"
#define TEXTO_RUMBO							"rumbo"
#define TEXTO_COMPLEMENTO					"complemento"
#define TEXTO_UHC							"flaguhc"
#define TEXTO_NUMDEPTOINTERIOR				"numdeptoointerior"
#define TEXTO_TELEFONOCELULAR				"telefonocelular"
#define TEXTO_CASAPREF						"casapref"
#define TEXTO_FECHANACIMIENTO				"fechanacimiento"
#define TEXTO_EDOCIVIL						"estadocivil"
#define TEXTO_SEXO							"sexo"
#define TEXTO_SITUACIONESPECIAL				"situacionespecial"
#define TEXTO_CAUSASITESPECIAL				"causasitesp"
#define TEXTO_IDSITUACIONESPECIAL			"idu_situacion"
#define TEXTO_IDMOTIVO						"id_motivo"
#define TEXTO_IDPERSONA						"id_persona"
#define TEXTO_DESRIPCIONCUENTAS				"des_cuentas"
#define TEXTO_PUNTUALIDAD					"puntualidad"
#define TEXTO_INGRESOMENSUAL				"ingresomensual"
#define TEXTO_LIMITECREDITO					"limitecredito"
#define TEXTO_REPOSICIONDETARJETA			"reposiciondetarjeta"
#define TEXTO_FLAGDESCUENTOESPECIAL			"flagdescuentoespecial"
#define TEXTO_FLAGHUELLA					"flaghuella"
#define TEXTO_LUGARTRABAJO					"lugartrabajo"
#define TEXTO_CIUDADTRABAJO					"ciudadtrabajo"
#define TEXTO_COLONIATRABAJO				"coloniatrabajo"
#define TEXTO_CALLETRABAJO					"calletrabajo"
#define TEXTO_CASATRABAJO					"casatrabajo"
#define TEXTO_NUMDEPTOINTERIORTRAB			"numdeptointeriortrab"
#define TEXTO_TELEFONOTRABAJO				"telefonotrabajo"
#define TEXTO_EXTENSION						"extension"
#define TEXTO_NOMBREREFERENCIA1				"nombrereferencia1"
#define TEXTO_APELLIDOPATERNOREFERENCIA1	"apellidopaternoreferencia1"
#define TEXTO_APELLIDOMATERNOREFERENCIA1	"apellidomaternoreferencia1"
#define TEXTO_TELEFONOREFERENCIA1			"telefonoreferencia1"
#define TEXTO_FECHAALTA						"fechaalta"
#define TEXTO_GRUPOSEMAFOROCN				"gruposemaforocn"
#define TEXTO_STATUSAFORE					"statusafore"
#define TEXTO_SUBPUNTUALIDAD				"subpuntualidad"
#define TEXTO_CORREO						"correo"


//Datos del domicilio del cliente
#define TEXTO_NUMEROCALLE				"numerocalle"
#define TEXTO_NOMBRECALLE				"nombrecalle"
#define TEXTO_NUMEROCASA				"numerocasa"
#define TEXTO_NUMERCIUDAD				"numerociudad"
#define TEXTO_NOMBRECIUDAD				"nombreciudad"
#define TEXTO_NUMEROZONA				"numerozona"
#define TEXTO_NOMBREZONA				"nombrezona"
#define TEXTO_POBLACION					"poblacion"
#define TEXTO_NUMEROESTADO				"numeroestado"
#define TEXTO_NOMBREESTADO				"nombreestado"
#define TEXTO_MUNICIPIO					"municipio"
#define TEXTO_PLANOCOORDENADAS			"planocoordenadas"
#define TEXTO_RUMBOZONA					"rumbozona"
#define TEXTO_COMPLEMENTO				"complemento"
#define TEXTO_CODIGOPOSTAL				"codigopostal"
#define TEXTO_DESCRIPCIONUHCMANZANA		"descripcionuhcmanzana"
#define TEXTO_DESCRIPCIONUHCOTROS		"descripcionuhcotros"
#define TEXTO_DESCRIPCIONUHCANDADOR		"descripcionuhcandador"
#define TEXTO_DESCRIPCIONUHCETAPA		"descripcionuhcetapa"
#define TEXTO_DESCRIPCIONUHCLOTE		"descripcionuhclote"
#define TEXTO_DESCRIPCIONUHCEDIFICIO	"descripcionuhcedificio"
#define TEXTO_DESCRIPCIONUHCENTRADA		"descripcionuhcentrada"
#define TEXTO_CALLEUNIDADHABITACIONAL	"calleunidadhabitacional"
#define TEXTO_CASAUNIDADHABITACIONAL	"casaunidadhabitacional"
#define TEXTO_RUMBO						"rumbo"

//Datos de la linea de credito del cliente
#define TEXTO_LINEADECREDITOTOPE		"lineadecreditotope"
#define TEXTO_LINEADECREDITOREAL		"lineadecreditoreal"
#define TEXTO_FECHALINEADECREDITOTOPE	"fechalineadecreditotope"
#define TEXTO_FECHALINEADECREDITOREAL	"fechalineadecreditoreal"
#define TEXTO_NIVELLINEACREDITOTOPE		"nivellineacreditotope"
#define TEXTO_NIVELLINEACREDITOREAL		"nivellineacreditoreal"
#define TEXTO_FLAGCREDITOCLIENTEESP		"flagcreditoclienteesp"
#define TEXTO_MARGENCREDITO				"margencredito"
#define TEXTO_SALDOCLIENTE				"saldocliente"
#define TEXTO_LINEAREALCREDITO			"linearealcredito"  
  

//Datos de los parametricos
#define TEXTO_PARCELULARES			"parcelulares"
#define TEXTO_MODELOCELULARES		"modelocelulares"
#define TEXTO_PARALTORIESGO			"paraltoriesgo"
#define TEXTO_PARPRESTAMO			"parprestamo"
#define TEXTO_FECHAPRIMERCOMPRA		"fechaprimercompra"
#define TEXTO_PREPUNTAJEALTORIESGO	"num_prepuntajealtoriesgo"
#define TEXTO_PAGOULTIMOSDOCEMESES	"imp_pagoultimosdocemeses"
#define TEXTO_PUNTAJEFINALAJUSTADO	"num_puntajefinalajustado"

//Datos para los prestamos
#define TEXTO_PLAZO					"plazo"
#define TEXTO_PRESTAMO				"prestamo"
#define TEXTO_PRESTAMOMINIMO		"prestamominimo"
#define TEXTO_PUNTOS_INICIALES		"puntosiniciales"
#define TEXTO_PUNTAJE_FINAL			"puntajefinal"
#define TEXTO_FACTOR_PRESTAMO		"factorprestamo"
#define TEXTO_GRUPO					"grupo"
#define TEXTO_ID_RECHAZO			"idrechazo"
#define TEXTO_MENSAJE				"mensaje"
#define TEXTO_PUNTOS_ANTIGUEDAD		"puntosantiguedad"
#define TEXTO_PUNTOS_CONSUMO		"puntosconsumo"
#define TEXTO_PUNTOS_PARPRESTAMO	"puntosprestamo"

//Datos para los convenios
#define TEXTO_TIPOCONVENIO			"tipoconvenio"
#define TEXTO_SUBTIPOCONVENIO		"subtipoconvenio"
#define TEXTO_FECHACONVENIO			"fechaconvenio"
#define TEXTO_PLAZOCONVENIO			"plazoconvenio"
#define TEXTO_IMPORTECONVENIO		"importeconvenio"
#define TEXTO_EFECTUOCONVENIO		"efectuoconvenio"

//Datos para cuentas activas
#define TEXTO_CUENTASACTIVAS			"cuentasactivas"
#define TEXTO_CUENTASACTIVASMUEBLES		"cuentasactivasmuebles"
#define TEXTO_CUENTASACTIVASMUEBLES30	"cuentasactivasmuebles30"

//Datos para candidatos aumentolrc
#define TEXTO_PUNTAJE_FINALLRC		"puntajefinal"

#define TEXTO_DETALLECUENTA			"detallecuenta"

//Datos para Maestro Detalle
#define TEXTO_SALDO_DETALLE					"saldodetalle"
#define TEXTO_INTERESADICIONAL_DETALLE		"interesadicionaldetalle"
#define TEXTO_TIPODEDUCCION_DETALLE			"tipodeducciondetalle"
#define TEXTO_FECHAULTIMACOMPRA_DETALLE		"fechaultimacompradetalle"

//Datos para Detalle Cuenta Perdida
#define TEXTO_SALDO_CTA_PERDIDA				"saldoctaperdida"
#define TEXTO_INTERESADICIONAL_CTA_PERDIDA	"interesadicionalctaperdida"
#define TEXTO_TIPODEDUCCION_CTA_PERDIDA		"tipodeduccionctaperdida"
#define TEXTO_FECHAULTIMACOMPRA_CTA_PERDIDA	"fechaultimacompractaperdida"
#define TEXTO_FECHADIFICILCOBRO_CTA_PERDIDA	"fechadificilcobroctaperdida"

//Datos para simulacion de la reestructura
#define TEXTO_ES_CANDIDATO			"iEsCandidato"
#define TEXTO_PAGO_CONDICIONADO		"iPagoCondicionado"
#define TEXTO_PRODUCTO_REESTRUCTURA	"iProductoReestructura"
#define TEXTO_IMP_SALDO12			"impsaldo12"
#define TEXTO_IMP_ABONOBASE12		"impabonobase12"
#define TEXTO_IMP_SALDO18			"impsaldo18"
#define TEXTO_IMP_ABONOBASE18		"impabonobase18"
#define TEXTO_IMP_SALDO24			"impsaldo24"
#define TEXTO_IMP_ABONOBASE24		"impabonobase24"
#define TEXTO_IMP_SALDOFINANCIADO	"imp_saldofinanciado"
#define TEXTO_ABONO_DESBLOQUEO		"iAbonosDesbloqueo"
#define TEXTO_TIENE_PORCENTAJE		"iTienePorcentaje"

// Datos para obtener la Bonificacion de Préstamos
#define TEXTO_BONIFICACIONPRESTAMO		        "lbonificacion"
#define TEXTO_INTERES_BONIFICACIONPRESTAMO		"linteres"
#define TEXTO_PORCENTAJE_BONIFICACIONPRESTAMO	"llporcentaje"
#define TEXTO_ESTADO_BONIFICACIONPRESTAMO		"estado"
#define TEXTO_MENSAJE_BONIFICACIONPRESTAMO		"mensaje"