// GridCapturarAbono.h : Interfase para la clase GridCapturarAbono	
//									
////////////////////////////////////////////////////////////////////////////////
//										
//      NINGUNA LINEA COMENTADA INSERTADA EN FORMA AUTOMATICA DEBE SER REMOVIDA
//										
//	    mendoza.12abr2004				
//										
////////////////////////////////////////////////////////////////////////////////
#ifndef INCLUIDO_GridCapturarAbono_GridCapturarAbono
#define INCLUIDO_GridCapturarAbono_GridCapturarAbono
#include <ugctrl.h>
#include "GridDesplegarTotal.hpp"
#include "CargarDLL.h"


class GridCapturarAbono :public CUGCtrl
{
public:

    void asociar(LPVOID lpGrid);

    GridCapturarAbono();
    ~GridCapturarAbono();

    CString sServer;
    short iTienda, iCaja, iMuestraMsg, iTotalCuentas, iContEntero, iFlagCargo, iSistema, iFlagConvenioRealizado;
	CString sNoCuentaAConveniar;
    long lEmpleado, lCliente;
    bool bEdicion;
    bool bFocoGrid, bLlenarGrid;
    bool bTeclaBack, bFlagNegativo;
    GridDesplegarTotal m_grid2;
    CUGCell m_cell;
    char cArea;
    char cPuntualidad[3], cSubPuntualidad[3], cUsuario[30];


    void llenarGrid();
    //bool abrirConexion();
    void obtenerTotalAbono();


protected:

private:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMainFrame)
    //}}AFX_VIRTUAL
    LPVOID lpGrid;

    //{{AFX_MSG(GridCapturarAbono)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
    //+GRID_MENSAJES
    /*00*/virtual void OnSetup();
    /*37*/virtual void OnKeyDown(UINT *vcKey, BOOL processed);
    /*39*/virtual void OnKillFocus(int section, CWnd *pNewWnd);
    /*55*/virtual void OnSetFocus(int section);
    virtual void OnLClicked(int col, long row, int updn, RECT *rect, POINT *point, int processed);
    virtual int OnEditVerify(int col, long row, CWnd *edit, UINT *vcKey);
    virtual int  OnCanMove(int oldcol, long oldrow, int newcol, long newrow);
    virtual int OnEditContinue(int oldcol, long oldrow, int* newcol, long* newrow);
    virtual void OnCellChange(int oldcol, int newcol, long oldrow, long newrow);
    virtual void OnCharDown(UINT *vcKey, BOOL processed);
    virtual int OnEditFinish(int col, long row, CWnd *edit, LPCTSTR string, BOOL cancelFlag);
    virtual int OnEditStart(int col, long row, CWnd **edit);
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    //GridDesplegarTotal *m_grid2;
//-GRID_MENSAJES
};
#endif
