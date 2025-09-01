#include "stdafx.h"
#include "sysCapturarAbono.h"
#include "CapturarAbono.h"
#include "DlgCapturarDatosSeguroMotos.h"
#include "sysCapturarAbono.h"
#include "Gnwproto.hpp"
#include "cawproto.hpp"
#include "folios.hpp"
#include "flags.hpp"
#include "CargarDLL.h"

#include "CFechaCoppel.hpp"
#include "CConsultarCliente.hpp"
#include "CCrHuellas.hpp"
#include "CConsultarPrecioSeguroClub.hpp"

//Para el seguro adicional
#include "DlgCapturarCambioSeguro.h"

// CDlgCapturarDatosSeguro dialog

IMPLEMENT_DYNAMIC(CDlgCapturarDatosSeguroMotos, CDialog2012)
CDlgCapturarDatosSeguroMotos::CDlgCapturarDatosSeguroMotos(CWnd* pParent /*=NULL*/)
    : CDialog2012(CDlgCapturarDatosSeguroMotos::IDD, pParent)
{
    iPuntualidad = 0;
    iColumnaClub = -1;
    iColumnaClubActual = -1;
    iSegurosAdicionales = 0;
    bAutorizado = true;

    iEdadMinimaClub = iEdadMaximaClub = iEdadMaximaClubAdicional = iEdadMaximaAbonoClub = iEdadMaximaAbonoClubAdic = iCantidadMaxSegurosCte = 0;
    lEmpleado = lMeses = lCuota = lPrecioSeguroClub = lCliente = lFolioSeguroNuevo = 0;
    iControles = iFoco = iMeses = iSeguros = iEsSeguroClub = iMuestraMsg = iFlagBanorte = iMesVencimiento = iAnioVencimiento =
    iDiaVencimiento = lCliente = iAnioNacimiento = iMesNacimiento = iDiaNacimiento = iAnioActual = iMesActual = iDiaActual = iMesEdad =
    iNumeroMeses = iFlagConsulta = iFlagCapturoBeneficiariosClubNuevo = iSistema = iFlagCancelo = iFlagCapturaBeneficiario =
    iCveSinBeneficiarios = iFlagSeguroAdicional = iEdadCliente = iPuntualidad = iTienda = iNumSegurosNuevo = iCiudad = 0;

	bBanderaTieneClub = bBanderaSeguroVigente = 0;
	iCaja = iOrigenSeguro = 0;
	lFolioSeguro = 0;
    SecureZeroMemory(cNombreCliente, sizeof(cNombreCliente));
    SecureZeroMemory(cSexo, sizeof(cSexo));
    iProcesoBeneficiariosAdicionales = 0;
}

CDlgCapturarDatosSeguroMotos::~CDlgCapturarDatosSeguroMotos()
{
	bBanderaTieneClub = 0;
	bBanderaSeguroVigente = 0;
	iNumSegurosNuevo = 0;
	iEsSeguroClub = 0;
	lCliente = 0;
	iCaja = 0;
	lEmpleado = 0;
	iMuestraMsg = 0;
	iColumnaClub = 0;
	iColumnaClubActual = 0;
	iFlagSeguroAdicional = 0;
	iPuntualidad = 0;
	iEdadCliente = 0;
	iEdadMaximaClubAdicional = 0;
	iEdadMinimaClub = 0;
	iSistema = 0;
	iSegurosAdicionales = 0;
	iOrigenSeguro = 0;
	iAnioVencimiento = 0;
	iMesVencimiento = 0;
	iDiaVencimiento = 0;
	iFlagBanorte = 0;
	iEdadMaximaClub = 0;
	iEdadMaximaAbonoClub = 0;
	iMesEdad = 0;
	iAnioActual = 0;
	iMesActual = 0;
	iDiaActual = 0;
	iAnioNacimiento = 0;
	iMesNacimiento = 0;
	iDiaNacimiento = 0;
	iTienda = 0;
	iEdadMaximaAbonoClubAdic = 0;
	lFolioSeguro = 0;
}

