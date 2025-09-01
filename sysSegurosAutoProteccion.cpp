#include "stdafx.h"
#include "DlgCapturarAbono.h"
#include "CSysFolioGlobal.hpp"
#include "CConsultarPolizaXML.hpp"


bool CDlgCapturarAbono::capturarAbonoSeguroAuto(long lPoliza)
{
    UNREFERENCED_PARAMETER(lPoliza);
    bool bRegresar = true;
    int iColX = 0, iTipoCovertura = 0, iMesesTranscurridosVenta = 0, iModelo = 0;
    long iPrimaSeguro = 0;
    char cFecha[11] = { 0 }, cNombreProyecto[100] = { 0 }, cNombreFuncionDLL[10] = { 0 }, cInputParam1[1024] = { 0 }, cInputParam2[1024] = { 0 }, cOutputParam1[1024] = { 0 }, cOutputParam2[1024] = { 0 };
    CString sDato;

    grabarLog("CDlgCapturarAbono::capturarAbonoSeguroAuto: Inicia Venta Seguro Auto");

    struct CRegresarSeguroAuto
    {
        long lImportePagar;
        int iMeses;
        int iDiaV,
            iMesV,
            iAnioV;
        int  iPolizaNueva;
        int NumPolizaNueva;
    };

    CRegresarSeguroAuto regresa;
    SParametros parametros;

    SecureZeroMemory(&parametros, sizeof(SParametros));
    SecureZeroMemory(&autoSeguro, sizeof(autoSeguro));
    SecureZeroMemory(&regresa, sizeof(regresa));

    iColX = m_grid.GetCurrentCol();
    m_grid.QuickGetText(iColX, 22, &sDato);
    iTipoCovertura = strtol(sDato, NULL, 10);
    m_grid.QuickGetText(iColX, 16, &sDato);
    iPrimaSeguro = strtol(sDato, NULL, 10);
    m_grid.QuickGetText(iColX, 24, &sDato);
    iMesesTranscurridosVenta = strtol(sDato, NULL, 10);
    m_grid.QuickGetText(iColX, 25, &sDato);
    if(sprintf_s(cFecha, "%s", sDato) < 0){;}
    m_grid.QuickGetText(iColX, 26, &sDato);
    iModelo = strtol(sDato, NULL, 10);
    m_grid.QuickGetText(iColX, 1, &sDato);

    if (!sDato.IsEmpty())
    {
        std::string str = sDato;
        std::string str2 = str.substr(1, 9);
        autoSeguro.lPoliza = strtol(str2.c_str(), NULL, 10);
    }

    if(sprintf_s(parametros.sServer, "%s", m_grid.sServer) < 0){;}
    parametros.iTienda = m_grid.iTienda;
    parametros.lEmpleado = m_grid.lEmpleado;
    parametros.iCajaActual = m_grid.iCaja;
    parametros.lCliente = m_grid.lCliente;
    parametros.iMuestraMsg = m_grid.iMuestraMsg;

    parametros.iTasaMuebles = 1; // Flag Autoproteccion valida acceso por caja de abonos
    parametros.iTipo = iTipoCovertura;
    parametros.lCantidad = iPrimaSeguro;
    parametros.iTipoCoordenada = iMesesTranscurridosVenta;
    parametros.iTipoServicio = iModelo;
    if(sprintf_s(parametros.sFechaDesde, "%s", cFecha) < 0){;}
    parametros.lCodigo1 = autoSeguro.lPoliza;
    //parametros.lCodigo1 = autoSeguro.lPoliza = atol(sDato);

    //CapturarAbonoSeguroAuto
    nombreArchivo("CN0101.DLL", cNombreProyecto, DIRECTORIO_CA);
    if(sprintf_s(cNombreFuncionDLL, "CN0101") < 0){;}
	if(memcpy_s(cInputParam1, sizeof(cInputParam1), &parametros, sizeof(SParametros)) < 0){;}

    CargarDLL cargarDll("C:\\SYS\\PROGX\\CN\\CN0101", "CN0101", cInputParam1, cInputParam2, cOutputParam1, cOutputParam2);
    iRegresaDll = cargarDll.getResultado();
	if(memcpy_s(&regresa, sizeof(regresa), cOutputParam1, sizeof(regresa)) < 0){;}


    if (iRegresaDll == 1/* && regresa.iMeses > 0*/)
    {





        //memset(cFecha,0,sizeof(cFecha));
/*
        NumPolizaNva = regresa.NumPolizaNueva;
        lCliente = parametros.lCliente;  */
        /*
        //Meses que pago
        sDato.Format("Poliza: %d",regresa.NumPolizaNueva);
        m_grid.QuickSetText(iColX,1,sDato);
        m_grid.QuickSetAlignment(iColX,1, UG_ALIGNCENTER);
        NumPolizaNva = regresa.NumPolizaNueva;

        sDato.Format("AFILIADO");
        m_grid.QuickSetText(iColX,2,sDato);
        m_grid.QuickSetAlignment(iColX,2, UG_ALIGNCENTER);

        //Fecha Vencimiento
        miniFecha(cFecha, regresa.iDiaV, regresa.iMesV, regresa.iAnioV);
        sDato.Format("%s", cFecha);
        m_grid.QuickSetText(iColX,3,sDato);
        m_grid.QuickSetAlignment(iColX,3, UG_ALIGNCENTER);

        //Meses que pago
        sDato.Format("# MESES %d",regresa.iMeses);
        m_grid.QuickSetText(iColX,13,sDato);
        m_grid.QuickSetAlignment(iColX,13, UG_ALIGNCENTER);

        //Importe de la compra
        sDato.Format("%ld",regresa.lImportePagar);
        m_grid.QuickSetText(iColX,21,sDato);
        m_grid.QuickSetAlignment(iColX,21, UG_ALIGNRIGHT);

        //Numero de meses que pago
        sDato.Format("%d",regresa.iMeses);
        m_grid.QuickSetText(iColX,23,sDato);

        //Fecha Vencimiento nueva
        sDato.Format("%02ld%02ld%04ld",regresa.iDiaV,regresa.iMesV,regresa.iAnioV);
        m_grid.QuickSetText(iColX,33,sDato);

        //Flag si se genera poliza nueva
        sDato.Format("%d",regresa.iPolizaNueva);
        m_grid.QuickSetText(iColX,36,sDato);

        m_grid.RedrawAll();
        */
        //inicializar();
        //bRegresar = true;
        //desplegarDatosCliente();
        //imprimirPoliza( lCliente , NumPolizaNva , 5320, RECIBO_ABONO_POLIZAS);


    }
    else
    {
        bRegresar = false;
    }

    return bRegresar;
}

