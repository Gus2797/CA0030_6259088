#pragma once
#include "afxwin.h"
#include "DialogoML.h"

// CDlgCapturarDatosComplementarios dialog

class CDlgCapturarDatosComplementarios : public CDialog
{
	DECLARE_DYNAMIC(CDlgCapturarDatosComplementarios)

public:
	CDlgCapturarDatosComplementarios(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCapturarDatosComplementarios();

// Dialog Data
	enum { IDD = IDD_DLGCAPTURARDATOSCOMPLEMENTARIOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	bool validarClick( int nTmpFocus );
	void asignarFoco();
	bool validarControl(char *cCadena);
	bool boton();
	bool validarControles();

	int iControles,iFoco;
	bool ShiftTab;

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_calle;
	CStatic m_colonia;
	CStatic m_casa;
	CStatic m_rumbo;
	CStatic m_nombre;
	CStatic m_apellidoPaterno;
	CStatic m_apellidoMaterno;
	CEdit m_casaPrf2;
	CEdit m_telefono2;
	CEdit m_sexo2;
	CEdit m_celular;
	CEdit m_dia;
	CEdit m_estadoCivil;
	CEdit m_ingreso;
	CEdit m_complemento;
	CEdit m_viveDesde;
	CEdit m_personasTrabajan;
	CEdit m_trabajaDesde;
	CEdit m_puesto;
	CButton m_noPideDatos;
	afx_msg void OnBnClickedNopidedatos();
	afx_msg void OnEnSetfocusCasaprf2();
	afx_msg void OnEnSetfocusTelefono2();
	afx_msg void OnEnSetfocusSexo2();
	CEdit m_mes;
	CEdit m_anio;
	afx_msg void OnEnSetfocusFechanacimiento();
	afx_msg void OnEnSetfocusMes();
	afx_msg void OnEnSetfocusAnio();
	afx_msg void OnEnSetfocusEstadocivil();
	afx_msg void OnEnSetfocusIngreso();
	afx_msg void OnEnSetfocusComplemento();
	afx_msg void OnEnSetfocusVivedesde();
	afx_msg void OnEnSetfocusPersonastrabajan();
	afx_msg void OnEnSetfocusTrabajadesde();
	afx_msg void OnEnSetfocusPuesto();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnSetfocusCelular();
	CEdit m_telefonoTrabajo;
	afx_msg void OnEnSetfocusTelefonotrabajo();
};
