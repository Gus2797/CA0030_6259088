#pragma once
#include "DialogoML.h"
#include "afxwin.h"

// CDlgMensajeCrezcaSuHogar dialog

class CDlgMensajeCrezcaSuHogar : public CDialog
{
	DECLARE_DYNAMIC(CDlgMensajeCrezcaSuHogar)

public:
	CDlgMensajeCrezcaSuHogar(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMensajeCrezcaSuHogar();

// Dialog Data
	enum { IDD = IDD_DLGMENSAJECREZCASUHOGAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool Si_NoAcepto(int iSiNoAcepto);	
	bool bAceptoInvitacion;
	bool imprimirLeyenda();
	bool impresionCajas(char *cRuta);
	bool impresionMueblesRopa(char *cRuta);
	
	CStatic m_mensajeCrezcasuHogar;
	
	CStatic m_barra, m_mensaje;
	char cServer[25],cIpServidorCartera[20],cIpServidorCredito[20],cNombre[20],cApellidoPaterno[20],cApellidoMaterno[20];
    int iTienda,iAnioActual,iMesActual,iDiaActual,iCajaActual,iMuestraMsg,iSistema,iFinLinea,iTipoImpresora;
	long lValorProyectoCH,lMensualidadCH,lEngancheCH,lTotalPagarCH,lCliente,lEmpleado;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