//23632: Se agrega metodo para abrir la Captura de CPV:
bool CDlgCapturarAbono::capturarVentaSeguroAuto()
{
    bool bRegresar = false;
    char cNombreProyecto[256] = { 0 }, cNombreFuncionDLL[256] = { 0 };
    char cInput1[1024] = { 0 }, cInput2[1024] = { 0 }, cOutput1[1024] = { 0 }, cOutput2[1024] = { 0 };
    SecureZeroMemory(cNombreProyecto, sizeof(cNombreProyecto));
    SecureZeroMemory(cNombreFuncionDLL, sizeof(cNombreFuncionDLL));
    if(sprintf_s(cNombreProyecto, "C:\\sys\\progx\\cn\\CN0101.DLL") < 0){;}
    if(sprintf_s(cNombreFuncionDLL, "CN0101") < 0){;}
    SParametros cParametros;
    SecureZeroMemory(&cParametros, sizeof(cParametros));
    if(sprintf_s(cParametros.sServer, "%s", m_grid.sServer) < 0){;}
    //cParametros.iLink = generarLink();
    cParametros.iTienda = m_grid.iTienda;
    cParametros.iNumSistema = iSistema;
    cParametros.lEmpleado = m_grid.lEmpleado;
    cParametros.iCajaActual = m_grid.iCaja;
    cParametros.iMuestraMsg = m_grid.iMuestraMsg;
    //cParametros.iGerente = 1;
    cParametros.lCliente = m_grid.lCliente;
	if(memcpy_s(cInput1, sizeof(cInput1), &cParametros, sizeof(SParametros)) < 0){;}
    CargarDLL cargarDll(cNombreProyecto, cNombreFuncionDLL, cInput1, cInput2, cOutput1, cOutput2);
    if (cargarDll.getResultado() == 1) {
        bRegresar = true;
    }
    return bRegresar;
}

//23632: Se agrega metodo obtener el tipo de Plan de CPV:
CString CDlgCapturarAbono::obtenerPlanSeguroAuto(int iTipoSeguro) {
    char cSql[200] = { 0 };
    CString csDescripcionPlanSeguro = "";
    if(sprintf_s(cSql, "SELECT INITCAP(descripcionseguro) AS descripcionseguro FROM crtiposeguro WHERE tiposeguro = %d AND fechaalta <= '%04d-%02d-%02d' ORDER BY fechaalta DESC LIMIT 1;", iTipoSeguro, iAnioActual, iMesActual, iDiaActual) < 0){;}
    CConsultarPlanSeguroAuto consultarPlanSeguroAuto(&odbc_1);
    if (consultarPlanSeguroAuto.Exec(cSql)) {
        consultarPlanSeguroAuto.activarCols();
        if (consultarPlanSeguroAuto.leer()) {
            csDescripcionPlanSeguro.Format("%s", consultarPlanSeguroAuto.descripcionseguro);
        }
    }
    return csDescripcionPlanSeguro.Trim();
}

//23632: Se agrega metodo obtener el costo del seguro de CPV:
long CDlgCapturarAbono::obtenerCostoSeguroAuto(int iTipoSeguro, int iTipovehiculo, int iNumMeses) {
    long lCostoSeguroAuto = 0L;
    char cSql[200] = { 0 };
    if(sprintf_s(cSql, "SELECT primatotal FROM crcostosautoseguro WHERE ciudad = %d AND tipovehiculo = %d AND tiposeguro = %d AND fechaalta <= '%04d-%02d-%02d' ORDER BY fechaalta DESC LIMIT 1;", iCiudadGnDominio, iTipovehiculo, iTipoSeguro, iAnioActual, iMesActual, iDiaActual) < 0){;}
    CMaximo consultarCostoSeguroAuto(&odbc_1);
    if (consultarCostoSeguroAuto.Exec(cSql)) {
        consultarCostoSeguroAuto.activarCols();
        if (consultarCostoSeguroAuto.leer()) {
            lCostoSeguroAuto = consultarCostoSeguroAuto.Total;
        }
    }
    lCostoSeguroAuto = (lCostoSeguroAuto / 100) * iNumMeses;
    return lCostoSeguroAuto;
}

bool CDlgCapturarAbono::buscarSegurosAuto()
{
    bool bRegresar = false;
    char cSql[150] = { 0 };

    if(sprintf_s(cSql, "SELECT COUNT(cliente) FROM  crsegurosauto WHERE cliente = %ld", m_grid.lCliente) < 0){;}

    CMaximo  consultarSeguros(&odbc_1);
    if (consultarSeguros.Exec(cSql))
    {
        consultarSeguros.activarCols();
        if (consultarSeguros.leer())
        {
            if (consultarSeguros.Total > 0)
            {
                bRegresar = true;
            }
        }
    }
    else
    {
        consultarSeguros.odbc->GetLastError(consultarSeguros.GetHstmt());
        grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "buscarSegurosAuto", "CMaximo", cSql, m_grid.lEmpleado, "ERROR EN LA CONSULTA(CGrabarTmpSeguroAutoCaCarmov01)", consultarSeguros.odbc, m_grid.iMuestraMsg);
    }

    return bRegresar;
}


