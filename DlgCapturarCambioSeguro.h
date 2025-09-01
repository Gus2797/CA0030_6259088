#pragma once
#include "afxwin.h"
#include "Dialog2012.h"
// DlgCapturarCambioSeguro dialog

class CDlgCapturarCambioSeguro : public CDialog2012
{
    DECLARE_DYNAMIC(CDlgCapturarCambioSeguro)

public:
    CDlgCapturarCambioSeguro(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgCapturarCambioSeguro();

    bool validarClick(int nTmpFocus);
    void asignarFoco();
    bool validarControl(char *cCadena);
    bool validarControles();
    void fechaNacimiento();
    void actualizarSeguros();
    bool obtenerAdicionales();
    bool consultarPrecioSeguroClub();
    void grabarLog(char *cTexto);

    int iControles, iFoco, iAnioNacimiento, iMesNacimiento, iDiaNacimiento, iAnioActual, iMesActual, iDiaActual,
        iEdad, iNumeroSegurosAnterior, iNumSeguros, iFlagCancelo, iFolio, iCaja, iTienda, iMuestraMsg, iProcesoBeneficiariosAdicionales,
        iAnioNacimientoTitular, iMesNacimientoTitular, iDiaNacimientoTitular, iAnioVencimiento, iMesVencimiento, iDiaVencimiento, iCiudad;
    short iSegurosAdicionales;
    long lCliente, lEmpleado, lPrecioSeguroClub, lFolioSeguro;
    bool ShiftTab;
    short iEdadMaximaAbonoClubAdic, iCantidadMaxSegurosCte;
    char cNombreCliente[50], cSexo[2];

    // Dialog Data
    enum { IDD = IDD_DLGCAPTURARCAMBIOSEGURO };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:

    CEdit m_seguros;

    afx_msg void OnEnSetfocusAsegurados();
    afx_msg void OnEnSetfocusSeguros();
    afx_msg void OnCbnSelchangeAsegurados();
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    CStatic m_barra;
    CStatic m_mensaje;

    afx_msg void OnBnClickedCancelar();
    afx_msg void OnBnClickedAceptar();
    CComboBox m_asegurados;
    CComboBox m_seguros2;
    CComboBox m_fechaNacimientoAdic;
};