// DlgCapturarCambioSeguro.cpp : implementation file
//

#include "stdafx.h"
#include "sysCapturarAbono.h"
#include "CapturarAbono.h"
#include "DlgCapturarCambioSeguro.h"
#include "CConsultarCrSegurosClubAdicional.hpp"
#include "CGrabarTmpCaCarmovSeguro.hpp"
#include "CConsultarPrecioSeguroClub.hpp"
#include "CargarDLL.h"
#include "DlgCapturarDatosSeguro.h"

// DlgCapturarCambioSeguro dialog


IMPLEMENT_DYNAMIC(CDlgCapturarCambioSeguro, CDialog2012)
CDlgCapturarCambioSeguro::CDlgCapturarCambioSeguro(CWnd* pParent /*=NULL*/)
    : CDialog2012(CDlgCapturarCambioSeguro::IDD, pParent)
{
    iEdadMaximaAbonoClubAdic = iSegurosAdicionales = 0;
    iAnioNacimientoTitular = iMesNacimientoTitular = iDiaNacimientoTitular = iAnioVencimiento = iMesVencimiento = iDiaVencimiento = iCiudad = 
		iTienda = iDiaNacimiento = iAnioActual = iDiaActual = 0;
    SecureZeroMemory(cNombreCliente, sizeof(cNombreCliente));
    SecureZeroMemory(cSexo, sizeof(cSexo));
    lFolioSeguro = 0;
    iProcesoBeneficiariosAdicionales = 0;
}

CDlgCapturarCambioSeguro::~CDlgCapturarCambioSeguro()
{
	lCliente = 0;
	iCaja = 0;
	lEmpleado = 0;
	iMuestraMsg = 0;
	iAnioActual = 0;
	iMesActual = 0;
	iDiaActual = 0;
	iEdadMaximaAbonoClubAdic = 0;
	iTienda = 0;
	iCiudad = 0;
	iSegurosAdicionales = 0;
	lFolioSeguro = 0;
	iAnioNacimientoTitular = 0;
	iMesNacimientoTitular = 0;
	iDiaNacimientoTitular = 0;
	iAnioVencimiento = 0;
	iMesVencimiento = 0;
	iDiaVencimiento = 0;
}

void CDlgCapturarCambioSeguro::DoDataExchange(CDataExchange* pDX)
{
    CDialog2012::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SEGUROS, m_seguros);
    DDX_Control(pDX, IDC_ASEGURADOS, m_asegurados);
    DDX_Control(pDX, IDC_SEGUROS2, m_seguros2);
    DDX_Control(pDX, IDC_FECHANACIMIENTOADIC, m_fechaNacimientoAdic);
}

BEGIN_MESSAGE_MAP(CDlgCapturarCambioSeguro, CDialog2012)
    ON_EN_SETFOCUS(IDC_ASEGURADOS, OnEnSetfocusAsegurados)
    ON_EN_SETFOCUS(IDC_SEGUROS, OnEnSetfocusSeguros)
    ON_BN_CLICKED(IDC_CANCELAR, OnBnClickedCancelar)
    ON_BN_CLICKED(IDC_ACEPTAR, OnBnClickedAceptar)
    ON_CBN_SELCHANGE(IDC_ASEGURADOS, OnCbnSelchangeAsegurados)
END_MESSAGE_MAP()

// DlgCapturarCambioSeguro message handlers

void CDlgCapturarCambioSeguro::OnEnSetfocusAsegurados()
{
    // TODO: Add your control notification handler code here
    validarClick(0);
}

void CDlgCapturarCambioSeguro::OnEnSetfocusSeguros()
{
    // TODO: Add your control notification handler code here
    validarClick(1);
}