bool CDlgCapturarAbono::grabarSeguroAutoCaCarmovTemporal(long lImporte, long lPrimaMes, int iFlagPoliza, long lPoliza, int iNumMeses,
    int iDiaVen, int iMesVen, int iAnioVen,
    int iDiaVAnt, int iMesVAnt, int iAnioVAnt,
    int iDiaVigencia, int iMesVigencia, int iAnioVigencia,
    int iTipoProducto, long lMinimoTotal, long lSaldoTotal, long lVencidoTotal, long lMinimoTotalFinal, long lSaldoTotalFinal, long lVencidoTotalFinal,
    int iTipovehiculo, int iDiaActi, int iMesActi, int iAnioActi, long lPolizaanteriorcancelar, long lImporteventacancelar,
    int iDiaVenta, int iMesVenta, int iAnioVenta)
{
    bool bContinuar = true;
    CString sConsulta, sDato;
    char cNombreCompleto[50] = { 0 }, cTipovehiculo[3] = { 0 };

    grabarLog("grabarSeguroAutoCaCarmovTemporal::Grabando seguro auto en tabla temporal");

    CGrabarTmpSeguroAutoCaCarmov01 tmpSeguroAutoCaCarmov(&odbc);	 // conexión al tienda.nnnn

    tmpSeguroAutoCaCarmov.clave[0] = 'G';
    tmpSeguroAutoCaCarmov.clave[1] = 0;
    tmpSeguroAutoCaCarmov.tipomovimiento[0] = '1';
    tmpSeguroAutoCaCarmov.tipomovimiento[1] = 0;
    tmpSeguroAutoCaCarmov.tienda = (short)m_grid.iTienda;
    tmpSeguroAutoCaCarmov.ciudad = (short)iCiudadGnDominio;
    tmpSeguroAutoCaCarmov.cliente = m_grid.lCliente;
    tmpSeguroAutoCaCarmov.caja = (short)m_grid.iCaja;
    tmpSeguroAutoCaCarmov.recibo = 0;
    tmpSeguroAutoCaCarmov.importe = lImporte;
    tmpSeguroAutoCaCarmov.saldoinicial = lPrimaMes;
    tmpSeguroAutoCaCarmov.tiposeguro[0] = '3';
    tmpSeguroAutoCaCarmov.tiposeguro[1] = 0;
    tmpSeguroAutoCaCarmov.cantidadmeses = (short)iNumMeses;
    tmpSeguroAutoCaCarmov.fechanacimiento.ponerFecha(iDiaVigencia, iMesVigencia, iAnioVigencia);
    tmpSeguroAutoCaCarmov.fechavencimiento.ponerFecha(iDiaVen, iMesVen, iAnioVen);
    tmpSeguroAutoCaCarmov.fechavencimientoanterior.ponerFecha(iDiaVAnt, iMesVAnt, iAnioVAnt);
    tmpSeguroAutoCaCarmov.fecha.ponerFecha(iDiaActual, iMesActual, iAnioActual);
    tmpSeguroAutoCaCarmov.efectuo = m_grid.lEmpleado;
    //autoSeguro.iFlagPoliza = (short) iFlagPoliza;

    if (iFlagPoliza == 1)
    {
        tmpSeguroAutoCaCarmov.factura = obtenerNumeroPoliza(1);
        tmpSeguroAutoCaCarmov.folioanterior = lPoliza;
        tmpSeguroAutoCaCarmov.idpoliza = consultarIdAseguradora(tmpSeguroAutoCaCarmov.factura);
    }
    else
    {
        tmpSeguroAutoCaCarmov.factura = lPoliza;
        tmpSeguroAutoCaCarmov.folioanterior = lPoliza;
        tmpSeguroAutoCaCarmov.idpoliza = consultarIdAseguradora(lPoliza);
    }

    if(sprintf_s(cTipovehiculo, "%d", iTipovehiculo) < 0){;}
    tmpSeguroAutoCaCarmov.tipovehiculo[0] = cTipovehiculo[0];
    tmpSeguroAutoCaCarmov.tipovehiculo[1] = 0;

    tmpSeguroAutoCaCarmov.fechaactivacioncancelar.ponerFecha(iDiaActi, iMesActi, iAnioActi);
    tmpSeguroAutoCaCarmov.polizaanteriorcancelar = lPolizaanteriorcancelar;
    tmpSeguroAutoCaCarmov.importeventacancelar = lImporteventacancelar;

    tmpSeguroAutoCaCarmov.clavelocal[0] = cLocal[0];
    tmpSeguroAutoCaCarmov.clavelocal[1] = 0;
    tmpSeguroAutoCaCarmov.fechaventacancelar.ponerFecha(iDiaVenta, iMesVenta, iAnioVenta);

    if (iSituacionEspecial == 1)
    {
        tmpSeguroAutoCaCarmov.clientelocalizar[0] = 'L';
        tmpSeguroAutoCaCarmov.clientelocalizar[1] = 0;
        iSituacionEspecial = 2;
    }
    else
    {
        tmpSeguroAutoCaCarmov.clientelocalizar[0] = '0';
        tmpSeguroAutoCaCarmov.clientelocalizar[1] = 0;
    }

    if(sprintf_s(tmpSeguroAutoCaCarmov.ipcarteracliente, "%s", cIpServidorCartera) < 0){;}
    tmpSeguroAutoCaCarmov.ipcarteracliente[16] = 0;

    tmpSeguroAutoCaCarmov.tarjeta = _atoi64(cTarjeta);

    if(sprintf_s(cNombreCompleto, "%s %s %s", sNombreCliente, sApellidoPaterno, sApellidoMaterno) < 0){;}
	if(memcpy_s(tmpSeguroAutoCaCarmov.nombrecliente, sizeof(tmpSeguroAutoCaCarmov.nombrecliente), cNombreCompleto, 45) < 0){;}
    tmpSeguroAutoCaCarmov.nombrecliente[44] = 0;

    tmpSeguroAutoCaCarmov.tipoproducto = (short)iTipoProducto;
    tmpSeguroAutoCaCarmov.minimototal = lMinimoTotal;
    tmpSeguroAutoCaCarmov.saldototal = lSaldoTotal;
    tmpSeguroAutoCaCarmov.vencidototal = lVencidoTotal;
    tmpSeguroAutoCaCarmov.minimototalfinal = lMinimoTotalFinal;
    tmpSeguroAutoCaCarmov.saldototalfinal = lSaldoTotalFinal;
    tmpSeguroAutoCaCarmov.vencidototalfinal = lVencidoTotalFinal;

    tmpSeguroAutoCaCarmov.prepararInsert("tmpseguroautocacarmov");
    if (tmpSeguroAutoCaCarmov.Insert())
    {
        tmpSeguroAutoCaCarmov.Commit();
    }
    else
    {
        sConsulta.Format("Error al Insertar en la Tabla TmpSeguroAutoCaCarmov");
        tmpSeguroAutoCaCarmov.odbc->GetLastError(tmpSeguroAutoCaCarmov.GetHstmt());
        grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "CDlgCapturarAbono", "tmpSeguroAutoCaCarmov", (LPTSTR)(LPCTSTR)sConsulta, m_grid.lEmpleado, "ERROR EN LA CONSULTA(CGrabarTmpSeguroAutoCaCarmov01)", tmpSeguroAutoCaCarmov.odbc, m_grid.iMuestraMsg);
        bContinuar = false;
    }

    return bContinuar;
}


