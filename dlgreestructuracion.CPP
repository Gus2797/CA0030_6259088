#include "stdafx.h"
#include "sysCapturarAbono.h"
#include "CapturarAbono.h"
#include "DlgReestructuracion.h"
#include "DlgCapturarAbono.h"
#include ".\DlgReestructuracion.h"
#include "gnwproto.hpp"
#include <process.h>
#include "Dialog2012.h"

IMPLEMENT_DYNAMIC(CDlgReestructuracion, CDialog2012)
CDlgReestructuracion::CDlgReestructuracion(CWnd* pParent) : CDialog2012(CDlgReestructuracion::IDD, pParent)
{

}

CDlgReestructuracion::~CDlgReestructuracion()
{

}
void CDlgReestructuracion::DoDataExchange(CDataExchange* pDX)
{
    CDialog2012::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MSGREESTRUCTURA, m_mensajebox);
}

BEGIN_MESSAGE_MAP(CDlgReestructuracion, CDialog2012)
    ON_BN_CLICKED(ID_REESTRUCTURA, OnBnClickedReestructura)
    ON_BN_CLICKED(ID_CANCELAR, OnBnClickedCancelar)
    ON_WM_KEYDOWN()
END_MESSAGE_MAP()

BOOL CDlgReestructuracion::OnInitDialog()
{
    CDialog2012::OnInitDialog();
    m_mensajebox.SetWindowText(m_mensajerest);
    iFlag_Reestructura = 0;
    return TRUE;
}

void CDlgReestructuracion::OnBnClickedReestructura()
{
    iFlag_Reestructura = 1;
    _spawnl(P_WAIT, PATH_PUENTETOCS, PATH_PUENTETOCS, this->sServidorIP, this->sTienda, PATH_REESTTRUCTURA_DLL, NOMBRE_FUNCION_INICIAL, this->jsonParams, NULL);
    EndDialog(0);
}


void CDlgReestructuracion::OnBnClickedCancelar()
{
    iFlag_Reestructura = 0;
    EndDialog(0);
}

//<API FRANCISCO TRIZÒN, FELIX>
BOOL CDlgReestructuracion::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->wParam == VK_ESCAPE)
    {
        pMsg->wParam = NULL;
        iFlag_Reestructura = 0;
        this->EndDialog(0);
        return false;
    }
    if (pMsg->wParam == VK_F10)
    {
        iFlag_Reestructura = 1;
        _spawnl(P_WAIT, PATH_PUENTETOCS, PATH_PUENTETOCS, this->sServidorIP, this->sTienda, PATH_REESTTRUCTURA_DLL, NOMBRE_FUNCION_INICIAL, this->jsonParams, NULL);
        EndDialog(0);
    }
    return CDialog2012::PreTranslateMessage(pMsg);
}
//</API FRANCISCO TRIZÒN, FELIX>