void CDlgCapturarDatosSeguroMotos::DoDataExchange(CDataExchange* pDX)
{
    CDialog2012::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SEGUROS, m_seguros);
    DDX_Control(pDX, IDC_MESES, m_meses);
    DDX_Control(pDX, IDC_CANCELAR, m_cancelar);
    DDX_Control(pDX, IDC_ACEPTAR, m_aceptar);
}

BEGIN_MESSAGE_MAP(CDlgCapturarDatosSeguroMotos, CDialog2012)
    ON_BN_CLICKED(IDC_CANCELAR, OnBnClickedCancelar)
    ON_BN_CLICKED(IDC_ACEPTAR, OnBnClickedAceptar)
    ON_EN_SETFOCUS(IDC_SEGUROS, OnEnSetfocusSeguros)
    ON_EN_SETFOCUS(IDC_MESES, OnEnSetfocusMeses)
END_MESSAGE_MAP()


// CDlgCapturarDatosSeguro message handlers

void CDlgCapturarDatosSeguroMotos::OnBnClickedCancelar()
{
    // TODO: Add your control notification handler code here

	iMeses = 0;
    CDialog2012::OnCancel();
}

void CDlgCapturarDatosSeguroMotos::OnBnClickedAceptar()
{
    int iEscambio = 0;
    int iHuella = 0, iFlagVenta = 0;
    iRespondio = 0;

    if (!bBanderaTieneClub || !bBanderaSeguroVigente)
    {
        iFlagVenta = 1;
        bAutorizado = true;
    }
    // TODO: Add your control notification handler code here
    if (validarControles())
    {	     //Si no tiene seguro 
        if (iEsSeguroClub == 1 || iEsSeguroClub == 2)
        {
            if (iEscambio == 1)
            {
                if (bBanderaTieneClub)
                {
                    //iHuella = checarHuellaChw(lCliente, iCaja, lEmpleado, iMuestraMsg);
                    if (iHuella > 0)
                    {
                        bAutorizado = true;
                    }
                }
                else
                {
                    bAutorizado = true;
                }
            }
        }

        CDialog2012::OnCancel();
    }
}

void CDlgCapturarDatosSeguroMotos::OnEnSetfocusSeguros()
{
    // TODO: Add your control notification handler code here
    validarClick(0);
}

void CDlgCapturarDatosSeguroMotos::OnEnSetfocusMeses()
{
    // TODO: Add your control notification handler code here
    validarClick(1);
}

BOOL CDlgCapturarDatosSeguroMotos::OnInitDialog()
{
    CDialog2012::OnInitDialog();
    CString sTexto;
    char cTexto[80] = { 0 };

    // TODO:  Add extra initialization here
    //SetWindowText(" CAPTURAR DATOS DEL SEGURO ");
    m_seguros.SetLimitText(1);
    m_meses.SetLimitText(2);

	iFoco = 0;
    iControles = 2;
    iFlagCapturoBeneficiariosClubNuevo = 0;
    iSeguros = 0;
    iMeses = 0;
    lCuota = 0L;

    iRespuesta = 0;

    lPrecioSeguroClub = 0;


    CEdit* pEditControl = (CEdit*)GetDlgItem(IDC_SEGUROS);
    pEditControl->ShowWindow(SW_HIDE);
    m_seguros.ShowWindow(SW_HIDE);
    iFoco = 1;
    
		
    sTexto.Format("%d", iNumeroMeses);
    m_meses.SetWindowText(sTexto);
    m_meses.SetSel(0, 1);

	if(sprintf_s(cFechaVencimiento, "%04d%02d%02d", iAnioVencimiento, iMesVencimiento, iDiaVencimiento) < 0){;}

    crearMensaje(this, m_barra, m_mensaje);

	if(sprintf_s(cTexto, " [ ESC ] Cancelar  [F10] Aceptar") < 0){;}
    m_seguros.EnableWindow(false);

    ponerMensaje(this, m_barra, m_mensaje, cTexto);
    //procesoSeguro();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgCapturarDatosSeguroMotos::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    char cPaso[255] = { 0 };
    CString sDato;
    CString sTexto;
    int iHuella = 0;
    ShiftTab = false;

    switch (pMsg->wParam)
    {
    case VK_F5: //9923
    {
    }
    pMsg->wParam = NULL;
    break;
    case VK_F10:
        iFlagCancelo = 1;
        OnBnClickedAceptar();
        pMsg->wParam = NULL;
        break;
    case VK_ESCAPE:
        iFlagCancelo = 0;
		iMeses = 0;
        CDialog2012::OnCancel();
        pMsg->wParam = NULL;
        break;

    case VK_RIGHT:
        break;
	case VK_RETURN:{}
		pMsg->wParam = NULL;
        break;
    default:
			iMeses = 0;
        break;
    }
    return CDialog2012::PreTranslateMessage(pMsg);
}

