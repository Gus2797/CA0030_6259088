// DlgCapturarDatosComplementarios.cpp : implementation file
//

#include "stdafx.h"
#include "CapturarAbono.h"
#include "DlgCapturarDatosComplementarios.h"
#include ".\dlgcapturardatoscomplementarios.h"
#include "sysCapturarAbono.h"


// CDlgCapturarDatosComplementarios dialog

IMPLEMENT_DYNAMIC(CDlgCapturarDatosComplementarios, CDialog)
CDlgCapturarDatosComplementarios::CDlgCapturarDatosComplementarios(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCapturarDatosComplementarios::IDD, pParent)
{
}

CDlgCapturarDatosComplementarios::~CDlgCapturarDatosComplementarios()
{
}

void CDlgCapturarDatosComplementarios::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CALLE, m_calle);
	DDX_Control(pDX, IDC_COLONIA, m_colonia);
	DDX_Control(pDX, IDC_CASA, m_casa);
	DDX_Control(pDX, IDC_RUMBO, m_rumbo);
	DDX_Control(pDX, IDC_NOMBRE, m_nombre);
	DDX_Control(pDX, IDC_APELLIDOPATERNO, m_apellidoPaterno);
	DDX_Control(pDX, IDC_APELLIDOMATERNO, m_apellidoMaterno);
	DDX_Control(pDX, IDC_CASAPRF2, m_casaPrf2);
	DDX_Control(pDX, IDC_TELEFONO2, m_telefono2);
	DDX_Control(pDX, IDC_SEXO2, m_sexo2);
	DDX_Control(pDX, IDC_CELULAR, m_celular);
	DDX_Control(pDX, IDC_FECHANACIMIENTO, m_dia);
	DDX_Control(pDX, IDC_ESTADOCIVIL, m_estadoCivil);
	DDX_Control(pDX, IDC_INGRESO, m_ingreso);
	DDX_Control(pDX, IDC_COMPLEMENTO, m_complemento);
	DDX_Control(pDX, IDC_VIVEDESDE, m_viveDesde);
	DDX_Control(pDX, IDC_PERSONASTRABAJAN, m_personasTrabajan);
	DDX_Control(pDX, IDC_TRABAJADESDE, m_trabajaDesde);
	DDX_Control(pDX, IDC_PUESTO, m_puesto);
	DDX_Control(pDX, IDC_NOPIDEDATOS, m_noPideDatos);
	DDX_Control(pDX, IDC_MES, m_mes);
	DDX_Control(pDX, IDC_ANIO, m_anio);
	DDX_Control(pDX, IDC_TELEFONOTRABAJO, m_telefonoTrabajo);
}


BEGIN_MESSAGE_MAP(CDlgCapturarDatosComplementarios, CDialog)
	ON_BN_CLICKED(IDC_NOPIDEDATOS, OnBnClickedNopidedatos)
	ON_EN_SETFOCUS(IDC_CASAPRF2, OnEnSetfocusCasaprf2)
	ON_EN_SETFOCUS(IDC_TELEFONO2, OnEnSetfocusTelefono2)
	ON_EN_SETFOCUS(IDC_SEXO2, OnEnSetfocusSexo2)
	ON_EN_SETFOCUS(IDC_FECHANACIMIENTO, OnEnSetfocusFechanacimiento)
	ON_EN_SETFOCUS(IDC_MES, OnEnSetfocusMes)
	ON_EN_SETFOCUS(IDC_ANIO, OnEnSetfocusAnio)
	ON_EN_SETFOCUS(IDC_ESTADOCIVIL, OnEnSetfocusEstadocivil)
	ON_EN_SETFOCUS(IDC_INGRESO, OnEnSetfocusIngreso)
	ON_EN_SETFOCUS(IDC_COMPLEMENTO, OnEnSetfocusComplemento)
	ON_EN_SETFOCUS(IDC_VIVEDESDE, OnEnSetfocusVivedesde)
	ON_EN_SETFOCUS(IDC_PERSONASTRABAJAN, OnEnSetfocusPersonastrabajan)
	ON_EN_SETFOCUS(IDC_TRABAJADESDE, OnEnSetfocusTrabajadesde)
	ON_EN_SETFOCUS(IDC_PUESTO, OnEnSetfocusPuesto)
	ON_EN_SETFOCUS(IDC_CELULAR, OnEnSetfocusCelular)
	ON_EN_SETFOCUS(IDC_TELEFONOTRABAJO, OnEnSetfocusTelefonotrabajo)
