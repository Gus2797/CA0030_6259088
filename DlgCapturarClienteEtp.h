#pragma once
#include "afxwin.h"
//#include "DialogoML.h"
#include "Dialog2012.h"

// CDlgCapturarClienteEtp dialog

class CDlgCapturarClienteEtp : public CDialog2012
{
    DECLARE_DYNAMIC(CDlgCapturarClienteEtp)

public:
    CDlgCapturarClienteEtp(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgCapturarClienteEtp();
    bool validarClick(int nTmpFocus);
    void asignarFoco();
    bool validarControl(char *cCadena);
    bool boton();
    bool validarControles();

    int iControles, iFoco;
    long lClienteEtp, lCteMaximo;
    bool ShiftTab;

    // Dialog Data
    enum { IDD = IDD_DLGCAPTURARCLIENTEETP };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnInitDialog();
    CEdit m_clienteEtp;
};
