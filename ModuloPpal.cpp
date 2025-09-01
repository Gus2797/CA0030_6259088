/* --------------------------------------------------------------------
    Fecha    : 25/10/04 13:01  ( dd-mm-aa )
    Elabor¢  : Joel Armando Arana Garcia
    Solicit¢ : Lic. Jos‚ G. Mendoza
    Actividad: Captura de Abonos
   -------------------------------------------------------------------- */

#define MAIN

#include "stdafx.h"
#include "sysCapturarAbono.h"
#include "CapturarAbono.h"
#include "DlgCapturarAbono.h"

#include "Gnwproto.hpp"
#include "Cnwproto.hpp"
#include "Cawstruc.hpp"
#include "Cawproto.hpp"
#include "password.hpp"
#include "flags.hpp"
#include "general.hpp"
#include "wTienda.hpp"

#include "c_menu.hpp"
#include "cargarDll.h"
#include "CConsumoAPICuentasSeguros.h"

static void recuperaTarjetas(int iTienda, int iCaja, int iAnio, int iMes, int iDia);
void CambiaResolucion(int iAncho, int iAlto);
int gnTipoCableUSB(char cArea, int iCaja);
int gnConectarImpresora(void);
int gnConectarLaser(void);
int gnDesconectarImpresora(void);
bool gnConectaUSB(char cArea, int iCaja);
void gnValidarCRTP(char flag);
CString serverIpTiendaLocal = "", sNumTienda = "", sNumCiudad = "", sNumEmpleado = "";