END_MESSAGE_MAP()


// CDlgCapturarDatosComplementarios message handlers

void CDlgCapturarDatosComplementarios::OnBnClickedNopidedatos()
{
	// TODO: Add your control notification handler code here
}
			

void CDlgCapturarDatosComplementarios::OnEnSetfocusCasaprf2()
{
	// TODO: Add your control notification handler code here
	validarClick( 0 );
}

void CDlgCapturarDatosComplementarios::OnEnSetfocusTelefono2()
{
	// TODO: Add your control notification handler code here
	validarClick( 1 );

}

void CDlgCapturarDatosComplementarios::OnEnSetfocusSexo2()
{
	// TODO: Add your control notification handler code here
	validarClick( 2 );
}

void CDlgCapturarDatosComplementarios::OnEnSetfocusCelular()
{
	// TODO: Add your control notification handler code here
	validarClick( 3 );
}

void CDlgCapturarDatosComplementarios::OnEnSetfocusFechanacimiento()
{
	// TODO: Add your control notification handler code here
	validarClick( 4 );

}

void CDlgCapturarDatosComplementarios::OnEnSetfocusMes()
{
	// TODO: Add your control notification handler code here
	validarClick( 5 );
}

void CDlgCapturarDatosComplementarios::OnEnSetfocusAnio()
{
	// TODO: Add your control notification handler code here
	validarClick( 6 );
}

void CDlgCapturarDatosComplementarios::OnEnSetfocusEstadocivil()
{
	// TODO: Add your control notification handler code here
	validarClick( 7 );
}

void CDlgCapturarDatosComplementarios::OnEnSetfocusIngreso()
{
	// TODO: Add your control notification handler code here
	validarClick( 8 );
}

void CDlgCapturarDatosComplementarios::OnEnSetfocusComplemento()
{
	// TODO: Add your control notification handler code here
	validarClick( 16 );
}

void CDlgCapturarDatosComplementarios::OnEnSetfocusVivedesde()
{
	// TODO: Add your control notification handler code here
	validarClick( 10 );
}

void CDlgCapturarDatosComplementarios::OnEnSetfocusPersonastrabajan()
{
	// TODO: Add your control notification handler code here
	validarClick( 11 );

}

void CDlgCapturarDatosComplementarios::OnEnSetfocusTrabajadesde()
{
	// TODO: Add your control notification handler code here
	validarClick( 12 );
}

void CDlgCapturarDatosComplementarios::OnEnSetfocusPuesto()
{
	// TODO: Add your control notification handler code here
	validarClick( 13 );
}
void CDlgCapturarDatosComplementarios::OnEnSetfocusTelefonotrabajo()
{
	// TODO: Add your control notification handler code here
	validarClick( 14 );
}


