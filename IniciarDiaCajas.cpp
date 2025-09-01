
#include "StdAfx.h"
#include "ctrlGlob.hpp"
#include "IniciarDiaCajas.h"
#include "wTienda.hpp"
#include "flags.hpp"
#include "folios.hpp"
#include "gnwProto.hpp"
#include "CargarDLL.h"
#include "password.hpp"

#include "CFlagCoppel.hpp"
#include "CFolioCoppel.hpp"
#include "CMaximo.hpp"


#include "CInsertarTdStel.hpp"
#include "CFlagCrTraslape.hpp"
#include "CInsertarMetaTdNumregCt.hpp"
#include "CConsultarTdNumRegCT.hpp"
#include "CCobranzaTelefonicaGnDominio.hpp"
#include "CDatosTdNumRegCT.hpp"
#include "CConsultarTdContador.hpp"
#include "CInsertarTdContador.hpp"
#include "CCaBanCT.hpp"
#include "CTiendaImprimirOS.hpp"
#include "CCaRetiroParcialFinal.hpp"
#include "CInsertarCaRetiroParcial.hpp"
#include "CInsertarCaRetiroParcialHistorial.hpp"


CIniciarDiaCajas::CIniciarDiaCajas(void)
{	
	SecureZeroMemory( cIP, sizeof( cIP ) );
	iTienda = 0;
	iCaja = 0;
	iCiudad = 0;
	iDesplegarError = 0;
	iDiaActual=0;
	iMesActual=0;
	iYearActual=0;
	lFechaSys = 0;
	lEmpleadoSys = 0;
}

CIniciarDiaCajas::~CIniciarDiaCajas(void)
{
}