bool CDlgCapturarAbono::grabarTmpSeguroAutoCaCarmov()
{
    bool bResultado = false;
    char cSql[55] = { 0 };

    grabarLog("grabarTmpSeguroAutoCaCarmov::grabando seguros de auto");

    if(sprintf_s(cSql, "SELECT cagrabartmpseguroautocacarmov('%ld')", lNumeroRecibo) < 0){;}

    CMaximo folioCoppel(&odbc, false);
    if (folioCoppel.Exec(cSql))
    {
        bResultado = true;
    }
    else
    {
        //Se obtiene el error
        folioCoppel.odbc->GetLastError(folioCoppel.GetHstmt());
    }
    return  bResultado;
}

bool CDlgCapturarAbono::grabarTmpCrSegurosAuto()
{
    bool bResultado = true;
    char cSql[220] = { 0 };

    grabarLog("grabarTmpCrSegurosAuto::grabando cuenta de seguros de auto en cartera");

    if(sprintf_s(cSql, "SELECT factura,fecha,fechavencimiento,importe,folioanterior, cantidadmeses, fechanacimiento FROM cacarmov "
        "WHERE recibo = %ld AND caja = %d AND clave = 'G' AND tiposeguro = '3' AND cliente = %ld", lNumeroRecibo, m_grid.iCaja, m_grid.lCliente) < 0){;}

    CConsultarAbonoSeguro2 consultarAbonoSeguro(&odbc, false);

    if (consultarAbonoSeguro.Exec(cSql))
    {
        consultarAbonoSeguro.activarCols();
        while (consultarAbonoSeguro.leer())
        {
            if (grabarCaSegurosAutoProteccion(consultarAbonoSeguro.factura, consultarAbonoSeguro.folioanterior, consultarAbonoSeguro.importe, consultarAbonoSeguro.cantidadmeses, consultarAbonoSeguro.fechavencimiento, consultarAbonoSeguro.fechanacimiento))
            {
                if(sprintf_s(cSql, "SELECT crgrabarabonoseguroauto('%ld', '%ld', '%04d%02d%02d', '%04d%02d%02d', '%ld', '%ld')", consultarAbonoSeguro.factura, m_grid.lCliente,
                    consultarAbonoSeguro.fecha.ano(), consultarAbonoSeguro.fecha.mes(), consultarAbonoSeguro.fecha.dia(),
                    consultarAbonoSeguro.fechavencimiento.ano(), consultarAbonoSeguro.fechavencimiento.mes(), consultarAbonoSeguro.fechavencimiento.dia(),
                    consultarAbonoSeguro.importe / 100, consultarAbonoSeguro.folioanterior) < 0){;}

                CMaximo ejecutarFuncion(&odbc_1, false);
                if (!ejecutarFuncion.Exec(cSql))
                {
                    ejecutarFuncion.odbc->GetLastError(ejecutarFuncion.GetHstmt());
                    bResultado = false;
                }
            }
            else
            {
                bResultado = false;
            }
        }
    }
    else
    {
        //Se obtiene el error
        consultarAbonoSeguro.odbc->GetLastError(consultarAbonoSeguro.GetHstmt());
        bResultado = false;
    }

    return bResultado;
}

void CDlgCapturarAbono::revizarImprimirPolizaSeguroAuto(int iTipoRecibo)
{
    char cSql[350] = { 0 };
    bool bImprimir = true;

    if(sprintf_s(cSql, "SELECT cliente,factura,digito,folioanterior FROM cacarmov WHERE cliente = %ld AND recibo = %ld AND caja = %d "
        "AND clave = 'G' AND tiposeguro = '3' order by factura", m_grid.lCliente, lNumeroRecibo, m_grid.iCaja) < 0){;}

    CConsultarPolizasNvas01 consultaPoliza(&odbc);
    if (consultaPoliza.Exec(cSql))
    {
        consultaPoliza.activarCols();
        while (consultaPoliza.leer())
        {
            if (iTipoRecibo == RECIBO_ABONO_POLIZAS)
            {
                if (bImprimir)
                {
                    imprimirPoliza(consultaPoliza.cliente, consultaPoliza.factura, consultaPoliza.digito, RECIBO_ABONO_POLIZAS);
                    bImprimir = false;
                    break;
                }
            }
            else if (iTipoRecibo == IMPRMIR_POLIZA_NUEVA)
            {
                if (consultaPoliza.factura != consultaPoliza.folioanterior)
                {
                    imprimirPoliza(consultaPoliza.cliente, consultaPoliza.factura, consultaPoliza.digito, IMPRMIR_POLIZA_NUEVA);
                }
            }
        }
    }
    else
    {
        consultaPoliza.odbc->GetLastError(consultaPoliza.GetHstmt());
        grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "revizarImprimirPolizaSeguroAuto", "CConsultarPolizasNvas", cSql, m_grid.lEmpleado, "ERROR EN LA CONSULTA(CGrabarTmpSeguroAutoCaCarmov01)", consultaPoliza.odbc, m_grid.iMuestraMsg);
    }

}