bool CDlgCapturarDatosComplementarios::validarClick( int nTmpFocus)
{
    CString msg;
    int nElementoTmp, i;
    bool regresa = true;
	char cPaso[80]={0};

    if (iFoco < nTmpFocus)
    {
        // validar control anterior
        if (!validarControl(cPaso))
        {
            asignarFoco();
            if (iFoco != iControles)//numero de controles para los que se quieren se vea el mebsaje de error
            {
                if ( !ShiftTab )
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
            for (i=0; i<=nTmpFocus; i++)
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

void CDlgCapturarDatosComplementarios::asignarFoco()
{
     
 
	switch (iFoco)
    {
		case 0:
			m_casaPrf2.SetFocus();
			break;
		case 1:
			m_telefono2.SetFocus();
			break;
		case 2:
			m_sexo2.SetFocus();
			break;
		case 3:
			m_celular.SetFocus();
			break;
		case 4:
			m_dia.SetFocus();
			break;
		case 5:
			m_mes.SetFocus();
			break;
		case 6:
			m_anio.SetFocus();
			break;
		case 7:
			m_estadoCivil.SetFocus();
			break;
		case 8:
			m_ingreso.SetFocus();
			break;
		case 9:
			m_complemento.SetFocus();
			break;   
  		case 10:
			m_viveDesde.SetFocus();
			break;
		case 11:
			m_personasTrabajan.SetFocus();
			break;
		case 12:
			m_trabajaDesde.SetFocus();
			break;
		case 13:
			m_puesto.SetFocus();
			break;
		case 14:
			m_telefonoTrabajo.SetFocus();
			break;
		case 15:
			m_noPideDatos.SetFocus();
			break;
       default:
            break;
	}
}

bool CDlgCapturarDatosComplementarios::validarControl(char * cCadena)
{
    bool valorRegresa = true;
    CString sTexto;

    switch (iFoco)
    {
		case 0:
			m_casaPrf2.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena, strnlen(cCadena, size_t(cCadena)),"%s","Tipo de Casa Incorrecto") < 0){;}
                m_casaPrf2.SetSel(0,1);
                valorRegresa = false;
			}
			else
			{

			}
			break;
		case 1:
			m_telefono2.GetWindowText(sTexto);
			break;
		case 2:
			m_sexo2.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena, strnlen(cCadena, size_t(cCadena)),"%s","Dato Incorrecto") < 0){;}
                m_sexo2.SetSel(0,1);
                valorRegresa = false;
			}
			else
			{

			}

			break;
		case 3:
			m_celular.GetWindowText(sTexto);
			break;
		case 4:
			m_dia.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena, strnlen(cCadena, size_t(cCadena)), "%s","Dia Incorrecto") <0){;}
                m_dia.SetSel(0,2);
                valorRegresa = false;
			}
			else
			{

			}

			break;
		case 5:
			m_mes.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena, strnlen(cCadena, size_t(cCadena)), "%s","Mes Incorrecto") < 0){;}
                m_mes.SetSel(0,2);
                valorRegresa = false;
			}
			else
			{

			}
			break;
		case 6:
			m_anio.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena, strnlen(cCadena, size_t(cCadena)), "%s","AÑO Incorrecto") < 0){;}
                m_anio.SetSel(0,4);
                valorRegresa = false;
			}
			else
			{

			}
			break;
		case 7:
			m_estadoCivil.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena, strnlen(cCadena, size_t(cCadena)),"%s","DATO INCORRECTO") < 0){;}
                m_estadoCivil.SetSel(0,1);
                valorRegresa = false;
			}
			else
			{

			}
			break;
		case 8:
			m_ingreso.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena, strnlen(cCadena, size_t(cCadena)),"%s","INGRESO INCORRECTO") < 0){;}
                m_ingreso.SetSel(0,9);
                valorRegresa = false;
			}
			else
			{

			}
			break;
		case 9:
			m_complemento.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena,strnlen(cCadena, size_t(cCadena)),"%s","FAVOR DE CAPTURAR COMPLEMENTO") < 0){;}
                m_complemento.SetSel(0,30);
                valorRegresa = false;
			}
			else
			{

			}
			break;   
  		case 10:
			m_viveDesde.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena, strnlen(cCadena, size_t(cCadena)),"%s","AÑO DESDE CUANDO VIVE INCORRECTO") < 0){;}
                m_viveDesde.SetSel(0,4);
                valorRegresa = false;
			}
			else
			{

			}
			break;
		case 11:
			m_personasTrabajan.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena, strnlen(cCadena, size_t(cCadena)),"%s","DATO INCORRECTO") < 0){;}
                m_personasTrabajan.SetSel(0,2);
                valorRegresa = false;
			}
			else
			{

			}
			break;
		case 12:
			m_trabajaDesde.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena, strnlen(cCadena, size_t(cCadena)), "%s","AÑO TRABAJA DESDE INCORRECTO") < 0){;}
                m_trabajaDesde.SetSel(0,4);
                valorRegresa = false;
			}
			else
			{

			}
			break;
		case 13:
			m_puesto.GetWindowText(sTexto);
			sTexto.TrimLeft();
            sTexto.TrimRight();
            if (sTexto.IsEmpty())
            {
				if(sprintf_s(cCadena, strnlen(cCadena, size_t(cCadena)), "%s","FAVOR DE CAPTURAR PUESTO") < 0){;}
                m_puesto.SetSel(0,1);
                valorRegresa = false;
			}
			else
			{

			}
			break;
		case 14:
			m_telefonoTrabajo.GetWindowText(sTexto);
			break;
		default:
            break;
    }

    return valorRegresa;
}

