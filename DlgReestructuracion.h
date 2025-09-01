#pragma once
#include "afxwin.h"
#include "CargarDLL.h"
//#include "DialogoML.h"
#include "Dialog2012.h"

#define PATH_PUENTETOCS "C:\\sys\\PROGS\\PuenteToCSharp.EXE"
#define PATH_REESTTRUCTURA_DLL "C:\\sys\\PROGX\\ca\\CA0208.dll"
#define NOMBRE_FUNCION_INICIAL "ReestructuraCpl.fondo"

class CDlgReestructuracion : public CDialog2012 {
    DECLARE_DYNAMIC(CDlgReestructuracion)
public:
    CDlgReestructuracion(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgReestructuracion();

    enum { IDD = IDD_DLGREESTRUCTURA };    // DDX/DDV support

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

public:
    virtual BOOL OnInitDialog();
    int iFlag_Reestructura;
    CStatic m_mensajebox;
    CString m_mensajerest;
    CString sTienda;
    CString sServidorIP;
    CString jsonParams;

    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedReestructura();
    afx_msg void OnBnClickedCancelar();
    virtual BOOL PreTranslateMessage(MSG* pMsg);


};