void CDlgCapturarAbono::imprimirPoliza(long lCliente, long lPoliza, int IdAseguradora, int iTipoRecibo)
{
    char cNombreProyecto[100] = { 0 }, cNombreFuncionDLL[10] = { 0 }, cInputParam1[1024] = { 0 }, cInputParam2[1024] = { 0 };

    SParametros parametros;
    SecureZeroMemory(&parametros, sizeof(SParametros));

    if(sprintf_s(parametros.sServer, "%s", m_grid.sServer) < 0){;}
    parametros.iTienda = m_grid.iTienda;
    parametros.iNumSistema = iSistema;
    parametros.lEmpleado = m_grid.lEmpleado;
    parametros.iCajaActual = m_grid.iCaja;
    parametros.iMuestraMsg = m_grid.iMuestraMsg;

    parametros.lCliente = lCliente;
    parametros.lFolioSeguro = lPoliza;
    parametros.lKeyX = IdAseguradora;
    parametros.iFlagServicio = iTipoRecibo;
    parametros.lFactura = lNumeroRecibo;

    //CapturarAbonoSeguroAuto
    nombreArchivo("CN0102.DLL", cNombreProyecto, DIRECTORIO_CN);
    if(sprintf_s(cNombreFuncionDLL, "CN0102") < 0){;}
	if(memcpy_s(cInputParam1, sizeof(cInputParam1), &parametros, sizeof(SParametros)) < 0){;}

    CargarDLL cargarDll(cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2);
    iRegresaDll = cargarDll.getResultado();

}

void CDlgCapturarAbono::ponerAcentoMayusculas(char *cCadena)
{
    int i = 0;
    CString sTexto;

    sTexto.Format("%s", cCadena);
    sTexto.Trim();

    for (i = 0; i < sTexto.GetLength(); i++)
    {
        switch (cCadena[i])
        {
        case 'á':
            cCadena[i] = ' ';
            break;
        case 'é':
            cCadena[i] = '‚';
            break;
        case 'í':
            cCadena[i] = '¡';
            break;
        case 'ó':
            cCadena[i] = '¢';
            break;
        case 'ú':
            cCadena[i] = '£';
            break;
        case 'ñ':
            cCadena[i] = '¤';
            break;
        case 'Ñ':
            cCadena[i] = '¥';
            break;
        case '/':
            cCadena[i] = ' ';
            break;
        case 'Á':
            cCadena[i] = 'A';
            break;
        case 'É':
            cCadena[i] = 'E';
            break;
        case 'Í':
            cCadena[i] = 'I';
            break;
        case 'Ó':
            cCadena[i] = 'O';
            break;
        case 'Ú':
            cCadena[i] = 'U';
            break;
        }
    }
}

long CDlgCapturarAbono::consultarIdAseguradora(long lFolio)
{
    long lIdAutoSeguro = 0;
    char cIPServidorSolicitudes[20] = { 0 }, cIPServidorSolicitudesAlterno[20] = { 0 }, cSql[255] = { 0 };

    if (consultarIpServidores(&odbc, cIPServidorSolicitudes, cIPServidorSolicitudesAlterno, SERV_SOLICITUDES, cSql, false))
    {
        if (abrirConexionBD(&odbcSolicitudes, cIPServidorSolicitudes, cIPServidorSolicitudesAlterno, CONECTA_SOLICITUDES, iTiendaDlg))
        {
            if(sprintf_s(cSql, "SELECT gnobtenerIdAseguradora('1');", lFolio) < 0){;}

            CMaximo consultarId(&odbcSolicitudes, false); //conexión a tienda.nnnn
            if (consultarId.Exec(cSql))
            {
                consultarId.activarCols();
                if (consultarId.Leer())
                {
                    lIdAutoSeguro = consultarId.Total;
                }
            }
            else
            {
                consultarId.odbc->GetLastError(consultarId.GetHstmt());
                grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CA0030", "CDlgCapturarAbono", "consultarIdAseguradora", cSql, m_grid.lEmpleado, "ERROR #10937", consultarId.odbc, m_grid.iMuestraMsg);
            }
        }
        odbcSolicitudes.Close();
    }

    return lIdAutoSeguro;
}

long CDlgCapturarAbono::obtenerNumeroPoliza(int iModo)
{
    bool bContinuar = false;
    long lPoliza = 0;
    char cTexto[11] = { 0 }, cCad[11] = { 0 };
    char cIPServidorSolicitudes[20] = { 0 }, cIPServidorSolicitudesAlterno[20] = { 0 }, cSql[255] = { 0 };

    if (consultarIpServidores(&odbc, cIPServidorSolicitudes, cIPServidorSolicitudesAlterno, SERV_SOLICITUDES, cSql, false))
    {
        if (abrirConexionBD(&odbcSolicitudes, cIPServidorSolicitudes, cIPServidorSolicitudesAlterno, CONECTA_SOLICITUDES, iTiendaDlg))
        {
            if(sprintf_s(cSql, "SELECT gnobtenerpoliza('%d')", iModo) < 0){;}

            CSysFolioGlobal  obtenerNumeroPoliza(&odbcSolicitudes);
            if (obtenerNumeroPoliza.Exec(cSql))
            {
                obtenerNumeroPoliza.activarCols();
                if (obtenerNumeroPoliza.Leer())
                {
                    if(sprintf_s(cTexto, "%I64d", obtenerNumeroPoliza.folio) < 0){;}
					if(memcpy_s(cCad, sizeof(cCad), &cTexto[4], 6) < 0){;}
                    lPoliza = strtol(cCad, NULL, 10);
                }
            }
            else
            {
                obtenerNumeroPoliza.odbc->GetLastError(obtenerNumeroPoliza.GetHstmt());
                grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CA0030", "CDlgCapturarAbono", "obtenerNumeroPoliza", cSql, m_grid.lEmpleado, "ERROR #10937", obtenerNumeroPoliza.odbc, m_grid.iMuestraMsg);
            }
        }
        odbcSolicitudes.Close();
    }
    return lPoliza;
}

