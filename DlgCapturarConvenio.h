#pragma once
#include "afxwin.h"
//#include "DialogoML.h"
#include "Dialog2012.h"

// CDlgCapturarConvenio dialog

class CDlgCapturarConvenio : public CDialog2012
{
    DECLARE_DYNAMIC(CDlgCapturarConvenio)

public:
    CDlgCapturarConvenio(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgCapturarConvenio();
    bool validarClick(int nTmpFocus);
    void asignarValor(int icontador);
    void asignarFoco();
    bool validarControl(char *cCadena);
    bool boton();
    bool validarControles();
    bool grabarConvenio();
    bool grabarConvenioTablaCorrespondiente();
    bool grabarConvenioTablaCorrespondienteValidado(int factura, int importe, short TipoCta);
    bool obtenerMesAnio();

    int iControles, iFoco, iDiaActual, iMesActual, iAnioActual,
        iFlagCapturo, iCaja, iMuestraMsg, iTotalVencido, iContadorConv;//Se agrego iTotalVencido para los convenios
    int imes, ianio, iTotalArreglo;//consultar mes y año
    long lEmpleado, lImporte, lSaldoCuenta, lFactura, lCliente;
    bool ShiftTab;
    short iPlazo, iTipoConvenio, iSubTipoConvenio, iTipo;

    // Dialog Data
    enum { IDD = IDD_DLGCAPTURARCONVENIO };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    CEdit m_grid;
    CEdit m_empleado;
    CEdit m_plazo;
    CEdit m_importe;
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    CButton m_cancelar;
    CButton m_aceptar;
    afx_msg void OnBnClickedCancelar();
    afx_msg void OnBnClickedAceptar();
    afx_msg void OnEnSetfocusEmpleado();
    afx_msg void OnEnSetfocusPlazo();
    afx_msg void OnEnSetfocusImporte();

    CStatic m_barra;
    CStatic m_mensaje;

	// 38970 Navidad Millonaria 2023
	bool sorteoNavidadMillonariaNav(int iTiendaNav, int iCajaNav, char* cIPServidorTiendaNumeroNav, int iAnioActualNav, int iMesActualNav, int iDiaActualNav);
	bool obtenerVigenciaLandingSorteo(CString sFechaTienda, int iduSorteo, int iCajaNav2, char* cServerNav2);
};