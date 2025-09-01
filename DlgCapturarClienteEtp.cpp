/* --------------------------------------------------------------------
    Fecha    :25/10/04 6:21  ( dd-mm-aa )
    Elabor¢  :Joel Armando Arana Garcia
    Solicit¢ :Lic. Jos‚ G. Mendoza
    Actividad:Captura de Abonos
   -------------------------------------------------------------------- */
   // DlgCapturarClienteEtp.cpp : implementation file
   //

#include "stdafx.h"
#include "CapturarAbono.h"
#include "DlgCapturarClienteEtp.h"
#include "gnwproto.hpp"
#include "sysCapturarAbono.h"

// CDlgCapturarClienteEtp dialog

IMPLEMENT_DYNAMIC(CDlgCapturarClienteEtp, CDialog2012)
CDlgCapturarClienteEtp::CDlgCapturarClienteEtp(CWnd* pParent /*=NULL*/)
    : CDialog2012(CDlgCapturarClienteEtp::IDD, pParent)
{
}

CDlgCapturarClienteEtp::~CDlgCapturarClienteEtp()
{
	ShiftTab = 0;
}

void CDlgCapturarClienteEtp::DoDataExchange(CDataExchange* pDX)
{
    CDialog2012::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CLIENTEETP, m_clienteEtp);
}


BEGIN_MESSAGE_MAP(CDlgCapturarClienteEtp, CDialog2012)
END_MESSAGE_MAP()


// CDlgCapturarClienteEtp message handlers

BOOL CDlgCapturarClienteEtp::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    char cPaso[255] = { 0 };

    ShiftTab = false;

    if (pMsg->message == WM_SYSKEYDOWN) // Teclas virtuales 
    {
        if (GetKeyState(VK_MENU) & 0x8000 || pMsg->wParam == VK_F10) //ELIMINO  ALT  
            pMsg->wParam = VK_SHIFT;
    }

    if (pMsg->message == WM_KEYDOWN)
    {
        if (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_UP)
        {
            iFoco--;
            if (iFoco < 0)	iFoco = 0;
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
                        asignarFoco();
                        if (iFoco == 1)
                        {	//Meter a una función
                            if (lClienteEtp > 0L)
                            {
                                CDialog2012::OnCancel();
                            }
                        }
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
                case VK_ESCAPE:
                    CDialog2012::OnCancel();
                    break;
                default:
                    break;
                }
            }
        }
    }

    return CDialog2012::PreTranslateMessage(pMsg);
}

BOOL CDlgCapturarClienteEtp::OnInitDialog()
{
    CDialog2012::OnInitDialog();

    // TODO:  Add extra initialization here
    m_clienteEtp.SetLimitText(9);
    iFoco = 0;
    asignarFoco();
    iControles = 1;
    lClienteEtp = 0L;

    return TRUE;  // return TRUE unless you set the focus to a control

    // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDlgCapturarClienteEtp::validarClick(int nTmpFocus)
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

void CDlgCapturarClienteEtp::asignarFoco()
{

    switch (iFoco)
    {
    case 0:
        m_clienteEtp.SetFocus();
        break;
    default:
        break;
    }
}

bool CDlgCapturarClienteEtp::validarControl(char * cCadena)
{
    bool valorRegresa = true;
    CString sTexto;

    switch (iFoco)
    {
    case 0:
        m_clienteEtp.GetWindowText(sTexto);
        sTexto.TrimLeft();
        sTexto.TrimRight();
        lClienteEtp = strtol(sTexto, NULL, 10);
        if (sTexto.IsEmpty())
        {
			if(sprintf_s(cCadena, strnlen(cCadena, 255), "%s", "El número de cliente no puede estar vacio...") < 0){;}
            lClienteEtp = 0L;
            m_clienteEtp.SetSel(0, 9);
            valorRegresa = false;
        }
        else
        {
            if (checar_digito(lClienteEtp) || esEmpleado(lClienteEtp) == 1)
            {
				if(sprintf_s(cCadena, strnlen(cCadena, 255), "%s", " !! DIGITO VERIFICADOR INVALIDO !! ") < 0){;}
                lClienteEtp = 0L;
                m_clienteEtp.SetWindowText("");
                valorRegresa = false;
            }
            else
            {
                if (lClienteEtp == 1)
                {
					if(sprintf_s(cCadena,strnlen(cCadena, 255), "%s", " CLIENTE INCORRECTO ") < 0){;}
                    lClienteEtp = 0L;
                    m_clienteEtp.SetWindowText("");
                    valorRegresa = false;
                }
            }
        }
        break;
    default:
        break;
    }

    return valorRegresa;
}

bool CDlgCapturarClienteEtp::boton()
{
    bool valorRegresa = false;

    return valorRegresa;
}

bool CDlgCapturarClienteEtp::validarControles()
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