__int64 CDlgCapturarAbono::buscarFolionuevo(__int64 lFacturaX, long lCliente, long lNumeroRecibo)
{
    char cSql[350] = { 0 };
    long lFolio = 0;
    char cCadena01[15] = { 0 }, cCadena02[15] = { 0 };
    __int64 l64Regresa = 0;

    if(sprintf_s(cCadena01, "%I64d", lFacturaX) < 0){;}
	if(memcpy_s(cCadena02, sizeof(cCadena02), &cCadena01[4], 6) < 0){;}
    lFolio = strtol(cCadena02, NULL, 10);

    if(sprintf_s(cSql, "SELECT cliente,factura,digito FROM cacarmov WHERE cliente = %ld AND recibo = %ld AND caja = %d "
        "AND factura <> folioanterior AND clave = 'G' AND tiposeguro = '3' AND  folioanterior = %ld ORDER BY factura", lCliente, lNumeroRecibo, m_grid.iCaja, lFolio) < 0){;}

    CConsultarPolizasNvas01 consultaPoliza(&odbc);
    if (consultaPoliza.Exec(cSql))
    {
        consultaPoliza.activarCols();
        if (consultaPoliza.leer())
        {
            SecureZeroMemory(cCadena01, sizeof(cCadena01));
            if(sprintf_s(cCadena01, "%04ld%06ld", consultaPoliza.digito, consultaPoliza.factura) < 0){;}
            l64Regresa = _atoi64(cCadena01);
        }
    }
    else
    {
        consultaPoliza.odbc->GetLastError(consultaPoliza.GetHstmt());
        grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "CDlgCapturarAbono", "buscarFolionuevo", cSql, m_grid.lEmpleado, "ERROR EN LA CONSULTA(obtenerplazo)", consultaPoliza.odbc, m_grid.iMuestraMsg);
    }

    return l64Regresa;
}


__int64 CDlgCapturarAbono::obtenerPolizaXML(long lPoliza)
{
    char cSql[350] = { 0 };
    long lFolio = 0;
    char cCadena01[15] = { 0 }, cCadena02[15] = { 0 };
    __int64 l64Regresa = 0;


    if(sprintf_s(cSql, "SELECT substring(unnest(cast(xpath('/Movimientos/Movimiento/@NoPoliza', (CONVERT_FROM((CONVERT(xml::bytea,'LATIN1','UTF8')),'SQL_ASCII')::character varying)::xml) as text)::text[]),3,10) FROM ctlcrseguroauto c where c.poliza = %10ld", lPoliza) < 0){;}

    CConsultarPolizaXML consultaPolizasXML(&odbc_1, false);
    if (consultaPolizasXML.Exec(cSql))
    {
        consultaPolizasXML.activarCols();
        if (consultaPolizasXML.leer())
        {

            l64Regresa = _atoi64(consultaPolizasXML.resultado);
        }
    }
    else
    {
        consultaPolizasXML.odbc->GetLastError(consultaPolizasXML.GetHstmt());
        grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "CDlgCapturarAbono", "buscarPolizaXML", cSql, m_grid.lEmpleado, "ERROR EN LA CONSULTA(buscarPolizaXML)", consultaPolizasXML.odbc, m_grid.iMuestraMsg);
    }

    return l64Regresa;
}

