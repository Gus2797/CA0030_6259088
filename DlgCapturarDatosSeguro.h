#pragma once
#include "afxwin.h"
#include "CargarDLL.h"
//#include "DialogoML.h"
#include "Dialog2012.h"

// CDlgCapturarDatosSeguro dialog

class CDlgCapturarDatosSeguro : public CDialog2012
{
    DECLARE_DYNAMIC(CDlgCapturarDatosSeguro)

public:
    CDlgCapturarDatosSeguro(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgCapturarDatosSeguro();

    bool validarClick(int nTmpFocus);
    void asignarFoco();
    bool validarControl(char *cCadena);
    bool boton();
    bool validarControles();
    void procesoSeguro();
    int mesesPagados(char *cFechaVencimiento);
    int mesesAbonar(int iEdad, int iMesEdad);
    void llamarBeneficiarios();
    bool obtenerSiTieneBeneficiariosCrSeguros(long lCliente);
    int OfrecerSeguroClubConyugal(long lCliente);
    long obtenerFolioSeguro();
    int checarHuellaChw(long lCliente, int iCaja, long lEmpleado, int iMuestraMsg);
    void cambioSeguro();
    bool consultarPrecioSeguroClub(short iFlagVenta);
    bool consultarMesesaAbonar();
    int edadAbono();
    void grabarLog(char *cTexto);

    long lEmpleado, lMeses, lCuota, lPrecioSeguroClub, lFolioSeguro, lFolioSeguroNuevo;
    int iControles, iFoco, iMeses, iSeguros, iEsSeguroClub, iCaja, iMuestraMsg, iFlagBanorte,
        iMesVencimiento, iAnioVencimiento, iDiaVencimiento, lCliente, iAnioNacimiento,
        iMesNacimiento, iDiaNacimiento, iAnioActual, iMesActual, iDiaActual, iEdad, iMesEdad,
        iNumeroSegurosAnterior, iNumeroMeses, iCantidad, iRango, iNumSeguros, iMax, iConyugal, iCiudad,
        iFlagConsulta, iFlagCapturoBeneficiariosClubNuevo, iSistema,
        iFlagCancelo, iFlagCapturaBeneficiario, iCveSinBeneficiarios,
        iFlagSeguroAdicional, iEdadCliente, iPuntualidad, iTienda, iOrigenSeguro, iProcesoBeneficiariosAdicionales, iNumSegurosNuevo;
    bool ShiftTab, bBanderaTieneClub, bBanderaSeguroVigente, bEsCambioPlanSeguro, bAutorizado;
    char cFechaVencimiento[10];

    char cIPServidorTiendaNumero[20], cNombreCliente[50], cSexo[2];
    int iRespondio, iColumnaClub, iColumnaClubActual, iSegurosAdicionales;
    short iRespuesta, iEdadMinimaClub, iEdadMaximaClub, iEdadMaximaClubAdicional, iEdadMaximaAbonoClub, iEdadMaximaAbonoClubAdic, iCantidadMaxSegurosCte;

    // Dialog Data
    enum { IDD = IDD_DLGCAPTURARDATOSSEGURO };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    CEdit m_seguros;
    CEdit m_meses;
    CButton m_cancelar;
    CButton m_aceptar;
    afx_msg void OnBnClickedCancelar();
    afx_msg void OnBnClickedAceptar();
    afx_msg void OnEnSetfocusSeguros();
    afx_msg void OnEnSetfocusMeses();
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    CStatic m_barra;
    CStatic m_mensaje;

};
