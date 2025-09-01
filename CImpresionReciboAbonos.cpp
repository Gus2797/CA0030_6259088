#pragma once

#include "stdafx.h"
#include "DlgCapturarAbono.h"
#include "CGRABARCERTIFICACIONABONO.HPP" 
#include "COBTENERFECHAPRIMERABONO.HPP" 

#define TOTAL_DETALLES 11           // Total de conceptos que salen impresos en el recibo de abono.
#define LONGITUD_COLUMNA_CTAS 115   // Ancho de las columnas para las cuentas.
#define COLUM_INICIA_ENCABEZADO 640 // Columna donde inicia el nombre
#define MAX_COLUMNAS 1455           // Maximo de columnas por default en el recibo y el recibo tendra mas de 8 cuentas este numero se incrementara.


void CDlgCapturarAbono::imprimirRecibo()
{
    char cMensaje[150] = { 0 };
    iRenglon = iRenglonCta = 0;
    SecureZeroMemory(&iAbonoConVencidoFinalImpresion, sizeof(iAbonoConVencidoFinalImpresion));
	if(sprintf_s(cMensaje, "CDlgCapturarAbono::Inicia Impresion del recibo, Cliente = %ld, Recibo = %ld", m_grid.lCliente, lNumeroRecibo) < 0){;}
    grabarLog(cMensaje);

    // IMPRIME LAS CUENTAS DEL CLIENTE

	if(sprintf_s(cArchivoImpresion, "c:\\sys\\mem\\ReciboAbono.PRN") < 0){;}

    imprimirReciboTermica();

	terminarMovimientoOperacion();//PET 20275
}

bool CDlgCapturarAbono::ObtenerVencido()
{
    bool bContinua = true;
    char sSqlTxtc[600] = { 0 };
	if(sprintf_s(sSqlTxtc, "SELECT clave,conceptocuenta,tienda,factura,fechacompra,importe,diapago,fechavencimiento,fechaultimomovimiento,fechasaldacon,fechaconvenio,empleadoconvenio,plazoconvenio,importeconvenio,saldo,interesadicional,base,vencido,minimo,saldacon,bonificacion,supago,numeroseguros,numeromeses,flagconyugal,fechavencimientoanterior,saldaconanteriormuebles,tipoconvenio,flagcapturoconvenio,status,cantidadanteriorseguros,subtipoconvenio,interesprimermes, tipoproducto, minimototal,saldototal,vencidototal,minimototalfinal,saldototalfinal,vencidototalfinal, flagcuentaperdida from tmpcagrabarabono ") < 0){;}
    CTmpCaGrabarAbono tmpCaGrabarAbono(&odbc);

    if (tmpCaGrabarAbono.Exec(sSqlTxtc))
    {
        int  i = 0;
        tmpCaGrabarAbono.activarCols();
        while (tmpCaGrabarAbono.Leer())
        {
			if(i>=0){iAbonoConVencidoFinalImpresion[i] = tmpCaGrabarAbono.vencido; i++;}
        }
    }
    else
    {
        tmpCaGrabarAbono.odbc->GetLastError(tmpCaGrabarAbono.GetHstmt());
        grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)odbc.m_strServer, "CA0030", "CDlgCapturarAbono", "ObtenerVencido", sSqlTxtc, lEmpleadoDlg, "ERROR EN LA CONSULTA", tmpCaGrabarAbono.odbc, iMuestraMsg);
    }

    return bContinua;
}

void CDlgCapturarAbono::imprimirReciboTermica()
{
    int iRenTmp = 0; // Renglon para controlar flujos alternos en la impresion.
    int iRenglonInicialCtas = 0; // Este renglon es de donde se empezara a imprimir las cuentas. No cambia y se asigna valor al terminar el encabezado del recibo.
    int iContDetalles = 0;
    bool bAplicaBonificacion = false;
    int iCtasAImp = 0, iFlagNoDebe = 0, iTipoPlanSegClub = 0;
    char cRespuesta[80] = { 0 };
    long lSuAbono = 0L, lAhoraDebe = 0L, lVencido = 0L, lSaldaCon = 0L, lImporteTotal = 0L, lCambio = 0;
    char cTexto[200] = { 0 };
    long lMontoClub = 0L;
    CWnd pWnd;
    CClientDC dc(&pWnd);
    CString sTexto = "";
	CString puntualidad = "";

    char cMensajeAlCliente[100] = { 0 };

    iConvenios = 0;
    termica->iniciarImpresion("BIXOLON SAMSUNG SRP-350plus", false); // se agrega false para que no cheque los sensores

    termica->impresionHorizontal(IMPRESION_HORIZONTAL);

    grabarLog("CDlgCapturarAbono::imprimirReciboTermica::Imprimiendo logo");

    termica->cargarImagen(dc, "C:\\sys\\progs\\logo.bmp", 0, 90);

    iCtasAImp = 0;
    iColMax = MAX_COLUMNAS;
    iColIniEncabezado = COLUM_INICIA_ENCABEZADO;

    termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);
    termica->alinearTexto(IZQUIERDA);

    grabarLog("CDlgCapturarAbono::imprimirReciboTermica::Imprimiendo Detallado");

    iRenglon = 150;
    iRenglon += 10;  termica->ponerTermica(iRenglon, 50, "Detallado");
    iRenglonInicialCtas = iRenglon;

    iRenglon += 25;
    iRenglon += 5;  termica->ponerTermica(iRenglon, 50, "Fecha de Compra:");
    iRenglon += 22; termica->ponerTermica(iRenglon, 50, "No. Factura:");
    iRenglon += 22; termica->ponerTermica(iRenglon, 50, "Usted Debía:");
    iRenglon += 23; termica->ponerTermica(iRenglon, 50, "Abono a Cuenta:");
    iRenglon += 22; termica->ponerTermica(iRenglon, 50, "Abono a Intereses:");
    iRenglon += 22; termica->ponerTermica(iRenglon, 50, "Usted Debe Hoy:");
    iRenglon += 22; termica->ponerTermica(iRenglon, 50, "Atrasado:");
    iRenglon += 23; termica->ponerTermica(iRenglon, 50, "Salda Con:");
    iRenglon += 22; termica->ponerTermica(iRenglon, 50, "Hasta el día");

    /***********  PONER CUENTAS DEL CLIENTE  ************/
    termica->alinearTexto(DERECHA);
    ObtenerVencido();
    if (m_grid.lCliente != 1708)
    {
        for (iContDetalles = 0, iRenglonCta = iRenglonInicialCtas; iContDetalles < TOTAL_DETALLES; iContDetalles++, iRenglonCta += 22)
        {
            lSuAbono = 0L;
            lAhoraDebe = 0L;
            lVencido = 0L;
            lSaldaCon = 0L;
			if(sprintf_s(cTexto, "CDlgCapturarAbono::imprimirReciboTermica --> Imprimiendo detalle[%d]", iContDetalles) < 0){;}
            grabarLog(cTexto);
            imprimirCuenta(iContDetalles, lSuAbono, lAhoraDebe, lVencido, lSaldaCon,
                iCtasAImp, iRenglonCta, bAplicaBonificacion, lMontoClub, iTipoPlanSegClub/*, termica*/);

            if (iContDetalles == 0) iRenglonCta += 7; // Si se imprimieron los nombres de las cuentas se agregan 7 pix al renglon debido a la linea que se imprime.
            if (iContDetalles == 3 || iContDetalles == 7) iRenglonCta += 1; // Se imprime de 22 estos dos renglones para "agrupar" conceptos.
        }
    }
    else
    {
        termica->alinearTexto(DERECHA);
        termica->ponerTermica(iRenglonInicialCtas, iColMax, "TOTALES");
    }
    termica->alinearTexto(IZQUIERDA);
    /****************************************************/

    iRenTmp = iRenglon;
    iRenglon = 0;
    imprimirEncabezadoTermica( /*termica*/);

    iRenglon += 20;
    termica->ponerLinea(iRenglon, 48, iRenglon, iColMax + 5);//liniea de bajo de encabezado
    iRenglon = iRenTmp;

    if (bAplicaBonificacion) iRenglon = iRenglonCta + 2; // Esto por si se puso la leyenda de Bonificacion, se agrega un renglon mas a los detalles. ( +3 para completar los 25 )
    else iRenglon += 25;
    termica->ponerLinea(iRenglon, 48, iRenglon, iColMax + 5);
    iRenglon += 5;
    iRenTmp = iRenglon;

    /*afiliado al seguro club*/
    if (lMontoClub > 0)
    {
        usingx("###,###", cTexto, (double)lMontoClub);
		if(sprintf_s(cRespuesta, "Afiliado con: Plan %s $%s", cPlanSeguroClub, cTexto) < 0){;}
        termica->ponerTermica(iRenTmp, 50, cRespuesta);
    }

    if (bBanderaTienePlan && !bTieneVencidoPlan)
    {
        m_grid.QuickGetText(iColumnaPlan, 12, &sTexto);
        sTexto.Trim();
        usingx("###,###.##", cRespuesta, (double)iSumaAseguradaPlan * 100);
		if(sprintf_s(cTexto, "Afiliado a Protección Salud con: Plan %s $%s", sTexto, cRespuesta) < 0){;}
        termica->ponerTermica(iRenTmp + 20, 50, cTexto);
    }

    /***********  TOTALES  ************/
    if (iAplicoDescuento == 1)
    {
        termica->alinearTexto(IZQUIERDA); termica->ponerTermica(iRenTmp, iColMax - 210, "Descuento:");
        usingx("##,###.##", cRespuesta, (double)imp_totaldescuento * 100);
        termica->alinearTexto(DERECHA); termica->ponerTermica(iRenTmp, iColMax, cRespuesta);
    }
    iRenTmp += 20;

    lImporteTotal = lTotalAPagar - lTotalGlobalServicios;
    termica->alinearTexto(IZQUIERDA); termica->ponerTermica(iRenTmp, iColMax - 210, "Total Abono:");
    usingx("###,###.##", cRespuesta, (double)lImporteTotal);
    termica->alinearTexto(DERECHA); termica->ponerTermica(iRenTmp, iColMax, cRespuesta);

    iRenTmp += 25;
    termica->alinearTexto(IZQUIERDA); termica->ponerTermica(iRenTmp, iColMax - 210, "Pago:");
    usingx("###,###.##", cRespuesta, (double)lPagoCliente);
    termica->alinearTexto(DERECHA); termica->ponerTermica(iRenTmp, iColMax, cRespuesta);

    iRenTmp += 25;
    termica->alinearTexto(IZQUIERDA); termica->ponerTermica(iRenTmp, iColMax - 210, "Cambio:");
    lCambio = lPagoCliente - lImporteTotal;
    usingx("###,###.##", cRespuesta, (double)lCambio);
    termica->alinearTexto(DERECHA); termica->ponerTermica(iRenTmp, iColMax, cRespuesta);
    /*********************************/

    lImporteTotal = lImporteTotal / 100L;

    termica->alinearTexto(IZQUIERDA);

    if (m_grid.lCliente > 0)
    {
        determinaMensajeReciboTermica(cMensajeAlCliente, iFlagNoDebe);
        termica->alinearTexto(CENTRO); termica->ponerTermica(iRenglon, iColMax / 2, cMensajeAlCliente);
    }

    termica->alinearTexto(IZQUIERDA);
    if (iFlagTiendaLocal >= 1)
    {
		if(sprintf_s(cRespuesta, "Sus movimientos estan actualizados al: %s", cFechaMasActualCte) < 0){;}
        iRenglon += 22;
        termica->ponerTermica(iRenglon, 50, cRespuesta);
    }
    else
    {
        if (iAplicoDescuento == 1)
        {
			if(sprintf_s(cRespuesta, "Descuento Plan ponte al día %d%s", prc_descuento, "%") < 0){;}
            iRenglon += 16;
            termica->ponerTermica(iRenglon, 50, cRespuesta);
        }
		puntualidad = cPuntualidad[0];

		if(puntualidad == "Z" && !sLeyenda.IsEmpty()) //Leyenda aclaracion de sdo para ctes Z
		{
			iRenglon += 16;		
			termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 6.5);
			termica->ponerTermica(482,50, (LPTSTR)(LPCTSTR)sLeyenda);
			termica->tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 8);
			termica->alinearTexto(CENTRO); termica->ponerTermica(478, iColMax / 2, "¡Coppel, Mejora tu vida!¡Gracias por tu Abono!");
			termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);
		}
		else if (iFlagTdaConCubrebocas == 1)
		{
			if (iFlagImpresionCuentasPerdidas == 0)
            {
                iRenglon += 22;
                termica->ponerTermica(482, 50, "RECUERDA USAR CUBREBOCAS");
            }
            else if (lMontoClub == 0)
            {
                iRenglon += 16;
                termica->ponerTermica(482, 50, "RECUERDA USAR CUBREBOCAS");
            }
            else
            {
                iRenglon += 16;
                termica->ponerTermica(482, 50, "RECUERDA USAR CUBREBOCAS");
            }
		}else if (iFlagTdaConEstacionamiento == 1)
        {
            if (iFlagImpresionCuentasPerdidas == 0)
            {
                iRenglon += 22;
                termica->ponerTermica(482, 50, "Estacionamiento exclusivo para Clientes");
            }
            else if (lMontoClub == 0)
            {
                iRenglon += 16;
                termica->ponerTermica(482, 50, "Estacionamiento exclusivo para Clientes");
            }
            else
            {
                iRenglon += 16;
                termica->ponerTermica(482, 50, "Estacionamiento exclusivo para Clientes");
            }
        }
    }

    if (iFlagImpresionCuentasPerdidas)
    {
        termica->alinearTexto(CENTRO);
        termica->ponerTermica(iRenglon + 23, iColMax / 2, cMensajeClienteZ);
    }
	//Leyenda de cliente con saldo en aclaracion y puntualidad diferente de Z	
	if(!sLeyenda.IsEmpty() && puntualidad != "Z")
	{
		iRenglon += 16;
		termica->tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 7);
		termica->ponerTermica(iRenglon + 23, iColMax / 2, (LPTSTR)(LPCTSTR)sLeyenda);	
		termica->tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 8);
		termica->alinearTexto(CENTRO); termica->ponerTermica(480, iColMax / 2, "¡Coppel, Mejora tu vida!¡Gracias por tu Abono!");
	}
	else if(sLeyenda.IsEmpty())
	{
		termica->tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 8);
		termica->alinearTexto(CENTRO); termica->ponerTermica(482, iColMax / 2, "¡Coppel, Mejora tu vida!¡Gracias por tu Abono!");
	}		

    grabarLog("CDlgCapturarAbono::imprimirReciboTermica::::grabando imagen en tira");
    sTexto.Format("%s", termica->sInfo);
    _unlink(cArchivoImpresion);

    termica->guardarCopiaVoucher(sTexto + "TERMINARIMPRESION");
    termica->sInfo = "";
    termica->grabarImagenTira(&odbc, &m_grid.cArea, 1, cArchivoImpresion, iDiaActual, iMesActual, iAnioActual, m_grid.iCaja, m_grid.lEmpleado, 1, lNumeroRecibo);
    termica->sInfo = sTexto;

    _unlink(cArchivoImpresion);
}