bool CDlgCapturarDatosComplementarios::boton()
{
    CWnd *pWnd = GetFocus();
    bool valorRegresa = false;

    switch(pWnd->GetDlgCtrlID())
    {
        /*case IDC_CANCELAR:
            valorRegresa = true;
            break;		*/
        case IDC_NOPIDEDATOS:						
            valorRegresa = true;
            break;
    }
    return valorRegresa;
}

bool CDlgCapturarDatosComplementarios::validarControles()
{
	bool bValorRegresa = false;
	int i, iFocoAnt;
	bool bandera = true;
	char cPaso[80]={0};

	iFocoAnt = iFoco;

    for (i=0; i < iControles; i++)
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

    if ( bandera )
    {
		bValorRegresa = true;
    }

    iFoco = iFocoAnt;
	asignarFoco();
	return bValorRegresa;
}

BOOL CDlgCapturarDatosComplementarios::OnInitDialog()
{
	CDialog::OnInitDialog();
		
	// TODO:  Add extra initialization here
	//SetWindowText(" DATOS COMPLEMENTARIOS DEL CLIENTE ");
	m_casaPrf2.SetLimitText(1);
	m_telefono2.SetLimitText(8);
	m_sexo2.SetLimitText(1);
	m_celular.SetLimitText(10);
	m_dia.SetLimitText(2);
	m_mes.SetLimitText(2);
	m_anio.SetLimitText(4);
	m_estadoCivil.SetLimitText(1);
	m_ingreso.SetLimitText(6);
	m_complemento.SetLimitText(30);
	m_viveDesde.SetLimitText(4);
	m_personasTrabajan.SetLimitText(1);
	m_trabajaDesde.SetLimitText(4);
	m_puesto.SetLimitText(1);
	m_telefonoTrabajo.SetLimitText(8);

	iFoco=0;
	iControles=15;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgCapturarDatosComplementarios::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    char cPaso[80]={0};
	//int iColumna=0;
	CString sDato;
	/*CString sTexto;
	sTexto.Format("Foco: %d Grid: %d cte %09ld ",iFoco,m_grid.bFocoGrid,m_grid.lCliente );
	SetWindowText(sTexto);*/

    ShiftTab = false;


	if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
	{
		if ( pMsg->wParam == VK_LEFT || pMsg->wParam == VK_UP )
		{
			iFoco--;
			if(iFoco<0)	iFoco = 0;
			asignarFoco();
		}
		if ( pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB || pMsg->wParam == VK_DOWN || pMsg->wParam == VK_RIGHT )
		{
			if(!boton())
			{
				if ( iFoco <= iControles) //numero de controles
				{
					if (validarControl(cPaso))
					{
						iFoco++;
						asignarFoco();
					}
					else
					{
						if ( !ShiftTab )
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
			/*else
			{
				if ( pMsg->wParam == VK_RETURN )
				{
					switch (iFoco)
					{
						case 15:								
							OnBnClickedNopidedatos();		
							break;
						default:
							break;
					}
					return TRUE;
				}
				iFoco++;
				if (iFoco > 15) 
					iFoco=0;
				asignarFoco();
			}*/
		}
		else
		{
			if ( pMsg->wParam == VK_TAB && GetKeyState(VK_SHIFT) & 0x8000 )
			{
				ShiftTab = true;
			}
			else
			{
				switch ( pMsg->wParam )
				{
					case VK_F5:							
						OnBnClickedNopidedatos();		
						break;
					case VK_ESCAPE:
						CDialog::OnCancel();
						break;
					case VK_RIGHT:
						if (boton())
						{
							iFoco++;
							if (iFoco > 15)
								iFoco=0;
							asignarFoco();
						}
						break;
					default:
						break;
				}
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}