bool CDlgCapturarDatosSeguroMotos::validarClick(int nTmpFocus)
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

void CDlgCapturarDatosSeguroMotos::asignarFoco()
{
    switch (iFoco)
    {
    case 0:
        m_seguros.SetFocus();
        break;
    case 1:
        m_meses.SetFocus();
        break;
    case 2:
        m_cancelar.SetFocus();
        break;
    case 3:
        m_aceptar.SetFocus();
        break;
    default:
        break;
    }
}

bool CDlgCapturarDatosSeguroMotos::validarControl(char * cCadena)
{
    bool valorRegresa = true;
    CString sTexto;

    switch (iFoco)
    {
    case 0:
        break;
    case 1:
        m_meses.GetWindowText(sTexto);
        sTexto.Trim();
        iNumeroMeses = strtol(sTexto, NULL, 10);
        if (sTexto.IsEmpty())
        {
			if(sprintf_s(cCadena, 255, "%s", "FAVOR DE CAPTURAR NUMERO DE MESES ") < 0){;}
            iMeses = 0;
            m_meses.SetSel(0, 2);
            valorRegresa = false;
        }
		if (iNumeroMeses<1)
        {   
			if(sprintf_s(cCadena, 255, "%s", "NUMERO DE MESES INCORRECTO ") < 0){;}
            iNumeroMeses = 0;
            m_meses.SetSel(0, 2);
            valorRegresa = false;
        }
        break;
    default:
        break;
    }
    return valorRegresa;
}

bool CDlgCapturarDatosSeguroMotos::boton()
{
    CWnd *pWnd = GetFocus();
    bool valorRegresa = false;

    switch (pWnd->GetDlgCtrlID())
    {
    case IDC_CANCELAR:
        valorRegresa = true;
        break;
    case IDC_ACEPTAR:
        valorRegresa = true;
        break;
    }
    return valorRegresa;
}

bool CDlgCapturarDatosSeguroMotos::validarControles()
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

void CDlgCapturarDatosSeguroMotos::grabarLog(char *cTexto)
{
    char sArch[80] = { 0 };
    char cTextoGrabar[2048] = { 0 };
    CTime tFecha = CTime::GetCurrentTime();

	if(sprintf_s(sArch, "C:\\sys\\mem\\CapturarAbonos%02d%02d.log", tFecha.GetMonth(), tFecha.GetDay()) < 0){;}

	if(sprintf_s(cTextoGrabar, "%04d-%02d-%02d %02d:%02d:%02d %s\n", tFecha.GetYear(), tFecha.GetMonth(), tFecha.GetDay(), tFecha.GetHour(), tFecha.GetMinute(), tFecha.GetSecond(), cTexto) < 0){;}
    C_Archivo arch(sArch, &cTextoGrabar, sizeof(cTextoGrabar));
    arch.posicionar((long)0, BASE_FINAL);
    arch.grabar(cTextoGrabar, (unsigned int)strnlen(cTextoGrabar, 2048));
}