bool CIniciarDiaCajas::checarInicioCajas( int iModo )
{
	int  iFlagIniciar=0, iFlagTiendaPrincipal=0, iFlagTda=0, iFlagRedCiudad=0, iFlagDepura=0, iFlag=0, iMes=0;
	int  iFlagRespaldaStel=0, iFlagBajarCartera=0, iFlagGeneraCT=0, iCiudadCobranzaTelefonica=0;
	int  iFlagBuro=0, iFlagTdaNormal=0, iFlagErrorExe=0;
	bool bContinuar=true, bIniciar=true;
	char cNombreProyecto[256], cNombreFuncionDLL[256], cRespuesta[20];	
    char cInputParam1[1024]={0}, cInputParam2[1024]={0}, cOutputParam1[1024]={0}, cOutputParam2[1024]={0};
	long lRespuesta=0L, lRegMax=0L, lGteHuella=0L, lGteHuella2=0L;
	CString sTexto;

	SecureZeroMemory(cNombreProyecto, 0, sizeof(cNombreProyecto));
	SecureZeroMemory(cNombreFuncionDLL, 0, sizeof(cNombreFuncionDLL));

	SParametros parametros;
	
	if ( abrirConexionTienda(&odbc) )
	{
		bContinuar = obtenerCiudadCobranza(iCiudadCobranzaTelefonica);

		if ( bContinuar )
		{

			bContinuar=consultarFlags( FLAG_TIENDAPRINCIPAL, '0', iFlagTiendaPrincipal );
			if ( bContinuar )
			{
				if ( iFlagTiendaPrincipal == 1 || iFlagTiendaPrincipal == 2 )
					iFlagTda=1;		
			}
			
			if ( bContinuar )
			{
				bContinuar=consultarFlags( FLAGC_CLAVEINICIOCAJAS, 'C', iFlagIniciar );
				if ( bContinuar )
				{
					if( iFlagIniciar != 1 )
					{
						if ( iCaja == 1 ) 
						{
							//Solo la caja 1 puede incrementar la fecha y los procesos de inicio del d¡a.

							//sprintf(respuesta,"\\tienda.%03d\\cajas\\xcajas\\solucion.%03d",coppel.tienda, coppel.tienda); //caajustesautomaticos
 							bContinuar=borrarCaAjustesAutomaticos();	

							//nombre_archivo("ALZONCAL.DAT",respuesta,DIRECTORIO_CAJAS); //caaltaszonascalles
							//nombre_archivo("CARMOV.DAT",respuesta,DIRECTORIO_CAJAS);  // cacarmov

							//nombre_archivo("tabla.ct",respuesta,DIRECTORIO_CAJAS);  ->Pendiente
							//sprintf(respuesta,"papel%02d.%02d",coppel.mes,coppel.dia); ->Pendiente

							//sprintf(respuesta, "KP%02d%02d%02d.%03d",coppel.dia,coppel.mes,ano_2000_2dig(coppel.ano),coppel.tienda); //cacortepanamericano

							//nombre_archivo("CNUEVOS.DAT",respuesta,DIRECTORIO_CAJAS); SoClientesNuevos
							//nombre_archivo("COMPLECD.DAT",respuesta,DIRECTORIO_CAJAS); soComplementoCambiosSolicitudes
							//sprintf(respuesta,"\\tienda.%03d\\muebles\\cheques.dat",coppel.tienda); tdCheques
							//sprintf(respuesta,"\\tienda.%03d\\muebles\\ventasm.dat",coppel.tienda); mufactura, mufacturadetalle
							//sprintf(respuesta,"\\tienda.%03d\\muebles\\ventasvr.dat",coppel.tienda);mudevolucion, mudevoluciondetalle
							//sprintf(respuesta,"\\tienda.%03d\\muebles\\fimov.dat",coppel.tienda); mumovimientos
							
							if ( bContinuar )
							{
								bContinuar=borrarTablasTiendaNumero(); 
							}

							//sprintf(respuesta,"\\tienda.%03d\\cajas\\xcajas\\chlistan.dat",coppel.tienda); tdlistanegraforaneos
							if ( bContinuar ) 
							{  
								bContinuar=borrarTdListaNegraForaneos(); 
							}

							//if ( iFlagTda == 1 )  // No se manda llamar (Ruben-01Feb06)
								//conversion_cartera_en2();    //ca_secar.cpp

							if ( bContinuar ) //nombre_archivo("alt_cord.dat",respuesta,DIRECTORIO_TIENDA);
							{   
								bContinuar=grabarSoComplementoZonas();
							}

							//if(access("h:\\coppel",0) == 0) -> No se Hace.....
							//	borrar_grupo("h:\\coppel","*.mov");

							//sprintf(fuente,"\\tienda.%03d\\cajas",coppel.tienda); ->No se Hace...
							//borrar_grupo(fuente,"kc*.*");
							//borrar_grupo(fuente,"xt*.*");

							//sprintf(respuesta,"\\progs\\xprogs"); ->No se Hace....
							//if (access(respuesta, 0)!=0)
									//mkdir(respuesta);

							//copiar_programas_cajas();  //ca_acpro.cpp // No se manda llamar (Ruben-01Feb06)

							//copiar_archivos_inicio(); //ca_copia.cpp (No Procede, David, ya que checa el arc de Nomina pagonom.dat, esos arch ya no los estan procesando )

							if ( bContinuar ) 
							{
								/*if ( consultarFlags( FLAG_REDCIUDAD, '0', iFlagRedCiudad ) )
								{
									if ( iFlagRedCiudad == 1 )
									{
										if ( consultarFlags( FLAGC_DEPURAEMPLEADOS, 'C', iFlagDepura ) )
										{
											if ( iFlagDepura == 1 )
											{
												//buscar_empleado_baja();  //gn_baemp.cpp ( No Procede )
											}
										}
										else
										{
											bContinuar=false;
										}
									}
									else
									{
										//buscar_empleado_baja();  //gn_baemp.cpp ( No procede )
									}
								}
								else
								{
									bContinuar=false;
								}*/

								iFlag=0;
								if ( iModo == 0 )
								{
									if ( iTienda == 800 )
									{
										do
										{
											parametros.iLink       = generarLink(); 
											if(sprintf_s( parametros.sServer, sizeof(parametros.sServer), "%s", cIP ) < 0){;}
											parametros.iTienda     = iTienda;       
											parametros.lEmpleado   = lEmpleadoSys;     
											parametros.iCajaActual = iCaja;         
											parametros.iMuestraMsg = iDesplegarError;   
											parametros.iNumSistema = 3;             

											nombreArchivo( "GN0055.DLL", cNombreProyecto, DIRECTORIO_GN );
											if(sprintf_s(cNombreFuncionDLL, sizeof(cNombreFuncionDLL), "GN0055") < 0){;}    
											if(memcpy_s( cInputParam1, sizeof(cInputParam1), &parametros, sizeof( cInputParam1 ) ) < 0){;}
											CargarDLL cargarDll( cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2, cOutputParam1, cOutputParam2 );
											lRespuesta = strtol( cOutputParam1, NULL, 10 );
									
											if( lRespuesta == 0 )
											{
												iFlagErrorExe=1;
												//AfxMessageBox( "Error al Cargar el Programa GN0055.DLL", MB_ICONERROR );                                        
											}
											else
											{
												if( esEmpleado( lRespuesta ) == 1 )
												{												
													iFlag=1;
												}
											}																				

										}while ( iFlag == 0 );
									}
									else
									{
										do
										{
											if ( iTienda>=500 )  //es tda canada
											{
												validarHuellaGteCanada(&odbc,lGteHuella,lGteHuella2,3,18,0L,iTienda,3,iCaja ); //gnwvahue.cpp
											}
											else
											{															
												validarHuellaEmpleadoGte(&odbc,lGteHuella,3,18,0L,iTienda,3,iCaja);  //gnwvahue.cpp
												if( lGteHuella == -1 )
												{
													parametros.iLink       = generarLink(); 
													if(sprintf_s( parametros.sServer, sizeof(parametros.sServer), "%s", cIP ) < 0){;}
													parametros.iTienda     = iTienda;       
													parametros.lEmpleado   = lEmpleadoSys;     
													parametros.iCajaActual = iCaja;         
													parametros.iMuestraMsg = iDesplegarError;   
													parametros.iNumSistema = 3;          

													nombreArchivo( "GN0055.DLL", cNombreProyecto, DIRECTORIO_GN );
													if(sprintf_s(cNombreFuncionDLL, sizeof(cNombreFuncionDLL), "GN0055") < 0){;}    
													if(memcpy_s( cInputParam1, sizeof(cInputParam1), &parametros, sizeof( cInputParam1 ) ) < 0){;}
													CargarDLL cargarDll( cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2, cOutputParam1, cOutputParam2 );
													lRespuesta = strtol( cOutputParam1, NULL, 10 );
													
													if( lRespuesta == 0 )
													{
														iFlagErrorExe = 1;
														//AfxMessageBox( "Error al cargar el programa GN0055.DLL", MB_ICONERROR );
													}
													else
													{
														lGteHuella = lRespuesta;
														if ( lGteHuella == 2 ) // No hay conexión
															iFlagErrorExe = 1;
													}
												}
											}														
											
											if ( lGteHuella < 16 )
											{
												if ( iFlagErrorExe == 0 )
												{
													pintarMensajesErrorPasstda(lGteHuella); //gnwvahue.cpp
												}															
												iFlag = 0;
											}
											else
											{
												iFlag = 1;
											}
										}while ( iFlag == 0 );
									}
								}

								if ( bContinuar )
								{
									bContinuar=consultarFlags( FLAGC_RESPALDARSTEL, 'C', iFlagRespaldaStel );
									if ( bContinuar )
									{
										bContinuar=inicializaTdStel( iFlagRespaldaStel );
									}							
								}
							}

							//sprintf(cArchivoPCMO,"PC%03d??.txt",coppel.tienda); Tabla ->caMovtosMoneyGram
							//sprintf(cArchivoPCMO,"MO%03d??.txt",coppel.tienda); Tabla ->caCarteraMoneyGram
							// Estas Tablas ya se borran en la funcion borrarTablasTiendaNumero()

							capturarGerente();

							/*traslapar_arch_cx();   //ca_tracx.cpp     ---> Pendiente en Funcion de Postgress...
							traslapar_arch_cw();   //ca_tracw.cpp
							TraslapeForaneos();     //ca_trafo.cpp
							traslapar_arch_ht();   //ca_traht.cpp*/

							iFlagBajarCartera = checarGenerarCartera( iFlagTda );

							if ( iFlagBajarCartera != 1 )
							{
								bContinuar=consultarFlags( FLAGC_GENERACT, 'C', iFlagGeneraCT );
								
								if ( bContinuar )
								{
									if ( iFlagGeneraCT == 1 && iCiudadCobranzaTelefonica > 0 )
									{
										//Se checa si se baj¢ cartera
										//if( actualizarFlagCartera( 0 ) == 1 || checarUltimoRegistroCT() == 1 )
										iFlag=checarUltimoRegistroCT(bContinuar);
										if ( bContinuar )
										{
											if ( iFlag == 1 )
											{
												actualizarNumreg( 1 );     //ca_acnur.cpp
											}
											else
											{
												actualizarNumreg( 0 );     //ca_acnur.cpp
											}

											bContinuar=actualizarMetas();       // ca_metas.cpp
										}
									}
								}
							}

							if ( bContinuar )
								bContinuar=actualizarClaveInicioCajas();

							if ( bContinuar )
							{
								if ( iTienda == 801 || iTienda == 802 || iTienda == 148 )
									bContinuar=actualizarClaveInicioRopa(9);
								else
									bContinuar=actualizarClaveInicioRopa(1);
							}

							if ( bContinuar )
							{
								bContinuar=pasarRegistrosRetirosParciales(); 
								if ( bContinuar )
								{   // nombre_archivo("retpfin.dat",fuente,DIRECTORIO_TIENDA);
									bContinuar=deleteTablasTiendaNumero(1);	
								}
							}

							if ( bContinuar )
								bContinuar=actualizarClaveInicioMuebles();

							if ( bContinuar )
							{
								sumarDia( 1, iDiaActual, iMesActual, iYearActual ); //24-1-2006-
								bContinuar=actualizarFechaGnDominio();
							}

							if ( iDiaActual == 1 )
							{
								//sprintf(fuente,"ct_estad.%02d",coppel.mes);
								bContinuar=deleteTablasTiendaNumero(2);	

								if ( bContinuar )
									bContinuar=deleteTablasTiendaNumero(3);	

								//Proceso para la nueva cobranza por tel‚fono
				                //renombrar_conv_vcdo(); No Se Hace..........
	
								if ( bContinuar )
									bContinuar=depurarControlLlamadas();          //ca_dpctr.cpp

								if ( bContinuar )
									bContinuar=depurarEstadistica();              //ca_dpest.cpp

								if ( bContinuar )
									bContinuar=deleteTablasTiendaNumero(7);

								if ( bContinuar )
									bContinuar=respaldarConveniosPorSupervisor();

							}

							//checar_ind_estad();    //ca_chest.cpp //No se hace, ya se crea un respaldo de la tabla.

							iniciarTl();

							//traslapar_reembolso_caja_chica();  // ca_cachi.cpp   Ya no se usa, ya estan centralizados estos movimientos Ruben/David 12/abril/06
																					
							iFlagBajarCartera=checarGenerarCartera(iFlagTda);  // //ca_carte.cpp
							if ( iFlagBajarCartera == 1 )
							{
								traslapeAutomaticoCartera();
								//traslape_automatico_cartera();  // \gen_car\gen_car.cpp	Pendiente.....		

								//bContinuar=depurarArchivoListan3(); No Se Hace, ya no se van a depurar el Listan3.dat
							}

							if ( bContinuar ) 
								bContinuar=actualizarMetas();   //ca_metas.cpp

							//traslapar_emps_new();   //ca_traem.cpp No Se Hace, ya no se va a traslapar el Emps.dat

							if ( bContinuar )
								bContinuar=pasarRechajus();    //ca_parec.cpp  
							
							iMes=iMesActual;
							if ( iMes == 1 )
							{
								iMes=12;
							}
							else
							{
								iMes--;
							}

							/*sprintf(respuesta2,"\\tienda.%03d\\cajas\\aj%02d%02d.log",coppel.tienda,coppel.dia,mes);
							if ( access(respuesta2,0)==0 )
								borrar_archivo(respuesta2);

							proceso_d100( 541 );

							memset(respuesta,0,80);
							memset(respuesta2,0,80);
							sprintf(respuesta,"\\tienda.%03d\\cajas\\xcajas\\encuesta.dat",coppel.tienda);
							if ( access(respuesta,0)==0 )
							{
								sprintf(respuesta2,"\\tienda.%03d\\cajas\\encuesta.dat",coppel.tienda);
								if ( access(respuesta2,0)==0 )
									borrar_archivo(respuesta2);

								proceso_d100( 542 );

								copiar_archivo(respuesta,respuesta2);
								memset(respuesta2,0,80);
								sprintf(respuesta2,"\\tienda.%03d\\cajas\\xcajas\\encuesta.res",coppel.tienda);


								proceso_d100( 543 );

								borrar_archivo(respuesta2);

								proceso_d100( 544 );

								copiar_archivo(respuesta,respuesta2);

								proceso_d100( 545 );

								borrar_archivo(respuesta);

								proceso_d100( 546 );

							}
							proceso_d100( 547 );

							memset(respuesta,0,80);
							memset(respuesta2,0,80);
							sprintf(respuesta,"\\tienda.%03d\\cajas\\xcajas\\enc_ecta.dat",coppel.tienda);
							if ( access(respuesta,0)==0 )
							{
								sprintf(respuesta2,"\\tienda.%03d\\cajas\\enc_ecta.dat",coppel.tienda);
								if ( access(respuesta2,0)==0 )
								{
									proceso_d100( 548 );

									borrar_archivo(respuesta2);
								}
								proceso_d100( 549 );

								copiar_archivo(respuesta,respuesta2);
								memset(respuesta2,0,80);
								sprintf(respuesta2,"\\tienda.%03d\\cajas\\xcajas\\enc_ecta.res",coppel.tienda);

								proceso_d100( 550 );

								borrar_archivo(respuesta2);

								proceso_d100( 551 );

								copiar_archivo(respuesta,respuesta2);

								proceso_d100( 552 );

								borrar_archivo(respuesta);

							}*/


							bContinuar=inicializarKC();   //ca_inikc.cpp 

							//BorrarNodoCaja();   //gn_disco.cpp, No Se Hace, no va a existir Nodo

							/*lRegMax=obtenerRegistrosNtdImpre(bContinuar); 
							if ( bContinuar )			
							{
								if ( iFlagTda == 1 )
								{
									if ( lRegMax == 0L )
									{
										generarNtdimpre(); //ca_tconv.cpp No Se Hace, ya no se usan esos Archivos
									}
								}
							}*/

							if ( bContinuar )
							{
								//inicializa folio de los archivo foliomf.dat
								bContinuar=inicializaFolioMiniFicha();
							}
						}
					}
				}
			}			
		}
	}

	if ( bContinuar )
	{
		//if( access(respuesta,0)!=0 ) 
		iniciarTl();
		
		if ( iModo == 1 )
		{
			bContinuar=consultarFlags( FLAGC_CLAVEINICIOCAJAS, 'C', iFlagIniciar );
			if ( bContinuar )
			{
				if( iFlagIniciar != 1 )
				{
					bContinuar=actualizarClaveInicioCajas();
					iFlag=1;
				}
			}
		}

		if ( iModo == 1 && iFlag == 1 )
		{
			capturaCajeras(1);
			if ( iDiaActual == 1 )
			{
				iFlag=existeBandera(bContinuar);
				if ( bContinuar )
				{
					if ( iFlag == 0 )
					{
						depurarEstadistica();   //ca_dpest.cpp
						graboBandera();
					}
				}
			}
			iMes=iMesActual;
			if ( iMes == 1 )
			{
				iMes=12;
			}
			else
			{
				iMes--;
			}
			bContinuar=deleteTablasTiendaNumero(5);

			if ( bContinuar )
			{
				bContinuar=consultarFlags( FLAGN_BUROCREDITO, 'N', iFlagBuro );  //gn_chfbu.cpp
				if ( bContinuar )
				{
					if ( iFlagBuro == 1 )
					{
						confirmarEnvioConsultaBuro();  // ca_envbu.cpp
					}
				}				
			}
		}
	}

	//convertir_carmovs();     //ca_cocar.cpp  No se Hace...

	if ( bContinuar )
	{
		bContinuar=consultarFlags( FLAGN_TDANORMAL, 'N', iFlagTdaNormal ); //SE CAMBIO A INICIO DEL DIA LUNES 13NOV2004. ARTURO SOLIS.
		if ( iFlagTdaNormal != 1 )
		{
			//no hace nada !!!
		}
		else
		{
			nombreDia(iDiaActual, iMesActual, iYearActual, cRespuesta, iYearActual);
			cRespuesta[7]=0;

			if( memcmp(cRespuesta,"LUNES",5) == 0 )
            {
				sTexto.Format("DEJE LA MICRO ENCENDIDA, SE CORRE UN PROCESO, \n NO SE NECESITA LA SUPERVISION DEL GERENTE." );
				AfxMessageBox( sTexto, MB_ICONINFORMATION );

				generarInformeBloque4y5();      // ca_blo45.cpp
			}
		}
	}

	bIniciar=bContinuar;

	return bIniciar;
}


