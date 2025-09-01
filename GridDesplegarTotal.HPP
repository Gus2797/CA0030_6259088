// GridDesplegarTotal.h : Interfase para la clase GridDesplegarTotal	
//									
////////////////////////////////////////////////////////////////////////////////
//										
//      NINGUNA LINEA COMENTADA INSERTADA EN FORMA AUTOMATICA DEBE SER REMOVIDA
//										
//	    mendoza.12abr2004				
//										
////////////////////////////////////////////////////////////////////////////////
#ifndef INCLUIDO_GridDesplegarTotal_GridDesplegarTotal
#define INCLUIDO_GridDesplegarTotal_GridDesplegarTotal
#include <ugctrl.h>

class GridDesplegarTotal :public CUGCtrl
{
public:
    GridDesplegarTotal();
    ~GridDesplegarTotal();

    bool bFocoGrid2, bLlenarGrid2;
    long lTotalAbonos;
    CUGCell m_cell;


protected:

private:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMainFrame)
    //}}AFX_VIRTUAL


    //{{AFX_MSG(GridDesplegarTotal)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
    //+GRID_MENSAJES
    /*00*/virtual void OnSetup();
    /*39*/virtual void OnKillFocus(int section, CWnd *pNewWnd);
    /*55*/virtual void OnSetFocus(int section);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //-GRID_MENSAJES
};
#endif