bool CDlgCapturarAbono::obtenerDatosSeguroAuto(char *cMensaje, long lFactura, long lFolioAnterior, int iImporte)
{
    bool bContinuar = false;
    char cSql[1800] = { 0 };
    char cTexto[11] = { 0 };
    char cSqlCad01[35] = { 0 };
    char cSqlCad02[35] = { 0 };
    CString sTexto, sDato;

    if (lFactura != lFolioAnterior)
    {
        sDato.Format("%04ld%06ld", consultarIdAseguradora(lFactura), lFolioAnterior);
        autoSeguro.iPolizaAnterior = _atoi64(sDato);

        sDato.Format("%04ld%06ld", consultarIdAseguradora(lFactura), lFactura);
        autoSeguro.iPolizaCompleta = _atoi64(sDato);

        autoSeguro.iFlagPoliza = 1;

        autoSeguro.lPoliza = lFolioAnterior;
        if(sprintf_s(cSqlCad01, "fechaalta <= '%04d%02d%02d'", iAnioActual, iMesActual, iDiaActual) < 0){;}
        if(sprintf_s(cSqlCad02, "y.fechaalta <= '%04d%02d%02d'", iAnioActual, iMesActual, iDiaActual) < 0){;}
    }
    else
    {
        autoSeguro.lPoliza = lFactura;
        lFolioAnterior = lFactura;

        autoSeguro.iFlagPoliza = 0;

        sDato.Format("%04ld%06ld", consultarIdAseguradora(lFactura), lFactura);
        autoSeguro.iPolizaCompleta = _atoi64(sDato);
        autoSeguro.iPolizaAnterior = _atoi64(sDato);
        autoSeguro.lPoliza = lFactura;
        if(sprintf_s(cSqlCad01, "fechaalta <= fechaventa") < 0){;}
        if(sprintf_s(cSqlCad02, "y.fechaalta <= fechaventa") < 0){;}
    }

    if(sprintf_s(cSql, "SELECT fechaventa,fechaactivacion,fechavencimiento,tipocobertura,placas AS placas, numerodeserie, modelo, x.tipovehiculo, tipouso, primaneta, "
        "udi, excedente, derechodepoliza, primaantesdeiva, primatotal, primanetaanual, excedenteanual,derechopolizaanual, "
        "primaantesdeivaanual, primatotalanual, x.fechaalta, udidespuesdeiva, excedentedespuesdeiva, derechodepolizadespuesdeiva, "
        "udianual, udidespuesdeivaanual, excedentedespuesdeivaanual, derechodepolizadespuesdeivaanual,claveamis, "
        "danosaterceros, gastosmedicosauto, gastosmedicoscamioneta, asistencialegal, gastosdeasistencialegal, "
        "marca,submarca, v.descripcionmarca, w.descripcionlinea "
        "FROM "
        "(SELECT fechaventa,fechaactivacion,fechavencimiento,a.tipocobertura,placas AS placas, numerodeserie, modelo, a.tipovehiculo, tipouso, primaneta, "
        "udi, excedente, derechodepoliza, primaantesdeiva, primatotal, primanetaanual, excedenteanual,derechopolizaanual, "
        "primaantesdeivaanual, primatotalanual, fechaalta, udidespuesdeiva, excedentedespuesdeiva, derechodepolizadespuesdeiva, "
        "udianual, udidespuesdeivaanual, excedentedespuesdeivaanual, derechodepolizadespuesdeivaanual,claveamis, marca, submarca "
        "FROM crsegurosauto AS A inner join "
        "crcostosautoseguro as B ON a.tipocobertura = b.tiposeguro AND a.tipovehiculo = b.tipovehiculo  AND a.ciudad = b.ciudad "
        "WHERE a.cliente = %d AND a.poliza = %d AND %s ORDER by fechaalta DESC limit 1) "
        "AS X inner  join crtiposeguro as y ON x.tipocobertura = y.tiposeguro "
        "INNER JOIN crmarcasvehiculo AS V ON v.clavemarca = x.marca "
        "INNER JOIN crlineasvehiculo AS W ON w.clavelinea = x.submarca "
        "WHERE %s ORDER by fechaalta DESC limit 1;",
        m_grid.lCliente, autoSeguro.lPoliza, cSqlCad01, cSqlCad02) < 0){;}

    CObtenerDatosSeguroAuto obtenerSeguro(&odbc_1, false);

    if (obtenerSeguro.Exec(cSql))
    {
        obtenerSeguro.activarCols();
        if (obtenerSeguro.Leer())
        {
            if (obtenerSeguro.primatotal > 0)
            {
                if (autoSeguro.iFlagPoliza != 1)
                {
                    if(sprintf_s(sFechaActivacion, "%04ld%02ld%02ld", obtenerSeguro.fechaactivacion.ano(), obtenerSeguro.fechaactivacion.mes(), obtenerSeguro.fechaactivacion.dia()) < 0){;}
                }
                if(sprintf_s(sFechaVencimientoAnterior, "%04d%02d%02d", obtenerSeguro.fechavencimiento.ano(), obtenerSeguro.fechavencimiento.mes(), obtenerSeguro.fechavencimiento.dia()) < 0){;}
                autoSeguro.lPrimaNeta = obtenerSeguro.primaneta;
                autoSeguro.lExcedente = obtenerSeguro.excedente;
                autoSeguro.lDerechoDePoliza = obtenerSeguro.derechodepoliza;
                autoSeguro.lPrimaTotal = obtenerSeguro.primatotal;
                autoSeguro.lPrimaAntesDeIva = obtenerSeguro.primaantesdeiva;
                autoSeguro.lUdi = obtenerSeguro.udi;
                autoSeguro.lUdiDespuesDeIva = obtenerSeguro.udidespuesdeiva;
                autoSeguro.lExcedenteDespuesDeIva = obtenerSeguro.excedentedespuesdeiva;
                autoSeguro.lDerechoDePolizaDespuesDeIva = obtenerSeguro.derechodepolizadespuesdeiva;
                autoSeguro.lPrimaNetaAnual = obtenerSeguro.primanetaanual;
                autoSeguro.lPrimaAntesDeIvaAnual = obtenerSeguro.primaantesdeivaanual;
                autoSeguro.lUdiaAnual = obtenerSeguro.udianual;
                autoSeguro.lUdiDespuesDeIvaAnual = obtenerSeguro.udidespuesdeivaanual;
                autoSeguro.lExcedenteAnual = obtenerSeguro.excedenteanual;
                autoSeguro.lExcedenteDespuesDeIvaAnual = obtenerSeguro.excedentedespuesdeivaanual;
                autoSeguro.lDerechoPolizaAnual = obtenerSeguro.derechopolizaanual;
                autoSeguro.lDerechoDePolizaDespuesDeIvaAnual = obtenerSeguro.derechodepolizadespuesdeivaanual;
                autoSeguro.lPrimaTotalAnual = obtenerSeguro.primatotalanual;
                sTexto.Format("%s", obtenerSeguro.claveamis);
                sTexto.Trim();
                if(sprintf_s(autoSeguro.cClaveAmis, "%s", sTexto) < 0){;}
                autoSeguro.lSuPago = iImporte;

                sTexto.Format("%s", obtenerSeguro.placas);
                sTexto.Trim();
                if(sprintf_s(autoSeguro.cPlaca, "%s", sTexto) < 0){;}
                autoSeguro.cPlaca[10] = 0;

                sTexto.Format("%s", obtenerSeguro.numerodeserie);
                sTexto.Trim();
                if(sprintf_s(autoSeguro.cNumSerie, "%s", sTexto) < 0){;}
                autoSeguro.cNumSerie[20] = 0;

                autoSeguro.iModelo = obtenerSeguro.modelo;
                autoSeguro.iMarca = obtenerSeguro.marca;
                autoSeguro.iLinea = obtenerSeguro.submarca;

                sTexto.Format("%s", obtenerSeguro.descripcionmarca);
                sTexto.Trim();
                if(sprintf_s(autoSeguro.cDescripcionMarca, "%s", sTexto) < 0){;}
                autoSeguro.cDescripcionMarca[24] = 0;

                sTexto.Format("%s", obtenerSeguro.descripcionlinea);
                sTexto.Trim();
                if(sprintf_s(autoSeguro.cDescripcionLinea, "%s", sTexto) < 0){;}
                autoSeguro.cDescripcionLinea[34] = 0;

                autoSeguro.iTipoVehiculo = obtenerSeguro.tipovehiculo;
                autoSeguro.iTipoUso = obtenerSeguro.tipouso;

                autoSeguro.iDaniosTerceros = obtenerSeguro.danosaterceros;

                if (autoSeguro.iTipoVehiculo == 1)
                {
                    autoSeguro.iGastosMedicos = obtenerSeguro.gastosmedicosauto;
                }
                else
                {
                    autoSeguro.iGastosMedicos = obtenerSeguro.gastosmedicoscamioneta;
                }
                sTexto.Format("%s", obtenerSeguro.asistencialegal);
                sTexto.Trim();
                if(sprintf_s(autoSeguro.cAsistenciaLegal, "%s", sTexto) < 0){;}
                autoSeguro.cAsistenciaLegal[15] = 0;

                autoSeguro.iGastosDeAsistenciaLegal = obtenerSeguro.gastosdeasistencialegal;

                autoSeguro.iTipoCobertura = obtenerSeguro.tipocobertura;

                bContinuar = true;
            }
            else
            {
				if(memcpy_s(cMensaje, strnlen(cMensaje, 130), "No el Costo del Seguro debe ser mayor que cero.", 47) < 0){;}
            }
        }
        else
        {
			if(memcpy_s(cMensaje, strnlen(cMensaje, 130), "No se encontro el Costo del Seguro en la cartera.", 48) < 0){;}
        }
    }
    else
    {
        obtenerSeguro.odbc->GetLastError(obtenerSeguro.GetHstmt());
        grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "CDlgCapturarAbono", "buscarFolionuevo", cSql, m_grid.lEmpleado, "ERROR EN LA CONSULTA(obtenerDatosSeguroAuto)", obtenerSeguro.odbc, m_grid.iMuestraMsg);
        bContinuar = false;
    }

    return bContinuar;
}

