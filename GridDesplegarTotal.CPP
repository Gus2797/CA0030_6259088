/* --------------------------------------------------------------------
    Fecha    :25/10/04 6:21  ( dd-mm-aa )
    Elabor¢  :Joel Armando Arana Garcia
    Solicit¢ :Lic. Jos‚ G. Mendoza
    Actividad:Captura de Abonos
   -------------------------------------------------------------------- */
   /////////////////////////////////////////////////////////////////////////////
   //	Clase derivada de CUGCtrl
   //
#include <GridDesplegarTotal.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(GridDesplegarTotal, CUGCtrl)
    //{{AFX_MSG_MAP(GridDesplegarTotal)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Standard GridDesplegarTotal construction/destruction
GridDesplegarTotal::GridDesplegarTotal()
{
}

GridDesplegarTotal::~GridDesplegarTotal()
{
}

void GridDesplegarTotal::OnSetup()
{
    int i = 0, j = 0;

    SetNumberRows(22);
    SetDefColWidth(120);
    SetNumberCols(1);
    SetSH_Width(145);
    SetHS_Height(0);

    GetCell(0, 11, &m_cell);
    m_cell.SetBackColor(RGB(236, 233, 216));
    SetCell(0, 11, &m_cell);
    RedrawCell(0, 11);
    GetCell(0, 17, &m_cell);
    m_cell.SetBackColor(RGB(236, 233, 216));
    SetCell(0, 17, &m_cell);
    RedrawCell(0, 17);
    GetCell(0, 20, &m_cell);
    m_cell.SetBackColor(RGB(236, 233, 216));
    SetCell(0, 20, &m_cell);
    RedrawCell(0, 20);

    SetColWidth(-1, 0);
    QuickSetAlignment(0, -1, UG_ALIGNCENTER);
    QuickSetText(0, -1, "TOTAL");
    SetColWidth(0, 95);

    QuickSetText(0, 0, "");
    QuickSetText(0, 1, "");	//CUENTAS
    QuickSetText(0, 2, "");	//# CTA ACTUAL
    QuickSetText(0, 3, "");	//IMPORTE
    QuickSetText(0, 4, "");
    QuickSetText(0, 5, "");
    QuickSetText(0, 6, "");
    QuickSetText(0, 7, "");
    QuickSetText(0, 8, "");
    QuickSetText(0, 9, "");
    //QuickSetText(0,10,"");	//IMPORTE CONV.
    QuickSetText(0, 11, "");
    QuickSetText(0, 12, "");	//SALDO
    QuickSetText(0, 13, "");	//INTERES ADICIONAL
    QuickSetText(0, 14, "");	//BASE
    QuickSetText(0, 15, "");	//VENCIDO
    //QuickSetText(0,16,"");	//MINIMO
    QuickSetText(0, 17, "");
    QuickSetText(0, 18, "");	//SALDA CON
    //QuickSetText(0,19,"");	//BONIFICA
    QuickSetText(0, 20, "");
    QuickSetText(0, 22, "");

    for (i = 0; i < 22; i++)
    {
        QuickSetAlignment(-1, i, UG_ALIGNLEFT);
    }
    for (i = 0; i < 22; i++)
    {
        for (j = 0; j < GetNumberCols(); j++)
        {
            QuickSetAlignment(j, i, UG_ALIGNRIGHT);
        }
    }
    SetRowHeight(11, 3);
    SetRowHeight(17, 3);
    SetRowHeight(20, 3);

    GotoCell(0, 17);

    SetUserSizingMode(FALSE);
    bLlenarGrid2 = false;
    bFocoGrid2 = false;
}
void GridDesplegarTotal::OnKillFocus(int section, CWnd *pNewWnd)
{
    UNREFERENCED_PARAMETER(section);
    UNREFERENCED_PARAMETER(pNewWnd);
    bFocoGrid2 = false;
}
void GridDesplegarTotal::OnSetFocus(int section)
{
    UNREFERENCED_PARAMETER(section);
    bFocoGrid2 = true;
}

BOOL GridDesplegarTotal::PreTranslateMessage(MSG* pMsg)
{
    BOOL bRespuesta = FALSE;

    if (pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_RBUTTONDOWN)
    {
        bRespuesta = TRUE;
    }

    if (bRespuesta == TRUE)
    {
        return bRespuesta;
    }
    else
    {
        return CUGCtrl::PreTranslateMessage(pMsg);
    }
}