#pragma once
#include "afxwin.h"
//#include "DialogoML.h"
#include "Dialog2012.h"

// CDlgCapturarNumEmpleSupervisor dialog

class CDlgCapturarNumEmpleSupervisor : public CDialog2012
{
    DECLARE_DYNAMIC(CDlgCapturarNumEmpleSupervisor)

public:

    CDlgCapturarNumEmpleSupervisor(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgCapturarNumEmpleSupervisor();

    void asignarFoco();
    bool validarControl(char *cCadena);
    bool boton();
    bool validarControles();
    bool buscarEmpleadoEnCobranza();

    int iControles, iFoco, iMuestraMsg, iCaja;
    long lEmpleadoSupervisor, lEmpleado;
    bool ShiftTab;

    // Dialog Data
    enum { IDD = IDD_DLGCAPTURAREMPLEADOSUPERVISOR };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    CEdit m_empleadoSupervisor;
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};