BOOL CDlgCapturarCambioSeguro::OnInitDialog()
{
    CDialog2012::OnInitDialog();
    char cTexto[80] = { 0 };
    int iHuellaAutorizado = 0;

    // TODO:  Add extra initialization here
    m_seguros.SetLimitText(1);
    m_asegurados.Clear();
    m_seguros2.Clear();
    m_fechaNacimientoAdic.Clear();
    iFoco = 0;
    iControles = 2;
    iNumSeguros = 0;
    lPrecioSeguroClub = 0;
    iCantidadMaxSegurosCte = 0;

    if (obtenerAdicionales())
    {
        if (m_asegurados.GetCount() > 0)
        {
            CDlgCapturarDatosSeguro dlg;
            iHuellaAutorizado = dlg.checarHuellaChw(lCliente, iCaja, lEmpleado, iMuestraMsg);
            if (iHuellaAutorizado > 0)
            {
                crearMensaje(this, m_barra, m_mensaje);
				if(sprintf_s(cTexto, sizeof(cTexto), " [ ESC ] Cancelar  [F10] Aceptar ") < 0){;}
                ponerMensaje(this, m_barra, m_mensaje, cTexto);
            }
            else
            {
                CDialog2012::OnCancel();
            }
        }
        else
        {
            AfxMessageBox("CLIENTE NO CUENTA CON CLUB ADICIONAL");
            CDialog2012::OnCancel();
        }
    }
    else
    {
        CDialog2012::OnCancel();
    }

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgCapturarCambioSeguro::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    char cPaso[255] = { 0 };

    ShiftTab = false;
    if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
    {
        if (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_UP)
        {
            iFoco--;
            if (iFoco < 0)
                iFoco = 0;
            asignarFoco();
        }
        if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB || pMsg->wParam == VK_DOWN || pMsg->wParam == VK_RIGHT)
        {
            if (iFoco <= iControles) //numero de controles
            {
                if (pMsg->wParam != VK_DOWN || iFoco != 0)
                {
                    if (validarControl(cPaso))
                    {
                        iFoco++;

                        if (iFoco == 2)
                            iFoco = 1;

                        asignarFoco();
                    }
                    else
                    {
                        if (!ShiftTab)
                        {
                            AfxMessageBox(cPaso);
                        }
                    }
                    return TRUE;
                }
            }
            else
            {
                if (pMsg->wParam != VK_RETURN)
                {
                    iFoco++;
                    asignarFoco();
                }
                else
                {
                    asignarFoco();
                }
                return TRUE;
            }
        }
        else
        {
            if (pMsg->wParam == VK_TAB && GetKeyState(VK_SHIFT) & 0x8000)
            {
                ShiftTab = true;
            }
            else
            {
                switch (pMsg->wParam)
                {
                case VK_F10:
                    iFlagCancelo = 1;
                    OnBnClickedAceptar();
                    pMsg->wParam = NULL;
                    break;
                case VK_ESCAPE:
                    iFlagCancelo = 0;
                    CDialog2012::OnCancel();
                    pMsg->wParam = NULL;
                    break;
                case VK_RIGHT:
                    iFoco++;
                    if (iFoco > 1)
                        iFoco = 0;
                    asignarFoco();
                    break;
                default:
                    break;
                }
            }
        }
    }
    return CDialog2012::PreTranslateMessage(pMsg);
}

void CDlgCapturarCambioSeguro::asignarFoco()
{
    switch (iFoco)
    {
    case 0:
        m_asegurados.SetFocus();
        break;
    case 1:
        m_seguros.SetFocus();
        break;
    default:
        break;
    }
}