void CDlgCapturarAbono::terminarReciboTermica()
{
    termica->terminarImpresion();

    // IMPRIME LOS CONVENIOS UNICOS
    if (checarSiTieneConvenioUnico() == 1) //Verifica si hubo convenio unico
    {
        imprimirReciboConvenioUnico();
    }

    // IMPRIME MENSAJE DE PROMOCIÓN *COPPEL ( EN TERMICA )
    verificarPromocionAsteriscoCoppel();

    // IMPRIME MENSAJE DE PROMOCIÓN DIRECTA ( EN TERMICA )
    if (bPromocion)
    {
        imprimeMensajePromocionDirecta();
    }


	if(sprintf_s(cMensaje, " CDlgCapturarAbono::terminarReciboTermica::Termina Impresion del recibo, Cliente = %ld, Recibo = %ld", m_grid.lCliente, lNumeroRecibo) < 0){;}
    grabarLog(cMensaje);
}

void CDlgCapturarAbono::imprimirEncabezadoTermica()
{
    char cNombreMes[5] = { 0 };
    char cRespuesta[80] = { 0 };
    int iControlRenglon = 0;

    grabarLog("CDlgCapturarAbono::imprimirEncabezadoTermica::Imprimiendo Encabezado Recibo");

    termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 9);
    termica->alinearTexto(IZQUIERDA);
    termica->ponerTermica(93, 60, "Coppel S.A. de C.V.");
    termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 7);
    termica->ponerTermica(96, 270, "República Pte. 2855 Recursos Hidráulicos.");
    termica->ponerTermica(116, 110, "Culiacán Rosales, Sinaloa 80105 RFC: COP-920428-Q20");
    termica->ponerTermica(134, 97, "Régimen Fiscal: Régimen General de Ley Personas Morales");

    termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 10);
	if(sprintf_s(cRespuesta, "Recibo de Abono No. %04d %06ld", m_grid.iTienda, lNumeroRecibo) < 0){;}
    termica->alinearTexto(CENTRO);
    termica->ponerTermica(iRenglon, iColIniEncabezado + ((iColMax - iColIniEncabezado) / 2), cRespuesta);
    termica->alinearTexto(IZQUIERDA);

    iRenglon += 32;
    termica->ponerLinea(iRenglon, iColIniEncabezado - 5, iRenglon, iColMax + 5);
    termica->ponerTermica(iRenglon, iColMax + 60, ".");

    grabarLog("CDlgCapturarAbono::imprimirEncabezadoTermica::Imprimiendo datos cliente");

    iRenglon += 3;
    termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 7);
    termica->alinearTexto(IZQUIERDA);
    termica->ponerTermica(iRenglon, iColIniEncabezado, "Nombre:");
    m_nombre.GetWindowText(sNombreCliente);
    sNombreCliente.Trim();
    m_apellidoPaterno.GetWindowText(sApellidoPaterno);
    sApellidoPaterno.Trim();
    m_apellidoMaterno.GetWindowText(sApellidoMaterno);
    sApellidoMaterno.Trim();
	if(sprintf_s(cRespuesta, "%s %s %s", sNombreCliente, sApellidoPaterno, sApellidoMaterno) < 0){;}
    termica->ponerTermica(iRenglon, iColIniEncabezado + 80, cRespuesta);

	if(sprintf_s(cRespuesta, "Cliente: %ld", m_grid.lCliente) < 0){;}
    termica->alinearTexto(DERECHA);
    termica->ponerTermica(iRenglon, iColMax, cRespuesta);

    grabarLog("CDlgCapturarAbono::imprimirEncabezadoTermica::Imprimiendo datos tienda");

    iRenglon += 20;
    termica->alinearTexto(IZQUIERDA);
	if(sprintf_s(cRespuesta, "T-%04d: ", m_grid.iTienda) < 0){;}
    termica->ponerTermica(iRenglon, iColIniEncabezado, cRespuesta);
    termica->ponerTermica(iRenglon, iColIniEncabezado + 80, cNombreSucursal);

    nombreMes(iMesActual, cNombreMes);
	if(sprintf_s(cRespuesta, "Fecha: %02d-%s-%02d", iDiaActual, cNombreMes, iAnioActual) < 0){;}
    termica->alinearTexto(DERECHA);
    termica->ponerTermica(iRenglon, iColMax, cRespuesta);

    iRenglon += 20;

    termica->alinearTexto(IZQUIERDA);
	if(sprintf_s(cRespuesta, "Tel: %s", cTelefonoGnDominio) < 0){;}
    termica->alinearTexto(DERECHA);
    termica->ponerTermica(iRenglon, iColMax, cRespuesta);

    iRenglon += 20;
    termica->alinearTexto(IZQUIERDA);
    termica->ponerTermica(iRenglon, iColIniEncabezado, "Exp en:");
    termica->ponerTermica(iRenglon, iColIniEncabezado + 80, cExpedicion);

	if(sprintf_s(cRespuesta, "Caja: %c%02d", m_grid.cArea, m_grid.iCaja) < 0){;}

    termica->alinearTexto(DERECHA);
    termica->ponerTermica(iRenglon, iColMax, cRespuesta);

    iRenglon += 20;
    termica->alinearTexto(IZQUIERDA);
    termica->ponerTermica(iRenglon, iColIniEncabezado, "Domicilio:");
    termica->tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 5);
    iControlRenglon = iRenglon;
    termica->ponerParrafoTermica(cDomicilioCompleto, iRenglon, iColIniEncabezado + 80, iColMax);
    if (iControlRenglon == iRenglon)
        iRenglon += 20;
    termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);
    grabarLog("CDlgCapturarAbono::imprimirEncabezadoTermica::Termina Impresion Encabezado Recibo");
}

void CDlgCapturarAbono::nombreMes(int iMes, char *cNombreMes)
{
    switch (iMes)
    {
    case 1:
		if(sprintf_s(cNombreMes, 4, "Ene") < 0){;}
        break;
    case 2:
		if(sprintf_s(cNombreMes, 4, "Feb") < 0){;}
        break;
    case 3:
		if(sprintf_s(cNombreMes, 4, "Mar") < 0){;}
        break;
    case 4:
		if(sprintf_s(cNombreMes, 4, "Abr") < 0){;}
        break;
    case 5:
		if(sprintf_s(cNombreMes, 4, "May") < 0){;}
        break;
    case 6:
		if(sprintf_s(cNombreMes, 4, "Jun") < 0){;}
        break;
    case 7:
		if(sprintf_s(cNombreMes, 4, "Jul") < 0){;}
        break;
    case 8:
		if(sprintf_s(cNombreMes, 4, "Ago") < 0){;}
        break;
    case 9:
		if(sprintf_s(cNombreMes, 4, "Sep") < 0){;}
        break;
    case 10:
		if(sprintf_s(cNombreMes, 4, "Oct") < 0){;}
        break;
    case 11:
		if(sprintf_s(cNombreMes, 4, "Nov") < 0){;}
        break;
    case 12:
		if(sprintf_s(cNombreMes, 4, "Dic") < 0){;}
        break;
    default: break;
    }
}

