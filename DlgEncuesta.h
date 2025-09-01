#pragma once
#include "afxwin.h"
#include "CargarDLL.h"
//#include "DialogoML.h"
#include "Dialog2012.h"
// CDlgEncuesta dialog

class CDlgEncuesta : public CDialog2012
{
    DECLARE_DYNAMIC(CDlgEncuesta)

public:
    CDlgEncuesta(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgEncuesta();
    bool validarClick(int nTmpFocus);
    void asignarFoco();
    bool validarControl(char *cCadena);
    bool validarControles();
    int buscarCiudad(int iNumCiudad);

    int iControles, iFoco, iCaja, iMuestraMsg, iCiudadCliente, iFlagAceptar, iNumCiudad;
    long lEmpleado, lTempZona, lTelefono, lZonaCliente, lColoniaTmp;
    bool ShiftTab;
    char cNombre[20], cApellidoMaterno[20], cApellidoPaterno[20], cNombreColonia[32];
    short iTienda, iCiudad;

    // Dialog Data
    enum { IDD = IDD_DLGENCUESTA };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    CEdit m_nombre;
    CEdit m_apellidoPaterno;
    CEdit m_apellidoMaterno;
    CEdit m_zona;
    CEdit m_telefono;
    afx_msg void OnEnSetfocusNombre2();
    afx_msg void OnEnSetfocusApellidopaterno2();
    afx_msg void OnEnSetfocusApellidomaterno2();
    afx_msg void OnEnSetfocusZona();
    afx_msg void OnEnSetfocusTelefono2();
    CButton m_aceptar;
    afx_msg void OnBnClickedAceptar();
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    CStatic m_mensajex;

    CStatic m_barra;
    CStatic m_mensaje;

    CEdit m_colonia;
    CStatic m_nombreColonia;
    afx_msg void OnEnSetfocusColonia();
};