bool CDlgCapturarCambioSeguro::validarControl(char * cCadena)
{
    bool valorRegresa = true;
    CString sTexto = "";

    switch (iFoco)
    {
    case 0:
        m_asegurados.GetWindowText(sTexto);
        sTexto.Trim();
        if (sTexto.IsEmpty())
        {
			if(sprintf_s(cCadena, 255, "%s", "FAVOR DE CAPTURAR ASEGURADO ") < 0){;}
            valorRegresa = false;
        }
        else
        {
            iFlagCancelo = 1;
        }
        break;
    default:
        break;
    case 1:
        m_seguros.GetWindowText(sTexto);
        sTexto.Trim();
        iNumSeguros = strtol(sTexto, NULL, 10);
        if (sTexto.IsEmpty())
        {
			if(sprintf_s(cCadena, 255, "%s", " FAVOR DE CAPTURAR NÚMERO DE SEGUROS ") < 0){;}
            iNumSeguros = 0;
            m_seguros.SetSel(0, 1);
            valorRegresa = false;
        }
        else
        {
            if (iNumSeguros < 1)
            {
				if(sprintf_s(cCadena, 255, "%s", " NÚMERO DE SEGUROS INCORRECTO ") < 0){;}
                iNumSeguros = 0;
                m_seguros.SetSel(0, 1);
                valorRegresa = false;
            }

            if (valorRegresa)
            {
                grabarLog("Consulta Precio seguro 13");
                consultarPrecioSeguroClub();
                if (iNumSeguros > iCantidadMaxSegurosCte)
                {
					if(sprintf_s(cCadena, 255, "EL CLIENTE ADICIONAL, POR SU RANGO DE EDAD, SOLO PUEDE COMPRAR HASTA %d SEGUROS", iCantidadMaxSegurosCte) < 0){;}
                    iNumSeguros = 0;
                    m_seguros.SetSel(0, 1);
                    valorRegresa = false;
                }
            }
        }
        break;
    }
    return valorRegresa;
}

bool CDlgCapturarCambioSeguro::validarControles()
{
    bool bValorRegresa = false;
    int i, iFocoAnt;
    bool bandera = true;
    char cPaso[255] = { 0 };

    iFocoAnt = iFoco;

    for (i = 0; i < iControles; i++)
    {
        iFoco = i;
        bandera = validarControl(cPaso);
        if (!bandera)
        {
            AfxMessageBox(cPaso);
            asignarFoco();
            break;
        }
    }

    if (bandera)
    {
        bValorRegresa = true;
    }

    iFoco = iFocoAnt;
    asignarFoco();
    return bValorRegresa;
}

void CDlgCapturarCambioSeguro::fechaNacimiento()
{
    iEdad = (int)iAnioActual - iAnioNacimiento;
    if (iMesActual < iMesNacimiento || (iMesActual == iMesNacimiento && iDiaActual < iDiaNacimiento))
    {
        iEdad--;
    }
}

bool CDlgCapturarCambioSeguro::validarClick(int nTmpFocus)
{
    int nElementoTmp, i;
    bool regresa = true;
    char cPaso[255] = { 0 };

    if (iFoco < nTmpFocus)
    {
        // validar control anterior
        if (!validarControl(cPaso))
        {
            asignarFoco();
            if (iFoco != iControles)//numero de controles para los que se quieren se vea el mebsaje de error
            {
                if (!ShiftTab)
                {
                    AfxMessageBox(cPaso);
                }
            }
            regresa = false;
        }
        else
        {
            nElementoTmp = iFoco;
            iFoco = nTmpFocus;
            for (i = 0; i <= nTmpFocus; i++)
            {
                iFoco = i;
                //valida hacia abajo los controles
                if (!validarControl(cPaso))
                {
                    break;
                }
            }
            asignarFoco();
        }
    }
    else
    {
        iFoco = nTmpFocus;
    }
    return regresa;
}

void CDlgCapturarCambioSeguro::OnBnClickedCancelar()
{
    // TODO: Add your control notification handler code here
    CDialog2012::OnCancel();
}

