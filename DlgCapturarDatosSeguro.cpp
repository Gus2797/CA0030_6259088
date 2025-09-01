// DlgCapturarDatosSeguro.cpp : implementation file
//

#include "stdafx.h"
#include "sysCapturarAbono.h"
#include "CapturarAbono.h"
#include "DlgCapturarDatosSeguro.h"
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

IMPLEMENT_DYNAMIC(CDlgCapturarDatosSeguro, CDialog2012)
CDlgCapturarDatosSeguro::CDlgCapturarDatosSeguro(CWnd* pParent /*=NULL*/)
    : CDialog2012(CDlgCapturarDatosSeguro::IDD, pParent)
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
        iNumeroSegurosAnterior = iNumeroMeses = iCantidad = iRango = iNumSeguros = iMax = iConyugal = iCiudad = iFlagConsulta =
        iFlagCapturoBeneficiariosClubNuevo = iSistema = iFlagCancelo = iFlagCapturaBeneficiario =
        iCveSinBeneficiarios = iFlagSeguroAdicional = iEdadCliente = iPuntualidad = iTienda = iNumSegurosNuevo = 0;

	bBanderaTieneClub = bBanderaSeguroVigente = 0;
	iCaja = iOrigenSeguro = 0;
	lFolioSeguro = 0;
    SecureZeroMemory(cNombreCliente, sizeof(cNombreCliente));
    SecureZeroMemory(cSexo, sizeof(cSexo));
    iProcesoBeneficiariosAdicionales = 0;
}

CDlgCapturarDatosSeguro::~CDlgCapturarDatosSeguro()
{
	bBanderaTieneClub = 0;
	bBanderaSeguroVigente = 0;
	iNumeroSegurosAnterior = 0;
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
	iRango = 0;
	iEdadMaximaAbonoClub = 0;
	iMesEdad = 0;
	iAnioActual = 0;
	iMesActual = 0;
	iDiaActual = 0;
	iAnioNacimiento = 0;
	iMesNacimiento = 0;
	iDiaNacimiento = 0;
	iTienda = 0;
	iCiudad = 0;
	iEdadMaximaAbonoClubAdic = 0;
	lFolioSeguro = 0;
}

void CDlgCapturarDatosSeguro::DoDataExchange(CDataExchange* pDX)
{
    CDialog2012::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SEGUROS, m_seguros);
    DDX_Control(pDX, IDC_MESES, m_meses);
    DDX_Control(pDX, IDC_CANCELAR, m_cancelar);
    DDX_Control(pDX, IDC_ACEPTAR, m_aceptar);
}

BEGIN_MESSAGE_MAP(CDlgCapturarDatosSeguro, CDialog2012)
    ON_BN_CLICKED(IDC_CANCELAR, OnBnClickedCancelar)
    ON_BN_CLICKED(IDC_ACEPTAR, OnBnClickedAceptar)
    ON_EN_SETFOCUS(IDC_SEGUROS, OnEnSetfocusSeguros)
    ON_EN_SETFOCUS(IDC_MESES, OnEnSetfocusMeses)
END_MESSAGE_MAP()


// CDlgCapturarDatosSeguro message handlers

void CDlgCapturarDatosSeguro::OnBnClickedCancelar()
{
    // TODO: Add your control notification handler code here
    CDialog2012::OnCancel();
}

void CDlgCapturarDatosSeguro::OnBnClickedAceptar()
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
        if (iNumSeguros > 0 && iNumeroSegurosAnterior > 0 && iNumSeguros != iNumeroSegurosAnterior && iFlagVenta == 0)//Realizó un cambio de plan
        {
            if (iNumSegurosNuevo != iNumSeguros)
            {
                iEscambio = 1;
            }
            bAutorizado = false;
        }
        if (iEsSeguroClub == 1 || iEsSeguroClub == 2)
        {
            if (iEscambio == 1)
            {
                if (bBanderaTieneClub)
                {
                    iHuella = checarHuellaChw(lCliente, iCaja, lEmpleado, iMuestraMsg);
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
            if (bAutorizado)
            {
                llamarBeneficiarios();
            }
        }

        if (bAutorizado)
        {
            if (iFlagSeguroAdicional == 1 && iEsSeguroClub != 0 && iColumnaClub == iColumnaClubActual) //Si esta activo el flag para vender seguros adicionales
            {
                if (iFlagCancelo == 1 && iEdadCliente >= iEdadMinimaClub && iEdadCliente <= iEdadMaximaClubAdicional && iPuntualidad != 1 && iSeguros <= 3)
                {
                    if (iSegurosAdicionales < 10 && iOrigenSeguro == 1 && iFlagVenta == 1 && iSistema == 3) //Se agrego validacion para que cuando el cliente tenga 10 seguros adicionales ya no le ofrece comprar otro adicional
                    {
                        if (AfxMessageBox("¿DESEA ADQUIRIR EL CLUB ADICIONAL?", MB_YESNO | MB_ICONQUESTION) == IDYES)
                        {
                            iRespondio = 1;
                        }
                    }
                }
            }
        }
        CDialog2012::OnCancel();
    }
}

void CDlgCapturarDatosSeguro::OnEnSetfocusSeguros()
{
    // TODO: Add your control notification handler code here
    validarClick(0);
}

void CDlgCapturarDatosSeguro::OnEnSetfocusMeses()
{
    // TODO: Add your control notification handler code here
    validarClick(1);
}