/*bool CIniciarDiaCajas::iniciarDia( void )
{
	char cSql[128];
	int iFlagIniciar = 0, iConverID[100] = {0};
	bool bIniciar = true;

	if( consultarFlag( &odbc, cSql, 'C', FLAGC_CLAVEINICIOCAJAS, iFlagIniciar ) == true )
	{
		if( iFlagIniciar != 1 )
		{
			if( iCaja == 1 )
			{
				//Solo la caja 1 puede incrementar la fecha y los procesos de inicio del d¡a.
				//...
				//.

				if( convertirArchivo( &odbc, 1, SISTEMA_CAJAS, iTienda, iCiudad, 0, lFechaSys, lEmpleadoSys, cIP, &iConverID[0], cSql ) == false )
				{
                    grabarMensajeError( "C", iCaja, cIP, "CA0", "CIniciarDiaCajas", "iniciarDia", cSql, lEmpleadoSys, "Error en el query", &odbc, iDesplegarError );
				}

				//.
				//...

			}
		}
	}

	return bIniciar;
}*/


bool CIniciarDiaCajas::consultarFlags( int iTipoFlag, char cArea, int &iFlag )
{
	CString sConsulta;
	bool bContinuar=true;

	CFlagCoppel flagCoppelSQL(&odbc);

	sConsulta.Format("SELECT gnconsultarflag('%c','%d')", cArea, iTipoFlag);
	
	if( flagCoppelSQL.Exec(sConsulta))
	{		
		flagCoppelSQL.activarCols();
		if ( flagCoppelSQL.leer() )
		{
			iFlag = flagCoppelSQL.flag;
		}
	}
	else
	{
		flagCoppelSQL.odbc->GetLastError(flagCoppelSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "consultarFlags", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar=false;
	}

    return bContinuar;
}

bool CIniciarDiaCajas::borrarCaAjustesAutomaticos()
{
	CString sConsulta;
	bool bContinuar=true;
                              
	sConsulta.Format(" SELECT caborrarcaajustesautomaticos('%d') ", iTienda );

	CMaximo borrarTablasSQL(&odbc);

	if( borrarTablasSQL.Exec(sConsulta) )
	{		
		borrarTablasSQL.activarCols();
		if ( borrarTablasSQL.leer() )
		{
			if( borrarTablasSQL.Total == 1 )
				bContinuar=true;
		}
	}
	else
	{
		borrarTablasSQL.odbc->GetLastError(borrarTablasSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "borrarCaAjustesAutomaticos", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar=false;
	}

    return bContinuar;
}


bool CIniciarDiaCajas::borrarTablasTiendaNumero()
{
	CString sConsulta;
	bool bContinuar=false;
	
	CMaximo borrarTablasSQL(&odbc,false);

	sConsulta.Format(" SELECT caborrartablasiniciodia() " );

	if( borrarTablasSQL.Exec(sConsulta) )
	{		
		borrarTablasSQL.activarCols();
		if ( borrarTablasSQL.leer() )
		{
			if( borrarTablasSQL.Total == 1 )
				bContinuar=true;
		}
	}
	else
	{
		borrarTablasSQL.odbc->GetLastError(borrarTablasSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "borrarTablasTiendaNumero", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar=false;
	}

    return bContinuar;
}

bool CIniciarDiaCajas::borrarTdListaNegraForaneos()
{
	CString sConsulta;
	bool bContinuar=true;

	CMaximo borrarTablasSQL(&odbc);

	sConsulta.Format(" SELECT caborrartdlistanegraforaneos('%d') ", iTienda );	

	if( borrarTablasSQL.Exec(sConsulta) )
	{		
		borrarTablasSQL.activarCols();
		if ( borrarTablasSQL.leer() )
		{
			if( borrarTablasSQL.Total == 1 )
				bContinuar=true;
		}
	}
	else
	{
		borrarTablasSQL.odbc->GetLastError(borrarTablasSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "borrarTdListaNegraForaneos", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar=false;
	}

	return bContinuar;
}


bool CIniciarDiaCajas::grabarSoComplementoZonas()
{
	CString sConsulta;
	bool bContinuar=true;

	CMaximo borrarTablaSQL(&odbc);

	sConsulta.Format(" SELECT cagrabarsocomplementozonas() " );	

	if( borrarTablaSQL.Exec(sConsulta) )
	{		
		borrarTablaSQL.activarCols();
		if ( borrarTablaSQL.leer() )
		{
			if( borrarTablaSQL.Total == 1 )
				bContinuar=true;
		}
	}
	else
	{
		borrarTablaSQL.odbc->GetLastError(borrarTablaSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "grabarSoComplementoZonas", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar=false;
	}

	return bContinuar;
}


bool CIniciarDiaCajas::inicializaTdStel( int iFlagRespaldaStel )
{
	CString sConsulta;
	bool bContinuar=true;
	int iDiaCoppel=1, iMesCoppel=1, iYearCoppel=1900;

	iDiaCoppel=iDiaActual;
	iMesCoppel=iMesActual;
	iYearCoppel=iYearActual;

	if ( iFlagRespaldaStel == 1 )
	{
		{
			CMaximo borrarTablaSQL(&odbc_3);
			sConsulta.Format(" DELETE FROM tdstel " );	

			if( borrarTablaSQL.Exec(sConsulta) )
			{		
				borrarTablaSQL.activarCols();
				if ( borrarTablaSQL.leer() )
				{
					bContinuar=true;
				}
			}
			else
			{
				borrarTablaSQL.odbc->GetLastError(borrarTablaSQL.GetHstmt());
				grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "inicializaTdStel", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
				bContinuar=false;
			}
		}

		if ( bContinuar )
		{
			{
				CInsertarTdStel xInsertarTdStel( &odbc_3 );

				xInsertarTdStel.activarCols();

				xInsertarTdStel.clave[ 0 ] = 'X';
				xInsertarTdStel.clave[ 1 ] = 0;
				xInsertarTdStel.cliente = 0L;
				xInsertarTdStel.empleado = 0L;
							
				sumarDia( 1, iDiaCoppel, iMesCoppel, iYearCoppel );

				xInsertarTdStel.fechamovto.ponerFecha( iDiaCoppel, iMesCoppel, iYearCoppel );

				xInsertarTdStel.prepararInsert();

				if( !xInsertarTdStel.Insert() )
				{
					sConsulta.Format("Error al Insertar en la Tabla TdStel");
					xInsertarTdStel.odbc->GetLastError(xInsertarTdStel.GetHstmt());
					grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "inicializaTdStel", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
					bContinuar=false;
				}
				else
				{
					xInsertarTdStel.Commit();
				}
			}
		}
	}

	return bContinuar;
}

void CIniciarDiaCajas::traslapeAutomaticoCartera()
{
	char cNombreProyecto[256]={0}, cNombreFuncionDLL[256]={0};	
    char cInputParam1[1024]={0}, cInputParam2[1024]={0};

	SParametros parametros;

	parametros.iLink       = generarLink(); 
	if(sprintf_s( parametros.sServer, sizeof(parametros.sServer), "%s", cIP ) < 0){;}
	parametros.iTienda     = iTienda;       
	parametros.lEmpleado   = lEmpleadoSys;     
	parametros.iCajaActual = iCaja;         
	parametros.iMuestraMsg = iDesplegarError;              

	nombreArchivo( "CA0095.DLL", cNombreProyecto, DIRECTORIO_CA );
	if(sprintf_s(cNombreFuncionDLL, sizeof(cNombreFuncionDLL), "CA0095") < 0){;}    
	if(memcpy_s( cInputParam1, sizeof(cInputParam1), &parametros, sizeof( cInputParam1 ) ) < 0){;}
	CargarDLL cargarDll( cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2 );
}

void CIniciarDiaCajas::capturarGerente()
{
	char cNombreProyecto[256], cNombreFuncionDLL[256];	
    char cInputParam1[1024]={0}, cInputParam2[1024]={0};

	SecureZeroMemory(cNombreProyecto, sizeof(cNombreProyecto));
	SecureZeroMemory(cNombreFuncionDLL, sizeof(cNombreFuncionDLL));

	SParametros parametros;

	parametros.iLink       = generarLink(); 
	if(sprintf_s( parametros.sServer, sizeof(parametros.sServer), "%s", cIP ) < 0){;}
	parametros.iTienda     = iTienda;       
	parametros.lEmpleado   = lEmpleadoSys;     
	parametros.iCajaActual = iCaja;         
	parametros.iMuestraMsg = iDesplegarError;   
	parametros.iNumSistema = 3;             

	nombreArchivo( "GN0012.DLL", cNombreProyecto, DIRECTORIO_GN );
	if(sprintf_s(cNombreFuncionDLL, sizeof(cNombreFuncionDLL), "GN0012") < 0){;}    
	if(memcpy_s( cInputParam1, sizeof(cInputParam1), &parametros, sizeof( cInputParam1 ) ) < 0){;}
	CargarDLL cargarDll( cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2 );

}

void CIniciarDiaCajas::actualizarNumreg( int iFlagActCobTel )
{
	char cNombreProyecto[256], cNombreFuncionDLL[256];	
    char cInputParam1[1024]={0}, cInputParam2[1024]={0};

	SecureZeroMemory(cNombreProyecto, sizeof(cNombreProyecto));
	SecureZeroMemory(cNombreFuncionDLL, sizeof(cNombreFuncionDLL));

	SParametros parametros;

	parametros.iLink       = generarLink(); 
	if(sprintf_s( parametros.sServer, sizeof(parametros.sServer), "%s", cIP ) < 0){;}
	parametros.iTienda     = iTienda;       
	parametros.lEmpleado   = lEmpleadoSys;     
	parametros.iCajaActual = iCaja;         
	parametros.iMuestraMsg = iDesplegarError;   
	parametros.iFlagServicio = iFlagActCobTel;             

	nombreArchivo( "CA0040.DLL", cNombreProyecto, DIRECTORIO_CA );
	if(sprintf_s(cNombreFuncionDLL, sizeof(cNombreFuncionDLL), "CA0040") < 0){;}    
	if(memcpy_s( cInputParam1, sizeof(cInputParam1), &parametros, sizeof( cInputParam1 ) ) < 0){;}
	CargarDLL cargarDll( cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2 );

}


int CIniciarDiaCajas::checarGenerarCartera(int iFlagTda)
{
	CString sConsulta;
	int iFlag=0;

	if ( iFlagTda == 1 || iFlagTda == 2 )	
	{
		if ( iDiaActual != 16 && iDiaActual != 1 )
		{
			CFlagCrTraslape traslapeSQL(&odbc_1);
			sConsulta.Format(" SELECT tienda, flag FROM crtraslape WHERE tienda=%d ",iTienda );	

			if ( traslapeSQL.Exec(sConsulta) )
			{
				traslapeSQL.activarCols();
				if( traslapeSQL.Leer() )
				{
					if ( traslapeSQL.flag == 1 )
					{
						iFlag=1;
					}
				}
			}
			else
			{
				sConsulta.Trim();
				traslapeSQL.odbc->GetLastError(traslapeSQL.GetHstmt());
				grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "checarGenerarCartera", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_1, iDesplegarError );
			}
		}
	}

	return iFlag;
}

/*int CIniciarDiaCajas::actualizarFlagCartera( int iFlagChecar )
{
	CString sConsulta;
	int iFlag=0;
	bool bContinuar=true;

	// flggenct.dat (No se Ocupa este Archivo)

	if ( iFlagChecar == 1 )
	{
		//Indica que al d¡a siguiente hay que generar el ct_cd###.dat
		CFlagCrTraslape traslapeSQL(&odbc_1);
		//sConsulta.Format(" UPDATE crtraslape SET flag=1 where tienda=%d ",iTienda );	

		if ( traslapeSQL.Exec(sConsulta) )
		{
			traslapeSQL.activarCols();
			if( traslapeSQL.Leer() )
			{
				bContinuar=true;
			}
		}
		else
		{
			sConsulta.Trim();
			traslapeSQL.odbc->GetLastError(traslapeSQL.GetHstmt());
			grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "checarGenerarCartera", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_1, iDesplegarError );
			bContinuar=false;
		}
	}
	else
	{
		//Se checa si hay que generar el ct_cd###.dat
		iFlag=1;
	}

	return iFlag;
}*/


/*bool CIniciarDiaCajas::actualizarNumreg( int iFlagActCtx, int &iFlagCobranza )
{
	CString sConsulta;
	bool bContinuar=true;
	int  iFlagAct=0, iFlag=0;
	long lClientesContactados=0L, lTotalRegistros=0L, lRegNumRegCT=0L;
	
	//sprintf(texto2,"estad%03d.dat",coppel.ciudad_ct0 ); tdestadisticact

	lClientesContactados = ctesContactadosTdEstadisticaCT( bContinuar );

	if ( lClientesContactados < 0L )
	{
		lClientesContactados=0L;
	}

	if ( bContinuar )
		lRegNumRegCT=regsTdNumRegCT( bContinuar );		

	if ( bContinuar )
		bContinuar=grabarTdNumRegCT( lClientesContactados, lRegNumRegCT );

	if( bContinuar )
	{
		//sprintf( archivo,"ct_cd%03d.dat",coppel.ciudad_ct0 ); tdcobtelciudad
		lTotalRegistros = regsTdCobTelCiudad( bContinuar );
		if( lTotalRegistros == 0L ) 
			iFlagAct = 1;
	}
	
	if ( bContinuar )
	{
		//Se checa si hay que actualizar la cob. por telefono
		if ( lTotalRegistros > 0L )
		{
			if ( (lClientesContactados * 100)/lTotalRegistros >= 70L )
				iFlagAct=1;
		}

		//if ( iFlagAct != 1 )
		//{
		//	Se checa si ayer se baj¢ cartera
		//	flag_act=checar_act_cartera( 0 ); Checar
		//}
		
		if ( iFlagAct == 1 ||     // Se ha trabajado la Cob el 70% o  no existe el ct_cd###.dat
			 iFlagActCtx == 1 )   //Se baj¢ cartera
		{
			//checar_act_cartera( 1 );  //No se usa archivo \tienda\cartera.cxt Checar

			//pantalla_act_cob_tel();         //ca_pa059.cpp
			//bContinuar=act_cob_telefonica();  //ca_acobt.cpp Checar

			bContinuar=respaldarNumReg();
					   

			//grabaCantidadDeClientes();      //ca_ctect.cpp  Checar

			iFlagCobranza=1;
		}	
	}

	return bContinuar;
}*/


/*long CIniciarDiaCajas::ctesContactadosTdEstadisticaCT( bool &bContinuar )
{
	CString sConsulta;
	long lCtesCont = 0L;

	sConsulta.Format( "SELECT ( SUM(convenios)+SUM(devoluciones)+SUM(recados)+"
								"SUM(recordatorios)+SUM(abono)+SUM(llamardespues)+SUM(nocontesto)+"
								"SUM(telefonoinvalido)+SUM(ctealocalizar)+SUM(supervisar)+SUM(ordenreparacion)+"
								"SUM(yanoviveahi))"
								" - ( SUM(ordenrepefectiva)+SUM(ctealocalizarefectiva)+SUM(supervisarefectiva)+"
								"SUM(yanoviveahiefectiva) )"
								"FROM tdEstadisticaCT WHERE dia = %d", iDiaActual );

	CMaximo tdEstadisticaSQL( &odbc_3 ); 
	
	if( tdEstadisticaSQL.Exec( sConsulta ) )
	{
		tdEstadisticaSQL.activarCols();
		if( tdEstadisticaSQL.Leer() )
		{
			lCtesCont = tdEstadisticaSQL.Total;
		}
	}
	else
	{
        tdEstadisticaSQL.odbc->GetLastError(tdEstadisticaSQL.GetHstmt());
        grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "ctesContactadosTdEstadisticaCT", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
		bContinuar = false;
	}	

	return lCtesCont;
}*/

long CIniciarDiaCajas::regsTdCobTelCiudad( bool &bContinuar )
{
	CString sConsulta;
	long lTotRegs = 0L;

	sConsulta.Format("SELECT COUNT(*) FROM pg_tables WHERE tablename = 'tdcobtelciudad' " ) ;

	CMaximo tdCobTelCiudadSQL( &odbc_3 );
	
	if( tdCobTelCiudadSQL.Exec( sConsulta ) )
	{
		tdCobTelCiudadSQL.activarCols();
		if( tdCobTelCiudadSQL.Leer() )
		{
			lTotRegs = tdCobTelCiudadSQL.Total;
		}
	}
	else
	{
        tdCobTelCiudadSQL.odbc->GetLastError(tdCobTelCiudadSQL.GetHstmt());
        grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "ctesContactadosTdEstadisticaCT", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
		bContinuar = false;
	}	

	return lTotRegs;
}

int CIniciarDiaCajas::checarUltimoRegistroCT(bool &bContinuar)
{
	CString sConsulta;
	int iFlag=0;	
	long lRegistros=0L;

	bContinuar=true;

	//sprintf( texto,"ctrl_%03d.dat",coppel.ciudad_ct0 );           caRegistroControlCT
	//sprintf( nombre_ct,"ct_cd%03d.dat",coppel.ciudad_ct0 );       tdCobTelCiudad

	lRegistros=regsTdCobTelCiudad(bContinuar);

	if ( bContinuar )
	{
		CMaximo controlCTSQL(&odbc);
		sConsulta.Format(" SELECT ultimoregistro FROM caRegistrocontrolct WHERE ultimoregistro=%ld", lRegistros );	

		if ( controlCTSQL.Exec(sConsulta) )
		{
			controlCTSQL.activarCols();
			if( controlCTSQL.Leer() )
			{
				iFlag=1;
			}
		}
		else
		{
			sConsulta.Trim();
			controlCTSQL.odbc->GetLastError(controlCTSQL.GetHstmt());
			grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "checarUltimoRegistroCT", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
			bContinuar=false;
		}
	}

	return iFlag;
}


long CIniciarDiaCajas::regsTdNumRegCT( bool &bContinuar )
{
	CString sConsulta;
	long lTotRegs = 0L;

	//sConsulta.Format("SELECT COUNT(*) FROM pg_tables WHERE tablename = 'tdnumregct' " ) ;
	sConsulta.Format("SELECT COUNT(*) FROM tdnumregct" );	//<--Total de registros.

	CMaximo tdCobTelCiudadSQL( &odbc_3 );
	
	if( tdCobTelCiudadSQL.Exec( sConsulta ) )
	{
		tdCobTelCiudadSQL.activarCols();
		if( tdCobTelCiudadSQL.Leer() )
		{
			lTotRegs = tdCobTelCiudadSQL.Total;
		}
	}
	else
	{
        tdCobTelCiudadSQL.odbc->GetLastError(tdCobTelCiudadSQL.GetHstmt());
        grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "regsTdNumRegCT", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
		bContinuar = false;
	}	

	return lTotRegs;
}

bool CIniciarDiaCajas::actualizarMetas()
{
	CString sConsulta;
	int iDia=1, iMes=1, iYear=1900, iDomingo=0, iDiario=0, iTmpMes=0;
	bool bContinuar=true;
	long lMetaMensual=0, lTotalRegistros=0L, lRegNumRegCT=0L, lMeta=0L;
	char cTexto[20], cRespuesta[10];

	SecureZeroMemory( cTexto,20 );
	SecureZeroMemory( cRespuesta,10 );

	iDia=iDiaActual;
	iMes=iMesActual;
	iYear=iYearActual;

	sumarDia( 1, iDia, iMes, iYear );

	if ( iMesActual < iMes )
	{
		iTmpMes=iMes;
		while ( iTmpMes == iMes )
		{
			nombreDia(iDia, iMes, iYear, cRespuesta, iYearActual);
			cRespuesta[7]=0;

			if( memcmp(cRespuesta,"DOMINGO",7)==0 )
            {
                iDomingo++;
            }
            else
            {
                iDiario++;
            }
			sumarDia( 1, iDia, iMes, iYear );
		}
		lMetaMensual = ( iDomingo*100 )+( iDiario*250 );

		//sprintf(texto1,"nureg%03d.dat",coppel.ciudad_ct0); tdnumregct
		lRegNumRegCT=regsTdNumRegCT( bContinuar );		

		if ( bContinuar )
		{
			if ( lRegNumRegCT == 0L )
			{
				bContinuar=grabarMetasTdNumRegCT( 1, lMetaMensual );
			}
			else
			{
				bContinuar=grabarMetasTdNumRegCT( 2, lMetaMensual );	
			}
		}
	}	
	else
	{
		//Se actualiza la nueva meta	
		lRegNumRegCT=regsTdNumRegCT( bContinuar );

		if ( bContinuar )
		{
			if ( lRegNumRegCT > 0L )
				lMeta=obtenerMeta(bContinuar);

			if ( bContinuar )
			{
				if ( lMeta < 1 )
				{
					//La meta actual tiene error se recalcula.
					lMeta=actualizaMetasCobranza(bContinuar);  //ca_acmet.cpp
					if ( bContinuar )
					{
						bContinuar=grabarMetasTdNumRegCT( 2, lMeta );	
					}
				}
			}
		}
	}

	return bContinuar;
}

bool CIniciarDiaCajas::obtenerCiudadCobranza( int &iCiudadCobranzaTelefonica )
{
CString sConsulta;
bool bContinuar=true;

	CCobranzaTelefonicaGnDominio gnDominioSQL(&odbc);																																																																																											(&odbc);

	sConsulta.Format( "select ciudadcobranzatelefonica from gndominio" );
    if ( gnDominioSQL.Exec(sConsulta))
    {
		gnDominioSQL.activarCols();
		if ( gnDominioSQL.leer() )
		{
			iCiudadCobranzaTelefonica=gnDominioSQL.ciudadcobranzatelefonica;
		}
	}
	else
	{
		gnDominioSQL.odbc->GetLastError(gnDominioSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "obtenerCiudadCobranza", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar=false;
	}

	return bContinuar;
}

/*bool CIniciarDiaCajas::grabarTdNumRegCT( long lClientesContactados, long lRegNumRegCT )
{
CString sConsulta;
bool bContinuar=true;
	
	if ( lRegNumRegCT == 0 )
	{
		CConsultarTdNumRegCT numregSQL( &odbc_3 );

		numregSQL.activarCols();

		numregSQL.clientescontactados = lClientesContactados;
					
		numregSQL.prepararInsert();

		if( !numregSQL.Insert() )
		{
			sConsulta.Format("Error al Insertar en la Tabla TdNumregCT");
			numregSQL.odbc->GetLastError(numregSQL.GetHstmt());
			grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "actualizarNumreg", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
			bContinuar=false;
		}
		else
		{
			numregSQL.Commit();
		}
	}
	else
	{
		CMaximo actualizarSQL(&odbc_3);
		sConsulta.Format(" UPDATE tdnumregct SET clientescontactados=%ld ", lClientesContactados );

		if ( actualizarSQL.Exec(sConsulta) )
		{
			actualizarSQL.activarCols();
			if( actualizarSQL.Leer() )
			{
				bContinuar=true;
			}
		}
		else
		{
			sConsulta.Trim();
			actualizarSQL.odbc->GetLastError(actualizarSQL.GetHstmt());
			grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "actualizarMetas", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
			bContinuar=false;
		}
	}

	return bContinuar;
}*/


bool CIniciarDiaCajas::respaldarNumReg()
{
CString sConsulta;
bool bContinuar=true;	
	
	//Se deja la misma meta del numreg.ant
	CMaximo actualizarSQL(&odbc_3);
	sConsulta.Format(" UPDATE tdnumregct SET clientescontactados=0 " );

	if ( actualizarSQL.Exec(sConsulta) )
	{
		actualizarSQL.activarCols();
		if( actualizarSQL.Leer() )
		{
			bContinuar=true;
		}
	}
	else
	{
		sConsulta.Trim();
		actualizarSQL.odbc->GetLastError(actualizarSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "respaldarNumReg", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
		bContinuar=false;
	}

	return bContinuar;
}

bool CIniciarDiaCajas::grabarMetasTdNumRegCT( int iFlag, long lMetaMensual )
{
CString sConsulta;
bool bContinuar=true;
	
	if ( iFlag == 1 )
	{
		CInsertarMetaTdNumregCt numregSQL( &odbc_3 );
		numregSQL.activarCols();

		numregSQL.meta = lMetaMensual;
					
		numregSQL.prepararInsert();

		if( !numregSQL.Insert() )
		{
			sConsulta.Format("Error al Insertar en la Tabla TdNumregCT");
			numregSQL.odbc->GetLastError(numregSQL.GetHstmt());
			grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "grabarMetasTdNumRegCT", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
			bContinuar=false;
		}
		else
		{
			numregSQL.Commit();
		}
	}
	else
	{
		CMaximo actualizarSQL(&odbc_3);
		sConsulta.Format(" UPDATE tdnumregct SET meta=%ld ", lMetaMensual );

		if ( actualizarSQL.Exec(sConsulta) )
		{
			bContinuar=true;
		}
		else
		{
			sConsulta.Trim();
			actualizarSQL.odbc->GetLastError(actualizarSQL.GetHstmt());
			grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "actualizarMetasTdNumRegCT", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
			bContinuar=false;
		}
	}
	

	return bContinuar;
}

long CIniciarDiaCajas::obtenerMeta( bool &bContinuar )
{
	CString sConsulta;
	long lMeta = 0L;

	bContinuar=true;

	CMaximo tdCobTelCiudadSQL( &odbc_3 );	

	sConsulta.Format("SELECT meta FROM tdnumregct " ) ;	
	if( tdCobTelCiudadSQL.Exec( sConsulta ) )
	{
		tdCobTelCiudadSQL.activarCols();
		if( tdCobTelCiudadSQL.Leer() )
		{
			lMeta = tdCobTelCiudadSQL.Total;
		}
	}
	else
	{
        tdCobTelCiudadSQL.odbc->GetLastError(tdCobTelCiudadSQL.GetHstmt());
        grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "obtenerMeta", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
		bContinuar = false;
	}	

	return lMeta;
}

long CIniciarDiaCajas::actualizaMetasCobranza(bool &bContinuar)
{
long lMeta=0L, lRegresaMeta=0L;
CString sConsulta;

	CDatosTdNumRegCT tdSQL(&odbc_3);
	sConsulta.Format(" SELECT meta, clientescontactados FROM tdnumregct " );
							
	if( tdSQL.Exec( sConsulta ) )
	{
		tdSQL.activarCols();
		if( tdSQL.Leer() )
		{
			if ( tdSQL.clientescontactados >=0 && tdSQL.clientescontactados <= 900 )
			{
				lMeta=long((double)tdSQL.clientescontactados*1.15);
			}
			else if ( tdSQL.clientescontactados > 900 && tdSQL.clientescontactados <= 2000 )
			{				
				lMeta=long((double)tdSQL.clientescontactados*1.10);
			}
			else if ( tdSQL.clientescontactados > 2000 )
			{				
				lMeta=long((double)tdSQL.clientescontactados*1.05);
			}
				
			lRegresaMeta=tdSQL.meta;
			if ( lMeta > tdSQL.meta )
			{
				lRegresaMeta=lMeta;
			}	
			else
			{
				//se deja la misma meta ya que es menor la meta nueva
			}
		}
	}
	else
	{
        tdSQL.odbc->GetLastError(tdSQL.GetHstmt());
        grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "ctesContactadosTdEstadisticaCT", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
		bContinuar = false;
	}

    return lRegresaMeta;
}

bool CIniciarDiaCajas::actualizarMetasTdNumRegCT(long lMeta)
{
CString sConsulta;
bool bContinuar=true;	
	
	CMaximo actualizarSQL(&odbc_3);
	sConsulta.Format(" UPDATE tdnumregct SET meta=%ld ", lMeta );

	if ( actualizarSQL.Exec(sConsulta) )
	{
		actualizarSQL.activarCols();
		if( actualizarSQL.Leer() )
		{
			bContinuar=true;
		}
	}
	else
	{
		sConsulta.Trim();
		actualizarSQL.odbc->GetLastError(actualizarSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "actualizarMetasTdNumRegCT", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
		bContinuar=false;
	}

	return bContinuar;
}

bool CIniciarDiaCajas::actualizarClaveInicioCajas()
{
CString sConsulta;
bool bContinuar=true;	
char cArea='C';
	
	CMaximo actualizarSQL(&odbc);
	sConsulta.Format(" UPDATE sysflags SET flag=1 WHERE area='%c' AND tipoflag=%d ", cArea, FLAGC_CLAVEINICIOCAJAS );

	if ( actualizarSQL.Exec(sConsulta) )
	{
		actualizarSQL.activarCols();
		if( actualizarSQL.Leer() )
		{
			bContinuar=true;
		}
	}
	else
	{
		sConsulta.Trim();
		actualizarSQL.odbc->GetLastError(actualizarSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "actualizarClaveInicioCajas", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar=false;
	}

	return bContinuar;
}


bool CIniciarDiaCajas::actualizarClaveInicioRopa(int iFlag)
{
CString sConsulta;
bool bContinuar=true;	
char cArea='R';
	
	CMaximo actualizarSQL(&odbc);
	sConsulta.Format(" UPDATE sysflags SET flag=%d WHERE area='%c' AND tipoflag=%d ", iFlag, cArea, FLAGR_CLAVEINICIOROPA );

	if ( actualizarSQL.Exec(sConsulta) )
	{
		actualizarSQL.activarCols();
		if( actualizarSQL.Leer() )
		{
			bContinuar=true;
		}
	}
	else
	{
		sConsulta.Trim();
		actualizarSQL.odbc->GetLastError(actualizarSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "actualizarClaveInicioRopa", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar=false;
	}

	return bContinuar;
}

bool CIniciarDiaCajas::pasarRegistrosRetirosParciales()
{
	bool bContinuar=true; 
	CString sConsulta;
	int iDia=1, iMes=1, iYear=1900, iCont=1;

	// Barrer la tabla caretiroparcialfinal e insertar en la tabla caretiroparcial y en el Historial

	CCaRetiroParcialFinal retParcialFinalSQL(&odbc);
	sConsulta.Format(" select fecha, caja, area, retiro, pesos, dolares, tipocambio, cheques, chequeslocales, "
					 " chequesforaneos, total, empleado, flagcortecaja, flagentregadopanamericano, flagconfirmacion "
					 " from caretiroparcialfinal " );
							
	if( retParcialFinalSQL.Exec( sConsulta ) )
	{
		retParcialFinalSQL.activarCols();
		while( retParcialFinalSQL.Leer() )
		{
			if ( bContinuar )
			{
				if( retParcialFinalSQL.total > 0L && iCont <= 9 )	
				{
					CInsertarCaRetiroParcial insRetiroParcialSQL( &odbc );
					insRetiroParcialSQL.activarCols();

					iDia=retParcialFinalSQL.fecha.dia();	
					iMes=retParcialFinalSQL.fecha.mes();
					iYear=retParcialFinalSQL.fecha.ano();
					insRetiroParcialSQL.fecha.ponerFecha( iDia, iMes, iYear );

					insRetiroParcialSQL.caja=retParcialFinalSQL.caja;

					insRetiroParcialSQL.area[0]=retParcialFinalSQL.area[0];
					insRetiroParcialSQL.area[1]=0;

					insRetiroParcialSQL.retiro=retParcialFinalSQL.retiro;

					insRetiroParcialSQL.pesos=retParcialFinalSQL.pesos;

					insRetiroParcialSQL.dolares=retParcialFinalSQL.dolares;

					insRetiroParcialSQL.tipocambio=retParcialFinalSQL.tipocambio;

					insRetiroParcialSQL.cheques=retParcialFinalSQL.cheques;

					insRetiroParcialSQL.chequeslocales=retParcialFinalSQL.chequeslocales;

					insRetiroParcialSQL.chequesforaneos=retParcialFinalSQL.chequesforaneos;

					insRetiroParcialSQL.total=retParcialFinalSQL.total;

					insRetiroParcialSQL.empleado=retParcialFinalSQL.empleado;

					insRetiroParcialSQL.flagcortecaja=retParcialFinalSQL.flagcortecaja;
				
					insRetiroParcialSQL.flagentregadopanamericano=retParcialFinalSQL.flagentregadopanamericano;

					insRetiroParcialSQL.flagconfirmacion=retParcialFinalSQL.flagconfirmacion;

					insRetiroParcialSQL.prepararInsert();

					if( !insRetiroParcialSQL.Insert() )
					{
						sConsulta.Format("Error al Insertar en la Tabla CaRetiroParcial");
						insRetiroParcialSQL.odbc->GetLastError(insRetiroParcialSQL.GetHstmt());
						grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "pasarRegistrosRetirosParciales", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
						bContinuar=false;
					}
					else
					{
						insRetiroParcialSQL.Commit();
					}

					if ( bContinuar )
					{
						CInsertarCaRetiroParcialHistorial insHistoriallSQL( &odbc );
						insHistoriallSQL.activarCols();

						iDia=retParcialFinalSQL.fecha.dia();	
						iMes=retParcialFinalSQL.fecha.mes();
						iYear=retParcialFinalSQL.fecha.ano();
						insHistoriallSQL.fecha.ponerFecha( iDia, iMes, iYear );

						insHistoriallSQL.caja=retParcialFinalSQL.caja;

						insHistoriallSQL.area[0]=retParcialFinalSQL.area[0];
						insHistoriallSQL.area[1]=0;

						insHistoriallSQL.retiro=retParcialFinalSQL.retiro;

						insHistoriallSQL.pesos=retParcialFinalSQL.pesos;

						insHistoriallSQL.dolares=retParcialFinalSQL.dolares;

						insHistoriallSQL.tipocambio=retParcialFinalSQL.tipocambio;

						insHistoriallSQL.cheques=retParcialFinalSQL.cheques;

						insHistoriallSQL.chequeslocales=retParcialFinalSQL.chequeslocales;

						insHistoriallSQL.chequesforaneos=retParcialFinalSQL.chequesforaneos;

						insHistoriallSQL.total=retParcialFinalSQL.total;

						insHistoriallSQL.empleado=retParcialFinalSQL.empleado;

						insHistoriallSQL.flagcortecaja=retParcialFinalSQL.flagcortecaja;
					
						insHistoriallSQL.flagentregadopanamericano=retParcialFinalSQL.flagentregadopanamericano;

						insHistoriallSQL.flagconfirmacion=retParcialFinalSQL.flagconfirmacion;
												
						insHistoriallSQL.prepararInsert();

						if( !insHistoriallSQL.Insert() )
						{
							sConsulta.Format("Error al Insertar en la Tabla CaRetiroParcialHistorial");
							insHistoriallSQL.odbc->GetLastError(insHistoriallSQL.GetHstmt());
							grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "pasarRegistrosRetirosParciales", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
							bContinuar=false;
						}
						else
						{
							insHistoriallSQL.Commit();
						}

						iCont++;
					}				
				}	
			}
		}
	}
	else
	{
        retParcialFinalSQL.odbc->GetLastError(retParcialFinalSQL.GetHstmt());
        grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "pasarRegistrosRetirosParciales", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar = false;
	}

	return bContinuar;
}

bool CIniciarDiaCajas::deleteTablasTiendaNumero(int iFlag)
{
CString sConsulta;
bool bContinuar=true;	
	
	CMaximo borrarSQL(&odbc);

	if ( iFlag == 1 ) 
		sConsulta.Format(" DELETE FROM caretiroparcialfinal " );

	if ( iFlag == 2 ) 
		sConsulta.Format(" DELETE FROM caestadisticacobranzatelefonica " );

	if ( iFlag == 3 ) 
		sConsulta.Format(" DELETE FROM caeficienciacajerasmensual " );

	if ( iFlag == 4 ) 
		sConsulta.Format(" DELETE FROM cacortecontable " );

	if ( iFlag == 5 ) 
		sConsulta.Format(" DELETE FROM cafichasdeposito " );

	if ( iFlag == 6 ) 
		sConsulta.Format(" DELETE FROM cavegatmp3dias " );  // VegaOS3d.%02d

	if ( iFlag == 7 )
		sConsulta.Format(" DELETE FROM caclubproteccionacumulado "); //ACUMVENC.ttt

	if ( borrarSQL.Exec(sConsulta) )
	{
		borrarSQL.activarCols();
		if( borrarSQL.Leer() )
		{
			bContinuar=true;
		}
	}
	else
	{
		borrarSQL.odbc->GetLastError(borrarSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "deleteTablasTiendaNumero", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar=false;
	}

	return bContinuar;
}


bool CIniciarDiaCajas::deleteTablasTienda(int iFlag)
{
CString sConsulta;
bool bContinuar=true;	
	
	CMaximo borrarSQL(&odbc_3);		
	if ( iFlag == 1  )
	{		
		sConsulta.Format(" DELETE FROM tdcontador " );
	}

	if ( iFlag == 2  )
	{		
		sConsulta.Format(" DELETE FROM tdnumregct " );
	}

	if ( borrarSQL.Exec(sConsulta) )
	{
		borrarSQL.activarCols();
		if( borrarSQL.Leer() )
		{
			bContinuar=true;
		}
	}
	else
	{
		borrarSQL.odbc->GetLastError(borrarSQL.GetHstmt());		
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "deleteTablasTienda", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
		bContinuar=false;
	}

	return bContinuar;
}

bool CIniciarDiaCajas::actualizarClaveInicioMuebles()
{
CString sConsulta;
bool bContinuar=true;	
char cArea='M';
	
	CMaximo actualizarSQL(&odbc);
	sConsulta.Format(" UPDATE sysflags SET flag=1 WHERE area='%c' AND tipoflag=%d ", cArea, FLAGM_CLAVEINICIOMUEBLES );

	if ( actualizarSQL.Exec(sConsulta) )
	{
		actualizarSQL.activarCols();
		if( actualizarSQL.Leer() )
		{
			bContinuar=true;
		}
	}
	else
	{
		sConsulta.Trim();
		actualizarSQL.odbc->GetLastError(actualizarSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "actualizarClaveInicioMuebles", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar=false;
	}

	return bContinuar;
}

bool CIniciarDiaCajas::actualizarFechaGnDominio()
{
CString sConsulta, sFechaCoppel;
bool bContinuar=true;
	
	sFechaCoppel.Format("%04d-%02d-%02d", iYearActual, iMesActual, iDiaActual);

	sConsulta.Format(" UPDATE gnDominio SET fecha = '%s' ", sFechaCoppel );

	CFlagCoppel fechaCoppel(&odbc);
	if ( !fechaCoppel.Exec(sConsulta) )
	{
		fechaCoppel.odbc->GetLastError(fechaCoppel.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "actualizarFechaGnDominio", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar = false;
	}	
		
	return bContinuar;	
}


bool CIniciarDiaCajas::depurarControlLlamadas()
{
CString sConsulta;
bool bContinuar=true, bExisteTabla=false, bInserto=false;
int iFlagAct=0;

	CConsultarTdContador tdContadorSQL(&odbc_3);
	sConsulta.Format(" select cliente, contador, causa from tdcontador " );
							
	if( tdContadorSQL.Exec( sConsulta ) )
	{
		tdContadorSQL.activarCols();
		while( tdContadorSQL.Leer() )
		{
			iFlagAct=1;
			if ( esEmpleadoSinDig(tdContadorSQL.cliente) == 1 ||        //N£mero de Empleado, No se considera
				  tdContadorSQL.cliente == 9000L ||                     //# solo para vtas. de ctado.
				  tdContadorSQL.cliente == 170L ||                      // Etp's
				  tdContadorSQL.cliente < 1L )
			{
				iFlagAct=0;	
			}
			else
			{
				if( ( esEmpleadoSinDig(tdContadorSQL.cliente) == 1 ) ||
 				    ( tdContadorSQL.cliente > 0 && tdContadorSQL.cliente < 10000 ))
				{
					if ( tdContadorSQL.cliente != 9000L )
					{
						//N£mero de cliente fuera de rango NO se considera
						iFlagAct=0;
					}
				}
			}
			if ( iFlagAct == 1 )
			{
				//N£mero de Cliente Valido
				CInsertarTdContador InsTmpTdContador( &odbc_3 );
				if ( crearTempTdContador( InsTmpTdContador, bExisteTabla ) )
				{
					InsTmpTdContador.cliente=tdContadorSQL.cliente;
					InsTmpTdContador.contador=tdContadorSQL.contador;
					InsTmpTdContador.causa=tdContadorSQL.causa;

					// Va a grabar en la Temporal TdContador
					InsTmpTdContador.prepararInsert( "tmptdcontador" );

					if( InsTmpTdContador.Insert() )
					{
						InsTmpTdContador.Commit();
						bInserto=true;
					}
					else
					{
						sConsulta.Format( "Error al Insertar en la Tabla tmpTdContador" );
						InsTmpTdContador.odbc->GetLastError(InsTmpTdContador.GetHstmt());
						grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "depurarControlLlamadas", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
						bContinuar=false;
					}
				}
			}
		}
	}
	else
	{
		tdContadorSQL.odbc->GetLastError(tdContadorSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "depurarControlLlamadas", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
		bContinuar = false;
	}

	if ( bContinuar )
	{
		if ( bInserto )
		{
			bContinuar=deleteTablasTienda(1);

			if ( bContinuar )
			{
				CConsultarTdContador tdContadorSQL(&odbc_3);

				sConsulta.Format(" INSERT INTO tdcontador (cliente, contador, causa) SELECT cliente, contador, causa from tmptdcontador " );
				if( tdContadorSQL.Exec( sConsulta ) )
				{
					tdContadorSQL.activarCols();
					if( tdContadorSQL.Leer() )
					{
						bContinuar=true;
					}
				}
				else
				{
					tdContadorSQL.odbc->GetLastError(tdContadorSQL.GetHstmt());
					grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "depurarControlLlamadas", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
					bContinuar = false;
				}
			}
		}
	}

	return  bContinuar;
}

bool CIniciarDiaCajas::crearTempTdContador( CInsertarTdContador &InsTmpTdContador, bool &bExisteTabla )
{
	CString  sConsulta;
	bool bContinuar=true;

	if ( !bExisteTabla ) 
	{
		sConsulta.Format( "CREATE TEMPORARY TABLE tmpTdContador ( LIKE TdContador INCLUDING DEFAULTS ) WITHOUT OIDS; " );
		if( InsTmpTdContador.Exec( sConsulta ) )
		{
			InsTmpTdContador.activarCols();
			InsTmpTdContador.prepararInsert( "tmpTdContador" );
			InsTmpTdContador.Commit();
			bExisteTabla=true;
		}
		else
		{
			sConsulta.Trim();
			InsTmpTdContador.odbc->GetLastError(InsTmpTdContador.GetHstmt());
			grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "crearTempTdContador", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_3, iDesplegarError );
			bContinuar=false;
		}
	}

	return  bContinuar;
}

bool CIniciarDiaCajas::depurarEstadistica()
{
	CString sSql;
	int iMes=1;
	bool bContinuar=true;

	iMes=iMesActual;
	iMes--;
	if( iMes < 1 ) 
		iMes=12;

	depurarEstadisticaNumReg();

	sSql.Format( "SELECT tdrespaldartdestadisticact('%ld')",lFechaSys );
	// Funcion Postgre que respalda y borra la tabla tdestadisticact
	CFlagCoppel respaldarSQL( &odbc_3, false );

	if ( respaldarSQL.Exec(sSql) )
	{
		if ( respaldarSQL.Leer() )
		{
			//Ejecuto funcion
		}
	}
	else
	{	
		sSql.Trim();
		respaldarSQL.odbc->GetLastError(respaldarSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "depurarEstadistica", (LPTSTR)(LPCTSTR)sSql, lEmpleadoSys, "ERROR EN LA CONSULTA", respaldarSQL.odbc, iDesplegarError );
		bContinuar=false;
	}

	//bContinuar=deleteTablasTienda(2); <-- Borra tdnumregct

	return bContinuar;
}


bool CIniciarDiaCajas::depurarEstadisticaNumReg()
{
	bool bContinuar=true;
	long lRegNumRegCT=0L, lMeta=0L;

	//Se actualiza la nueva meta
	//Peticion 16 de Enero del 2003	
	lRegNumRegCT=regsTdNumRegCT( bContinuar );

	if ( bContinuar && lRegNumRegCT > 0L )
	{
		lMeta=actualizaMetasCobranza(bContinuar);  //ca_acmet.cpp
		if ( bContinuar )
		{
			bContinuar=grabarMetasTdNumRegCT( 2, lMeta );	
		}
	}

	return bContinuar;
}

bool CIniciarDiaCajas::inicializarKC()
{
	bool bContinuar=true;

	bContinuar=deleteTablasTiendaNumero(4);	

	return bContinuar;
}

/*long CIniciarDiaCajas::obtenerRegistrosNtdImpre( bool &bContinuar )
{
	CString sConsulta;
	long lTotRegs = 0L;

	sConsulta.Format("SELECT COUNT(*) FROM pg_tables WHERE tablename = 'sotiendaimpresion' " ) ;

	CMaximo tiendaImpresionSQL( &odbc_2 );  // Solicitudes
	
	if( tiendaImpresionSQL.Exec( sConsulta ) )
	{
		tiendaImpresionSQL.activarCols();
		if( tiendaImpresionSQL.Leer() )
		{
			lTotRegs = tiendaImpresionSQL.Total;
		}
	}
	else
	{
        tiendaImpresionSQL.odbc->GetLastError(tiendaImpresionSQL.GetHstmt());
        grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "obtenerRegistrosNtdImpre", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_2, iDesplegarError );
		bContinuar = false;
	}	

	return lTotRegs;
}*/


bool CIniciarDiaCajas::inicializaFolioMiniFicha()
{
CString sConsulta;
bool bContinuar=true;	
char cArea='C';
		
	// foliomf.dat	-----> Es el Folio FOLIOC_RETIROPARCIAL

	// CAJAS
	CMaximo actualizarSQL(&odbc);
	sConsulta.Format(" UPDATE sysfolios SET folio=0 WHERE area='%c' and tipofolio=%d ", cArea, FOLIOC_RETIROPARCIAL );

	if ( actualizarSQL.Exec(sConsulta) )
	{
		actualizarSQL.activarCols();
		if( actualizarSQL.Leer() )
		{
			bContinuar=true;
		}
	}
	else
	{
		sConsulta.Trim();
		actualizarSQL.odbc->GetLastError(actualizarSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "inicializaFolioMiniFicha", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar=false;
	}


	if ( bContinuar )   // ROPA
	{	
		cArea='R';
		CMaximo actualizarSQL(&odbc);
		sConsulta.Format(" UPDATE sysfolios SET folio=0 WHERE area='%c' and tipofolio=%d ", cArea, FOLIOR_RETIROPARCIAL );

		if ( actualizarSQL.Exec(sConsulta) )
		{
			actualizarSQL.activarCols();
			if( actualizarSQL.Leer() )
			{
				bContinuar=true;
			}
		}
		else
		{
			sConsulta.Trim();
			actualizarSQL.odbc->GetLastError(actualizarSQL.GetHstmt());
			grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "inicializaFolioMiniFicha", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
			bContinuar=false;
		}
	}

	if ( bContinuar )	// MUEBLES
	{
		cArea='M';
		CMaximo actualizarSQL(&odbc);
		sConsulta.Format(" UPDATE sysfolios SET folio=0 WHERE area='%c' and tipofolio=%d ", cArea, FOLIOM_RETIROPARCIAL );

		if ( actualizarSQL.Exec(sConsulta) )
		{
			actualizarSQL.activarCols();
			if( actualizarSQL.Leer() )
			{
				bContinuar=true;
			}
		}
		else
		{
			sConsulta.Trim();
			actualizarSQL.odbc->GetLastError(actualizarSQL.GetHstmt());
			grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "inicializaFolioMiniFicha", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
			bContinuar=false;
		}
	}

	return bContinuar;
}

void CIniciarDiaCajas::capturaCajeras(int iModo)
{
	char cNombreProyecto[256], cNombreFuncionDLL[256];	
    char cInputParam1[1024]={0}, cInputParam2[1024]={0};

	SecureZeroMemory(cNombreProyecto, sizeof(cNombreProyecto));
	SecureZeroMemory(cNombreFuncionDLL, sizeof(cNombreFuncionDLL));

	SParametros parametros;

	parametros.iLink       = generarLink(); 
	if(sprintf_s( parametros.sServer, sizeof(parametros.sServer), "%s", cIP ) < 0){;}
	parametros.iTienda     = iTienda;       
	parametros.lEmpleado   = lEmpleadoSys;     
	parametros.iCajaActual = iCaja;         
	parametros.iMuestraMsg = iDesplegarError;   
	if(sprintf_s( parametros.sModo, sizeof(parametros.sModo), "%d", iModo ) < 0){;}

	nombreArchivo( "CA0083.DLL", cNombreProyecto, DIRECTORIO_CA );
	if(sprintf_s(cNombreFuncionDLL, sizeof(cNombreFuncionDLL), "CA0083") < 0){;}    
	if(memcpy_s( cInputParam1, sizeof(cInputParam1), &parametros, sizeof( cInputParam1 ) ) < 0){;}
	CargarDLL cargarDll( cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2 );

}

int CIniciarDiaCajas::existeBandera( bool &bContinuar )
{
	CString sConsulta;
	int iBandera=0;

	bContinuar=true;

	sConsulta.Format(" SELECT clave FROM cabanct " ) ;

	CCaBanCT cabanctSQL( &odbc );	
	if( cabanctSQL.Exec( sConsulta ) )
	{
		cabanctSQL.activarCols();
		if( cabanctSQL.Leer() )
		{
			if ( cabanctSQL.clave[0] == '1' )
				iBandera=1;
			else
				iBandera=0;
		}
	}
	else
	{
        cabanctSQL.odbc->GetLastError(cabanctSQL.GetHstmt());
        grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "existeBandera", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
		bContinuar = false;
	}	

	return iBandera;
}

void CIniciarDiaCajas::confirmarEnvioConsultaBuro()
{
	CString sFecha, sTexto;
	int  iCapturoHuellaGte=0, iNumSistema=3;
	long lGteHuella=0L;

	sFecha.Format("%02d-%02d-%04d",iDiaActual, iMesActual, iYearActual);
	sTexto.Format("SE HA REALIZADO EL ENVIO DE AUTORIZACIONES IMPRESAS \n PARA EL BURO DE CREDITO DEL DIA: %s " ,sFecha);

	AfxMessageBox( sTexto, MB_ICONINFORMATION );

	AfxMessageBox(" !!! SE VALIDARA HUELLA DE GERENTE !!! ");

	do
	{
		//tipo de movimiento 16
		validarHuellaEmpleadoGte(&odbc,lGteHuella,1,16,0,iTienda,iNumSistema,iCaja);
		if ( lGteHuella == -1 )
		{
			lGteHuella=5;
		}

		if ( lGteHuella > 15 )
        {
            iCapturoHuellaGte=1;
        }
        else
        {
            pintarMensajesErrorPasstda(lGteHuella);
        }
		
	}while ( iCapturoHuellaGte == 0 );

}

void CIniciarDiaCajas::generarInformeBloque4y5()
{
	char cNombreProyecto[256], cNombreFuncionDLL[256];	
    char cInputParam1[1024]={0}, cInputParam2[1024]={0};

	SecureZeroMemory(cNombreProyecto, sizeof(cNombreProyecto));
	SecureZeroMemory(cNombreFuncionDLL, sizeof(cNombreFuncionDLL));

	SParametros parametros;

	parametros.iLink       = generarLink(); 
	if(sprintf_s( parametros.sServer, sizeof(parametros.sServer), "%s", cIP ) < 0){;}
	parametros.iTienda     = iTienda;       
	parametros.lEmpleado   = lEmpleadoSys;     
	parametros.iCajaActual = iCaja;         
	parametros.iMuestraMsg = iDesplegarError;   

	nombreArchivo( "CA0012.DLL", cNombreProyecto, DIRECTORIO_CA );
	if(sprintf_s(cNombreFuncionDLL, sizeof(cNombreFuncionDLL), "CA0012") < 0){;}    
	if(memcpy_s( cInputParam1, sizeof(cInputParam1), &parametros, sizeof( cInputParam1 ) ) < 0){;}
	CargarDLL cargarDll( cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2 );

}


/*void CIniciarDiaCajas::generarReporte()
{
	CString sConsulta;
	int iAntig=0, iTda990u992=0, iEntra=0;
	int iDiaAlta=1, iMesAlta=1, iYearAlta=1900;
	char cFecha[20], cTexto[80], cNombreZona[50], cNombreCalle[50]; 
		
	memset(cNombreZona,' ',50);
	memset(cNombreCalle,' ',50);
	memset(cFecha,' ',sizeof(cFecha));

	//Ordenes de supervisi¢n con mas de tres d¡as forma el archivo temporal

	bContinuar=deleteTablasTiendaNumero(6);

	if ( bContinuar )
	{

		CConsultarSoClienteSupervisar supervisarSQL(&odbc_2);
		sConsulta.Format(" SELECT clave, tiendafolio, folio, nombre, apellidopaterno, apellidomaterno, ciudad, "
						" colonia, calle, situacionespecial, casa, fechaaltacliente FROM soclientesupervisar " );

		if( supervisarSQL.Exec( sConsulta ) )
		{
			supervisarSQL.activarCols();
			if( supervisarSQL.Leer() )
			{			
				sprintf(cFecha,"%s",supervisarSQL.fechaaltacliente);

				iAntig=antiguedad(cFecha);
				iTda990u992=antiguedad990u992(cFecha);

				if ( (supervisarSQL.clv[0] == 'P' || supervisarSQL.clv[0] == 'M' ) && iAntig == 0 && supervisarSQL.situacionespecial[0] != 'L' )
				{
					if ( (supervisarSQL.tiendafolio == 990 || supervisarSQL.tiendafolio == 992 || 
						supervisarSQL.clv[0] == 'M' ) && iTda990u992 == 1 )
					{
						iEntra=1;
					}

					if ( iEntra == 0 )
					{
						CCaVegaTmp3Dias caVegaSQL( &odbc );

						caVegaSQL.tienda=iTienda;

						iDiaAlta=supervisarSQL.fechaaltacliente.dia();
						iMesAlta=supervisarSQL.fechaaltacliente.mes();
						iYearAlta=supervisarSQL.fechaaltacliente.ano();
						caVegaSQL.fechaaltacliente.ponerFecha( iDiaAlta, iMesAlta, iYearAlta );

						caVegaSQL.tiendafolio=supervisarSQL.tiendafolio;					

						caVegaSQL.folio=supervisarSQL.folio;

						unirNombre(cTexto,80,supervisarSQL.nombre, supervisarSQL.apellidopaterno, supervisarSQL.apellidomaterno);
						memcpy(caVegaSQL.nombrecliente,cTexto,45);
						caVegaSQL.nombrecliente[45]=0;

						caVegaSQL.ciudad=supervisarSQL.ciudad;

						buscarNombreZona(supervisarSQL.ciudad, supervisarSQL.colonia, cNombreZona );
						memcpy(caVegaSQL.nombrezona,cNombreZona,20);
						caVegaSQL.nombrezona[20]=0;

						buscarNombreCalle(supervisarSQL.calle, cNombreCalle );
						memcpy(caVegaSQL.nombrecalle,cNombreCalle,20);
						caVegaSQL.nombrecalle[20]=0;

						caVegaSQL.casa=supervisarSQL.casa;

						caVegaSQL.fecha.ponerFecha( iDiaActual, iMesActual, iYearActual );

						caVegaSQL.prepararInsert();
						if( caVegaSQL.Insert() )
						{
							caVegaSQL.Commit();
						}
						else
						{
							sConsulta.Format( "Error al Insertar en la Tabla CaVegaOS" );
							caVegaSQL.odbc->GetLastError(caVegaSQL.GetHstmt());
							grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "generarReporte", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc, iDesplegarError );
							bContinuar=false;
						}
					}
					iEntra=0;
				}
			}
		}
		else
		{
			supervisarSQL.odbc->GetLastError(supervisarSQL.GetHstmt());
			grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "generarReporte", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_2, iDesplegarError );
			bContinuar=false;
		}
	}	
}

int CIniciarDiaCajas::antiguedad( char *cFechaAlta )
{
	int iDia=0, iMes=0, iAno=0, iTempDia=0, iTempMes=0, iTempAno=0, iFlag=0;
	long lFecha=0L, lFecha2=0L;
	char cTexto[10], cTexto2[10];

	memset(cTexto,' ',10);
    memset(cTexto2,' ',10);

	iDia=iDiaActual;
	iMes=iMesActual;
	iAno=iYearActual;

	sumarDia( -3, iDia, iMes, iAno );
	sprintf(cTexto,"%04d%02d%02d", iAno, iMes, iDia-1);
    lFecha=valor_campo(cTexto,8);

	iTempDia=iDiaActual;
	iTempMes=iMesActual;
	iTempAno=iYearActual;

	sumarDia( -30, iTempDia, iTempMes, iTempAno );
	sprintf(cTexto2,"%04d%02d%02d",iTempAno,iTempMes,iTempDia-1);
	lFecha2=valor_campo(cTexto2,8);

	if ( valor_campo(cFechaAlta,8) <= lFecha && valor_campo(cFechaAlta,8) >= lFecha2 )
	{
		iFlag=0; // es menor igual que la fecha del sistema menos 14 dias y es >= a la fecha del sistema -31 días
	}
	else
	{
		iFlag=1;
	}

	return iFlag;
}

int CIniciarDiaCajas::antiguedad990u992( char *cFechaAlta )
{
	int iDia=0, iMes=0, iAno=0, iTempDia=0, iTempMes=0, iTempAno=0, iFlag=0;
	long lFecha=0L, lFecha2=0L;
	char cTexto[10], cTexto2[10];

	memset(cTexto,' ',10);
    memset(cTexto2,' ',10);

	iDia=iDiaActual;
	iMes=iMesActual;
	iAno=iYearActual;

	sumarDia( -14, iDia, iMes, iAno );
	sprintf(cTexto,"%04d%02d%02d", iAno, iMes, iDia);
    lFecha=valor_campo(cTexto,8);

	iTempDia=iDiaActual;
	iTempMes=iMesActual;
	iTempAno=iYearActual;

	sumarDia( -30, iTempDia, iTempMes, iTempAno );
	sprintf(cTexto2,"%04d%02d%02d",iTempAno,iTempMes,iTempDia);
	lFecha2=valor_campo(cTexto2,8);

	if ( valor_campo(cFechaAlta,8) <= lFecha && valor_campo(cFechaAlta,8) >= lFecha2 )
	{
		iFlag=0; // es menor igual que la fecha del sistema menos 14 dias y es >= a la fecha del sistema -31 días
	}
	else
	{
		iFlag=1;
	}

	return iFlag;
}

bool CIniciarDiaCajas::buscarNombreZona(int iCiudad, int iColonia, char *cNombreZona)
{
	CString sConsulta;
	bool bEncontro=false;

	memset(cNombreZona,' ',50);

	CConsultarNombreZona zonasSQL(&odbc_1);

	sConsulta.Format(" select nombrezona from crzonas where ciudad=%d and colonia=%d ",iCiudad, iColonia );

	if ( zonasSQL.Exec(sConsulta) )
	{
		zonasSQL.activarCols();
		if( zonasSQL.Leer() )
		{
			memcpy(cNombreZona,zonasSQL.nombrezona,20);
			cNombreZona[20]=0;

			bEncontro=true;
		}
	}
	else
	{
		sConsulta.Trim();
		zonasSQL.odbc->GetLastError(zonasSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "buscarNombreZona", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_1, iDesplegarError );
	}

	return bEncontro;
}

bool CDlgCapturarDatosConyuge::buscarNombreCalle(long lCalle, char *cNombreCalle)
{
	CString sConsulta;
	bool bEncontro=false;

	memset(cNombreCalle,' ',50);

	CConsultarCalle calleSQL(&odbc_1);

	sConsulta.Format(" select calle, nombrecalle FROM crcalles where calle=%ld ", lCalle );

	if ( calleSQL.Exec(sConsulta) )
	{	
		calleSQL.activarCols();
		if( calleSQL.Leer() )
		{
			memcpy(cNombreCalle,calleSQL.nombrecalle,20);
			cNombreCalle[20]=0;

			bEncontro=true;
		}
	}
	else
	{
		sConsulta.Trim();
		calleSQL.odbc->GetLastError(calleSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "buscarNombreCalle", (LPTSTR)(LPCTSTR)sConsulta, lEmpleadoSys, "ERROR EN LA CONSULTA", &odbc_1, iDesplegarError );
	}

	return bEncontro;
}*/

bool CIniciarDiaCajas::graboBandera()
{
	CString sSql;
	bool bContinuar=true;
	int iFlag = 0;

	sSql.Format( "SELECT cagrabarbanderacabanct()" );

	CFlagCoppel grabarBanderaSQL( &odbc,false );

	if ( grabarBanderaSQL.Exec(sSql) )
	{
		if ( grabarBanderaSQL.Leer() )
		{
			iFlag = grabarBanderaSQL.flag;
			// iFlag = 1 --> Si grabo
			// iFlag = 0 --> No grabo
		}
	}
   	else
	{
        grabarBanderaSQL.odbc->GetLastError(grabarBanderaSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "graboBandera", (LPTSTR)(LPCTSTR)sSql, lEmpleadoSys, "ERROR EN LA CONSULTA", grabarBanderaSQL.odbc, iDesplegarError );
		bContinuar = false;
	}

	return bContinuar;
}

bool CIniciarDiaCajas::respaldarConveniosPorSupervisor()
{
	CString sSql;
	bool bContinuar=true;
	int iFlag = 0;

	sSql.Format( "SELECT tdrespaldarcaacumconvsupervisor('%ld')",lFechaSys );

	CFlagCoppel respaldarConveniosSQL( &odbc_3,false );

	if ( respaldarConveniosSQL.Exec(sSql) )
	{
		respaldarConveniosSQL.Leer();
	}
   	else
	{
        respaldarConveniosSQL.odbc->GetLastError(respaldarConveniosSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "respaldarConveniosPorSupervisor", (LPTSTR)(LPCTSTR)sSql, lEmpleadoSys, "ERROR EN LA CONSULTA", respaldarConveniosSQL.odbc, iDesplegarError );
		bContinuar = false;
	}

	return bContinuar;
}

bool CIniciarDiaCajas::iniciarTl()
{
	CString sSql;
	bool bContinuar = true;

	sSql.Format("UPDATE tdtotaleslinea SET regsaltahuellas=-1,regsaltahuellasinvalidas=0");

	CFlagCoppel totaleslineaSQL(&odbc,false);

	if ( !totaleslineaSQL.Exec(sSql) )
	{
	    totaleslineaSQL.odbc->GetLastError(totaleslineaSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "respaldarConveniosPorSupervisor", (LPTSTR)(LPCTSTR)sSql, lEmpleadoSys, "ERROR EN LA ACTUALIZACION", totaleslineaSQL.odbc, iDesplegarError );
		bContinuar = false;

	}

	return bContinuar;
}

bool CIniciarDiaCajas::pasarRechajus()
{
	CString sSql;
	bool bContinuar = true;

	sSql.Format("SELECT capasarcaajustes()");

	CFlagCoppel caAjustesSQL(&odbc,false);

	if ( !caAjustesSQL.Exec(sSql) )
	{
	    caAjustesSQL.odbc->GetLastError(caAjustesSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIP, "CA0030", "CIniciarDiaCajas", "pasarRechajus", (LPTSTR)(LPCTSTR)sSql, lEmpleadoSys, "ERROR EN LA CONSULTA", caAjustesSQL.odbc, iDesplegarError );
		bContinuar = false;

	}

	return bContinuar;
}