void CDlgCapturarCambioSeguro::OnBnClickedAceptar()
{
    // TODO: Add your control notification handler code here
    CString sTexto;
    if (validarControles())
    {

        actualizarSeguros();
        if (iProcesoBeneficiariosAdicionales >= 1)
        {
            sTexto.Format("¿DESEA REALIZAR OTRO CAMBIO?");
            if (AfxMessageBox(sTexto, MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                m_seguros.SetWindowText("");
                m_asegurados.SetCurSel(CB_ERR);
                iFoco = 0;
                m_asegurados.SetFocus();
            }
            else
            {
                CDialog2012::OnCancel();
            }
        }
        else
        {
            CDialog2012::OnCancel();
        }

    }
}

bool CDlgCapturarCambioSeguro::obtenerAdicionales()
{
    bool bRegresa = true;
    char cTexto[55] = { 0 }, cSql[340] = { 0 };
    short iEdadAdicional = 0;

	if(sprintf_s(cSql, sizeof(cSql), "SELECT folio,cantidadseguros,TRIM(nombreadicional) AS nombreadicional,TRIM(apellidopaternoadic) AS apellidopaternoadic,TRIM(apellidomaternoadic) AS apellidomaternoadic,fecnacadic,parentescoadic FROM crseguros WHERE cliente = %ld AND tiposeguro=2 AND claveconyugal = 1 AND claveseguro='C' AND statusseguro='A' ORDER BY folio;", lCliente) < 0){;}

    CConsultarCrSegurosClubAdicional crSegurosSQL(&odbc_1);
    if (crSegurosSQL.Exec(cSql))
    {
        crSegurosSQL.activarCols();
        while (crSegurosSQL.Leer())
        {
            //Se calcula la edad del adicional
            iEdadAdicional = (short)(iAnioActual - crSegurosSQL.fecnacadic.ano());
            if (iMesActual < crSegurosSQL.fecnacadic.mes() || (iMesActual == crSegurosSQL.fecnacadic.mes() && iDiaActual < crSegurosSQL.fecnacadic.dia()))
            {
                iEdadAdicional--;
            }

            if (iEdadAdicional <= iEdadMaximaAbonoClubAdic)
            {
				if(sprintf_s(cTexto, sizeof(cTexto), "%s %s %s", crSegurosSQL.nombreadicional, crSegurosSQL.apellidopaternoadic, crSegurosSQL.apellidomaternoadic) < 0){;}
                m_asegurados.AddString(cTexto);
				if(sprintf_s(cTexto, sizeof(cTexto), "%d%d", crSegurosSQL.cantidadseguros, crSegurosSQL.folio) < 0){;}
                m_seguros2.AddString(cTexto);
				if(sprintf_s(cTexto, sizeof(cTexto), "%04d%02d%02d", crSegurosSQL.fecnacadic.ano(), crSegurosSQL.fecnacadic.mes(), crSegurosSQL.fecnacadic.dia()) < 0){;}
                m_fechaNacimientoAdic.AddString(cTexto);
            }
        }
    }
    else
    {
        bRegresa = false;
        crSegurosSQL.odbc->GetLastError(crSegurosSQL.GetHstmt());
    }
    return bRegresa;
}

void CDlgCapturarCambioSeguro::actualizarSeguros()
{
    CString sTexto = "";
    m_seguros.GetWindowText(sTexto);
    iNumSeguros = strtol(sTexto, NULL, 10);
    grabarLog("CDlgCapturarCambioSeguro::actualizarSeguros(), Actualiza seguros");
    grabarLog("Consulta Precio seguro 14");
    if (consultarPrecioSeguroClub())
    {
        if (iNumSeguros > 0 && iNumeroSegurosAnterior > 0 && iNumSeguros != iNumeroSegurosAnterior)//Realizó un cambio de plan
        {
            char cNombreProyecto[256] = { 0 }, cNombreFuncionDLL[256] = { 0 }, cInputParam1[1024] = { 0 }, cInputParam2[1024] = { 0 },
                cOutputParam1[1024] = { 0 }, cOutputParam2[1024] = { 0 }, cSql[200] = { 0 }, cMensaje[200] = { 0 };
            int iRegresaDll = 0;
            SParametros parametros;
            EstructuraCliente parametrosAdicional;

            SecureZeroMemory(&parametros, sizeof(SParametros));
            SecureZeroMemory(&parametrosAdicional, sizeof(EstructuraCliente));

            parametros.iLink = generarLink();
			if(sprintf_s(parametros.sServer, sizeof(parametros.sServer), odbc.m_strServer) < 0 ){;}
            parametros.iTienda = iTienda;
            parametros.lEmpleado = lEmpleado;
            parametros.iCajaActual = iCaja;
            parametros.iMuestraMsg = iMuestraMsg;
            parametros.iNumSistema = SISTEMA_CAJAS;
            parametros.lCliente = lCliente;
            parametros.iCiudad = iCiudad;
            parametros.iFlagGeneral = iSegurosAdicionales; //Para saber cuantos adicionales tiene el cliente
            parametros.lFactura = iFolio;
            parametros.iTipo = iNumSeguros;

            parametrosAdicional.lFolio = lFolioSeguro; //Folio del seguro titular
            parametrosAdicional.iAnioNac = iAnioNacimientoTitular; //Año de nacimiento del cliente
            parametrosAdicional.iDiaNac = iDiaNacimientoTitular; //Dia de nacimiento del cliente
            parametrosAdicional.iMesNac = iMesNacimientoTitular; //Mes de nacimiento del cliente
            parametrosAdicional.iFlagCapturaAbonos = 1;//Para saber que se llamo desde el modulo capturarabono
            parametrosAdicional.iVentaSeguroClub = 3; //Para saber que es venta de seguro adicional
            parametrosAdicional.iCantidadMeses = 0; //Numero de meses que se le cobraran al seguro adicional
            parametrosAdicional.iAnioVenc = iAnioVencimiento; //Año de vencimiento del seguro
            parametrosAdicional.iMesVenc = iMesVencimiento; //Mes de vencimiento del seguro
            parametrosAdicional.iDiaVenc = iDiaVencimiento; //Dia de vencimiento del seguro
			if(sprintf_s(parametrosAdicional.cNombreCompleto, sizeof(parametrosAdicional.cNombreCompleto), cNombreCliente) < 0){;} //Nombre del completo del cliente
			if(sprintf_s(parametrosAdicional.cSexo, sizeof(parametrosAdicional.cSexo), "%s", cSexo) < 0){;}

			if(memcpy_s(cInputParam1, sizeof(cInputParam1), &parametros, sizeof(SParametros)) < 0){;}
			if(memcpy_s(cInputParam2, sizeof(cInputParam2), &parametrosAdicional, sizeof(EstructuraCliente)) < 0){;}
			if(sprintf_s(cMensaje, sizeof(cMensaje), "CDlgCapturarCambioSeguro::actualizarSeguros(), Manda llamar el modulo CA0149.DLL, Folio : %d", lFolioSeguro) < 0){;}
            grabarLog(cMensaje);
            // Ruta del archivo DLL a ejecutar
            nombreArchivo("CA0149.DLL", cNombreProyecto, DIRECTORIO_CA);
            // Nombre de la función principal en el DLL
			if(sprintf_s(cNombreFuncionDLL, sizeof(cNombreFuncionDLL), "CA0149") < 0){;}
            CargarDLL cargarDll(cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2, cOutputParam1, cOutputParam2);
            iRegresaDll = cargarDll.getResultado();

            if (iRegresaDll <= 0)
            {
                AfxMessageBox(" Error al cargar el programa CA0149.DLL ");
            }
            else
            {
                CGrabarTmpCaCarmovSeguro tmpcaCarmovSeguros(&odbc);
				if(sprintf_s(cSql, sizeof(cSql), "UPDATE tmpcacarmovseguros SET cantidadsegurosanterior=%d, cantidadseguros=%d, importe=%d WHERE cliente = %ld AND folio=%d AND clave='G' AND tienda=%d AND caja=%d;", iNumeroSegurosAnterior, iNumSeguros, lPrecioSeguroClub, lCliente, iFolio, iTienda, iCaja) < 0){;}

                if (tmpcaCarmovSeguros.Exec(cSql))
                {
                    iProcesoBeneficiariosAdicionales = 1;
                }
                else
                {
                    tmpcaCarmovSeguros.odbc->GetLastError(tmpcaCarmovSeguros.GetHstmt());
                    grabarMensajeError("C", iCaja, (LPTSTR)(LPCTSTR)odbc.m_strServer, "CA0030", "CDlgCapturarDatosSeguro", "actualizarSeguros", cSql, lEmpleado, "Error al cambiar seguro adicional", tmpcaCarmovSeguros.odbc, iMuestraMsg);
                }
            }

        }
    }
}

void CDlgCapturarCambioSeguro::OnCbnSelchangeAsegurados()
{
    // TODO: Add your control notification handler code here
    CString sTexto = "";
    int iPos = m_asegurados.GetCurSel();
    if (iPos != CB_ERR)
    {
        m_seguros2.GetLBText(iPos, sTexto);
        m_seguros.SetWindowText(sTexto.Mid(0, 1));
        iNumeroSegurosAnterior = strtol(sTexto.Mid(0, 1), NULL, 10);
        iFolio = strtol(sTexto.Mid(1), NULL, 10);
        m_fechaNacimientoAdic.GetLBText(iPos, sTexto);
        iAnioNacimiento = strtol(sTexto.Mid(0, 4), NULL, 10);
        iMesNacimiento = strtol(sTexto.Mid(4, 2), NULL, 10);
        iDiaNacimiento = strtol(sTexto.Mid(6, 2), NULL, 10);
        fechaNacimiento();
    }
}

bool CDlgCapturarCambioSeguro::consultarPrecioSeguroClub()
{
    bool bRegresa = true;
    char cSql[180] = { 0 }, cMensajeSeguimiento[150] = { 0 };

    CConsultarPrecioSeguroClub precio(&odbc_1);

	if(sprintf_s(cSql, sizeof(cSql), "SELECT precioseguro, montoseguro, maximoseguros FROM fun_consultarPlanesSeguroClub01( '%04d-%02d-%02d', '%ld', '%d', '1', '2', '%d', '1' )", iAnioActual, iMesActual, iDiaActual, lCliente, iNumSeguros, iEdad) < 0){;}

    if (precio.Exec(cSql))
    {
        precio.activarCols();
        if (precio.leer())
        {
            iCantidadMaxSegurosCte = precio.maximoseguros;
            lPrecioSeguroClub = precio.precioseguro;
			if(sprintf_s(cMensajeSeguimiento, sizeof(cMensajeSeguimiento), "consultarPrecioSeguroClub:Consulta precios seguro y cantidad de seguros iCantidadMaxSegurosCte: %d precio seguro %ld", iCantidadMaxSegurosCte, lPrecioSeguroClub) < 0){;}
            grabarLog(cMensajeSeguimiento);
        }
    }
    else
    {
        bRegresa = false;
        precio.odbc->GetLastError(precio.GetHstmt());
        grabarMensajeError("C", iCaja, (LPTSTR)(LPCTSTR)odbc_1.m_strServer, "CA0030", "CDlgCapturarDatosSeguro", "consultarPrecioSeguroClub", cSql, lEmpleado, "Error al Consultar Precio Seguro Club", precio.odbc, iMuestraMsg);
    }

    return bRegresa;
}
void CDlgCapturarCambioSeguro::grabarLog(char *cTexto)
{
    char sArch[80] = { 0 };
    char cTextoGrabar[2048] = { 0 };
    CTime tFecha = CTime::GetCurrentTime();

	if(sprintf_s(sArch, sizeof(sArch), "C:\\sys\\mem\\CapturarAbonos%02d%02d.log", tFecha.GetMonth(), tFecha.GetDay()) < 0){;}

	if(sprintf_s(cTextoGrabar, sizeof(cTextoGrabar), "%04d-%02d-%02d %02d:%02d:%02d %s\n", tFecha.GetYear(), tFecha.GetMonth(), tFecha.GetDay(), tFecha.GetHour(), tFecha.GetMinute(), tFecha.GetSecond(), cTexto) < 0){;}
    C_Archivo arch(sArch, &cTextoGrabar, sizeof(cTextoGrabar));
    arch.posicionar((long)0, BASE_FINAL);
    arch.grabar(cTextoGrabar, (unsigned int)strnlen(cTextoGrabar, 2048));
}