BOOL CDlgCapturarDatosSeguro::OnInitDialog()
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
    iMax = 6;
    iRespuesta = 0;

    lPrecioSeguroClub = 0;

    sTexto.Format("%d", iNumSeguros);
    m_seguros.SetWindowText(sTexto);
    m_seguros.SetSel(0, 1);

    sTexto.Format("%d", iNumeroMeses);
    m_meses.SetWindowText(sTexto);
    m_meses.SetSel(0, 1);

	if(sprintf_s(cFechaVencimiento, "%04d%02d%02d", iAnioVencimiento, iMesVencimiento, iDiaVencimiento) < 0){;}

    crearMensaje(this, m_barra, m_mensaje);

    if (iSistema == 3)
    {
		if(sprintf_s(cTexto, " [ ESC ] Cancelar  [F10] Aceptar  [F5] Cambio Seguro") < 0){;}
    }
    else
    {
		if(sprintf_s(cTexto, " [ ESC ] Cancelar  [F10] Aceptar") < 0){;}
        m_seguros.EnableWindow(false);
    }

    ponerMensaje(this, m_barra, m_mensaje, cTexto);
    procesoSeguro();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgCapturarDatosSeguro::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    char cPaso[255] = { 0 };
    CString sDato;
    CString sTexto;
    int iHuella = 0;
    ShiftTab = false;

    if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
    {
        if (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_UP)
        {
            iFoco--;
            if (iFoco < 0)     iFoco = 0;
            asignarFoco();
        }
        if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB || pMsg->wParam == VK_DOWN || pMsg->wParam == VK_RIGHT)
        {
            if (!boton())
            {
                if (iFoco <= iControles) //numero de controles
                {
                    if (validarControl(cPaso))
                    {
                        iFoco++;

                        if (iFoco == 1)
                        {
                            sTexto.Format("%d", iNumeroMeses);
                            m_meses.SetWindowText(sTexto);
                            m_meses.SetSel(0, 1);
                        }

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
                case VK_F5: //9923
                {
                    if (iSistema == 3)
                    {
                        cambioSeguro();
                    }
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
                    CDialog2012::OnCancel();
                    pMsg->wParam = NULL;
                    break;
                case VK_RIGHT:
                    if (boton())
                    {
                        iFoco++;
                        if (iFoco > 3)
                            iFoco = 0;
                        asignarFoco();
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    return CDialog2012::PreTranslateMessage(pMsg);
}

bool CDlgCapturarDatosSeguro::validarClick(int nTmpFocus)
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

void CDlgCapturarDatosSeguro::asignarFoco()
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

bool CDlgCapturarDatosSeguro::validarControl(char * cCadena)
{
    bool valorRegresa = true;
    CString sTexto;

    switch (iFoco)
    {
    case 0:
        m_seguros.GetWindowText(sTexto);
        sTexto.Trim();
        iSeguros = strtol(sTexto, NULL, 10);
        if (sTexto.IsEmpty())
        {
			if(sprintf_s(cCadena, 255, "%s", " FAVOR DE CAPTURAR NÚMERO DE SEGUROS ") < 0){;}
            iSeguros = 0;
            m_seguros.SetSel(0, 1);
            valorRegresa = false;
        }
        else
        {
            if (iFlagBanorte != 0 && (iEsSeguroClub == 1 || iEsSeguroClub == 2)) //es seguro club
            {
                if (iSeguros < 1)
                {
					if(sprintf_s(cCadena, 255, "%s", " NÚMERO DE SEGUROS INCORRECTO ") < 0){;}
                    iSeguros = 0;
                    m_seguros.SetSel(0, 1);
                    valorRegresa = false;
                }
                if (valorRegresa)
                {
                    if (iSeguros > iNumeroSegurosAnterior && bBanderaTieneClub)
                    {
                        grabarLog("Consulta Precio seguro 15");
                        consultarPrecioSeguroClub(1);
                        if (iCantidadMaxSegurosCte < (short)iNumeroSegurosAnterior && bBanderaSeguroVigente)
                        {
                            iCantidadMaxSegurosCte = (short)iNumeroSegurosAnterior;
                        }
                    }


                    /*
                    if ( iSeguros > iCantidadMaxSegurosCte && bBanderaSeguroVigente )
                    {
                        sprintf(cCadena,"EL CLIENTE, POR SU RANGO DE EDAD, SOLO PUEDE COMPRAR HASTA %d SEGUROS",iCantidadMaxSegurosCte);
                        iSeguros=0;
                        m_seguros.SetSel(0,1);
                        valorRegresa = false;
                    }
                    */

                    if (bBanderaTieneClub && !bBanderaSeguroVigente && iCantidadMaxSegurosCte == 0) {
                        iCantidadMaxSegurosCte = 1;
                    }
                    //if ( iSeguros > iCantidadMaxSegurosCte && (bBanderaSeguroVigente || !bBanderaSeguroVigente) )
                    if (iSeguros > iCantidadMaxSegurosCte)
                    {
						if(sprintf_s(cCadena, 255, "EL CLIENTE, POR SU RANGO DE EDAD, SOLO PUEDE COMPRAR HASTA %d SEGUROS", iCantidadMaxSegurosCte) < 0){;}
                        iSeguros = 0;
                        m_seguros.SetSel(0, 1);
                        valorRegresa = false;
                    }

                }
            }
            else
            {
                if (valorRegresa == true)
                {
                    if (iSeguros < 1 || iSeguros>5)
                    {
						if(sprintf_s(cCadena, 255, "%s", " NÚMERO DE SEGUROS INCORRECTO ") < 0){;}
                        iSeguros = 0;
                        m_seguros.SetSel(0, 1);
                        valorRegresa = false;
                    }
                }
            }
            if (valorRegresa)
            {
                if (iFlagBanorte != 0 && (iEsSeguroClub == 1 || iEsSeguroClub == 2)) //es seguro club
                {

                    if (iNumeroSegurosAnterior == 0 && iEdadCliente > iEdadMaximaClub)
                    {

						if(sprintf_s(cCadena, 255, " CLIENTE MAYOR DE %d AÑOS, NO VENDER SEGUROS ", iEdadMaximaClub) < 0){;}
                        iSeguros = 0;
                        m_seguros.SetSel(0, 1);
                        valorRegresa = false;
                    }
                }
                else
                {
                    if (iNumeroSegurosAnterior == 0 && iRango == 4)
                    {
						if(sprintf_s(cCadena, 255, "%s", " CLIENTE MAYOR DE 60 A¥OS, NO VENDER SEGUROS ") < 0){;}
                        iSeguros = 0;
                        m_seguros.SetSel(0, 1);
                        valorRegresa = false;
                    }
                }
            }
            if (valorRegresa)
            {
                if (bBanderaSeguroVigente && iSeguros < (int)iNumeroSegurosAnterior)
                {
					if(sprintf_s(cCadena, 255, "%s", "EL NUM. DE SEGUROS CAPTURADOS, ES MENOR A LA CANTIDAD DE SEGUROS DEL CLIENTE") < 0){;}
                    iSeguros = (int)iNumeroSegurosAnterior;
                    m_seguros.SetSel(0, 1);
                    valorRegresa = false;
                }
            }
        }
        break;
    case 1:
        m_meses.GetWindowText(sTexto);
        sTexto.Trim();
        iNumeroMeses = strtol(sTexto, NULL, 10);
        if (sTexto.IsEmpty())
        {
			if(sprintf_s(cCadena, 255, "%s", "FAVOR DE CAPTURAR NÚMERO DE MESES ") < 0){;}
            iMeses = 0;
            m_meses.SetSel(0, 2);
            valorRegresa = false;
        }
        else
        {
            if (iNumeroMeses<1 || iNumeroMeses>iMax)
            {
				if(sprintf_s(cCadena, 255, "%s", "NÚMERO DE MESES INCORRECTO ") < 0){;}
                iNumeroMeses = 0;
                m_meses.SetSel(0, 2);
                valorRegresa = false;
            }
            if (valorRegresa == true)
            {
                if (iNumeroMeses < 1 || iNumeroMeses>99)
                {
					if(sprintf_s(cCadena, 255, "%s", " NÚMERO DE MESES INCORRECTO ") < 0){;}
                    iNumeroMeses = 0;
                    m_meses.SetSel(0, 2);
                    valorRegresa = false;
                }
            }
            if (valorRegresa == true)
            {
                if (iNumeroMeses > lMeses && lMeses > 0)
                {
					if(sprintf_s(cCadena, 255, " EL CLIENTE PUEDE REACTIVAR SU SEGURO HASTA POR %d MESES ", lMeses) < 0){;}
                    iNumeroMeses = 0;
                    m_meses.SetSel(0, 2);
                    valorRegresa = false;
                }
                else if (lMeses == 0)
                {
                    if (edadAbono() <= iEdadMaximaAbonoClub)
                    {
						if(sprintf_s(cCadena, 255, " EL CLIENTE YA NO PUEDE ABONAR A SU SEGURO, DEBIDO A QUE EL MAXIMO DE MESES ABONADOS ES 12 ") < 0){;}
                    }
                    else
                    {
						if(sprintf_s(cCadena, 255, " EL CLIENTE YA NO PUEDE ABONAR A SU SEGURO, DEBIDO A QUE SOBREPASARÁ LA EDAD MAXIMA ") < 0){;}
                    }
                    iNumeroMeses = 0;
                    m_meses.SetSel(0, 2);
                    valorRegresa = false;
                }
            }

            iFlagCancelo = 1;
            iNumSeguros = iSeguros;
        }
        break;
    default:
        break;
    }
    return valorRegresa;
}

bool CDlgCapturarDatosSeguro::boton()
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

bool CDlgCapturarDatosSeguro::validarControles()
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

void CDlgCapturarDatosSeguro::procesoSeguro()
{
    char cTexto[20] = { 0 }, cTexto2[20] = { 0 };
    int iAnio2 = 0, iFlagConsulta = 0;
    long lMesAnioActual = 0L, lMesVence = 0L;
    bool bConsulta = false;
    char cSqlTxt[255] = { 0 }, cMensaje[80] = { 0 };
    short iFlagVenta = 0;

    if (iFlagBanorte != 0 && (iEsSeguroClub == 1 || iEsSeguroClub == 2))//es club
    {
        iMax = mesesAbonar(iEdadCliente, iMesEdad);
		if(sprintf_s(cTexto, "%04d%02d%02d", iAnioActual, iMesActual, iDiaActual) < 0){;}
        if (valor_campo(cFechaVencimiento, 8) > valor_campo(cTexto, 8))
        {
            iMax = 12 - mesesPagados(cFechaVencimiento);
        }
        if (iMax > 12) iMax = 12;

        if (!bBanderaTieneClub || !bBanderaSeguroVigente)
        {
            iFlagVenta = 1;
        }

        grabarLog("Consulta Precio seguro 16");
        if (!consultarPrecioSeguroClub(iFlagVenta) || !consultarMesesaAbonar())
        {
            OnCancel();
        }
    }
    else
    {
        iMax = 6;
    }

    if (!(iFlagBanorte != 0 && (iEsSeguroClub == 1 || iEsSeguroClub == 2)))//si no es club
    {
        obtenerCuotaSeguroR(iRango, &odbc, cSqlTxt, bConsulta, iFlagConsulta, lCliente, &odbc_1);
        if (bConsulta == false && iFlagConsulta != 1)
        {
            //Se obtiene el error
            grabarMensajeError("C", iCaja, cIPServidorTiendaNumero, "CA0030", "CDlgCapturarDatosSeguro", "procesoSeguro", (LPTSTR)(LPCTSTR)cSqlTxt, lEmpleado, "ERROR EN LA CONSULTA(procesoseguro dlgcapturardatosseguro)", &odbc, iMuestraMsg);
        }

        SecureZeroMemory(cTexto, 20);
		if(sprintf_s(cTexto, "%04d%02d", iAnioActual, iMesActual) < 0){;}
        lMesAnioActual = valor_campo(cTexto, 6);

		if(sprintf_s(cTexto2, "%04d%02d", iAnioNacimiento, iMesNacimiento) < 0){;}

        SecureZeroMemory(cTexto, 20);
		if(sprintf_s(cTexto, "%04d%02d", ((int)iAnioNacimiento + iEdadMaximaAbonoClub), (int)iMesNacimiento) < 0){;}
        lMesVence = valor_campo(cTexto, 6);

        lMeses = lMesVence - lMesAnioActual;

        iAnio2 = ((int)iAnioNacimiento + iEdadMaximaAbonoClub) - iAnioActual;
        if (lMeses < 0) lMeses = 0;
        if (lMeses > 80) lMeses = (lMeses - (90 * iAnio2)) + (2 * iAnio2);
    }

    /*if( iEdadCliente > iEdadMaximaAbonoClub || ( iEdadCliente > iEdadMaximaClub && bBanderaTieneClub && !bBanderaSeguroVigente ) )
    {
        if( iEdadCliente > iEdadMaximaAbonoClub )
        {
            sprintf( cMensaje, " CLIENTE MAYOR DE  %d AÑOS, NO VENDER SEGUROS ", iEdadMaximaAbonoClub );
        }
        else
        {
            sprintf( cMensaje, " CLIENTE MAYOR DE  %d AÑOS, NO VENDER SEGUROS ", iEdadMaximaClub );
        }

        AfxMessageBox( cMensaje );
        OnCancel();
    }*/

    if (iEdadCliente > (iEdadMaximaAbonoClub - 1) || (iEdadCliente > iEdadMaximaClub && bBanderaTieneClub && !bBanderaSeguroVigente))
    {
        if (iEdadCliente > (iEdadMaximaAbonoClub - 1))
        {
			if(sprintf_s(cMensaje, "CLIENTE MAYOR DE %d AÑOS, NO VENDER SEGUROS ", iEdadMaximaAbonoClub) < 0){;}
            AfxMessageBox(cMensaje);
            OnCancel();
        }
        else if (iEdadCliente > iEdadMaximaClub && (!bBanderaTieneClub))
        {
			if(sprintf_s(cMensaje, "CLIENTE MAYOR DE %d AÑOS, NO VENDER SEGUROS ", iEdadMaximaClub) < 0){;}
            AfxMessageBox(cMensaje);
            OnCancel();
        }
        else if (iEdadCliente > (iEdadMaximaAbonoClub - 1) && (!bBanderaTieneClub && !bBanderaSeguroVigente)) {
			if(sprintf_s(cMensaje, "CLIENTE MAYOR DE %d AÑOS, NO VENDER SEGUROS ", iEdadMaximaAbonoClub) < 0){;}
            AfxMessageBox(cMensaje);
            OnCancel();
        }

    }
}

int CDlgCapturarDatosSeguro::mesesAbonar(int iEdad, int iMesEdad)
{
    int iMeses = 0, iCont;

    iCont = (iEdadMaximaAbonoClub - 1 - iEdad) * 12;
    iMeses = (iCont - iMesEdad) + 11;
    return iMeses;
}

int CDlgCapturarDatosSeguro::mesesPagados(char *cFechaVencimiento)
{
    int iMeses = 0;

    if (valor_campo(cFechaVencimiento, 4) == iAnioActual)
    {
        iMeses = valor_campo(&cFechaVencimiento[4], 2) - iMesActual;
    }
    else
    {
        iMeses = 12 - iMesActual;
        iMeses += valor_campo(&cFechaVencimiento[4], 2);
    }
    return iMeses;
}

void CDlgCapturarDatosSeguro::llamarBeneficiarios()
{
    int iFlag = -1, iHuella = 0, iOpcion = 0, iRegresaDll = 0;
    char cNombreProyecto[256] = { 0 }, cNombreFuncionDLL[256] = { 0 };
    char cInputParam1[1024] = { 0 }, cInputParam2[1024] = { 0 },
        cOutputParam1[1024] = { 0 }, cOutputParam2[1024] = { 0 };
    short iFlagVenta = 0;
    char cSeguros[3] = { 0 }, cMensaje[200] = { 0 };

    grabarLog("Inicia metodo llamarBeneficiarios()");

    SParametros parametros;
    SecureZeroMemory(&parametros, sizeof(SParametros));

    {
        if (!bBanderaTieneClub || !bBanderaSeguroVigente)
        {
            iFlagVenta = 1;
        }
        grabarLog("Consulta Precio seguro 17");
        if (consultarPrecioSeguroClub(iFlagVenta))
        {
            if (!bBanderaTieneClub)  //Si no tiene seguro
            {
                iHuella = checarHuellaChw(lCliente, iCaja, lEmpleado, iMuestraMsg);
                if (iHuella > 0)
                {
                    // CapturarBeneficiarioSeguroClub
                    lFolioSeguroNuevo = obtenerFolioSeguro();
                    iConyugal = iEsSeguroClub;
                    iFlagConsulta = false;
                    lCuota = lPrecioSeguroClub;

                    SecureZeroMemory(cNombreProyecto, sizeof(cNombreProyecto));
                    SecureZeroMemory(cNombreFuncionDLL, sizeof(cNombreFuncionDLL));

                    parametros.iLink = generarLink();
					if(sprintf_s(parametros.sServer, "%s", cIPServidorTiendaNumero) < 0){;}
                    parametros.iTienda = iTienda;
                    parametros.lEmpleado = lEmpleado;
                    parametros.iCajaActual = iCaja;
                    parametros.iMuestraMsg = iMuestraMsg;

                    parametros.lCliente = lCliente;
                    parametros.lFolioSeguro = lFolioSeguroNuevo;	 // Folio
                    parametros.iSensor = iSeguros;	// Numero de Seguros
                    parametros.iTipoServicio = iNumeroMeses;	 // Numero de Meses
                    parametros.lCantidad = (lCuota*iNumeroMeses); // Su Pago
                    parametros.iFlagGeneral = 0;	  // Bandera=1 Graba en todas las Tablas menos en la Tabla TemptdBeneficiarios
                                                // Bandera=0 Graba nada mas en la Tabla Temporal TemptdBeneficiarios
                    //AfxMessageBox("Entro Por estos Lados");
                    //parametros.iTiendaFactura = 2;

					if(memcpy_s(cInputParam1, sizeof(cInputParam1), &parametros, sizeof(SParametros)) < 0){;}
                    if (iConyugal == 1)
                    {
						if(sprintf_s(cMensaje, "llamarBeneficiarios::Si no tiene seguro manda llamar modulo CA0071.dll: lFolioSeguroNuevo: %ld, iFlagGeneral = %d", parametros.lFolioSeguro, parametros.iFlagGeneral) < 0){;}
                        grabarLog(cMensaje);

                        // Ruta del archivo DLL a ejecutar
                        nombreArchivo("CA0071.DLL", cNombreProyecto, DIRECTORIO_CA);
                        // Nombre de la función principal en el DLL
						if(sprintf_s(cNombreFuncionDLL, "CA0071") < 0){;}

                        CargarDLL cargarDll(cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2, cOutputParam1, cOutputParam2);
                        iRegresaDll = cargarDll.getResultado();

                        if (strtol(cOutputParam1, NULL, 10) > 0) //si capturo beneficiarios
                        {
                            iFlagCapturoBeneficiariosClubNuevo = 2;
                            iRespuesta = (short)strtol(cOutputParam2, NULL, 10);
                        }
                        else
                        {
                            iFlagCapturoBeneficiariosClubNuevo = 0;
                            lCuota = 0L;
                            iFlagCancelo = 0;
                        }

                        if (iRegresaDll <= 0)
                        {
                            AfxMessageBox("Error al cargar el programa CA0071.DLL");
                        }
                    }
                    else
                    {
						if(sprintf_s(cMensaje, "llamarBeneficiarios::Si no tiene seguro manda llamar modulo CA0108.dll: lFolioSeguroNuevo: %ld, iFlagGeneral = %d", parametros.lFolioSeguro, parametros.iFlagGeneral) < 0){;}
                        grabarLog(cMensaje);
                        // Ruta del archivo DLL a ejecutar
                        nombreArchivo("CA0108.DLL", cNombreProyecto, DIRECTORIO_CA);
						if(sprintf_s(cNombreFuncionDLL, "b") < 0){;}
                        CargarDLL cargarDll(cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2, cOutputParam1, cOutputParam2);
                        iRegresaDll = cargarDll.getResultado();

                        if (strtol(cOutputParam1, NULL, 10) > 0) //si capturo beneficiarios
                        {
                            iFlagCapturoBeneficiariosClubNuevo = 2;

                            iOpcion = AfxMessageBox("¿ Padece o ha padecido enfermedades del Corazón, Diabetes, SIDA, Cáncer, Insuficiencia renal, Hipertensión arterial, Cirrosis hepática, Hepatitis, Leucemia, Pancreatitis, Meningitis, Linfoma o Enfermedades Pulmonares?", MB_YESNO | MB_ICONQUESTION);
                            if (iOpcion == IDYES)
                            {
                                iRespuesta = 1;
                            }
                            else
                            {
                                iRespuesta = 0;
                            }
                        }
                        else
                        {
                            iFlagCapturoBeneficiariosClubNuevo = 0;
                            lCuota = 0L;
                            iFlagCancelo = 0;
                        }

                        if (iRegresaDll <= 0)
                        {
                            AfxMessageBox("Error al cargar el programa CA0108.DLL");
                        }
                    }
                }
                else
                {
                    iFlagCancelo = 0;
                }
            }
            else
            {
                iFlagConsulta = false;
                lCuota = lPrecioSeguroClub;

                SecureZeroMemory(cNombreProyecto, sizeof(cNombreProyecto));
                SecureZeroMemory(cNombreFuncionDLL, sizeof(cNombreFuncionDLL));

                parametros.iLink = generarLink();
				if(sprintf_s(parametros.sServer, "%s", cIPServidorTiendaNumero) < 0){;}
                parametros.iTienda = iTienda;
                parametros.lEmpleado = lEmpleado;
                parametros.iCajaActual = iCaja;
                parametros.iMuestraMsg = iMuestraMsg;

                parametros.lCliente = lCliente;
                parametros.lFolioSeguro = 999999;	 // Folio
                parametros.iSensor = iSeguros;	// Numero de Seguros
                parametros.iTipoServicio = iNumeroMeses;	 // Numero de Meses
                parametros.lCantidad = (lCuota*iNumeroMeses); // Su Pago
                parametros.iFlagGeneral = 0;	  // Bandera=1 Graba en todas las Tablas menos en la Tabla TemptdBeneficiarios
                                            // Bandera=0 Graba nada mas en la Tabla Temporal TemptdBeneficiarios

                if (iNumSeguros > 0 && iNumeroSegurosAnterior > 0 && iNumSeguros != iNumeroSegurosAnterior)//Realizó un cambio de plan
                {
                    iFlagCapturaBeneficiario = 1;
                    lFolioSeguroNuevo = obtenerFolioSeguro();  // Generar nuevo folio
                    parametros.lFolioSeguro = lFolioSeguroNuevo;	 // Folio

                //	AfxMessageBox("Entro Por estos Lados 1");
                //	parametros.iTiendaFactura = 2;
                    //capturar beneficiarios
					if(memcpy_s(cInputParam1, sizeof(cInputParam1), &parametros, sizeof(SParametros)) < 0){;}

					if(sprintf_s(cMensaje, "llamarBeneficiarios::Realizo un cambio de plan manda llamar modulo CA0071.dll: lFolioSeguroNuevo: %ld, iFlagGeneral = %d", parametros.lFolioSeguro, parametros.iFlagGeneral) < 0){;}
                    grabarLog(cMensaje);
                    // Ruta del archivo DLL a ejecutar
                    nombreArchivo("CA0071.DLL", cNombreProyecto, DIRECTORIO_CA);
                    // Nombre de la función principal en el DLL
					if(sprintf_s(cNombreFuncionDLL, "CA0071") < 0){;}
                    CargarDLL cargarDll(cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2, cOutputParam1, cOutputParam2);
                    iRegresaDll = cargarDll.getResultado();

                    if (strtol(cOutputParam1, NULL, 10) > 0) //si capturo beneficiarios
                    {
                        iFlagCapturoBeneficiariosClubNuevo = 2;
                    }
                    else
                    {
                        lFolioSeguroNuevo = 0;
                        iFlagCapturoBeneficiariosClubNuevo = 0;
                        lCuota = 0L;
                        iNumSeguros = iNumeroSegurosAnterior;
						if(sprintf_s(cSeguros, "%d", iNumSeguros) < 0){;}
                        m_seguros.SetWindowText(cSeguros);
                    }

                    if (iRegresaDll <= 0)
                    {
                        AfxMessageBox("Error al cargar el programa CA0071.DLL");
                    }
                }
                else
                {
                    if (iFlagCapturaBeneficiario == 1)
                    {
                        if (obtenerSiTieneBeneficiariosCrSeguros(lCliente))
                        {
                            if (lCuota > 0 && (iEsSeguroClub == 1 || iEsSeguroClub == 2) && iCveSinBeneficiarios == 2) //Tiene club pero no benef.
                            {
                                if (AfxMessageBox("Mensaje al Cliente: Usted es Titular", MB_YESNO | MB_ICONQUESTION) == IDYES)
                                {
                                    if (AfxMessageBox("MENSAJE AL CLIENTE: USTED NO CUENTA CON BENEFICIARIOS EN SU SEGURO CLUB DE PROTECCIÓN FAMILIAR. ¿DESEA PROPORCIONARLOS AHORA?", MB_ICONQUESTION) == IDYES)
                                    {
                                        iConyugal = OfrecerSeguroClubConyugal(lCliente);
                                        //AfxMessageBox("Entro Por estos Lados 2");
                                        //parametros.iTiendaFactura = 2;
										if(memcpy_s(cInputParam1, sizeof(cInputParam1), &parametros, sizeof(SParametros)) < 0){;}
                                        if (iConyugal == 1)
                                        {
											if(sprintf_s(cMensaje, "llamarBeneficiarios::No cuenta con beneficiario manda llamar modulo CA0071.dll: lFolioSeguroNuevo: %ld, iFlagGeneral = %d", parametros.lFolioSeguro, parametros.iFlagGeneral) < 0){;}
                                            grabarLog(cMensaje);
                                            // Ruta del archivo DLL a ejecutar
                                            nombreArchivo("CA0071.DLL", cNombreProyecto, DIRECTORIO_CA);
                                            // Nombre de la función principal en el DLL
											if(sprintf_s(cNombreFuncionDLL, "CA0071") < 0){;}
                                            CargarDLL cargarDll(cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2, cOutputParam1, cOutputParam2);
                                            iRegresaDll = cargarDll.getResultado();
                                            if (strtol(cOutputParam1, NULL, 10) > 0) //si capturo beneficiarios
                                            {
                                                iFlagCapturoBeneficiariosClubNuevo = 2;
                                                iRespuesta = (short)strtol(cOutputParam2, NULL, 10);
                                            }
                                            else
                                            {
                                                iFlagCapturoBeneficiariosClubNuevo = 0;
                                                lCuota = 0L;
                                            }

                                            if (iRegresaDll <= 0)
                                            {
                                                AfxMessageBox("Error al cargar el programa CA0071.DLL");
                                            }
                                        }
                                        else
                                        {
                                            //AfxMessageBox("Entro Por estos Lados 4");
                                        //parametros.iTiendaFactura = 2;
											if(sprintf_s(cMensaje, "llamarBeneficiarios::No cuenta con beneficiario manda llamar modulo CA0108.dll: lFolioSeguroNuevo: %ld, iFlagGeneral = %d", parametros.lFolioSeguro, parametros.iFlagGeneral) < 0){;}
                                            grabarLog(cMensaje);
                                            // Ruta del archivo DLL a ejecutar
                                            nombreArchivo("CA0108.DLL", cNombreProyecto, DIRECTORIO_CA);
											if(sprintf_s(cNombreFuncionDLL, "CA0108") < 0){;}
                                            CargarDLL cargarDll(cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2, cOutputParam1, cOutputParam2);
                                            iRegresaDll = cargarDll.getResultado();
                                            if (strtol(cOutputParam1, NULL, 10) > 0) //si capturo beneficiarios
                                            {
                                                iFlagCapturoBeneficiariosClubNuevo = 2;

                                                iOpcion = AfxMessageBox("¿ Padece o ha padecido enfermedades del Corazón, Diabetes, SIDA, Cáncer, Insuficiencia renal, Hipertensión arterial, Cirrosis hepática, Hepatitis, Leucemia, Pancreatitis, Meningitis, Linfoma o Enfermedades Pulmonares?", MB_YESNO | MB_ICONQUESTION);
                                                if (iOpcion == IDYES)
                                                {
                                                    iRespuesta = 1;
                                                }
                                                else
                                                {
                                                    iRespuesta = 0;
                                                }
                                            }
                                            else
                                            {
                                                iFlagCapturoBeneficiariosClubNuevo = 0;
                                                lCuota = 0L;
                                            }

                                            if (iRegresaDll <= 0)
                                            {
                                                AfxMessageBox("Error al cargar el programa CA0108.DLL");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool CDlgCapturarDatosSeguro::obtenerSiTieneBeneficiariosCrSeguros(long lCliente)
{
    char cSql[70] = { 0 };
    bool valorRegresa = false;

	if(sprintf_s(cSql, "SELECT cvesinbeneficiarios FROM crseguros WHERE cliente = %09ld", lCliente) < 0){;}

    CMaximo flagCoppel(&odbc_1);

    if (flagCoppel.Exec(cSql))
    {
        flagCoppel.activarCols();
        if (flagCoppel.Leer())
        {
            iCveSinBeneficiarios = (int)flagCoppel.Total;
            valorRegresa = true;
        }
    }
    else
    {
        //Se obtiene el error
        flagCoppel.odbc->GetLastError(flagCoppel.GetHstmt());
        //grabarMensajeError("C", iCaja, , "CapturarAbono", "CDlgCapturarDatosSeguro", "obtenerSiTieneBeneficiariosCrSeguros", (LPTSTR)(LPCTSTR)sSqlTxt,.lEmpleado,"ERROR EN LA CONSULTA(obtenerSiTieneBeneficiariosCrSeguros)",FlagCoppel.odbc,iMuestraMsg);
    }

    return(valorRegresa);
}

int CDlgCapturarDatosSeguro::OfrecerSeguroClubConyugal(long lCliente)
{
    int iFlag = 1;
    char cSql[100] = { 0 };

	if(sprintf_s(cSql, "SELECT CASE WHEN estadocivil = 'C' THEN 2 ELSE 1 END FROM crcliente WHERE cliente = %ld", lCliente) < 0){;}
    CMaximo xEstadoCivil(&odbc_1);
    if (xEstadoCivil.Exec(cSql))
    {
        xEstadoCivil.activarCols();
        if (xEstadoCivil.Leer())
        {
            iFlag = xEstadoCivil.Total;
        }
    }
    else
    {
        xEstadoCivil.Error();
        xEstadoCivil.odbc->GetLastError(xEstadoCivil.GetHstmt());
        grabarMensajeError("C", iCaja, cIPServidorTiendaNumero, "CA0030", "CDlgCapturarAbono", "OfrecerSeguroClubConyugal", cSql, lEmpleado, "ERROR EN LA CONSULTA", xEstadoCivil.odbc, iMuestraMsg);
    }

    return iFlag;
}

long CDlgCapturarDatosSeguro::obtenerFolioSeguro()
{
    long lNumFolio = 0L;
    char cSql[50] = { 0 };

	if(sprintf_s(cSql, "SELECT gnincrementarfolio('C', '0', '%d', '0' )", FOLIOC_SEGURO) < 0){;}

    CMaximo FolioCoppel(&odbc);

    if (FolioCoppel.Exec(cSql))
    {
        FolioCoppel.activarCols();
        if (FolioCoppel.Leer())
        {
            lNumFolio = FolioCoppel.Total;
            lNumFolio++;
        }
    }
    else
    {
        FolioCoppel.odbc->GetLastError(FolioCoppel.GetHstmt());
        grabarMensajeError("C", iCaja, cIPServidorTiendaNumero, "CA0030", "CDlgCapturarAbono", "ObtenerFolioSeguro", cSql, lEmpleado, "ERROR EN LA CONSULTA", FolioCoppel.odbc, iMuestraMsg);
    }

    return lNumFolio;
}

int CDlgCapturarDatosSeguro::checarHuellaChw(long lCliente, int iCaja, long lEmpleado, int iMuestraMsg)
{
    CString  sNombre, sApellidoPaterno, sApellidoMaterno, sTexto;
    char cSexo = ' ';
    char cNombre[20] = { 0 }, cApellidoPaterno[20] = { 0 }, cApellidoMaterno[20] = { 0 };
    int i = 0, iFlag = 0, iFlagInvalido = 0, iFlagResp = 0, iTipo = 0;
    long lHuella = 0, lGteHuella = 0;
    long lRespuesta = 0L;
    bool bRespuesta = true, bProceso = false;
    char cSql[255] = { 0 };
    long lCteParametro = 0L, lFlagResp1 = 0L, lFlagResp2 = 0L;
    int iFlagRecaptura = 0;

	if(sprintf_s(cSql, "SELECT nombre,apellidopaterno,apellidomaterno,ciudad,colonia,puntualidad,situacionespecial,causasitesp,sexo,fechanacimiento,ingresomensual FROM crcliente WHERE cliente = %ld", lCliente) < 0 ){;}
    CConsultarCliente consultarClienteSQL(&odbc_1);
    if (!consultarClienteSQL.Exec(cSql))
    {
        consultarClienteSQL.odbc->GetLastError(consultarClienteSQL.GetHstmt());
        grabarMensajeError("C", iCaja, cIPServidorTiendaNumero, "CA0030", "CDlgCapturarAbono", "checarHuellaChw", cSql, lEmpleado, "ERROR EN LA CONSULTA", consultarClienteSQL.odbc, iMuestraMsg);
        bRespuesta = false;
    }
    else
    {
        consultarClienteSQL.activarCols();
        if (consultarClienteSQL.Leer())
        {
            sNombre.Format("%s", consultarClienteSQL.nombre);
            sNombre.Trim();
            sApellidoPaterno.Format("%s", consultarClienteSQL.apellidopaterno);
            sApellidoPaterno.Trim();
            sApellidoMaterno.Format("%s", consultarClienteSQL.apellidomaterno);
            sApellidoMaterno.Trim();
            cSexo = consultarClienteSQL.sexo[0];
			if(sprintf_s(cNombre, "%s", sNombre) < 0){;}
            if(sprintf_s(cApellidoPaterno, "%s", sApellidoPaterno) < 0){;}
            if(sprintf_s(cApellidoMaterno, "%s", sApellidoMaterno) < 0){;}
        }
    }

    if (bRespuesta)
    {
        lRespuesta = llamarChW(5, lCliente, iTienda, iCiudad, iCaja, iSistema, cNombre, cApellidoPaterno, cApellidoMaterno,
            cSexo, &odbc, cSql, bProceso, lCteParametro, lFlagResp1, lFlagResp2, 0, iFlagRecaptura); // gnwchwdl.cpp

        if (lFlagResp2 != 1)
        {
            sTexto.Format("HUELLA DEL CLIENTE NO HA SIDO RECONOCIDA. ¿AUTORIZACION DEL GERENTE?");
            if (AfxMessageBox(sTexto, MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                //llamar al cnw para validar huella del gerente
                validarHuellaEmpleadoGte01(&odbc, lGteHuella, 1, 2, lCliente, iTienda, SISTEMA_CAJAS, iCaja, "CA0030");//gnwSuplirHuellaGerente.cpp   
                if (lGteHuella == -1)
                {
                    lGteHuella = 0L;
                    iFlag = 0;
                    AfxMessageBox("NO HAY ENLACE CON EL SERVIDOR DE HUELLAS");
                }
                else
                {
                    if (lGteHuella < 16)
                    {
                        iFlag = 0;
                        pintarMensajesErrorPasstda(lGteHuella); //gnwvahue.cpp
                    }
                    else
                    {
                        iFlag = 1;
                    }
                }
            }
            else
            {
                iFlag = 0;
            }
        }
        else
        {
            iFlag = 1;
        }
    }

    return iFlag;
}

void CDlgCapturarDatosSeguro::cambioSeguro()
{
    CDlgCapturarCambioSeguro dlgCapturarCambioSeguro;
    dlgCapturarCambioSeguro.iAnioActual = iAnioActual;
    dlgCapturarCambioSeguro.iMesActual = iMesActual;
    dlgCapturarCambioSeguro.iDiaActual = iDiaActual;
    dlgCapturarCambioSeguro.lCliente = lCliente;
    dlgCapturarCambioSeguro.lEmpleado = lEmpleado;
    dlgCapturarCambioSeguro.iCaja = iCaja;
    dlgCapturarCambioSeguro.iTienda = iTienda;
    dlgCapturarCambioSeguro.iMuestraMsg = iMuestraMsg;
    dlgCapturarCambioSeguro.iEdadMaximaAbonoClubAdic = iEdadMaximaAbonoClubAdic;
    dlgCapturarCambioSeguro.iSegurosAdicionales = (short)iSegurosAdicionales;
    dlgCapturarCambioSeguro.iAnioNacimientoTitular = iAnioNacimiento;
    dlgCapturarCambioSeguro.iMesNacimientoTitular = iMesNacimiento;
    dlgCapturarCambioSeguro.iDiaNacimientoTitular = iDiaNacimiento;
    dlgCapturarCambioSeguro.iAnioVencimiento = iAnioVencimiento;
    dlgCapturarCambioSeguro.iMesVencimiento = iMesVencimiento;
    dlgCapturarCambioSeguro.iDiaVencimiento = iDiaVencimiento;
    dlgCapturarCambioSeguro.iCiudad = iCiudad;
    dlgCapturarCambioSeguro.lFolioSeguro = lFolioSeguro;
    if(sprintf_s(dlgCapturarCambioSeguro.cNombreCliente, cNombreCliente) < 0){;}
    if(sprintf_s(dlgCapturarCambioSeguro.cSexo, cSexo) < 0){;}
    dlgCapturarCambioSeguro.DoModal();
    iProcesoBeneficiariosAdicionales = dlgCapturarCambioSeguro.iProcesoBeneficiariosAdicionales;

    if (iProcesoBeneficiariosAdicionales != 1)
    {
        //CDialog2012:: OnCancel();
    }
}

bool CDlgCapturarDatosSeguro::consultarPrecioSeguroClub(short iFlagVenta)
{
    bool bRegresa = true;
    char cSql[200] = { 0 }, cMensajeSeguimiento[150] = { 0 };

    CConsultarPrecioSeguroClub precio(&odbc_1);

    if(sprintf_s(cSql, "SELECT precioseguro, montoseguro, maximoseguros FROM fun_consultarPlanesSeguroClub01( '%04d-%02d-%02d', '%ld', '%d', '1', '1', '0', '%d' )", iAnioActual, iMesActual, iDiaActual, lCliente, iSeguros, iFlagVenta) < 0){;}

    if (precio.Exec(cSql))
    {
        precio.activarCols();
        if (precio.leer())
        {
            iCantidadMaxSegurosCte = precio.maximoseguros;
            lPrecioSeguroClub = precio.precioseguro;

            if (iCantidadMaxSegurosCte == 0 && iNumeroSegurosAnterior > 0 && bBanderaSeguroVigente)
            {
                iCantidadMaxSegurosCte = (short)iNumeroSegurosAnterior;
                if(sprintf_s(cMensajeSeguimiento, "consultarPrecioSeguroClub:Consulta precios seguro y cantidad de seguros iCantidadMaxSegurosCte: %d", iCantidadMaxSegurosCte) < 0){;}
                grabarLog(cMensajeSeguimiento);
            }
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

bool CDlgCapturarDatosSeguro::consultarMesesaAbonar()
{
    bool bRegresa = true;
    char cSql[100] = { 0 };

    lMeses = 0;
    grabarLog("consultarMesesaAbonar: Consulta el total de meses abonar en funcion fun_mesesabonoseguroclub");
    CMaximo mesesAbono(&odbc);

    if(sprintf_s(cSql, "SELECT fun_mesesabonoseguroclub('%04d-%02d-%02d','%04d-%02d-%02d','%d' )", iAnioNacimiento, iMesNacimiento, iDiaNacimiento, iAnioVencimiento, iMesVencimiento, iDiaVencimiento, iEdadMaximaAbonoClub) < 0){;}

    if (mesesAbono.Exec(cSql))
    {
        mesesAbono.activarCols();
        if (mesesAbono.leer())
        {
            lMeses = mesesAbono.Total;
        }
    }
    else
    {
        bRegresa = false;
        mesesAbono.odbc->GetLastError(mesesAbono.GetHstmt());
        grabarMensajeError("C", iCaja, (LPTSTR)(LPCTSTR)odbc.m_strServer, "CA0030", "CDlgCapturarDatosSeguro", "consultarMesesaAbonar", cSql, lEmpleado, "Error al Consultar Meses a Abonar", mesesAbono.odbc, iMuestraMsg);
    }

    return bRegresa;
}

int CDlgCapturarDatosSeguro::edadAbono()
{
    int iEdadAbono = 0, iMesAbono = 0, iAnioAbono = 0, iDiaAbono = 0;

    if (bBanderaSeguroVigente)
    {
        iAnioAbono = iAnioVencimiento;
        iMesAbono = iMesVencimiento + iNumeroMeses;
        iDiaAbono = iDiaVencimiento;
    }
    else
    {
        iAnioAbono = iAnioActual;
        iMesAbono = iMesActual + iNumeroMeses;
        iDiaAbono = iDiaActual;
    }

    if (iMesAbono > 12)
    {
        iAnioAbono++;
    }

    iEdadAbono = iAnioAbono - iAnioNacimiento;

    if (iMesAbono < iMesNacimiento || (iMesAbono == iMesNacimiento && iDiaAbono < iDiaNacimiento))
    {
        iEdadAbono--;
    }

    return iEdadAbono;
}
void CDlgCapturarDatosSeguro::grabarLog(char *cTexto)
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