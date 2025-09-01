// Dlg_CapturaAbonoCelulares.cpp: archivo de implementación
//

#include "stdafx.h"
#include "CapturarAbono.h"
#include "Dlg_CapturaAbonoCelulares.h"
#include "afxdialogex.h"
#include <include\ArduinoJson.h>


// Cuadro de diálogo de Dlg_CapturaAbonoCelulares

IMPLEMENT_DYNAMIC(Dlg_CapturaAbonoCelulares, CDialog2012)

	Dlg_CapturaAbonoCelulares::Dlg_CapturaAbonoCelulares(CWnd* pParent /*=NULL*/)
	: CDialog2012(Dlg_CapturaAbonoCelulares::IDD, pParent)
{
	this->mesesRestantes = 0;
	this->mesesAbonados = 0;
	this->numeroPlazos = 0;
	this->mesesRestantes = 0;
	this->iNumeroMeses = 0;
	this->mesesaAbonar = 0; 
	this->importeCelular = 0;
	this->mensualidad = 0;
}

Dlg_CapturaAbonoCelulares::~Dlg_CapturaAbonoCelulares()
{
	this->mesesRestantes = 0;
	this->mesesAbonados = 0;
	this->numeroPlazos = 0;
	this->mesesRestantes = 0;
	this->iNumeroMeses = 0;
	this->mesesaAbonar = 0; 
	this->importeCelular = 0;
	this->mensualidad = 0;
}

void Dlg_CapturaAbonoCelulares::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LBL_BARRA, m_lblBarra);
	DDX_Control(pDX, IDC_LBL_TEXTO, m_lblTexto);
	DDX_Control(pDX, IDC_TXT_MESES, m_txtMeses);
}


BEGIN_MESSAGE_MAP(Dlg_CapturaAbonoCelulares, CDialog)
END_MESSAGE_MAP()


// Controladores de mensajes de Dlg_CapturaAbonoCelulares


BOOL Dlg_CapturaAbonoCelulares::OnInitDialog()
{
	CDialog2012::OnInitDialog();
	CString barra = "", 
		sTexto = "";
	barra.Format("[ ESC ] Cancelar  [F10] Aceptar");
	crearMensajeNR(this, m_lblBarra, m_lblTexto);
	ponerMensajeNR(this,m_lblBarra, m_lblTexto,barra.GetBuffer()); 

	sTexto.Format("%d", iNumeroMeses);
	m_txtMeses.SetWindowText(sTexto);
	m_txtMeses.SetLimitText(2);
	return TRUE;
}


BOOL Dlg_CapturaAbonoCelulares::PreTranslateMessage(MSG* pMsg)
{
	CWnd *pWnd = GetFocus();
	CString sTexto = "";

	// Bloquea el scroll del Mouse.
	if( pMsg->message == WM_MOUSEWHEEL )
	{
		int iRueda = GET_WHEEL_DELTA_WPARAM( pMsg->wParam );
		{                    
			return TRUE;
		}
	}

	// Bloquea los dos click del mouse.
	if ( pMsg->message == WM_LBUTTONDOWN ||
		pMsg->message == WM_LBUTTONDBLCLK ||
		pMsg->message == WM_RBUTTONDOWN || pMsg->message == WM_RBUTTONDBLCLK )
	{
		pMsg->wParam = VK_SHIFT;
		return TRUE;
	}

	// Se bloquean caracteres especiales como: #%//#$/)=?=)!"#:_
	if ( ( GetKeyState( VK_SHIFT ) & 0x8000 ) && ( pMsg->wParam >= 32 && pMsg->wParam <= 47 ) ||
		( pMsg->wParam >= 58 && pMsg->wParam <= 64 ) ||
		( pMsg->wParam >= 91 && pMsg->wParam <= 95 ) ||
		( pMsg->wParam >= 123 && pMsg->wParam <= 255 ))
	{
		pMsg->wParam = NULL;
		return TRUE;
	}

	if( ( pMsg->wParam >= 65 && pMsg->wParam <= 90 )  ||
		( pMsg->wParam >= 96 && pMsg->wParam <= 105 ) ||
		( pMsg->wParam >= 48 && pMsg->wParam <= 57 )  ||
		pMsg->wParam == VK_DOWN	||
		pMsg->wParam == VK_TAB	||
		pMsg->wParam == VK_RIGHT	|| 
		pMsg->wParam == VK_UP		||
		pMsg->wParam == VK_LEFT   ||
		pMsg->wParam == VK_F2		||
		pMsg->wParam == VK_ESCAPE ||
		pMsg->wParam == VK_BACK	||
		pMsg->wParam == VK_TAB    ||
		pMsg->wParam == VK_SHIFT  ||
		pMsg->wParam == VK_DELETE || 
		pMsg->wParam == 35		||
		pMsg->wParam == 36		||
		pMsg->wParam == VK_F1		||
		pMsg->wParam == VK_F10	|| 
		!( ( GetKeyState( VK_SHIFT ) & 0x8000 ) &&( pMsg->wParam == 36 || pMsg->wParam == 35 || pMsg->wParam == VK_TAB   ) ) )
	{
		switch( pMsg->wParam )
		{
		case VK_RETURN:
			pMsg->wParam = NULL;
			break;

		case VK_ESCAPE:
			pMsg->wParam = NULL;
			this->OnCancel();
			break;

		case VK_F10:
			pMsg->wParam = NULL;
			m_txtMeses.GetWindowText(sTexto);
			sTexto.Trim();
			this->iNumeroMeses = _ttol(sTexto);
			if (ValidaMeses()==true){
				this->OnOK();
			}
			break;
		}
	}
	else
	{
		pMsg->wParam = NULL;
		return TRUE;
	}



	return CDialog2012::PreTranslateMessage(pMsg);
}


bool Dlg_CapturaAbonoCelulares::ValidaMeses(){
	bool regresa = false;
	CString mensaje = "";
	if (iNumeroMeses > 0){
		if(iNumeroMeses <= mesesRestantes){    //Validacion para no excedernos de los meses que se pueda abonar
			importeCelular = (mensualidad * iNumeroMeses);
			regresa = true;
		}else{
			mensaje.Format("Número de meses %i invalidos. Favor de capturar un numero de meses validos no mayor a %i meses.", iNumeroMeses, mesesRestantes);
			AfxMessageBox(mensaje, MB_ICONASTERISK);
		}
	} else {
		AfxMessageBox("Número de meses incorrectos.", MB_ICONASTERISK);
	}

	return regresa;
}