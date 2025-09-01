/* --------------------------------------------------------------------
    Fecha    :25/10/04 6:21  ( dd-mm-aa )
    Elabor¢  :Joel Armando Arana Garcia
    Solicit¢ :Lic. Jos‚ G. Mendoza
    Actividad:Captura de Abonos
   -------------------------------------------------------------------- */
   // DlgCapturarNumEmpleSupervisor.cpp : implementation file
   //

#include "stdafx.h"
#include "CapturarAbono.h"
#include "DlgCapturarNumEmpleSupervisor.h"
#include "gnwproto.hpp"
#include "syscapturarabono.h"

// CDlgCapturarNumEmpleSupervisor dialog

IMPLEMENT_DYNAMIC(CDlgCapturarNumEmpleSupervisor, CDialog2012)
CDlgCapturarNumEmpleSupervisor::CDlgCapturarNumEmpleSupervisor(CWnd* pParent /*=NULL*/)
    : CDialog2012(CDlgCapturarNumEmpleSupervisor::IDD, pParent)
{
    iControles = iFoco = iMuestraMsg = iCaja = 0;
    lEmpleadoSupervisor = lEmpleado = 0L;
    ShiftTab = false;
}

CDlgCapturarNumEmpleSupervisor::~CDlgCapturarNumEmpleSupervisor()
{
	iControles = 0;
}

void CDlgCapturarNumEmpleSupervisor::DoDataExchange(CDataExchange* pDX)
{
    CDialog2012::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EMPLEADOSUPERVISOR, m_empleadoSupervisor);
}


BEGIN_MESSAGE_MAP(CDlgCapturarNumEmpleSupervisor, CDialog2012)
END_MESSAGE_MAP()


// CDlgCapturarNumEmpleSupervisor message handlers

BOOL CDlgCapturarNumEmpleSupervisor::OnInitDialog()
{
    CDialog2012::OnInitDialog();

    //SetWindowText("CAPTURAR NUMERO DE EMPLEADO DEL SUPERVISOR");
    m_empleadoSupervisor.SetLimitText(8);
    iFoco = 0;
    iControles = 1;
    lEmpleadoSupervisor = 0L;

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgCapturarNumEmpleSupervisor::PreTranslateMessage(MSG* pMsg)
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
                            if (lEmpleadoSupervisor > 0L)
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

void CDlgCapturarNumEmpleSupervisor::asignarFoco()
{

    switch (iFoco)
    {
    case 0:
        m_empleadoSupervisor.SetFocus();
        break;
    default:
        break;
    }
}

bool CDlgCapturarNumEmpleSupervisor::validarControl(char * cCadena)
{
    bool valorRegresa = true;
    CString sTexto;
    char cSql[255] = { 0 };

    switch (iFoco)
    {
    case 0:
        m_empleadoSupervisor.GetWindowText(sTexto);
        sTexto.Trim();
        lEmpleadoSupervisor = strtol(sTexto, NULL, 10);
        if (sTexto.IsEmpty())
        {
			if(sprintf_s(cCadena, strnlen(cCadena, 255), "%s", "El número del supervisor  no puede estar vacio...") < 0){;}
            lEmpleadoSupervisor = 0L;
            m_empleadoSupervisor.SetSel(0, 8);
            valorRegresa = false;
        }
        else
        {
            if (esEmpleado(lEmpleadoSupervisor) != 1)
            {
				if(sprintf_s(cCadena, strnlen(cCadena, 255), "%s", " NUMERO DE EMPLEADO INVALIDO ") < 0){;}
                lEmpleadoSupervisor = 0L;
                m_empleadoSupervisor.SetSel(0, 8);
                valorRegresa = false;
            }
        }
        break;
    default:
        break;
    }

    return valorRegresa;
}

bool CDlgCapturarNumEmpleSupervisor::boton()
{
    //CWnd *pWnd = GetFocus();
    bool valorRegresa = false;

    return valorRegresa;
}

bool CDlgCapturarNumEmpleSupervisor::validarControles()
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

bool CDlgCapturarNumEmpleSupervisor::buscarEmpleadoEnCobranza()
{
    CString sCentro, sDigitos;
    int iDigitos;
    bool bContinuar = true;
    char cMsjCadena[255] = { 0 }, cSql[255] = { 0 };

    InfoEmpleado infoEmpleado;
    sCentro.Format("");
    sDigitos.Format("");
    if (buscarEmpleado(&odbc, infoEmpleado, lEmpleadoSupervisor, cMsjCadena, 0, cSql)) //gnwemple.cpp
    {
        sCentro.Format("%ld", infoEmpleado.lCentro);
        sDigitos.Format("%s", sCentro.Left(2));
        iDigitos = strtol(sDigitos, NULL, 10);
        if (iDigitos != 10)
        {
            bContinuar = false;
        }
    }

    return bContinuar;
}