bool CDlgCapturarAbono::grabarCaSegurosAutoProteccion(long lFactura, long lFolioAnterior, int iImporte, int iCantidadMeses, SqlTimeStamp fechavencimiento, SqlTimeStamp fechaactivacion)
{
    bool bResultado = false;
    char cMensaje[130] = { 0 }, cSql[1000] = { 0 };

    if(sprintf_s(sFechaVencimiento, "%04ld%02ld%02ld", fechavencimiento.ano(), fechavencimiento.mes(), fechavencimiento.dia()) < 0){;}
    if(sprintf_s(sFechaActivacion, "%04ld%02ld%02ld", fechaactivacion.ano(), fechaactivacion.mes(), fechaactivacion.dia()) < 0){;}

    if (obtenerDatosSeguroAuto(cMensaje, lFactura, lFolioAnterior, iImporte))
    {
        if(sprintf_s(cSql, "SELECT cagrabarventaseguroauto( '%ld', '%d', '%d', '%d', '%ld', "
            "'%d', '%ld', '%d', '%d', '%d', "
            "'%d', '%d', '%d','%s','%s', '%s', '%s', "
            "'%04d-%02d-%02d', '%I64d', '%c', '%ld', '%ld', '%ld', '%ld', '%ld', '%ld', '%ld', "
            "'%ld', '%ld', '%ld', '%ld', '%ld', '%ld', '%ld', '%ld', '%ld', '%ld', '%ld', '%s', '%s', '%s', '%s', '%I64d', '%ld', "
            "'%I64d','%I64d','%d');",
            m_grid.lCliente, m_grid.iTienda, (short)iCiudadGnDominio, m_grid.iCaja, (autoSeguro.lSuPago / 100),
            iCantidadMeses, m_grid.lEmpleado, autoSeguro.iTipoCobertura, autoSeguro.iTipoVehiculo, autoSeguro.iTipoUso,
            autoSeguro.iModelo, autoSeguro.iMarca, autoSeguro.iLinea, autoSeguro.cDescripcionMarca, autoSeguro.cDescripcionLinea,
            autoSeguro.cNumSerie, autoSeguro.cPlaca,
            iAnioActual, iMesActual, iDiaActual, autoSeguro.iPolizaCompleta, m_grid.cArea, autoSeguro.lPrimaNeta,
            autoSeguro.lPrimaAntesDeIva, autoSeguro.lUdi, autoSeguro.lUdiDespuesDeIva, autoSeguro.lExcedente,
            autoSeguro.lExcedenteDespuesDeIva, autoSeguro.lDerechoDePoliza, autoSeguro.lDerechoDePolizaDespuesDeIva,
            autoSeguro.lPrimaTotal, autoSeguro.lPrimaNetaAnual, autoSeguro.lPrimaAntesDeIvaAnual, autoSeguro.lUdiaAnual,
            autoSeguro.lUdiDespuesDeIvaAnual, autoSeguro.lExcedenteAnual, autoSeguro.lExcedenteDespuesDeIvaAnual,
            autoSeguro.lDerechoPolizaAnual, autoSeguro.lDerechoDePolizaDespuesDeIvaAnual, autoSeguro.lPrimaTotalAnual,
            autoSeguro.cClaveAmis, sFechaActivacion, sFechaVencimiento, sFechaVencimientoAnterior, autoSeguro.iPolizaAnterior, lNumeroRecibo,
            autoSeguro.iDaniosTerceros, autoSeguro.iGastosMedicos, autoSeguro.iGastosDeAsistenciaLegal) < 0){;}

        CMaximo gabarSeguroAutoTienda(&odbc, false);
        if (gabarSeguroAutoTienda.Exec(cSql))
        {
            gabarSeguroAutoTienda.activarCols();
            if (gabarSeguroAutoTienda.Leer())
            {
                autoSeguro.lRecibo = gabarSeguroAutoTienda.Total;
                bResultado = true;
            }
        }
        else
        {
            gabarSeguroAutoTienda.odbc->GetLastError(gabarSeguroAutoTienda.GetHstmt());
            bResultado = false;
        }
    }

    return bResultado;
}