int CA0030(char *cInput1, char *cInput2)
{
    UNREFERENCED_PARAMETER(cInput2);
    WinExec("C:\\Windows\\Microsoft.NET\\Framework\\v4.0.30319\\RegAsm.exe C:\\sys\\progx\\libcsharp\\puentecsharptienda.dll /tlb:C:\\sys\\progx\\libcsharp\\puentecsharptienda.tlb /codebase", SW_HIDE);//SW_SHOW
    int actualWidth = 0, actualHeight = 0, newWidth = 0, newHeight = 0;
    gnConsultarResolucion(actualWidth, actualHeight);
    CambiaResolucion(1280, 800);
    char cSqlTxt[255] = { 0 }, cFechaSys[15] = { 0 }, cAreaImp = ' ', cIpTienda[22] = { 0 }, cIpTiendaLocal[25] = { 0 }, cMensajeSeguimiento[150] = { 0 };
    int iFlagConexion = 0, iOpcion = 0, iEncontroDerechos = 0;
    bool bSalir = true, bContinuar = true, bCambiarResolucion = false;
    CUtil util;
    char cLog[500] = { 0 };
    SParametros sParametros;
    SecureZeroMemory(&sParametros, sizeof(SParametros));
	if(memcpy_s(&sParametros, sizeof(sParametros), cInput1, sizeof(SParametros)) < 0){;}

    if (checarLink(sParametros.iLink))
    {
        CDlgCapturarAbono dlg;

        dlg.m_grid.sServer.Format("%s", sParametros.sServer);
        dlg.m_grid.sServer.Trim();
        if(sprintf_s(dlg.m_grid.cUsuario, "systiendacartera") < 0){;}
        dlg.m_grid.iTienda = (short)sParametros.iTienda;

        dlg.m_grid.lEmpleado = sParametros.lEmpleado;
        dlg.m_grid.iCaja = (short)sParametros.iCajaActual;
        dlg.m_grid.iMuestraMsg = (short)sParametros.iMuestraMsg;
        dlg.m_grid.lCliente = sParametros.lCliente;
        dlg.iSistema = (short)sParametros.iNumSistema;
        dlg.iCiudad = sParametros.iCiudad;

        if(sprintf_s(cLog, "FC0200805103819972 - inicio - CA0030 ******************************************************") < 0){;}
        util.GrabarLog(cLog);
        if(sprintf_s(cLog, "FC0200805103819975 - iTienda=%d, iCajaActual=%d, iSistema=%d, lEmpleado=%ld",
            dlg.m_grid.iTienda, dlg.m_grid.iCaja, dlg.iSistema, dlg.m_grid.lEmpleado) < 0){;}
        util.GrabarLog(cLog);

        switch (dlg.iSistema)
        {
        case SISTEMA_MUEBLES:
            cAreaImp = 'M';
            break;
        case SISTEMA_ROPA:
            cAreaImp = 'R';
            break;
        case SISTEMA_CAJAS:
            cAreaImp = 'C';
            break;
        case SISTEMA_CLIENTES_NUEVOS:
            cAreaImp = 'N';
            break;
        default:
            cAreaImp = 'C';
        }

        dlg.m_grid.cArea = cAreaImp;

        iFlagConexion = 0;

        if(sprintf_s(cIpTiendaLocal, "%s", dlg.m_grid.sServer) < 0){;}

        if (abrirConexionBD(&odbc, cIpTiendaLocal, cIpTiendaLocal, CONECTA_TIENDANUMERO, dlg.m_grid.iTienda))
        {
            if (dlg.iSistema == SISTEMA_CAJAS)
            {
                //Se abortan los procesos del ActiveSync si este esta activo
                activarASync(false);
                gnConectaUSB(&odbc, 'C', dlg.m_grid.iCaja);
            }

            if (dlg.obtenerDatosGnDominio())
            {
                if (dlg.iSistema == SISTEMA_CAJAS)
                {
                    recuperaTarjetas(dlg.m_grid.iTienda, dlg.m_grid.iCaja, dlg.iAnioActual, dlg.iMesActual, dlg.iDiaActual);
                }

                if (dlg.obtenerFlag('C', FLAGC_SEGUROBANORTE, dlg.iFlagBanorte) &&
                    dlg.obtenerFlag('C', FLAGC_VOLANTE, dlg.iFlagVolante) &&
                    dlg.obtenerFlag('C', FLAGC_SEGUROS, dlg.iFlagSegAfirme) &&
                    dlg.obtenerFlag('0', FLAG_TDAESTACIONAMIENTO, dlg.iFlagTdaConEstacionamiento) &&
                    dlg.obtenerFlag('C', FLAGC_CLAVETERMINACION, dlg.iFlagTerminacion) &&
                    dlg.obtenerFlag('C', FLAGC_CAPTURABENEFICIARIO, dlg.iFlagCapturaBeneficiario) &&
                    dlg.obtenerFlag('0', FLAG_SEGUROS_AUTO_PROTECCION, dlg.iFlagSeguroAuto) &&
                    //dlg.obtenerFlag( '0',FLAG_VALIDAR_TELEFONOS_COFETEL,dlg.iFlagCapturarTelefonos) && //21749
                    dlg.obtenerFlag('C', FLAGC_ENCUESTA_CAT, dlg.iFlagEncuestaCat) &&
                    dlg.obtenerFlag('0', FLAG_VENTA_SEGS_ADICIONALES, dlg.iFlagSeguroAdicional) &&
                    dlg.obtenerFlag('0', FLAG_CANDIDATOASTERISCOCOPPEL, dlg.iFlagAsteriscoCoppel) &&
                    dlg.obtenerFlag('0', FLAG_CANDIDATOPROMOCIONDIRECTA, dlg.iFlagPromocionDirecta) &&
                    dlg.obtenerFlag('0', FLAG_CONTACTO_EFECTIVO, dlg.iFlagContactoEfectivo) &&
                    dlg.obtenerFlag('C', FLAGC_DOMICILIACION_CUENTAS, dlg.iFlagDomiciliacion) &&
                    dlg.obtenerFlag('0', FLAG_CANCELACION_SEGUROS_PF, dlg.iFlagPermiteCancelarSeguros) &&
                    dlg.obtenerFlag('0', FLAG_PERMITIR_SEGURO_ADICIONAL_BANCOPPEL, dlg.iFlagPermiteSeguroAdicionalBancoppel) &&
                    dlg.obtenerFlag('0', FLAG_PAGO_APOYO_ADICIONAL, dlg.iFlagApoyoAdicionalPF) &&
                    dlg.obtenerFlag('0', FLAG_CLUB_PROTECCION_SALUD, dlg.iFlagPlandeSalud) &&
                    dlg.obtenerFlag('C', FLAGC_MARCADO_CANDIDATOS_CPF, dlg.iFlagMarcadoCandidatosCPF) &&
                    dlg.obtenerFlag('C', FLAGC_REGISTRO_PLANDELEALTAD, dlg.iFlagRegistroPL) &&
                    dlg.obtenerFlag('C', FLAGC_CAMPO_INTELIGENTE, dlg.iFlagCampoInteligentePL) &&
					dlg.obtenerFlag('C', FLAGC_FUNCIONALIDAD_ETP, dlg.iFlagETP) &&
					dlg.obtenerFlag('C', FLAGC_MOSTRAR_ABONOS_PUNTUALES_LEGADO, dlg.iflagCoppelRecompensaTuPuntualidad) &&
					dlg.obtenerFlag('C', FLAGC_MOSTRAR_DINERO_ELECTRONICO_ABONOS_LEGADO, dlg.iflagDineroElectronico) &&
					dlg.obtenerFlag('C', FLAGC_FUNCIONALIDAD_NME_ABONOS_LEGADO, dlg.iflagNuevoMonederoElectronico) &&
					dlg.obtenerFlag('C', FLAGC_MENSAJE_GANADOR_COPPEL_MAX, dlg.iflagGanador) &&
					dlg.obtenerFlag('C', FLAGC_IMPRIMIR_GANADOR_COPPEL_MAX_NPV, dlg.iflagTicketsCoppelMax))
                {
                    if(sprintf_s(cMensajeSeguimiento, "Consulta flag 174 FLAG_CLUB_PROTECCION_SALUD: %d", dlg.iFlagPlandeSalud) < 0){;}
                    dlg.grabarLog(cMensajeSeguimiento);
                    if (consultarIpServidor(&odbc, dlg.cIpServidorCFE, SERV_PSCFE, cSqlTxt))
                    {
                        if (consultarIpServidor(&odbc, dlg.cIpServidorTelmex, SERV_PSTELMEX, cSqlTxt))
                        {
                            if (consultarIpServidor(&odbc, dlg.cIpServidorCentral, SERV_CENTRALEMPS, cSqlTxt))
                            {
                                if (consultarIpServidor(&odbc, dlg.cIpServidorCartera, SERV_CARTERA, cSqlTxt))
                                {
                                    if (consultarIpServidor(&odbc, dlg.cIpServidorCredito, SERV_CREDITO, cSqlTxt))
                                    {
                                        if (consultarIpServidor(&odbc, dlg.cIpServidorPlanes, SERV_PLANES_TA, cSqlTxt))
                                        {
                                            dlg.iFinLinea = finLinea(&odbc, cAreaImp, dlg.m_grid.iCaja, bContinuar, cSqlTxt, true);
                                            if (bContinuar)
                                            {
                                                dlg.iTipoImpresora = tipoImpresora(&odbc, cAreaImp, dlg.m_grid.iCaja, bContinuar, cSqlTxt, true);
                                                if (!bContinuar)
                                                {
                                                    AfxMessageBox(" ERROR AL OBTENER TIPOIMPRESORA ");
                                                }
                                                else
                                                {
                                                    InicioDiaCajas inicioDiaCajas;
                                                    SecureZeroMemory(&inicioDiaCajas, sizeof(InicioDiaCajas));
                                                    inicioDiaCajas.iTienda = dlg.m_grid.iTienda;
                                                    inicioDiaCajas.iCiudad = dlg.iCiudadGnDominio;
                                                    inicioDiaCajas.iCaja = dlg.m_grid.iCaja;
                                                    inicioDiaCajas.iDesplegarError = dlg.m_grid.iMuestraMsg;
                                                    inicioDiaCajas.lEmpleadoSys = dlg.m_grid.lEmpleado;
                                                    if(sprintf_s(inicioDiaCajas.cIP, "%s", dlg.m_grid.sServer) < 0){;}
													if(sprintf_s(cFechaSys, "%04d%02d%02d", dlg.iAnioActual, dlg.iMesActual, dlg.iDiaActual) < 0){;}
                                                    inicioDiaCajas.iDiaActual = dlg.iDiaActual;
                                                    inicioDiaCajas.iMesActual = dlg.iMesActual;
                                                    inicioDiaCajas.iYearActual = dlg.iAnioActual;
                                                    inicioDiaCajas.lFechaSys = strtol(cFechaSys, NULL, 10);
                                                    if (dlg.checarCorteCajas() != 1)  //no se ha hecho el corte de caja puede entrar al sistema normal    
                                                    {
                                                        if (dlg.iSistema == SISTEMA_CAJAS)
                                                        {
                                                            if (checarInicioCajas(&odbc, 1, cSqlTxt, inicioDiaCajas))
                                                            {
                                                                iFlagConexion = 1;
                                                                dlg.obtenerDatosGnDominio();//Retoma la fecha despues que la modifico el Inicio del dia
                                                                // Se manda llamar el ejecutable "VALIDACAMPANASDE.EXE", de forma asincrona, es decir que corra en paralelo.
                                                                if (inicioDiaCajas.iCaja == 1)
                                                                {
                                                                    CString sIptienda = "", sTienda = "", sAccion = "", sCiudad = "";
                                                                    sIptienda.Format("%s", inicioDiaCajas.cIP);
                                                                    sTienda.Format("%d", inicioDiaCajas.iTienda);
                                                                    sCiudad.Format("%d", inicioDiaCajas.iCiudad);
                                                                    sAccion = "3";


                                                                    serverIpTiendaLocal = sIptienda;
                                                                    sNumTienda = sTienda;
                                                                    sNumCiudad = sCiudad;
                                                                    sNumEmpleado.Format("%ld", dlg.m_grid.lEmpleado);
                                                                    /*dlg.grabarLog("main: Cargando modulo GN0276.DLL");
                                                                    gnValidarCRTP('0');
                                                                    dlg.grabarLog("main: Fin modulo GN0276.DLL");*/

                                                                    _spawnl(P_NOWAITO, "C:\\SYS\\PROGS\\VALIDACAMPANASDE.EXE", "C:\\SYS\\PROGS\\VALIDACAMPANASDE.EXE", sIptienda, sTienda, sCiudad, sAccion, NULL);
                                                                    //Se ejecuta VALIDAMOVSRECOMPENSA.EXE para evaluar los movimientos pendientes de coppel recompensa. Folio 19589
                                                                    _spawnl(P_NOWAITO, "C:\\SYS\\PROGS\\VALIDAMOVSRECOMPENSA.EXE", "C:\\SYS\\PROGS\\VALIDAMOVSRECOMPENSA.EXE", sIptienda, sTienda, sCiudad, sAccion, NULL);
                                                                }
                                                                //se valida
                                                            }
                                                            else
                                                            {
                                                                grabarMensajeError("C", dlg.m_grid.iCaja, (LPTSTR)(LPCTSTR)dlg.m_grid.sServer, "CapturarAbono", "ModuloPpal.cpp", "CA0030", (LPTSTR)(LPCTSTR)cSqlTxt, dlg.m_grid.lEmpleado, "ERROR EN LA CONSULTA(moduloPpal)", &odbc, dlg.m_grid.iMuestraMsg);
                                                                AfxMessageBox("Ocurrio Error al inicio del dia checar SysMensajeError ");
                                                            }
                                                        }
                                                        else
                                                        {
                                                            iFlagConexion = 1;
                                                            dlg.obtenerDatosGnDominio();
                                                        }
                                                    }
                                                    else
                                                    {
                                                        dlg.procesoCierreCajas();
                                                        if (dlg.iFlagCorte != 3)
                                                        {
                                                            dlg.menuOperacionesVarias();
                                                            iFlagConexion = 1;
                                                            dlg.iFlagCorte = 1;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        else
                                        {
                                            AfxMessageBox(" ERROR AL OBTENER SERVIDOR PLANES (capturarAbono) ");
                                        }
                                    }
                                    else
                                    {
                                        AfxMessageBox(" ERROR AL OBTENER SERVIDOR HUELLAS (CapturarAbono) ");
                                    }
                                }
                                else
                                {
                                    AfxMessageBox(" ERROR AL OBTENER SERVIDOR CARTERA (CapturarAbono) ");
                                }
                            }
                            else
                            {
                                AfxMessageBox(" ERROR AL OBTENER SERVIDOR CENTRAL (CapturarAbono) ");
                            }
                        }
                        else
                        {
                            AfxMessageBox(" ERROR AL OBTENER SERVIDOR TELMEX (CapturarAbono) ");
                        }
                    }
                    else
                    {
                        AfxMessageBox(" ERROR AL OBTENER SERVIDOR CFE (CapturarAbono) ");
                    }

                }
                else
                {
                    AfxMessageBox(" ERROR AL OBTENER LOS FLAGS ");
                }
            }
            else
            {
                AfxMessageBox(" ERROR AL OBTENER DATOS EN GNDOMINIO ");
            }
        }
        else
        {
            cerrarConexionBD(&odbc);
            AfxMessageBox("Error al abrir conexión BD TIENDA.####");
        }

        if (iFlagConexion == 1)
        {
            if (dlg.iSistema != SISTEMA_ROPA && dlg.iSistema != SISTEMA_MUEBLES)
            {
                if (dlg.iSistema == SISTEMA_CAJERA_CAPTURISTA)
                {
                    if (dlg.iFlagCorte != 1)
                    {
                        dlg.iFlagMovimiento = 2;
                        dlg.m_grid.iFlagCargo = 2;
                        dlg.DoModal();
                    }
                }
                else
                {
                    while (bSalir && dlg.iFlagCorte != 1)
                    {

						char * opciones[] = { "F1   Recibir Abonos de Ctes                   ",
											  "F2   Elaborar Cargos de Ctes                  ",
											  "Esc  Salir                                    ",
											  "" };

						int respuesta[] = { F1,F2,ESC,0 };

						if (dlg.obtenerFlag('C', 301, dlg.iFlagMenuInicial))
						{
							// SI ESTÁ PRENDIDO EL FLAG MUESTRA EL MENU
							if (dlg.iFlagMenuInicial == 1)
							{
								C_Menu menu("  C A J A S    D E    A B O N O S  ", opciones, respuesta);

								dlg.iOpcionSeleccionadaMenuInicial = menu.OpcionSeleccionada();
							}
							else
							{
								// SI NO ESTÁ PRENDIDO SE MUESTRA DIRECTAMENTE LA OPCION F1
								dlg.iOpcionSeleccionadaMenuInicial = F1;
							}
						}
						else
						{
							// SI NO SE HACE LA CONSULTA NO SE MUESTRA EL MENÚ
							dlg.iOpcionSeleccionadaMenuInicial = F1;
						}

						if (dlg.iFlagMenuInicial != 1)
						{
							dlg.iFlagMenuInicial = 0;
						}


                        switch (dlg.iOpcionSeleccionadaMenuInicial)
                        {
                        case F1:
                        {
                            if (dlg.iSistema == SISTEMA_CAJAS)
                            {
                                dlg.verificarEmpleadoTdClaves(dlg.m_grid.lEmpleado, iEncontroDerechos);
                                if (iEncontroDerechos != 1)
                                {
                                    CString sTexto;
                                    sTexto.Format("EL EMPLEADO %ld NO TIENE DERECHOS EN CAJAS, POR LO CUAL NO SERA TOMADO EN CUENTA\nEN EL REPORTE DE LA EFICIENCIA DE LAS CAJERAS, USE LA OPCIÓN DE ALTA DE CLAVES", dlg.m_grid.lEmpleado);
                                    AfxMessageBox(sTexto);
                                }
                                iEncontroDerechos = 0;
                            }

                            dlg.iFlagMovimiento = 1;
                            dlg.m_grid.iFlagCargo = 1;
                            dlg.consultarMensajeSeguro();
                            dlg.DoModal();

                            if (dlg.bFlagSalirXCaja)	bSalir = false;

                            if (dlg.iFlagCorte == 1)	// Checa si ya se efectuo el corte de caja
                            {
                                bSalir = false;
                            }
                            else if (dlg.iFlagCorte == 3)
                            {
                                bSalir = false;
                            }

							if (dlg.iFlagMenuInicial == 0)
							{
								iOpcion = AfxMessageBox("CONFIRMAR SALIDA", MB_YESNO | MB_ICONQUESTION);
								if (iOpcion == IDYES)
								{
									dlg.grabarLog("Main: Saliendo del Capturar Abono");
									bSalir = false;
								}
							}
                        }
                        break;
                        case F2:
                        {
                            dlg.iFlagMovimiento = 0;
                            dlg.m_grid.iFlagCargo = 0;
                            dlg.DoModal();
                            if (dlg.bFlagSalirXCaja)	bSalir = false;
                        }
                        break;
                        case ESC:
                            iOpcion = AfxMessageBox("CONFIRMAR SALIDA", MB_YESNO | MB_ICONQUESTION);
                            if (iOpcion == IDYES)
                            {
                                dlg.grabarLog("Main: Saliendo del Capturar Abono");
                                bSalir = false;
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            else
            {
                dlg.iFlagMovimiento = 1;
                dlg.m_grid.iFlagCargo = 1;
                dlg.DoModal();
            }

            if (dlg.iFlagCorte == 1)	// Ya se efectuo el corte de caja
            {
                bSalir = true;
                while (bSalir)
                {
                    iOpcion = AfxMessageBox("CONFIRMAR SALIDA", MB_YESNO | MB_ICONQUESTION);
                    if (iOpcion == IDYES)
                    {
                        bSalir = false;
                        if (dlg.iSistema != SISTEMA_CAJAS)
                        {
                            bCambiarResolucion = true;
                        }
                    }
                    else
                    {
                        dlg.procesoCierreCajas();
                        dlg.menuOperacionesVarias();
                    }
                }
            }
            else
            {
                if (dlg.iSistema != SISTEMA_CAJAS)
                {
                    bCambiarResolucion = true;
                }
            }
            if (bCambiarResolucion)
            {
                gnConsultarResolucion(newWidth, newHeight);
                if ((actualWidth != newWidth) || (actualHeight != newHeight))
                {
                    CambiaResolucion(actualWidth, actualHeight);
                }
            }
        }

        dlg.grabarLog("FC0200805103819980 - fin - CA0030 ------------------------------------------------------");
    }
    cerrarConexionBD(&odbc);
    cerrarConexionBD(&odbc_1);
    cerrarConexionBD(&odbcSolicitudes);
    cerrarConexionBD(&odbcCuentasPerdidas);

    return true;
}

static void recuperaTarjetas(int iTienda, int iCaja, int iAnio, int iMes, int iDia)
{
    char cIPServidorSolicitudes[20] = { 0 }, cIPServidorSolicitudesAlterno[20] = { 0 };
    char cSql[255] = { 0 }, cFecha[12] = { 0 };

	if(sprintf_s(cFecha, "%04d-%02d-%02d", iAnio, iMes, iDia) < 0){;}

    if (consultarIpServidores(&odbc, cIPServidorSolicitudes, cIPServidorSolicitudesAlterno, SERV_SOLICITUDES, cSql))
    {
        if (abrirConexionBD(&odbcSolicitudes, cIPServidorSolicitudes, cIPServidorSolicitudesAlterno, CONECTA_SOLICITUDES, iTienda))
        {
			if(sprintf_s(cSql, "UPDATE soTarjetasCredito SET status=1,caja=0 WHERE tienda=%d AND caja=%d AND status=2 AND fechaentrega='%s';", iTienda, iCaja, cFecha) < 0){;}

            CMaximo recTarjetas(&odbcSolicitudes);

            if (recTarjetas.Exec(cSql))
            {
                recTarjetas.Commit();
            }
        }
    }

    cerrarConexionBD(&odbcSolicitudes);
}

void CambiaResolucion(int iAncho, int iAlto)
{
    Sleep(1000);
    DEVMODE devmode;
    ZeroMemory(&devmode, sizeof(DEVMODE));

    devmode.dmSize = sizeof(DEVMODE);
    devmode.dmPelsWidth = iAncho;
    devmode.dmPelsHeight = iAlto;
    devmode.dmFields |= DM_PELSWIDTH;
    devmode.dmFields |= DM_PELSHEIGHT;
    devmode.dmBitsPerPel = 32;
    devmode.dmFields |= DM_BITSPERPEL;

    long result = ChangeDisplaySettings(&devmode, CDS_UPDATEREGISTRY);
}

int gnTipoCableUSB(char cArea, int iCaja)
{
    int iRegresa = 0;
    char cSql[128] = { 0 };

    {
		if(sprintf_s(cSql, "SELECT tipocable FROM sysMicros WHERE area = '%c' AND caja = '%d';", cArea, iCaja) < 0){;}

        CMaximo consultarTipoCable(&odbc);

        if (!consultarTipoCable.Exec(cSql))
        {
            consultarTipoCable.odbc->GetLastError(consultarTipoCable.GetHstmt());
            AfxMessageBox("Error al buscar dato tipocable en sysMicros");
        }
        else
        {
            consultarTipoCable.activarCols();
            if (consultarTipoCable.Leer())
            {
                if (consultarTipoCable.Total == 1)
                {
                    iRegresa = 1;
                }
            }
            else
            {
                AfxMessageBox("No existen datos en tipocable de sysMicros");
            }
        }
    }

    if (iRegresa == 1)
    {
		if(sprintf_s(cSql, "SELECT tipoimpresora FROM sysMicros WHERE area = '%c' AND caja = '%d';", cArea, iCaja) < 0){;}

        CMaximo consultarTipoImpresora(&odbc);

        if (!consultarTipoImpresora.Exec(cSql))
        {
            consultarTipoImpresora.odbc->GetLastError(consultarTipoImpresora.GetHstmt());
            AfxMessageBox("Error al buscar dato tipoimpresora en sysMicros");
        }
        else
        {
            consultarTipoImpresora.activarCols();
            if (consultarTipoImpresora.Leer())
            {
                if (consultarTipoImpresora.Total == 1)
                {
                    iRegresa = 2;
                }
            }
        }
    }

    return iRegresa;
}

int gnConectarImpresora(void)
{
    int iRespuesta = -1;

    iRespuesta = system("\\windows\\system32\\net use lpt1: \\\\127.0.0.1\\Impresora /persistent:yes>>c:\\sys\\mem\\error.txt");

    return iRespuesta;
}

int gnConectarLaser(void)
{
    int iRespuesta = -1;

    iRespuesta = system("\\windows\\system32\\net use lpt1: \\\\127.0.0.1\\Laser /persistent:yes>>c:\\sys\\mem\\error.txt");

    return iRespuesta;
}

int gnDesconectarImpresora(void)
{
    int iRespuesta = -1;

    iRespuesta = system("\\windows\\system32\\net use lpt1: /d");

    return iRespuesta;
}

bool gnConectaUSB(char cArea, int iCaja)
{
    bool bRegresa = true;
    int iUSB = 0;

    gnDesconectarImpresora();

    iUSB = gnTipoCableUSB(&odbc, cArea, iCaja);

    if (iUSB != 0)
    {
        if (iUSB == 1)
        {
            if (gnConectaImpresora() != 0)
            {
                bRegresa = false;
            }
        }
        else
        {
            if (cArea == 'M')
            {
                if (gnConectaLaser() != 0)
                {
                    bRegresa = false;
                }
            }
            else
            {
                bRegresa = false;
            }
        }
    }

    return bRegresa;
}

void gnValidarCRTP(char flag) {

    CString sReciboFin = "", sCliente = "", sCajaActual = "", cArea = "",
        sNomCliente = "", sTipoMovimiento = "", sAccion = "", sCajaOriginal = "", sPuntualidad = ""
        , sTotalCuentas = "", sMinimo = "", sTipoCuenta = "", jsonDatosClientes = "", facturaCuenta = "";

    CString iFlagCRTP = "";
    iFlagCRTP.Format("%c", flag);


    CString url = "C:\\SYS\\PROGX\\GN\\GN0276.DLL";
    CString nomMetodo = "ValidaCRTP.ValidaClienteCRTP";
    CargarDLLCS cargarDatosDllCS;
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)serverIpTiendaLocal);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)sNumTienda);
    cargarDatosDllCS.addParam("C:\\sys\\PROGX\\gn\\GN0276.DLL");
    cargarDatosDllCS.addParam("ValidarCRTP.Form1");
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)cArea);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)sCajaActual);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)sNumCiudad);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)sCliente);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)sNomCliente);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)sReciboFin);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)sTipoMovimiento);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)sAccion);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)sCajaOriginal);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)iFlagCRTP);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)jsonDatosClientes);
    cargarDatosDllCS.addParam((LPTSTR)(LPCTSTR)sNumEmpleado);

    cargarDatosDllCS.cargarDllCS("C:\\sys\\PROGX\\gn\\GN0276.DLL", "ValidarCRTP.Form1");

}