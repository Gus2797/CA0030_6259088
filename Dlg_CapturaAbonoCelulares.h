#pragma once
#include "afxwin.h"
#include "CargarDLL.h"
//#include "DialogoML.h"
#include "Dialog2012.h"
#include "CapturarAbono.h"
#include "gnwproto.hpp"



// Cuadro de diálogo de Dlg_CapturaAbonoCelulares

class Dlg_CapturaAbonoCelulares : public CDialog2012
{
	DECLARE_DYNAMIC(Dlg_CapturaAbonoCelulares)

public:
	//Variables
	CString jsonCelulares, meses, tmpMeses;
	int mesesAbonados, numeroPlazos, mesesRestantes, iNumeroMeses, mesesaAbonar,importeCelular,mensualidad;
	//Metodos
	bool ValidaMeses();

	Dlg_CapturaAbonoCelulares(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~Dlg_CapturaAbonoCelulares();

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_CAPTURAABONOCELULARES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_lblBarra;
	CStatic m_lblTexto;
	CEdit m_txtMeses;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};