void CDlgCapturarAbono::determinaMensajeReciboTermica(char *cMensaje, int iFlagNoDebe)
{
    int i = 0, iFlagVencido = 0;
    long lTotalVencido = 0L, lVencido = 0L, lVencidoGrid = 0L, lSuPagoGrid = 0;
    char cRespuesta[80] = { 0 };
    CString sTexto;
    SecureZeroMemory(cMensajeClienteZ, sizeof(cMensajeClienteZ));

    grabarLog("determinaMensajeRecibo::Obteniendo Mensaje Recibo");

    SecureZeroMemory(cMensaje, 100);
    for (i = 0; i < iTotalCuentas; i++)
    {
        m_grid.QuickGetText(i, 15, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lVencidoGrid = strtol(cRespuesta, NULL, 10);

        m_grid.QuickGetText(i, 21, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lSuPagoGrid = strtol(cRespuesta, NULL, 10);

        if (iCandidatoAprobado == 1 && iAplicoDescuento == 1)
        {
            m_grid.QuickGetText(i, 32, &sTexto);
            sTexto.Trim(); sTexto.Remove(','); sTexto.Remove('.');
			if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
            lSuPagoGrid += strtol(cRespuesta, NULL, 10);
        }

        if (lVencidoGrid > 0)
        {
            if (lSuPagoGrid > 0)
            {
                lVencido = lVencidoGrid - lSuPagoGrid;
                if (lVencido < 0) lVencido = 0;
                if (lVencido > 0) iFlagVencido = 1;
            }
            else
            {
                lVencido = lVencidoGrid;
                iFlagVencido = 1;
            }
            lTotalVencido += lVencido;
        }
    }

    if (m_grid.lCliente > 0L)
    {
        switch (cPuntualidad[0])
        {
        case 'A':
            if (iFlagVencido == 1)
            {
				if(sprintf_s(cMensaje, 100, "Continúe Pagando Puntualmente. No deje Pagos Vencidos") < 0){;}
            }
            else
            {
                if (iFlagNoDebe == 0)
                {
					if(sprintf_s(cMensaje, 100, "Sea Puntual y Aproveche su Crédito") < 0){;}
                }
                else
                {
					if(sprintf_s(cMensaje, 100, "Gracias por Abonar Puntualmente") < 0){;}
                }
            }
            break;
        case 'B':
            if (iFlagVencido == 1)
            {
				if(sprintf_s(cMensaje, 100, "Pagando Oportunamente se evitan Intereses Adicionales") < 0){;}
            }
            else
            {
				if(sprintf_s(cMensaje, 100, "Continúe Pagando Puntualmente") < 0){;}
            }
            break;
        case 'C':
            if (iFlagVencido == 1)
            {
                usingx("###,###,###", cRespuesta, lTotalVencido);
				if(sprintf_s(cMensaje, 100, "Evite Intereses Adicionales, Pague $%s Vencidos", cRespuesta) < 0){;}
            }
            else
            {
				if(sprintf_s(cMensaje, 100, "Continúe Pagando Puntualmente") < 0){;}
            }
            break;
        case 'D':
            if (iFlagVencido == 1)
            {
                usingx("###,###,###", cRespuesta, lTotalVencido);
				if(sprintf_s(cMensaje, 100, "Evite Intereses Adicionales Pague $%s Vencidos", cRespuesta) < 0){;}
            }
            else
            {
				if(sprintf_s(cMensaje, 100, "Pagando Oportunamente se evitan Intereses Adicionales") < 0){;}
            }
            break;
        case 'N':
            if (iFlagVencido != 1)
            {
				if(sprintf_s(cMensaje, 100, "Continúe Pagando Puntualmente. No deje Pagos Vencidos") < 0){;}
            }
            else
            {
				if(sprintf_s(cMensaje, 100, "Pagando Oportunamente se evitan Intereses Adicionales") < 0){;}
            }
            break;
        case 'Z':
            if (iFlagVencido == 1)
            {
                usingx("###,###,###", cRespuesta, lTotalVencido);
				if(sprintf_s(cMensaje, 100, "Evite Intereses Adicionales, Pague $%s Vencidos", cRespuesta) < 0){;}
            }
            else
            {
				if(sprintf_s(cMensaje, 100, "Pagando Oportunamente se evitan Intereses Adicionales") < 0){;}
            }
            if (iFlagImpresionCuentasPerdidas == 1)
            {
				if(sprintf_s(cMensajeClienteZ, "Saldo sujeto a cambios de acuerdo con el aumento al salario mínimo del país.") < 0){;}
            }
            break;
        default:
            if (iFlagVencido == 1)
            {
				if(sprintf_s(cMensaje, 100, "Pagando Oportunamente se evitan Intereses Adicionales") < 0){;}
            }
            else
            {
				if(sprintf_s(cMensaje, 100, "Continúe Pagando Puntualmente. No deje Pagos Vencidos") < 0){;}
            }
            break;
        }
    }

    grabarLog("determinaMensajeRecibo::Fin");
}

/*--------------------------------------------------------------------
Fecha: 16-06-2021
Autor: Luis Fernando Sierra Lizarraga
Peticion: 30165
Descripción: Se modifica para cambiar la forma en que se muestra la fecha en la que se va relizar el pago de los convenios.
--------------------------------------------------------------------*/
void CDlgCapturarAbono::imprimirCuenta(int iTipoDetalle, long &lSuAbono, long &lAhoraDebe, long &lVencido, long &lSaldaCon, int &iCtasAImp, int &iRen, bool &bAplicaBonificacion, long &lMontoSeguroClub, int &iTipoPlanSegClub)
{
    long lUstedDebia = 0L, lAbonoTotal = 0L, lInteresTotal = 0L, lDebeTotal = 0L, lVencidoTotal = 0L, lSaldaConTotal = 0L, lMontoClub = 0L;
    int iContCtas = 0, iCuentasImpresas = 0, iNumeroSeguros = 0, iNumeroMeses = 0, iContMuebles = 0;
    char cNombreMes[5] = { 0 }, cTxt[80] = { 0 }, cFecha[20] = { 0 }, cRespuestaAux[20] = { 0 }, cRespuesta[20] = { 0 }, cDescripcion[15] = { 0 }, cDescripcionAux[15] = { 0 };
    char cFechaSalda[10] = { 0 }, cFechaPago[10] = { 0 };
    long lDebe = 0, lVencidoNuevo = 0, lSaldaConNuevo = 0L, lBaseX = 0L, lAbonoCte = 0L, lAbonoInteresCte = 0L, lInteresAdicionalCte = 0L, lSaldoDespues = 0L;
    long lSuPagoX = 0L, lSaldoX = 0L, lImporteConvenioX = 0L, lInteresesAdicionalesX = 0L, lInteresMesUnoX = 0L,
        lSaldaConX = 0L, lVencidoX = 0L, lMinimoX = 0L, lAtrasadoX = 0L, lBonificacionX = 0L, lSaldaConAntX = 0L, lAbonoCuenta = 0L, lAbonoInteres = 0L, lSaldaConNuevoRopa = 0L;
    int iEsSeguro = 0, iMesVenta = 0, iAnioVenta = 0, iDiaVenta = 0, iDiaV = 0, iMesV = 0, iAnioV = 0, iPagado = 0, iDiaS = 0, iMesS = 0, iAnioS = 0, iMesesVencidos = 0;
    CString sTexto = "", sDato = "";
    int iMesRopa = 0, iAnioRopa = 0, iFlagConyugalX = 0, iTipoCtaBuscar = 0, iFlagCapturoConvenioX = 0, iDias = 0, iPlazoConvenioX = 0, iFlagSaldaConRopa = 0, iDescuento = 0;
    __int64 lFacturaX = 0;
    char cMensaje[100] = { 0 };
    int iCol = 340;

    lDebe = 0;
    lVencidoNuevo = 0;

    //sprintf_s(cMensaje, "imprimirCuenta::Imprimiendo cuenta");
    //grabarLog(cMensaje);

    for (iContCtas = iCtasAImp; iContCtas < iTotalCuentas; iContCtas++)
    {
        m_grid.QuickGetText(iContCtas, 2, &sTexto);
        sTexto.Trim();
		if(sprintf_s(cTxt, "%s", sTexto) < 0){;}
        iMesVenta = obtenerMes(cTxt);
        iAnioVenta = ano_2000_4dig((int)valor_campo(&cTxt[5], 2), iAnioActual);
        iDiaVenta = valor_campo(&cTxt[0], 2);

        SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
        m_grid.QuickGetText(iContCtas, 21, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lSuPagoX = strtol(cRespuesta, NULL, 10);
        if (iCandidatoAprobado == 1 && iAplicoDescuento == 1)
        {
            m_grid.QuickGetText(iContCtas, 32, &sTexto);
            sTexto.Trim(); sTexto.Remove(','); sTexto.Remove('.');
			if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
            lSuPagoX += strtol(cRespuesta, NULL, 10);
        }


        m_grid.QuickGetText(iContCtas, 1, &sTexto);
        lFacturaX = _atoi64(sTexto);

        SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
        m_grid.QuickGetText(iContCtas, 12, &sTexto);
        sTexto.Remove('.');
        sTexto.Remove(',');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lSaldoX = strtol(cRespuesta, NULL, 10);

        SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
        m_grid.QuickGetText(iContCtas, 10, &sTexto);
        sTexto.Remove('.');
        sTexto.Remove(',');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lImporteConvenioX = strtol(cRespuesta, NULL, 10);

        m_grid.QuickGetText(iContCtas, -1, &sTexto);
        sTexto.Trim();
		if(sprintf_s(cTxt, "%s", sTexto) < 0){;}

        m_grid.QuickGetText(iContCtas, -1, &sTexto);
        sTexto.Trim();
		if(sprintf_s(cDescripcion, "%s", sTexto) < 0){;}

        SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
        m_grid.QuickGetText(iContCtas, 13, &sTexto);
        sTexto.Trim();
        sTexto.Remove('.');
        sTexto.Remove(',');
        lInteresesAdicionalesX = strtol(sTexto, NULL, 10);

        SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
        m_grid.QuickGetText(iContCtas, 18, &sTexto);
        sTexto.Trim();
        sTexto.Remove(',');
        sTexto.Remove('.');
        lSaldaConX = strtol(sTexto, NULL, 10);

        SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
        m_grid.QuickGetText(iContCtas, 15, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lVencidoX = strtol(cRespuesta, NULL, 10);

		SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
        m_grid.QuickGetText(iContCtas, 15, &sTexto);
        sTexto.Remove('.');
        sTexto.Remove(',');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lAtrasadoX = strtol(cRespuesta, NULL, 10);

		SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
        m_grid.QuickGetText(iContCtas, 16, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lMinimoX = strtol(cRespuesta, NULL, 10);

        SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
        m_grid.QuickGetText(iContCtas, 19, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lBonificacionX = strtol(cRespuesta, NULL, 10);

        SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
        m_grid.QuickGetText(iContCtas, 26, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lSaldaConAntX = strtol(cRespuesta, NULL, 10);

        SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
        m_grid.QuickGetText(iContCtas, 35, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lInteresMesUnoX = strtol(cRespuesta, NULL, 10);

        m_grid.QuickGetText(iContCtas, 14, &sTexto);
        sTexto.Trim();
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lBaseX = strtol(cRespuesta, NULL, 10);

        m_grid.QuickGetText(iContCtas, 23, &sTexto);
        iNumeroMeses = strtol(sTexto, NULL, 10);

        m_grid.QuickGetText(iContCtas, 32, &sTexto);
        sTexto.Trim(); sTexto.Remove(','); sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        iDescuento = strtol(cRespuesta, NULL, 10);

        SecureZeroMemory(cMensajeClienteZ, sizeof(cMensajeClienteZ));

        if (lVencidoX > 0 && lBaseX > 0)
        {
            iMesesVencidos = (lVencidoX - lInteresesAdicionalesX) / lBaseX;
            //Si es el primer mes vencido se le quita le intere primer mes al interes adicional
            if (iMesesVencidos == 1)
            {
                lInteresesAdicionalesX = lInteresesAdicionalesX - lInteresMesUnoX;
            }
            else if (iMesesVencidos > 1)
            {
                lInteresMesUnoX = 0;
            }
        }

        if (lInteresesAdicionalesX == 0 && lInteresMesUnoX > 0)
        {
            lSaldoX = lSaldoX - lInteresMesUnoX;
            lVencidoX = lVencidoX - lInteresMesUnoX;
        }

        int lVencidoFinalTicket = 0;
        if (lSuPagoX >= lVencidoX)
        {
            lVencidoFinalTicket = 0;
        }
        else
        {
            lVencidoFinalTicket = lVencidoX - lSuPagoX;
        }

        if (lVencidoFinalTicket <= lImporteConvenioX)//En Caso que el vencido sea menor al conv, se topara al vencido de la cuenta..
        {
            lImporteConvenioX = lVencidoFinalTicket;
        }

        if (memcmp(cTxt, "SEGURO", 6) == 0)
            iEsSeguro = 1;
        else
            iEsSeguro = 0;

        // Si la factura es mayor a 999999 o < 0 hay error, se lo brinca...
        //if ((lFacturaX > 999999 && memcmp(cDescripcion, "AUTO PROT.", 10) != 0 && memcmp(cDescripcion, "P.FAMILIAR", 10) != 0) || lFacturaX < 0)
		//if ((memcmp(cDescripcion, "AUTO PROT.", 10) != 0 && memcmp(cDescripcion, "P.FAMILIAR", 10) != 0) || lFacturaX < 0)
		//if ((lFacturaX > 9999999 && memcmp(cDescripcion, "AUTO PROT.", 10) != 0 && memcmp(cDescripcion, "P.FAMILIAR", 10) != 0) || lFacturaX < 0)
		  if ( lFacturaX < 0)
            continue;

        if (memcmp(cDescripcion, "PLAN MOVISTAR", 13) == 0)
            continue;
        if (lSaldoX == 0 && lSuPagoX == 0 && lImporteConvenioX == 0)
            continue;

        if (lSuPagoX > 0 && memcmp(cDescripcion, "T.AIRE", 6) == 0)
            iFlagAbonoTA = 1;

        iFlagSaldaConRopa = 0;
        iFlagCapturoConvenioX = 0;
        if (lVencidoFinalTicket > 0)
        {
            m_grid.QuickGetText(iContCtas, 28, &sTexto);
            iFlagCapturoConvenioX = strtol(sTexto, NULL, 10);
        }
        switch (iTipoDetalle)
        {
        case 0: // NOMBRE DE LA CUENTA
            //sprintf_s(cMensaje, "imprimirCuenta::nombre de la cuenta");
            //grabarLog(cMensaje);
            if (lFacturaX == 0 || memcmp(cDescripcion, "T.AIRE", 6) == 0 || memcmp(cDescripcion, "COMP ADC", 8) == 0)
            {
                if (memcmp(cDescripcion, "T.AIRE", 6) == 0)
                {
                    termica->ponerTermica(iRen, iCol, "T.AIRE");
                }
                else if (memcmp(cDescripcion, "COMP ADC", 8) == 0)
                {
                    termica->ponerTermica(iRen, iCol, "COMP ADC");
                }
                else if (memcmp(cDescripcion, "P.FAMILIAR", 10) == 0)
                {
                    if(memcpy_s(cDescripcionAux, sizeof(cDescripcionAux), &cDescripcion[0], 8) < 0){;}
                    cDescripcionAux[8] = 0;
                    termica->ponerTermica(iRen, iCol, cDescripcionAux);
                }
				else if (memcmp(cDescripcion, "SEG. MOTOS", 10) == 0){
					termica->ponerTermica(iRen, iCol, "SEG.MOT");
				}
				else if (memcmp(cDescripcion, "P. CELULAR", 10) == 0){
					termica->ponerTermica(iRen, iCol, "P. CELULAR");
				}
                else
                {
                    termica->ponerTermica(iRen, iCol, "ROPA");
                }
            }
            else
            {
                if (iEsSeguro != 1)
                {
                    if (memcmp(cDescripcion, "CP COMP ADC", 11) == 0)
                    {
                        termica->ponerTermica(iRen, iCol, "CP ADC");
                    }
                    else
                    {
						if(memcpy_s(cDescripcionAux, sizeof(cDescripcionAux), &cDescripcion[0], 8) < 0){;}
                        cDescripcionAux[8] = 0;
                        termica->ponerTermica(iRen, iCol, cDescripcionAux);
                    }
                }
                else
                {
					if(memcpy_s(cDescripcionAux, sizeof(cDescripcionAux), &cDescripcion[0], 7) < 0){;}
                    cDescripcionAux[7] = 0;
                    termica->ponerTermica(iRen, iCol, cDescripcionAux);
                }
            }

            iCuentasImpresas++;
            iCol += LONGITUD_COLUMNA_CTAS;

            if (iFlagCapturoConvenioX == 1)
            {
                iCuentasImpresas++;
                iConvenios++;
                iCol += LONGITUD_COLUMNA_CTAS + 5;
            }
            break;
        case 1: // FECHA DE COMPRA
            //sprintf_s(cMensaje, "imprimirCuenta:: fecha de la compra");
            //grabarLog(cMensaje);
            if (iEsSeguro != 1 && strncmp(cDescripcion, "P.FAMILIAR", 10) != 0 && memcmp(cDescripcion, "AUTO PROT.", 10) != 0 && memcmp(cDescripcion, "P.SALUD", 7) != 0)
            {
                if (lFacturaX != 0)
                {
                    nombreMes(iMesVenta, cNombreMes);
                    sTexto.Format("%d", iAnioVenta);
					if(sprintf_s(cRespuesta, "%02d%s%s", iDiaVenta, cNombreMes, sTexto.Right(2)) < 0){;}
                    if (iAnioVenta > 99)
                    {
						if(memcpy_s(cRespuestaAux, sizeof(cRespuestaAux), &cRespuesta[0], 5) < 0){;}
						if(memcpy_s(&cRespuestaAux[5], sizeof(cRespuestaAux), &cRespuesta[5], 2) < 0){;}
                        cRespuestaAux[7] = 0;

						if(memcpy_s(&cRespuesta[0], sizeof(cRespuesta), &cRespuestaAux[0], 7) < 0){;}
                        cRespuesta[7] = 0;
                    }
                    if (iFlagDespliegaDatosZ == 0)
                    {
                        termica->ponerTermica(iRen, iCol, cRespuesta);
                    }
                }
            }

            iCol += LONGITUD_COLUMNA_CTAS;

            if (iFlagCapturoConvenioX == 1)
            {
                iCol += 5;
                termica->ponerTermica(iRen, iCol, "CONVENIO");
                iCol += LONGITUD_COLUMNA_CTAS;
            }
            break;
        case 2: //NUMERO DE FACTURA
            //sprintf_s(cMensaje, "imprimirCuenta::numero de factura");
            //grabarLog(cMensaje);
            if (lFacturaX != 0)
            {
                if (memcmp(cDescripcion, "AUTO PROT.", 10) != 0)
                {
					if(sprintf_s(cRespuesta, "%6I64d", lFacturaX) < 0){;}
                    termica->ponerTermica(iRen, iCol, cRespuesta);
                }
                else
                {
                    m_grid.QuickGetText(iContCtas, 36, &sTexto);

                    if (strtol(sTexto, NULL, 10) == 0)
                    {
						if(sprintf_s(cRespuesta, "%I64d", lFacturaX) < 0){;}
                        termica->ponerTermica(iRen, iCol, cRespuesta);
                    }
                    else
                    {
						if(sprintf_s(cRespuesta, "%I64d", buscarFolionuevo(lFacturaX, m_grid.lCliente, lNumeroRecibo)) < 0){;}
                        termica->ponerTermica(iRen, iCol, cRespuesta);
                    }
                }
            }

            iCol += LONGITUD_COLUMNA_CTAS;

            if (iFlagCapturoConvenioX == 1)
            {
                iCol += 5;
                if (lFacturaX != 0)
                {
					if(sprintf_s(cRespuesta, "Fact. %6I64d", lFacturaX) < 0){;}
                    termica->ponerTermica(iRen, iCol, cRespuesta);
                }
                iCol += LONGITUD_COLUMNA_CTAS;
            }
            break;
        case 3: //USTED DEBÍA
                //sprintf_s(cMensaje, "imprimirCuenta::Usted debia");
                //grabarLog(cMensaje);
            if (strncmp(cDescripcion, "P.FAMILIAR", 10) != 0 && iEsSeguro != 1 && memcmp(cDescripcion, "AUTO PROT.", 10) != 0 && memcmp(cDescripcion, "P.SALUD", 7) != 0)
            {
                if (lSaldoX < 0)
                    usingx("###,###", cRespuesta, (double)0);
                else
                    usingx("###,###", cRespuesta, (double)lSaldoX);

                termica->ponerTermica(iRen, iCol, cRespuesta);

                if (lSaldoX > 0) lUstedDebia += lSaldoX;
            }
            else if (memcmp(cDescripcion, "AUTO PROT.", 10) != 0)
            {
                //Cantidad de Seguros
                if (strncmp(cDescripcion, "P.FAMILIAR", 10) == 0)
                {
                    m_grid.QuickGetText(iContCtas, 22, &sTexto);
                    iTipoPlanSegClub = strtol(sTexto, NULL, 10);
                }
                else if (strncmp(cDescripcion, "P.SALUD", 7) == 0)
                {
                    // no hace nada
                }
                else
                {
                    m_grid.QuickGetText(iContCtas, 22, &sTexto);
					if(sprintf_s(cRespuesta, "Segs %s", sTexto) < 0){;}
                    termica->ponerTermica(iRen, iCol, cRespuesta);
                }
			}
			else if (strncmp(cDescripcion, "SEG. MOTOS", 10) == 0){
				usingx("###,###", cRespuesta, lSaldoX);
				termica->ponerTermica(iRen, iCol, cRespuesta);
			}

			else if (strncmp(cDescripcion, "P. CELULAR", 10) == 0){
				usingx("###,###", cRespuesta, lSaldoX);
				termica->ponerTermica(iRen, iCol, cRespuesta);
			}
            

            iCol += LONGITUD_COLUMNA_CTAS;

            if (iFlagCapturoConvenioX == 1)
            {
                iCol += 5;
                termica->ponerTermica(iRen, iCol, "Usted");
                iCol += LONGITUD_COLUMNA_CTAS;
            }
            break;
        case 4: //ABONO A CUENTA
            //sprintf_s(cMensaje, "imprimirCuenta::abono a cuenta");
            //grabarLog(cMensaje);
            if (iEsSeguro != 1)
            {
                if ((lSuPagoX > 0 && lSaldoX > 0 && lInteresesAdicionalesX > 0)
                    || (lSuPagoX > 0 && lInteresesAdicionalesX > 0))
                {
                    lAbonoCuenta = 0;
                    lAbonoInteres = 0;
                    calculaAbonoInteres(lInteresesAdicionalesX, lSuPagoX, lAbonoCuenta, lAbonoInteres);
                    usingx("###,###", cRespuesta, (double)lAbonoCuenta);
                    lAbonoTotal += lAbonoCuenta;
                }
                else
                {
                    usingx("###,###", cRespuesta, (double)lSuPagoX);
                    lSuAbono += lSuPagoX;
                    lAbonoTotal += lSuPagoX;
                }
            }
            else
            {
                usingx("###,###", cRespuesta, (double)lSuPagoX);
                lSuAbono += lSuPagoX;
                lAbonoTotal += lSuPagoX;
            }
            termica->ponerTermica(iRen, iCol, cRespuesta);

            iCol += LONGITUD_COLUMNA_CTAS;

            if (iFlagCapturoConvenioX == 1)
            {
                iCol += 5;
                termica->ponerTermica(iRen, iCol, "promete");
                iCol += LONGITUD_COLUMNA_CTAS;
            }
            break;
        case 5: //ABONO A INTERESES
            //sprintf_s(cMensaje, "imprimirCuenta::abono a intereses");
            //grabarLog(cMensaje);
            if (iEsSeguro != 1 && memcmp(cDescripcion, "AUTO PROT.", 10) != 0)
            {
                if (strncmp(cDescripcion, "P.FAMILIAR", 10) == 0)
                {
                    if (iSegurosAdicionales > 0)
						if(sprintf_s(cRespuesta, "Adics %d", iSegurosAdicionales) < 0){;}
                    else
                        SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
                }
                else if (strncmp(cDescripcion, "P.SALUD", 7) == 0)
                {
                    if (iPlanAdicionales > 0)
						if(sprintf_s(cRespuesta, "Adics %d", iPlanAdicionales) < 0){;}
                    else
                        SecureZeroMemory(cRespuesta, sizeof(cRespuesta));
                }
                else
                {
                    if ((lSuPagoX > 0 && lSaldoX > 0 && lInteresesAdicionalesX > 0)
                        || (lSuPagoX > 0 && lInteresesAdicionalesX > 0)
                        || (lSuPagoX > 0 && lInteresMesUnoX > 0))
                    {
                        lAbonoCuenta = 0;
                        lAbonoInteres = 0;
                        calculaAbonoInteres(lInteresesAdicionalesX, lSuPagoX, lAbonoCuenta, lAbonoInteres);

                        if (lInteresesAdicionalesX == 0 && lInteresMesUnoX > 0 && lSuPagoX >= (lVencidoX - lInteresMesUnoX))
                        {
                            usingx(" ### B", cRespuesta, (double)lInteresMesUnoX);
                        }
                        else
                        {
                            if (iAplicoDescuento == 1)
                            {
                                lAbonoInteres -= iDescuento;
                                usingx("###,###", cRespuesta, (double)lAbonoInteres);
                                lAbonoInteres += iDescuento;
                            }
                            else
                            {
                                usingx("###,###", cRespuesta, (double)lAbonoInteres);
                            }
                            lInteresTotal += lAbonoInteres;

                        }
                    }
                    else
                    {
                        usingx("###,###", cRespuesta, (double)0);
                    }
                }
            }
            else if (memcmp(cDescripcion, "AUTO PROT.", 10) == 0)
            {
                usingx("###,###", cRespuesta, (double)lSuPagoX);
            }

            termica->ponerTermica(iRen, iCol, cRespuesta);

            iCol += LONGITUD_COLUMNA_CTAS;
            if (iFlagCapturoConvenioX == 1)
            {
                iCol += 5;
                termica->ponerTermica(iRen, iCol, "pagar");
                iCol += LONGITUD_COLUMNA_CTAS;
            }
            break;
        case 6: //USTED DEBE HOY
            //sprintf_s(cMensaje, "imprimirCuenta::Usted debe hoy");
            //grabarLog(cMensaje);
            if (strncmp(cDescripcion, "P.FAMILIAR", 10) == 0)
            {
                m_grid.QuickGetText(iContCtas, 22, &sTexto);
                iNumeroSeguros = strtol(sTexto, NULL, 10);

                consultarMontoSeguroClub(lMontoClub, (short)iNumeroSeguros, 1, 0);

                lMontoSeguroClub = lMontoClub;
            }
            else if (memcmp(cDescripcion, "AUTO PROT.", 10) == 0)
            {
                m_grid.QuickGetText(iContCtas, 22, &sTexto);
                iNumeroSeguros = strtol(sTexto, NULL, 10);

                if (iNumeroSeguros == 2 || iNumeroSeguros == 5)
                {
                    termica->ponerTermica(iRen, iCol, "B. Plus");
                }
                else
                {
                    termica->ponerTermica(iRen, iCol, "Básico");
                }
			}
			else if (strncmp(cDescripcion, "SEG. MOTOS", 10) == 0){
				lDebe = lSaldoX - lSuPagoX;
				usingx("###,###", cRespuesta, lDebe);
				termica->ponerTermica(iRen, iCol, cRespuesta);
			}
			else if (strncmp(cDescripcion, "P. CELULAR", 10) == 0){
				lDebe = lSaldoX - lSuPagoX;
				usingx("###,###", cRespuesta, lDebe);
				termica->ponerTermica(iRen, iCol, cRespuesta);
            }
            else if (memcmp(cDescripcion, "P.SALUD", 7) == 0)
            {
				if(sprintf_s(cRespuesta, "") < 0){;}
            }
            else if (iEsSeguro == 1)
            {
                iFlagConyugalX = obtenerClaveConyugalCrSegurosAf(m_grid.lCliente);

                m_grid.QuickGetText(iContCtas, 22, &sTexto);
                iNumeroSeguros = strtol(sTexto, NULL, 10);

                lMontoClub = obtenerMontoSeguro();
                lMontoClub = lMontoClub * iNumeroSeguros;

                if (iFlagConyugalX == 1)
                {
                    if (iNumeroMeses > 5)
                        lMontoClub = long(lMontoClub*1.75);
                    else
                        lMontoClub = long(lMontoClub*1.50);
                }
                else
                {
                    if (iNumeroMeses > 5)
                        lMontoClub = long(lMontoClub*1.50);
                }

                usingx("###,###", cRespuesta, (double)lMontoClub);
            }
            else
            {
                lDebe = (lSaldoX - lSuPagoX);
                if (lDebe < 0)
                {
                    if ((lDebe * -1) > lSuPagoX)
                        lDebe = lSuPagoX * -1;
                }

                if (lDebe > 0 && lSuPagoX < lSaldaConX)
                {
                    iPagado = 1;
                    usingx("###,###", cRespuesta, (double)lDebe);
                    lDebeTotal += lDebe;
                }
                else
                {
                    iPagado = 0;
                    usingx("###,###", cRespuesta, (double)0);
                }
            }

            termica->ponerTermica(iRen, iCol, cRespuesta);
            if (lDebe > 0) lAhoraDebe += lDebe;

            iCol += LONGITUD_COLUMNA_CTAS;

            if (iFlagCapturoConvenioX == 1)
            {
                usingx("###,###", cRespuestaAux, (double)lImporteConvenioX);
				if(sprintf_s(cRespuesta, "$ %s", cRespuestaAux) <0){;}
                iCol += 5;
                termica->ponerTermica(iRen, iCol, cRespuesta);
                iCol += LONGITUD_COLUMNA_CTAS;
            }
            break;
        case 7: //ATRASADO
            //sprintf_s(cMensaje, "imprimirCuenta:: atrasado");
            //grabarLog(cMensaje);
            if (strncmp(cDescripcion, "P.FAMILIAR", 10) == 0 || iEsSeguro == 1)
            {
                termica->ponerTermica(iRen, iCol, "Venc.");
            }
            else if (strncmp(cDescripcion, "P.SALUD", 7) == 0)
            {
                termica->ponerTermica(iRen, iCol, "Venc.");
            }
			else if (strncmp(cDescripcion, "SEG. MOTOS", 10) == 0){
				if(lSuPagoX == 0) {
					usingx("###,###", cRespuesta, (double)lAtrasadoX);
					termica->ponerTermica(iRen, iCol, cRespuesta);
					lVencidoTotal = lVencidoTotal + lAtrasadoX;
				} else {
					usingx("###,###", cRespuesta, (double) 0);
					termica->ponerTermica(iRen, iCol, cRespuesta);
				}
			}
			else if (strncmp(cDescripcion, "P. CELULAR", 10) == 0){
				if(lSuPagoX == 0) {
					usingx("###,###", cRespuesta, (double)lAtrasadoX);
					termica->ponerTermica(iRen, iCol, cRespuesta);
					lVencidoTotal = lVencidoTotal + lAtrasadoX;
				} else {
					usingx("###,###", cRespuesta, (double) 0);
					termica->ponerTermica(iRen, iCol, cRespuesta);
				}
			}
            else if (memcmp(cDescripcion, "AUTO PROT.", 10) != 0)
            {
                lVencidoNuevo = lVencidoX - lSuPagoX;

                if (lVencidoNuevo < 0) lVencidoNuevo = 0;

                usingx("###,###", cRespuesta, (double)lVencidoNuevo);
                termica->ponerTermica(iRen, iCol, cRespuesta);

                lVencido += lVencidoNuevo;
                lVencidoTotal += lVencidoNuevo;
            }

            iCol += LONGITUD_COLUMNA_CTAS;
            if (iFlagCapturoConvenioX == 1)
            {
                iCol += 5;
                termica->ponerTermica(iRen, iCol, "para el");
                iCol += LONGITUD_COLUMNA_CTAS;
            }
            break;
        case 8: //SALDA CON
            //sprintf_s(cMensaje, "imprimirCuenta::salda con");
            //grabarLog(cMensaje);

            m_grid.QuickGetText(iContCtas, 2, &sTexto);
            sTexto.Trim();
			if(sprintf_s(cConceptoCta, "%s", sTexto) < 0){;}

            if (strncmp(cDescripcion, "P.FAMILIAR", 10) == 0 || iEsSeguro == 1)
            {
                m_grid.QuickGetText(iContCtas, 25, &sTexto);
                sTexto.Trim();
				if(sprintf_s(cRespuesta, "%s", sTexto.Mid(2, 2)) < 0){;}
                nombreMes(strtol(cRespuesta, NULL, 10), cNombreMes);

				if(sprintf_s(cRespuesta, "%02s-%s-%02s", sTexto.Left(2), cNombreMes, sTexto.Right(2)) < 0){;}
                termica->ponerTermica(iRen, iCol, cRespuesta);
            }
            else if (strncmp(cDescripcion, "P.SALUD", 7) == 0)
            {
                m_grid.QuickGetText(iContCtas, 25, &sTexto);
                sTexto.Trim();
				if(sprintf_s(cRespuesta, "%s", sTexto.Mid(2, 2)) < 0){;}
                nombreMes(strtol(cRespuesta, NULL, 10), cNombreMes);

				if(sprintf_s(cRespuesta, "%02s-%s-%02s", sTexto.Left(2), cNombreMes, sTexto.Right(2)) < 0){;}
                termica->ponerTermica(iRen, iCol, cRespuesta);
            }
            else if (memcmp(cDescripcion, "AUTO PROT.", 10) == 0)
            {
                termica->ponerTermica(iRen, iCol, "Vence");
            }
			else if (strncmp(cDescripcion, "SEG. MOTOS", 10) == 0){
				lDebe = lSaldoX - lSuPagoX;
				usingx("###,###", cRespuesta, lDebe);
				termica->ponerTermica(iRen, iCol, cRespuesta);
			}
			else if (strncmp(cDescripcion, "P. CELULAR", 10) == 0){
				lDebe = lSaldoX - lSuPagoX;
				usingx("###,###", cRespuesta, lDebe);
				termica->ponerTermica(iRen, iCol, cRespuesta);
			}
            else
            {
                if (strncmp(cDescripcion, "PRESTAMO", 8) != 0 && iFlagTiendaLocal == 0 && strncmp(cDescripcion, "BANCOPPE", 8) != 0 && VerificarCuentaBcpl2(cDescripcion, "SOLEX") == 0)
                {
                    lSaldaConNuevo = lSaldaConX - lSuPagoX;

                    if (iContCtas > 0 && lSaldaConAntX > 0)
                        lSaldaConNuevo = lSaldaConAntX - lSuPagoX;

                    if (lSaldaConNuevo < 0) lSaldaConNuevo = 0;

                    lDebe = lSaldoX - lSuPagoX;
                    if (lDebe < 0)
                    {
                        if ((lDebe * -1) > lSuPagoX)
                            lDebe = lSuPagoX * -1;
                    }

                    if (lDebe > 0 && lSuPagoX < lSaldaConX)
                        iPagado = 1;
                    else
                        iPagado = 0;

                    if (lFacturaX == 0) // Ropa o Tiempo aire
                    {
                        if (strncmp(cDescripcion, "T.AIRE", 6) == 0)
                        {
                            iTipoCtaBuscar = 4;
                        }
                        else if (strncmp(cDescripcion, "COMP ADC", 8) == 0)
                        {
                            iTipoCtaBuscar = 6;
                        }

                        if (iDiaActual > 20 && iDiaActual <= 31) //RECALCULAR EL IMPORTE DEL SALDACON DE ROPA O TA
                        {
                            iMesRopa = iMesActual + 1;
                            iAnioRopa = iAnioActual;
                            if (iMesRopa > 12)
                            {
                                iAnioRopa++;
                                iMesRopa = 1;
                            }
                        }
                        else
                        {
                            iMesRopa = iMesActual;
                            iAnioRopa = iAnioActual;
                        }

						if(sprintf_s(cFecha, "%04d-%02d-20", iAnioRopa, iMesRopa) < 0){;}//Fecha Corte

						if(sprintf_s(cMensaje, "imprimirCuenta::Consultando cuenta %d", iTipoCtaBuscar) < 0){;}
                        grabarLog(cMensaje);

                        CCuentaWeb *pCuentaRopa = new CCuentaWeb(m_grid.lCliente, cFecha, (short)m_grid.iTienda, (short)iCiudadGnDominio, cIpServidorCartera, cIpServidorCCuentaWeb, (short)iFlagTimeOutCCuenta);
                        pCuentaRopa->leerCliente();

						if(sprintf_s(cMensaje, "imprimirCuenta:: pCuentaRopa->bClienteValido %d", pCuentaRopa->bClienteValido) < 0){;}
                        grabarLog(cMensaje);

                        if (pCuentaRopa->bClienteValido)
                        {
                            switch (iTipoCtaBuscar)
                            {
                            case 4:
                                pCuentaRopa->leerCuenta01("4");
                                break;
                            case 6:
                                pCuentaRopa->leerCuenta01("6");
                                break;
                            default:
                                pCuentaRopa->leerCuenta01("0");
                                break;
                            }

                            for (int k = 0; k < pCuentaRopa->iCuentas; k++)
                            {
                                if (pCuentaRopa->pCuenta[k].iTipoDeCuenta == iTipoCtaBuscar)
                                {
                                    if (pCuentaRopa->pCuenta[k].lSaldo > 0)
                                    {
                                        lSaldaConNuevoRopa = pCuentaRopa->pCuenta[k].lSaldaCon;
                                        miniFecha(cFechaSalda, pCuentaRopa->pCuenta[k].tFechaSaldaCon.dia(), pCuentaRopa->pCuenta[k].tFechaSaldaCon.mes(), pCuentaRopa->pCuenta[k].tFechaSaldaCon.ano());
										if(strncpy_s(cFechaPago, cFechaSalda, 5) < 0){;}
                                        cFechaPago[5] = 0;
                                        iFlagSaldaConRopa = 1;
                                        break;
                                    }
                                }
                            }
                        }

                        delete pCuentaRopa;
                    }

                    if (lFacturaX == 0 && iFlagSaldaConRopa == 1)
                    {
                        if (iPagado == 0)
                        {
                            usingx("###,###", cRespuesta, 0L);
                        }
                        else
                        {
                            usingx("###,###", cRespuesta, lSaldaConNuevoRopa);
                        }
                    }
                    else
                    {
                        if (iPagado == 0)
                        {
                            usingx("###,###", cRespuesta, (double)0);
                        }
                        else
                        {
                            if (lFacturaX != 0 && lFacturaX != 999999 && lFacturaX != 999997)
                            {
                                if (memcmp(cDescripcion, "AUTO PROT.", 10) != 0 && memcmp(cConceptoCta, "CP MUEB", 7) != 0)
                                {
									if(sprintf_s(cRespuesta, "%d", stDatosCertificacion[iContMuebles].iSaldaConCorte) < 0){;}
                                    lSaldaConNuevo = strtol(cRespuesta, NULL, 10);
                                    lSaldaConNuevo = lSaldaConNuevo - lSuPagoX;
                                    usingx("###,###", cRespuesta, (double)lSaldaConNuevo);
                                }
                                else
                                {
                                    usingx("###,###", cRespuesta, (double)lSaldaConNuevo);
                                }
                            }
                            else
                            {
                                usingx("###,###", cRespuesta, (double)lSaldaConNuevo);
                            }
                        }
                    }

                    termica->ponerTermica(iRen, iCol, cRespuesta);

                    if (lFacturaX != 0)
                    {
                        iContMuebles++;
                    }

                    if (iPagado == 1)
                    {
                        lSaldaCon += lSaldaConNuevo;
                        lSaldaConTotal += lSaldaConNuevo;
                    }
                }
            }

            iCol += LONGITUD_COLUMNA_CTAS;
            if (iFlagCapturoConvenioX == 1)
            {
				iCol += 5;
				termica->ponerTermica(iRen, iCol, "día");
				iCol += LONGITUD_COLUMNA_CTAS;
            }
            break;
        case 9: //HASTA EL DIA...
            //sprintf_s(cMensaje, "imprimirCuenta::Hasta el dia..");
            //grabarLog(cMensaje);
            if (iFlagTiendaLocal == 0 && strncmp(cDescripcion, "P.FAMILIAR", 10) != 0 && iEsSeguro != 1 && memcmp(cDescripcion, "AUTO PROT.", 10) != 0 && memcmp(cDescripcion, "P.SALUD", 7) != 0 
				&& strncmp(cDescripcion, "SEG. MOTOS", 10) != 0 && strncmp(cDescripcion, "P. CELULAR", 10) != 0
					)
            {
                if (iEsSeguro != 1)
                {
                    m_grid.QuickGetText(iContCtas, 2, &sTexto);
                    sTexto.Trim();
					if(sprintf_s(cConceptoCta, "%s", sTexto) < 0){;}

                    if (lFacturaX == 0) // Ropa o Tiempo aire
                    {
                        if (iDiaActual > 20 && iDiaActual <= 31)
                        {
                            iMesRopa = iMesActual + 1;
                            iAnioRopa = iAnioActual;
                            if (iMesRopa > 12)
                            {
                                iAnioRopa++;
                                iMesRopa = 1;
                            }
                        }
                        else
                        {
                            iMesRopa = iMesActual;
                            iAnioRopa = iAnioActual;
                        }
                        nombreMes(iMesRopa, cNombreMes);
                        sTexto.Format("%d", iAnioRopa);
						if(sprintf_s(cFechaSalda, "%02d%s%s", 20, cNombreMes, sTexto.Right(2)) < 0){;}
						if(strncpy_s(cFechaPago, cFechaSalda, 5) < 0){;}
                        cFechaPago[5] = 0;
                    }
                    else
                    {
                        iDiaS = iDiaVenta;
                        iMesS = iMesVenta;
                        iAnioS = iAnioVenta;

                        if (memcmp(cConceptoCta, "CP ROPA", 7) == 0 || memcmp(cConceptoCta, "CP MUEB", 7) == 0 || memcmp(cConceptoCta, "CP T.AIRE", 9) == 0 || memcmp(cConceptoCta, "CP BANC", 7) == 0 || memcmp(cConceptoCta, "CP PRES", 7) == 0 || memcmp(cConceptoCta, "CP COMP ADC", 11) == 0)
                        {
                            iAnioS = iAnioActual;
                            iMesS = iMesActual;
                            iDiaS = 1;

                            if (iDiaActual > iDiaS)
                            {
                                iMesS = iMesS + 1;
                            }

                            if (iMesS > 12)
                            {
                                iMesS = 1;
                                iAnioS = iAnioS + 1;
                            }
                        }
                        else
                        {
                            if (lFacturaX != 0 && lFacturaX != 999999 && lFacturaX != 999997)
                            {
                                if (memcmp(cDescripcion, "AUTO PROT.", 10) != 0 && memcmp(cConceptoCta, "CP MUEB", 7) != 0)
                                {
                                    sDato.Format("%s", stDatosCertificacion[iContMuebles].cFechaSaldaConCorte);
                                    sDato.Trim();

                                    sTexto.Format("%s", sDato.Left(4));
                                    iAnioS = strtol(sTexto, NULL, 10);

                                    sTexto.Format("%s", sDato.Mid(4, 2));
                                    iMesS = strtol(sTexto, NULL, 10);

                                    sTexto.Format("%s", sDato.Right(2));
                                    iDiaS = strtol(sTexto, NULL, 10);

                                    //sprintf_s(cMensaje, "Fecha: %s", sDato);
                                    //grabarLog(cMensaje);
                                }
                                else
                                {
                                    obtenerFechaSaldaCon(iAnioS, iMesS, iDiaS);
                                    //sprintf_s(cMensaje, "Entra a obtener la fecha %d %d %d", iAnioS, iMesS, iDiaS);
                                    //grabarLog(cMensaje);
                                }
                            }
                            else
                            {
                                obtenerFechaSaldaCon(iAnioS, iMesS, iDiaS);
                                //sprintf_s(cMensaje, "Entra a obtener la fecha %d %d %d", iAnioS, iMesS, iDiaS);
                                //grabarLog(cMensaje);
                            }
                        }

                        nombreMes(iMesS, cNombreMes);
                        sTexto.Format("%d", iAnioS);
						if(sprintf_s(cFechaSalda, "%02d%s%s", iDiaS, cNombreMes, sTexto.Right(2)) < 0){;}
						if(strncpy_s(cFechaPago, cFechaSalda, 5) < 0){;}
                        cFechaPago[5] = 0;
                    }

                    lDebe = (lSaldoX - lSuPagoX);
                    if (lDebe < 0)
                    {
                        if ((lDebe * -1) > lSuPagoX)
                            lDebe = lSuPagoX * -1;
                    }

                    if (lDebe > 0 && lSuPagoX < lSaldaConX)
                        iPagado = 1;
                    else
                        iPagado = 0;

                    if (iPagado == 1)
                    {
                        if (strncmp(cDescripcion, "PRESTAMO", 8) != 0 && strncmp(cDescripcion, "BANCOPPE", 8) != 0 && VerificarCuentaBcpl2(cDescripcion, "SOLEX") == 0)
                        {
                            if ((memcmp(cConceptoCta, "CP ROPA", 7) == 0 || memcmp(cConceptoCta, "CP MUEB", 7) == 0 ||
                                memcmp(cConceptoCta, "CP T.AIRE", 9) == 0 || memcmp(cConceptoCta, "CP BANC", 7) == 0 ||
                                memcmp(cConceptoCta, "CP PRES", 7) == 0 || memcmp(cConceptoCta, "CP COMP ADC", 11) == 0) &&
                                iFlagImpresionCuentasPerdidas == 1)
                            {
                                consultarMensaje(447, cMensajeClienteZ);
                                termica->ponerTermica(iRen, iCol, cMensajeClienteZ);
                            }
                            else
                            {
                                termica->ponerTermica(iRen, iCol, cFechaPago);
                            }
                        }
                    }
                    else
                    {
                        if (lFacturaX != 0)
                        {
                            sDato.Format("%d", stDatosCertificacion[iContMuebles].iInteresAdicional);
                            lInteresAdicionalCte = strtol(sDato, NULL, 10);
                            calculaAbonoInteres(lInteresAdicionalCte, lSuPagoX, lAbonoCte, lAbonoInteresCte);

                            sDato.Format("%ld", lAbonoCte);
                            stDatosCertificacion[iContMuebles].iAbono = strtol(sDato, NULL, 10);

                            sDato.Format("%ld", lAbonoInteresCte);
                            stDatosCertificacion[iContMuebles].iAbonoInteres = strtol(sDato, NULL, 10);

                            lSaldoDespues = (lSaldaConX - lSuPagoX);

                            sDato.Format("%ld", lSaldoDespues);
                            stDatosCertificacion[iContMuebles].iSaldoDespues = strtol(sDato, NULL, 10);

                            obtenerFechaPrimerAbono(iContMuebles);

                            if(iFlagCertificacionBonidicacion == 1)
							{
								guardarCertificacionAbonos(iContMuebles);
							}
                        }

                        if (strncmp(cDescripcion, "SEG. MOTOS", 10) == 0 || strncmp(cDescripcion, "P. CELULAR", 10) == 0 ){
							termica->ponerTermica(iRen, iCol, "");
						} else {
							termica->ponerTermica(iRen, iCol, "PAGADO");
						}

                    }

                    if (lFacturaX != 0)
                    {
                        iContMuebles++;
                    }

                }
                else
                {
                    nombreMes(iMesVenta, cNombreMes);
                    sTexto.Format("%d", iAnioVenta);
					if(sprintf_s(cRespuesta, "%02d%s%02d", iDiaVenta, cNombreMes, sTexto.Right(2)) < 0){;}
                    if ((int)iAnioVenta > 99)
                    {
						if(memcpy_s(cRespuestaAux, sizeof(cRespuestaAux), &cRespuesta[0], 5) < 0){;}
						if(memcpy_s(&cRespuestaAux[5], sizeof(cRespuestaAux), &cRespuesta[5], 2) < 0){;}
                        cRespuestaAux[7] = 0;

						if(memcpy_s(&cRespuesta[0], sizeof(cRespuesta), &cRespuestaAux[0], 7) < 0){;}
                        cRespuesta[7] = 0;
                    }

                    termica->ponerTermica(iRen, iCol, cRespuesta);
                }
            }
            else if (memcmp(cDescripcion, "AUTO PROT.", 10) == 0)
            {
                if (lSuPagoX > 0)
                {
                    m_grid.QuickGetText(iContCtas, 33, &sTexto);
                }
                else
                {
                    m_grid.QuickGetText(iContCtas, 25, &sTexto);
                }
                sTexto.Trim();
				if(sprintf_s(cTxt, "%s", sTexto) < 0){;}

                iMesV = valor_campo(&cTxt[2], 2);
                iAnioV = valor_campo(&cTxt[6], 2);
                iDiaV = valor_campo(&cTxt[0], 2);

                SecureZeroMemory(cRespuesta, sizeof(cRespuesta));

                nombreMes(iMesV, cNombreMes);
				if(sprintf_s(cRespuesta, "%02d%s%02d", iDiaV, cNombreMes, iAnioV) < 0){;}

                termica->ponerTermica(iRen, iCol, cRespuesta);
            } else if (strncmp(cDescripcion, "SEG. MOTOS", 10) == 0 || strncmp(cDescripcion, "P. CELULAR", 10) == 0 ) {
				termica->ponerTermica(iRen, iCol, "");
			}

            iCol += LONGITUD_COLUMNA_CTAS;

            if (iFlagCapturoConvenioX == 1)
            {
				short iDiasConvenio = 0, iAnioConvenio = 0, iMesConvenio = 0, iDiaConvenio = 0;
				m_grid.QuickGetText(iContCtas, 9, &sTexto);
				sTexto.Trim();
				iPlazoConvenioX = strtol(sTexto, NULL, 10);

				iDiasConvenio = (short)iPlazoConvenioX * 7;

				iAnioConvenio = iAnioActual;
				iMesConvenio = iMesActual;
				iDiaConvenio = iDiaActual;

				sumarDias(iDiasConvenio, iDiaConvenio, iMesConvenio, iAnioConvenio);
				nombreMes(iMesConvenio, cNombreMes);
				if(sprintf_s(cRespuesta, "%02d-%s", iDiaConvenio, cNombreMes) < 0){;}
				iCol += 5;
				termica->ponerTermica(iRen, iCol, cRespuesta);
				iCol += LONGITUD_COLUMNA_CTAS;
            }
            break;
        case 10: //Bonificación
            if (lBonificacionX > 0 && lSuPagoX >= lSaldaConX)
            {
                if (lSaldoX > 0)
                {
                    if (lSuPagoX > lSaldaConX)
                    {
                        lBonificacionX = lSaldoX - lSuPagoX;
                        if (lBonificacionX < 0) lBonificacionX = 0;
                    }
                }
                lAhoraDebe -= lBonificacionX;
                if (lBonificacionX > 0)
                {
                    bAplicaBonificacion = true;
                    termica->alinearTexto(IZQUIERDA); termica->ponerTermica(iRen, 50, "Bonificación");
                    termica->alinearTexto(DERECHA);
                    usingx("###,###", cRespuesta, (double)lBonificacionX);
                    termica->ponerTermica(iRen, iCol, cRespuesta);

                    lSuAbono += lBonificacionX;
                }
            }

            iCol += LONGITUD_COLUMNA_CTAS;

            if (iFlagCapturoConvenioX == 1)
            {
                iCol += LONGITUD_COLUMNA_CTAS + 5;
            }
            break;
        default:
            break;
        }
    }

    if (iContCtas == iTotalCuentas)
    {
        if (iTipoDetalle == 0) // Si se imprimieron los nombres de las cuentas se agregan 5 pix al renglon debido a la linea que se imprime.
        {
            if (iCuentasImpresas > 8)
            {
                iColMax += (iCuentasImpresas - 8) * LONGITUD_COLUMNA_CTAS;
                iColIniEncabezado += (iCuentasImpresas - 8) * LONGITUD_COLUMNA_CTAS;
            }

            if (iConvenios > 0 && iCuentasImpresas >= 8)
            {
                iColMax += iConvenios * 5; //Se incrementa 5 pixeles por cada cuenta con convenio
            }
        }


        switch (iTipoDetalle)
        {
        case 0: //Cuenta
            termica->ponerTermica(iRen, iColMax, "TOTALES");
            break;
        case 3: //Usted Debía
            usingx("###,###", cRespuesta, (double)lUstedDebia);
            termica->ponerTermica(iRen, iColMax, cRespuesta);
            break;
        case 4: //Abono a Cuenta
            usingx("###,###", cRespuesta, (double)lAbonoTotal);
            termica->ponerTermica(iRen, iColMax, cRespuesta);
            break;
        case 5: //Abono Intereses
            usingx("###,###", cRespuesta, (double)lInteresTotal);
            termica->ponerTermica(iRen, iColMax, cRespuesta);
            break;
        case 6: //Usted Debe Hoy
            usingx("###,###", cRespuesta, (double)lDebeTotal);
            termica->ponerTermica(iRen, iColMax, cRespuesta);
            break;
        case 7: //Atrasado
            usingx("###,###", cRespuesta, (double)lVencidoTotal);
            termica->ponerTermica(iRen, iColMax, cRespuesta);
            break;
        case 8: //Salda Con
            if (iFlagTiendaLocal == 0)
            {
                usingx("###,###", cRespuesta, (double)lSaldaConTotal);
                termica->ponerTermica(iRen, iColMax, cRespuesta);
            }
            break;
        default:
            break;
        }
    }
    //sprintf_s(cMensaje, "imprimirCuenta:: Termina Imprimiendo cuenta.");
    //grabarLog(cMensaje);
}

int CDlgCapturarAbono::obtenerMes(char *cFecha)
{
    char cMes[5] = { 0 };
    int iMes = 0;

	if(memcpy_s(cMes, sizeof(cMes), &cFecha[2], 3) < 0){;}
    cMes[3] = 0;

    if (memcmp(cMes, "ENE", 3) == 0)
    {
        iMes = 1;
    }
    else if (memcmp(cMes, "MAR", 3) == 0)
    {
        iMes = 3;
    }
    else if (memcmp(cMes, "FEB", 3) == 0)
    {
        iMes = 2;
    }
    else if (memcmp(cMes, "ABR", 3) == 0)
    {
        iMes = 4;
    }
    else if (memcmp(cMes, "MAY", 3) == 0)
    {
        iMes = 5;
    }
    else if (memcmp(cMes, "JUN", 3) == 0)
    {
        iMes = 6;
    }
    else if (memcmp(cMes, "JUL", 3) == 0)
    {
        iMes = 7;
    }
    else if (memcmp(cMes, "AGO", 3) == 0)
    {
        iMes = 8;
    }
    else if (memcmp(cMes, "SEP", 3) == 0)
    {
        iMes = 9;
    }
    else if (memcmp(cMes, "OCT", 3) == 0)
    {
        iMes = 10;
    }
    else if (memcmp(cMes, "NOV", 3) == 0)
    {
        iMes = 11;
    }
    else if (memcmp(cMes, "DIC", 3) == 0)
    {
        iMes = 12;
    }

    return iMes;
}

void CDlgCapturarAbono::imprimirEncabezadoConvenioUnico()
{
    char cMensaje[100] = { 0 };
    char cNombreMes[5] = { 0 };
    CString sNombre, sApellidoPaterno, sApellidoMaterno;

    CWnd pWnd;
    CClientDC dc(&pWnd);

    grabarLog("imprimirEncabezadoConvenioUnico::Imprimiendo encabezado Convenio Unico");

    termica->alinearTexto(CENTRO);

    termica->cargarImagen(dc, "c:\\sys\\progs\\logo.bmp", iRenglon);
    termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 10);

    iRenglon += 100;

    termica->ponerTermica(iRenglon, 250, "Coppel S.A. de C.V. República 2855");
    iRenglon += 30;
    termica->ponerTermica(iRenglon, 250, "Culiacán, Sin. RFC: COP-920428-Q20");
    iRenglon += 50;

    termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 11);
	if(sprintf_s(cMensaje, "Convenio Único") < 0){;}
    termica->ponerTermica(iRenglon, 250, cMensaje);

    iRenglon += 35;
    termica->ponerLinea(iRenglon, 0, iRenglon, 500);

    iRenglon += 5;
    termica->alinearTexto(IZQUIERDA);
    termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);

    nombreMes(iMesActual, cNombreMes);
	if(sprintf_s(cMensaje, "%02d-%s-%02d", iDiaActual, cNombreMes, iAnioActual) < 0){;}
    termica->ponerTermica(iRenglon, 0, "Fecha: ");
    termica->ponerTermica(iRenglon, 90, cMensaje);
	if(sprintf_s(cMensaje, "Tel: %s", cTelefonoGnDominio) < 0){;}
    termica->alinearTexto(DERECHA);
    termica->ponerTermica(iRenglon, 500, cMensaje);
    iRenglon += 25;
    termica->alinearTexto(IZQUIERDA);
	if(sprintf_s(cMensaje, "T-%03d: ", m_grid.iTienda) < 0){;}
    termica->ponerTermica(iRenglon, 0, cMensaje);
	if(sprintf_s(cMensaje, "%s", cNombreSucursal) < 0){;}
    termica->ponerTermica(iRenglon, 90, cMensaje);
	if(sprintf_s(cMensaje, "Caja: %c%02d", m_grid.cArea, m_grid.iCaja) < 0){;}
    termica->alinearTexto(DERECHA);
    termica->ponerTermica(iRenglon, 500, cMensaje);
    iRenglon += 25;
    termica->alinearTexto(IZQUIERDA);
    termica->ponerTermica(iRenglon, 0, "Domicilio: ");
    termica->ponerTermica(iRenglon, 90, cDomicilio);
    termica->alinearTexto(DERECHA);
    termica->ponerTermica(iRenglon, 500, cNombreCiudad);
    termica->alinearTexto(IZQUIERDA);
    iRenglon += 25;
    termica->ponerLinea(iRenglon, 0, iRenglon, 500);
    iRenglon += 5;

    termica->ponerTermica(iRenglon, 0, "Nombre:");
    m_nombre.GetWindowText(sNombre);
    sNombre.Trim();
    m_apellidoPaterno.GetWindowText(sApellidoPaterno);
    sApellidoPaterno.Trim();
    m_apellidoMaterno.GetWindowText(sApellidoMaterno);
    sApellidoMaterno.Trim();
	if(sprintf_s(cMensaje, "%s %s %s", sNombre, sApellidoPaterno, sApellidoMaterno) < 0){;}
    termica->ponerParrafoTermica(cMensaje, iRenglon, 80, 500);

    iRenglon += 25;
	if(sprintf_s(cMensaje, "%ld", m_grid.lCliente) < 0){;}
    termica->ponerTermica(iRenglon, 0, "Cliente: ");
    termica->ponerTermica(iRenglon, 80, cMensaje);
    iRenglon += 25;
    termica->ponerLinea(iRenglon, 0, iRenglon, 500);
    grabarLog("imprimirEncabezadoConvenioUnico::Termina encabezado Convenio Unico");
}

void CDlgCapturarAbono::imprimirReciboConvenioTienda(long lTotalImporteConvenio, char *cFecha)
{
    char cMensaje[60] = { 0 }, cImporteConvenio[15] = { 0 };

    grabarLog("imprimirReciboConvenioTienda::Imprimiendo Recibo Convenio Tienda");

    imprimirEncabezadoConvenioUnico();

    iRenglon += 25;
    usingx("###,###", cImporteConvenio, (double)lTotalImporteConvenio);
	if(sprintf_s(cMensaje, "Me comprometo a pagar $ %s", cImporteConvenio) < 0){;}
    termica->ponerTermica(iRenglon, 0, cMensaje);
    iRenglon += 25;
	if(sprintf_s(cMensaje, "Antes del día %s en la Tienda Coppel.", cFecha) < 0){;}
    termica->ponerTermica(iRenglon, 0, cMensaje);

    iRenglon += 100;
    termica->ponerLinea(iRenglon, 100, iRenglon, 400);
    iRenglon += 5;
    termica->alinearTexto(CENTRO);
    termica->ponerTermica(iRenglon, 250, "Firma del Cliente");

    iRenglon += 50;
    termica->alinearTexto(IZQUIERDA);
    termica->terminarImpresionParcial(iRenglon);
    grabarLog("imprimirReciboConvenioTienda::Termina Recibo Convenio Tienda");
}

void CDlgCapturarAbono::imprimirReciboConvenioCliente(long lTotalImporteConvenio, char *cFecha)
{
    char cMensaje[60] = { 0 }, cImporteConvenio[15] = { 0 };
    CString sNombre, sApellidoPaterno, sApellidoMaterno;

    grabarLog("imprimirReciboConvenioCliente::Imprimiendo Recibo Convenio Cliente");

    imprimirEncabezadoConvenioUnico();

    iRenglon += 25;
    m_nombre.GetWindowText(sNombre);
    sNombre.Trim();
    m_apellidoPaterno.GetWindowText(sApellidoPaterno);
    sApellidoPaterno.Trim();
    m_apellidoMaterno.GetWindowText(sApellidoMaterno);
    sApellidoMaterno.Trim();
	if(sprintf_s(cMensaje, "%s %s %s", sNombre, sApellidoPaterno, sApellidoMaterno) < 0){;}
    termica->ponerTermica(iRenglon, 0, "Yo");
    termica->ponerParrafoTermica(cMensaje, iRenglon, 30, 500);
    termica->ponerTermica(iRenglon, 30, cMensaje);
    iRenglon += 25;
    usingx("###,###", cImporteConvenio, (double)lTotalImporteConvenio);
	if(sprintf_s(cMensaje, "me comprometo a pagar $ %s antes del día %s", cImporteConvenio, cFecha) < 0){;}
    termica->ponerTermica(iRenglon, 0, cMensaje);
    iRenglon += 25;
    termica->ponerTermica(iRenglon, 0, " en la Tienda Coppel. En caso de no cumplir con este ");
    iRenglon += 25;
    termica->ponerTermica(iRenglon, 0, "convenio autorizo al Departamento de Cobranzas para ");
    iRenglon += 25;
    termica->ponerTermica(iRenglon, 0, "que recoja los artículos suficientes para cubrir mi deuda.");
    iRenglon += 50;

    termica->ponerTermica(iRenglon, 0, "El cumplimiento de este convenio, le permitirá benefecios");
    iRenglon += 25;
    termica->ponerTermica(iRenglon, 0, "como: Conservar su crédito, más facilidades al comprar,");
    iRenglon += 25;
    termica->ponerTermica(iRenglon, 0, "no ser reportados a otros negocios.");

    iRenglon += 25;

    grabarLog("imprimirReciboConvenioCliente::Termina Recibo Convenio Cliente");
}

void CDlgCapturarAbono::imprimirReciboConvenioUnico()
{
    int  i = 0, iDia1 = 0, iDia2 = 0, iAnio = 0, iMes = 0, iDia = 0, iMesConvenio = 0,
        iDiaConvenio = 0, iTipoConvenio = 0, iSubTipoConvenio = 0, iPlazoConvenio = 0;
    int iTipoConvenioX = 0;
    bool bImprimeFirma = false;
    int lSaldaConN = 0, lVencidoFinalTicket = 0, lVencidoN = 0;
    long lConvenioTotal = 0L, lEfectuoConvenio = 0L, lImporteConvenio = 0L, lSuPagoGrid = 0L, lFactura = 0L;
    char cRespuesta[80] = { 0 }, cFechaConvenio[10] = { 0 }, cDesc[20] = { 0 }, cNombreMes[5] = { 0 }, cAnio[5] = { 0 }, cImporteConvenio[15] = { 0 };
    CString sTexto;

    grabarLog("imprimirReciboConvenioUnico::Imprimiendo Recibo Convenio Unico");

    termica->iniciarImpresion("BIXOLON SAMSUNG SRP-350plus", false);
    termica->impresionHorizontal(IMPRESION_VERTICAL);
    iRenglon = 0;

    for (i = 0; i < iTotalCuentas; i++)
    {
        m_grid.QuickGetText(i, 7, &sTexto);
        sTexto.Trim();
		if(sprintf_s(cFechaConvenio, "%s", sTexto) < 0){;}
        iMesConvenio = obtenerMes(cFechaConvenio);
        iDiaConvenio = valor_campo(&cFechaConvenio[0], 2);

        m_grid.QuickGetText(i, 9, &sTexto);
        sTexto.Trim();
        iPlazoConvenio = strtol(sTexto, NULL, 10);

        m_grid.QuickGetText(i, 27, &sTexto);
        iTipoConvenio = 0;
        iTipoConvenio = strtol(sTexto, NULL, 10);

        m_grid.QuickGetText(i, 34, &sTexto);
        iSubTipoConvenio = 0;
        iSubTipoConvenio = strtol(sTexto, NULL, 10);

        sTexto.Format("%d%d", iTipoConvenio, iSubTipoConvenio);
        iTipoConvenioX = strtol(sTexto, NULL, 10);

        m_grid.QuickGetText(i, 10, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lImporteConvenio = strtol(cRespuesta, NULL, 10);

        m_grid.QuickGetText(i, 18, &sTexto);
        sTexto.Trim();
        sTexto.Remove(',');
        sTexto.Remove('.');
        lSaldaConN = strtol(sTexto, NULL, 10);

        m_grid.QuickGetText(i, 21, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
        sTexto.Trim();
        lSuPagoGrid = strtol(sTexto, NULL, 10);

        m_grid.QuickGetText(i, 15, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lVencidoN = strtol(cRespuesta, NULL, 10);

        if (lSuPagoGrid >= lVencidoN)
        {
            lVencidoFinalTicket = 0;
        }
        else
        {
            lVencidoFinalTicket = iAbonoConVencidoFinalImpresion[i] - lSuPagoGrid;
        }
        if (lVencidoFinalTicket <= lImporteConvenio)//En Caso que el vencido sea menor al conv, se topara al vencido de la cuenta..
        {
            lImporteConvenio = lVencidoFinalTicket;
        }

        if (iTipoConvenioX == 12 && iDiaActual == iDiaConvenio && iMesActual == iMesConvenio) //convenio unico
        {
            m_grid.QuickGetText(i, 8, &sTexto);
            sTexto.Trim();
            lEfectuoConvenio = strtol(sTexto, NULL, 10);

            lConvenioTotal += lImporteConvenio;
            iDia2 = (int)iPlazoConvenio * 7;
            if (iDia2 > iDia1) iDia1 = iDia2;
        }
    }
    iAnio = iAnioActual; iMes = iMesActual; iDia = iDiaActual;
    sumarDia(iDia1, iDia, iMes, iAnio); //gn_dia.cpp

    nombreMes(iMes, cNombreMes);
	if(sprintf_s(cAnio, "%d", iAnio) < 0){;}
	if(sprintf_s(cRespuesta, "%d-%s-%s", iDia, cNombreMes, CString(cAnio).Mid(2, 2)) < 0){;}
    if (lConvenioTotal > 0)//El importe conveniado debe ser mayor a 0 para imrpimir ticket cov-Unico
    {
        imprimirReciboConvenioTienda(lConvenioTotal, cRespuesta);
        imprimirReciboConvenioCliente(lConvenioTotal, cRespuesta); // Imprime el encabezado del recibo para el cliente
    }
    for (i = 0; i < iTotalCuentas; i++)
    {
        m_grid.QuickGetText(i, 7, &sTexto);
        sTexto.Trim();
		if(sprintf_s(cFechaConvenio, "%s", sTexto) < 0){;}
        iMesConvenio = obtenerMes(cFechaConvenio);
        iDiaConvenio = valor_campo(&cFechaConvenio[0], 2);

        m_grid.QuickGetText(i, 27, &sTexto);
        iTipoConvenio = 0;
        iTipoConvenio = strtol(sTexto, NULL, 10);

        m_grid.QuickGetText(i, 34, &sTexto);
        iSubTipoConvenio = 0;
        iSubTipoConvenio = strtol(sTexto, NULL, 10);

        sTexto.Format("%d%d", iTipoConvenio, iSubTipoConvenio);
        iTipoConvenioX = strtol(sTexto, NULL, 10);

        lFactura = 0L;
        if (i > 0)
        {
            m_grid.QuickGetText(i, 1, &sTexto);
            sTexto.Trim();
            lFactura = strtol(sTexto, NULL, 10);
        }

        m_grid.QuickGetText(i, 10, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lImporteConvenio = strtol(cRespuesta, NULL, 10);

        m_grid.QuickGetText(i, 18, &sTexto);
        sTexto.Trim();
        sTexto.Remove(',');
        sTexto.Remove('.');
        lSaldaConN = strtol(sTexto, NULL, 10);

        m_grid.QuickGetText(i, 21, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
        sTexto.Trim();
        lSuPagoGrid = strtol(sTexto, NULL, 10);

        m_grid.QuickGetText(i, 15, &sTexto);
        sTexto.Remove(',');
        sTexto.Remove('.');
		if(sprintf_s(cRespuesta, "%s", sTexto) < 0){;}
        lVencidoN = strtol(cRespuesta, NULL, 10);

        m_grid.QuickGetText(i, -1, &sTexto);
        sTexto.Remove(',');
		if(sprintf_s(cDesc, "%s", sTexto) < 0){;}

        if (lSuPagoGrid >= lVencidoN)
        {
            lVencidoFinalTicket = 0;
        }
        else
        {
            lVencidoFinalTicket = iAbonoConVencidoFinalImpresion[i] - lSuPagoGrid;
        }
        if (lVencidoFinalTicket <= lImporteConvenio)//En Caso que el vencido sea menor al conv, se topara al vencido de la cuenta..
        {
            lImporteConvenio = lVencidoFinalTicket;
        }

        if (iTipoConvenioX == 12 && iDiaActual == iDiaConvenio && iMesActual == iMesConvenio) //convenio unico
        {
            if (lFactura == 0L || memcmp(cDesc, "T.AIRE", 6) == 0)
            {
                if (memcmp(cDesc, "T.AIRE", 6) == 0)
                {
					if(sprintf_s(cRespuesta, "No. Factura: T.AIRE") < 0){;}
                }
                else if (memcmp(cDesc, "COMP ADC", 8) == 0)
                {
					if(sprintf_s(cRespuesta, "No. Factura: COMP ADC") < 0){;}
                }
                else
                {
					if(sprintf_s(cRespuesta, "No. Factura: ROPA") < 0){;}
                }
            }
            else
            {
				if(sprintf_s(cRespuesta, "No. Factura: %ld", lFactura) < 0){;}
            }

            if (lImporteConvenio > 0)
            {
                iRenglon += 25;
                termica->alinearTexto(IZQUIERDA);
                termica->ponerTermica(iRenglon, 0, cRespuesta);
                termica->alinearTexto(DERECHA);
                usingx("###,###", cImporteConvenio, (double)lImporteConvenio);
				if(sprintf_s(cRespuesta, "Importe:   %s", cImporteConvenio) < 0){;}
                termica->ponerTermica(iRenglon, 500, cRespuesta);
                bImprimeFirma = true;
            }
        }
    }

    if (bImprimeFirma)//Si Tiene Convenio-Unico Imprime
    {
        iRenglon += 100;
        termica->ponerLinea(iRenglon, 100, iRenglon, 400);
        iRenglon += 5;
        termica->alinearTexto(CENTRO);
        termica->ponerTermica(iRenglon, 250, "Firma del empleado");
        iRenglon += 25;
		if(sprintf_s(cRespuesta, "No. Empleado: %ld", lEfectuoConvenio) < 0){;}
        termica->ponerTermica(iRenglon, 250, cRespuesta);

        iRenglon += 75;
        termica->tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 8);
        termica->ponerTermica(iRenglon, 250, "¡Coppel, Mejora tu vida!");

        iRenglon += 50;
        termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);
        termica->ponerTermica(iRenglon, 250, ".");

        termica->terminarImpresion();
    }

    grabarLog("imprimirReciboConvenioUnico::Termina Recibo Convenio Unico");
}

void CDlgCapturarAbono::imprimeMensajePromocionDirecta()
{
    CWnd pWnd;
    CClientDC dc(&pWnd);

    iRenglon = 0;

    grabarLog("imprimeMensajePromocionDirecta::Imprimiendo Mensaje Promocion Directa");

    if ((strnlen(cEncabezado, sizeof(cEncabezado)) != 0) && (strnlen(cParrafo1, sizeof(cParrafo1)) != 0) && (strnlen(cParrafo2, sizeof(cParrafo2)) != 0) &&
        (strnlen(cParrafo3, sizeof(cParrafo3)) != 0) && (strnlen(cParrafo4, sizeof(cParrafo4)) != 0))
    {
        termica->iniciarImpresion("BIXOLON SAMSUNG SRP-350plus", false);

        termica->impresionHorizontal(IMPRESION_VERTICAL);

        termica->alinearTexto(CENTRO);
        termica->cargarImagen(dc, "c:\\sys\\progs\\logo.bmp", iRenglon);

        termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 9);
        iRenglon += 100;
        termica->ponerTermica(iRenglon, 250, "Coppel S.A. de C.V.");

        termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 7);
        iRenglon += 30;
        termica->ponerTermica(iRenglon, 250, "Republica Pte. 2855 Recursos Hidráulicos");
        iRenglon += 30;
        termica->ponerTermica(iRenglon, 250, "Culiacán Rosales, Sinaloa 80105 ");
        iRenglon += 30;
        termica->ponerTermica(iRenglon, 250, "RFC: COP-920428-Q20");
        iRenglon += 50;
        termica->tipoLetra(&cNewFont, "Arial", &pcOldFont, 8);
        termica->alinearTexto(IZQUIERDA);
        termica->ponerParrafoTermica(cEncabezado, iRenglon, 0, 500);
        iRenglon += 50;
        termica->ponerParrafoTermica(cParrafo1, iRenglon, 0, 500);
        iRenglon += 50;
        termica->ponerParrafoTermica(cParrafo2, iRenglon, 0, 500);
        iRenglon += 50;
        termica->ponerParrafoTermica(cParrafo3, iRenglon, 0, 500);
        iRenglon += 50;
        termica->alinearTexto(DERECHA);
        termica->ponerTermica(iRenglon, 470, cParrafo4);

        termica->tipoLetra(&cNewFont, "Arial Black", &pcOldFont, 8);

        iRenglon += 25;
        termica->alinearTexto(CENTRO);
        iRenglon += 50;
        termica->ponerTermica(iRenglon, 0, ".");
        termica->terminarImpresion();
    }
}

int CDlgCapturarAbono::VerificarCuentaBcpl2(char *cadena, char *subcadena)
{
    // busca una subcadena en otra cadena.
    int i, j;
    int l_cadena = strnlen(cadena, 15);
    int l_subcadena = strnlen(subcadena, 5);

    if (l_cadena < l_subcadena)
        return 0;
    if (cadena[0] == NULL && subcadena[0] == NULL)
        return 1;

    for (i = 0; i < l_cadena; i++)
        if (cadena[i] == subcadena[0])
        {
            if (l_cadena - i < l_subcadena)
                return 0;

            for (j = 0; j < l_subcadena; j++)
                if (cadena[i + j] != subcadena[j])
                    break;

            if (j == l_subcadena)
                return 1;
        }

    return 0;
}

void CDlgCapturarAbono::guardarCertificacionAbonos(int i)
{
    char sSqlGrabarCertificacion[900] = { 0 };
    int idOrigen = 0;

    idOrigen = 1; // Tienda

    if(sprintf_s(sSqlGrabarCertificacion, "SELECT estado, mensaje FROM fun_guardarcertificacionbonificaciondiaria01('%d', '%d', %d, %d, %d, '%d', '%s', '%s', '%d', %d, %d, %d, %d, '%s', %d, %d, %d, '%d', %d, '%d', %d, %d, %d, %d, %d);",
		idOrigen, stDatosCertificacion[i].iTipoCuenta, stDatosCertificacion[i].iCliente, stDatosCertificacion[i].iFactura, stDatosCertificacion[i].iTienda, stDatosCertificacion[i].iCaja, stDatosCertificacion[i].cFechaCompra, stDatosCertificacion[i].cFechaApartir, stDatosCertificacion[i].iPlazo, stDatosCertificacion[i].iContado, stDatosCertificacion[i].iIsc, stDatosCertificacion[i].iCredito, stDatosCertificacion[i].iAbonoBase, stDatosCertificacion[i].cFechaMovto, stDatosCertificacion[i].iAbono, stDatosCertificacion[i].iAbonoInteres, stDatosCertificacion[i].iSaldaCon, stDatosCertificacion[i].iDiasTranscurridos, stDatosCertificacion[i].iBonificacion, stDatosCertificacion[i].iPorcBonificacion, stDatosCertificacion[i].iSaldoVencido, stDatosCertificacion[i].iInteresAdicional, stDatosCertificacion[i].iSaldoAnterior, stDatosCertificacion[i].iSaldoDespues, stDatosCertificacion[i].iInteresadicionalPrimerMesc) < 0){;}

    grabarLog(sSqlGrabarCertificacion);
	
    CGrabarCertificacionAbono certificacionAbono(&odbc, false);

    if (certificacionAbono.Exec(sSqlGrabarCertificacion))
    {
        certificacionAbono.activarCols();
        if (certificacionAbono.Leer())
        {
            if (certificacionAbono.estado != 0)
            {
                certificacionAbono.odbc->GetLastError(certificacionAbono.GetHstmt());
                grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "CImpresionReciboAbonos", "guardarCertificacionAbonos", sSqlGrabarCertificacion, m_grid.lEmpleado, "ERROR EN LA CONSULTA(fun_guardarcertificacionbonificaciondiaria)", certificacionAbono.odbc, m_grid.iMuestraMsg);

            }
        }
    }
}

bool CDlgCapturarAbono::obtenerFechaPrimerAbono(int i)
{
    bool bRegresa = true;
    char cSql[100] = { 0 };
    int iDiaPrimerAbono = 0, iMesPrimerAbono = 0, iAnioPrimerAbono = 0, iAnioS = 0, iMesS = 0, iDiaS = 0, iFlagPlazo = -1;
    CString sDato = "", sTexto = "";

    if (stDatosCertificacion[i].iPlazo == 12 || stDatosCertificacion[i].iPlazo == 18 || stDatosCertificacion[i].iPlazo == 24)
    {
        iFlagPlazo = 0;
    }
    else
    {
        iFlagPlazo = 1;
    }

    sDato.Format("%s", stDatosCertificacion[i].cFechaCompra);
    sDato.Trim();

    sTexto.Format("%s", sDato.Left(4));
    iAnioS = strtol(sTexto, NULL, 10);

    sTexto.Format("%s", sDato.Mid(4, 2));
    iMesS = strtol(sTexto, NULL, 10);

    sTexto.Format("%s", sDato.Right(2));
    iDiaS = strtol(sTexto, NULL, 10);

	if(sprintf_s(cSql, "SELECT diapago, mespago, aniopago FROM gncalculardiadepago( '%d', '%d', '%d', '%d');", iFlagPlazo, iDiaS, iMesS, iAnioS) < 0){;}

    CObtenerFechaPrimerAbono consultarFechaAbono(&odbc, false);

    consultarFechaAbono.diapago = 0;
    consultarFechaAbono.mespago = 0;
    consultarFechaAbono.aniopago = 0;

    if (consultarFechaAbono.Exec(cSql))
    {
        consultarFechaAbono.activarCols();
        if (consultarFechaAbono.leer())
        {
            iDiaPrimerAbono = (short)consultarFechaAbono.diapago;
            iMesPrimerAbono = (short)consultarFechaAbono.mespago;
            iAnioPrimerAbono = (int)consultarFechaAbono.aniopago;

			if(sprintf_s(stDatosCertificacion[i].cFechaApartir, "%04d%02d%02d", iAnioPrimerAbono, iMesPrimerAbono, iDiaPrimerAbono) < 0){;}
        }
        else
        {
            bRegresa = false;
        }
    }
    else
    {
        bRegresa = false;
    }

    if (!bRegresa)
    {
        consultarFechaAbono.odbc->GetLastError(consultarFechaAbono.GetHstmt());
        grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "CDlgCapturarAbono", "gncalculardiadepago", cSql, m_grid.lEmpleado, "ERROR EN LA CONSULTA(gncalculardiadepago)", consultarFechaAbono.odbc, m_grid.iMuestraMsg);

    }
    return bRegresa;
}