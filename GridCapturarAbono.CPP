/* --------------------------------------------------------------------
    Fecha    :25/10/04 6:21  ( dd-mm-aa )
    Elabor¢  :Joel Armando Arana Garcia
    Solicit¢ :Lic. Jos‚ G. Mendoza
    Actividad:Captura de AbonosiTotalCuentas
   -------------------------------------------------------------------- */
   /////////////////////////////////////////////////////////////////////////////
   //	Clase derivada de CUGCtrl
   //
#include <GridCapturarAbono.hpp>
#include "sysCapturarAbono.h"
#include <GridDesplegarTotal.hpp>
#include "password.hpp"
//#include "ctrlglob.hpp"

#include "gnwProto.hpp"
#include "wTienda.hpp"
#include "process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(GridCapturarAbono, CUGCtrl)
    //{{AFX_MSG_MAP(GridCapturarAbono)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Standard GridCapturarAbono construction/destruction
GridCapturarAbono::GridCapturarAbono()
{
    SecureZeroMemory(cPuntualidad, sizeof(cPuntualidad));
    SecureZeroMemory(cSubPuntualidad, sizeof(cSubPuntualidad));
    SecureZeroMemory(cUsuario, sizeof(cUsuario));
    iTotalCuentas = 0;
	iFlagConvenioRealizado = 0;
}

GridCapturarAbono::~GridCapturarAbono()
{
	lCliente = 0;
	iFlagCargo = 0;
	iTotalCuentas = 0;
	iFlagConvenioRealizado = 0;
	cArea = 0;
	iTienda = 0;
	iSistema = 0;
	iCaja = 0;
	lEmpleado = 0;
	iMuestraMsg = 0;
}

void GridCapturarAbono::OnSetup()
{
    int i = 0, j = 0;
    //******* Get the index value of the font. 
    int fontID = AddFont("Lucida Console Bold", 14, 200);

    //****** Set the rows and columns 
    SetNumberRows(40);
    SetNumberCols(8);
    SetDefColWidth(120);

    SetRowHeight(22, 0); //cantidad de seguros capturada,												tipo cobertura Seguro Auto
    SetRowHeight(23, 0); //numero de meses del seguro capturado											Numeros de mese que pago seguro auto
    SetRowHeight(24, 0); //Flag seguro conyugal,															meses pagados de la poliza del seguro auto
    SetRowHeight(25, 0); //Fecha Vencimiento Anterior del seguro											Fecha Vencimiento Seguro Auto
    SetRowHeight(26, 0); // Salda Con Anterior cuentas de muebles,										modelo del automovil
    SetRowHeight(27, 0); // tipo de convenio																Fecha de vigencia sel seguro auto
    SetRowHeight(28, 0); //flag capturo convenio a la cuenta
    SetRowHeight(29, 0); //flag para saber si el seguro esta vigente										Poliza Anterior
    SetRowHeight(30, 0); //status para saber si la cuenta de obtuvo del ccuenta por si hay anexos		Importe de venta
    SetRowHeight(31, 0); //cantidad de seguros anterior													Fecha de Venta del Seguro Auto
    SetRowHeight(32, 0); //iFlagMesUltimoMovimiento toma valor menu afirme opcion F4.
    SetRowHeight(33, 0); // Fecha de Vencimiento															Fecha Vencimiento nueva seguro auto
    SetRowHeight(34, 0); // SubTipo de Convenio															tipo Vehiculo
    SetRowHeight(35, 0); // Interes Adicional Primer Mes													Fecha de activacion
    SetRowHeight(36, 0); //Tipo Producto de la tabla CrCMuebles,											Si se genera poliza nueva
    SetRowHeight(37, 0); //para almacenar el tipo de cuenta de cada cartera de las cuentas del cliente
    SetRowHeight(38, 0); //para almacenar el iPorcentajeBonificacion
    SetRowHeight(39, 0); //para almacenar la fecha de ultima compra


    SetSH_Width(145);
    SetHS_Height(0);
    for (i = -1; i < 8; i++)
    {
        QuickSetFont(i, -1, fontID);

        GetCell(i, 11, &m_cell);
        m_cell.SetBackColor(RGB(236, 233, 216));
        SetCell(i, 11, &m_cell);
        RedrawCell(i, 11);
        GetCell(i, 17, &m_cell);
        m_cell.SetBackColor(RGB(236, 233, 216));
        SetCell(i, 17, &m_cell);
        RedrawCell(i, 17);
        GetCell(i, 20, &m_cell);
        m_cell.SetBackColor(RGB(236, 233, 216));
        SetCell(i, 20, &m_cell);
        RedrawCell(i, 20);
    }

    QuickSetText(0, -1, "ROPA");
    QuickSetText(1, -1, "ARTÍCULO 1");
    QuickSetText(2, -1, "ARTÍCULO 2");
    QuickSetText(3, -1, "ARTÍCULO 3");
    QuickSetText(4, -1, "ARTÍCULO 4");
    QuickSetText(5, -1, "ARTÍCULO 5");
    QuickSetText(6, -1, "ARTÍCULO 6");
    QuickSetText(7, -1, "ARTÍCULO 7");


    SetColWidth(-1, 120);
    SetColWidth(0, 83);
    SetColWidth(1, 83);
    SetColWidth(2, 83);
    SetColWidth(3, 83);
    SetColWidth(4, 83);
    SetColWidth(5, 83);
    SetColWidth(6, 83);
    SetColWidth(7, 83);


    QuickSetText(-1, 0, "TIENDA");
    QuickSetText(-1, 1, "FACTURA");
    QuickSetText(-1, 2, "FECHA COMPRA");
    QuickSetText(-1, 3, "IMPORTE");
    QuickSetText(-1, 4, "");
    QuickSetText(-1, 5, "F.U.M.");
    QuickSetText(-1, 6, "F.S.C.");
    QuickSetText(-1, 7, "FECHA CONV");
    QuickSetText(-1, 8, "EFECTUO CONV");
    QuickSetText(-1, 9, "PLAZO");
    QuickSetText(-1, 10, "IMPORTE CONV.");
    QuickSetText(-1, 12, "SALDO");
    QuickSetText(-1, 13, "INTERÉS ADIC.");
    QuickSetText(-1, 14, "BASE");
    QuickSetText(-1, 15, "VENCIDO");
    QuickSetText(-1, 16, "MÍNIMO");
    QuickSetText(-1, 18, "SALDA CON");
    QuickSetText(-1, 19, "BONIFICA");
    QuickSetText(-1, 21, "SU PAGO");

    for (i = 0; i < 34; i++)
    {
        QuickSetAlignment(-1, i, UG_ALIGNLEFT);
    }
    for (i = 0; i < 34; i++)
    {
        for (j = 0; j < GetNumberCols(); j++)
        {
            QuickSetAlignment(j, i, UG_ALIGNRIGHT);
        }
    }
    SetRowHeight(11, 3);
    SetRowHeight(17, 3);
    SetRowHeight(20, 3);

    GotoCell(0, 21);

    SetUserSizingMode(FALSE);
    bLlenarGrid = false;
    bFocoGrid = false;
    bEdicion = false;
    iContEntero = 0;
}

void GridCapturarAbono::OnKillFocus(int section, CWnd *pNewWnd)
{
    UNREFERENCED_PARAMETER(section);
    UNREFERENCED_PARAMETER(pNewWnd);
    bFocoGrid = false;
}

void GridCapturarAbono::OnSetFocus(int section)
{
    UNREFERENCED_PARAMETER(section);
    bFocoGrid = true;
}

void GridCapturarAbono::llenarGrid()
{
}

void GridCapturarAbono::OnKeyDown(UINT *vcKey, BOOL processed)
{
    UNREFERENCED_PARAMETER(*vcKey);
    UNREFERENCED_PARAMETER(processed);
    int iTecla = 0, iColumna = 0, iRen = 0;
    CString sTxt;
    char cTxt[20] = { 0 };

    bTeclaBack = false;
    iTecla = int(*vcKey);
    iColumna = GetCurrentCol();

    QuickGetText(iColumna, -1, &sTxt);
    sTxt.Trim();
    if(sprintf_s(cTxt, "%s", sTxt) < 0){;}

    iRen = GetCurrentRow();
    if (iRen != 21) iRen = 21;
    GotoCell(iColumna--, iRen);
    switch (iTecla)
    {
    case VK_UP:    // Arriba	38
        GotoCell(iColumna--, iRen);
        break;
    case VK_DOWN:    // Abajo	40
    case VK_RETURN:
    case VK_TAB:
        GotoCell(iColumna++, iRen);
        break;
    case VK_BACK:
        bTeclaBack = true;
        if (memcmp(cTxt, "SEGURO", 6) != 0 && memcmp(cTxt, "P.FAMILIAR", 10) != 0 && memcmp(cTxt, "PLAN MOVISTAR", 13) != 0 && memcmp(cTxt, "P.SALUD", 7) != 0)
        {
            StartEdit();
        }
        break;
    default:
        break;
    }
}

void GridCapturarAbono::OnLClicked(int col, long row, int updn, RECT *rect, POINT *point, int processed)
{
    UNREFERENCED_PARAMETER(rect);
    UNREFERENCED_PARAMETER(processed);
    UNREFERENCED_PARAMETER(point);
    UNREFERENCED_PARAMETER(col);
    UNREFERENCED_PARAMETER(updn);
    int iCol = 0;
    CString sDato, sConcepto;
    char cTxt[20] = { 0 };

    bFocoGrid = true;
    iCol = GetCurrentCol();
    QuickGetText(iCol, 12, &sDato);
    sDato.Trim();

    QuickGetText(iCol, -1, &sConcepto);
    sConcepto.Trim();
    if(printf_s(cTxt, "%s", sConcepto) < 0){;}

    if (strtol(sDato, NULL, 10) > 0L || (memcmp(cTxt, "SEGURO", 6) == 0 || memcmp(cTxt, "P.FAMILIAR", 10) == 0) || lCliente == 1708 || memcmp(cTxt, "ROPA", 4) == 0 || memcmp(cTxt, "T.AIRE", 6) == 0 || memcmp(cTxt, "PLAN MOVISTAR", 13) == 0 || memcmp(cTxt, "P.SALUD", 7) == 0)
    {
        obtenerTotalAbono();
        {
            if (row != 21) row = 21;
            GotoCell(iCol, row);
            if (memcmp(cTxt, "SEGURO", 6) != 0 && memcmp(cTxt, "P.FAMILIAR", 10) != 0 && memcmp(cTxt, "PLAN MOVISTAR", 13) != 0 && memcmp(cTxt, "P.SALUD", 7) != 0)
            {
                StartEdit();
            }
        }
    }
}

void GridCapturarAbono::asociar(LPVOID lpGrid)
{
    GridCapturarAbono::lpGrid = lpGrid;
}

int GridCapturarAbono::OnEditVerify(int col, long row, CWnd *edit, UINT *vcKey)
{
    UNREFERENCED_PARAMETER(edit);
    UNREFERENCED_PARAMETER(col);
    CString sValor, sDato;

    if (row == 21)
    {
        if (((*vcKey >= 48 && *vcKey <= 57)) || (iFlagCargo == 0 && *vcKey == 45))
        {
            if (iFlagCargo == 0 && *vcKey == 45 && iContEntero == 0 && bFlagNegativo == false)
            {
                //Flag de signo -
                bFlagNegativo = true;
                iContEntero--;
            }
            else if (iFlagCargo == 0 && ((bFlagNegativo == true && *vcKey == 45) || (*vcKey == 45 && iContEntero != 0) ||
                (bFlagNegativo == false && *vcKey != 45)))
            {
                return FALSE;
            }

            iContEntero++;
            if (iContEntero <= 0 && iFlagCargo != 0)
            {
                iContEntero = 0;
                return FALSE;
            }
            else
            {
                if (iContEntero > 6)
                {
                    iContEntero = 6;
                    return FALSE;
                }
                else
                {
                    return TRUE;
                }
            }
        }
        else if (*vcKey == VK_BACK && iContEntero == 0)
        {
            bFlagNegativo = false;
        }

        if (*vcKey == 8)
        {
            iContEntero--;
            if (iContEntero <= 0) iContEntero = 0;
            if (iContEntero > 6) iContEntero = 6;

            return TRUE;
        }

    }
    return FALSE;
}

int GridCapturarAbono::OnEditStart(int col, long row, CWnd **edit)
{
    CString sTxt;
	char cTxt[20] = { 0 };

	if(iFlagConvenioRealizado == 1)
	{
		CString sColumnName, sColumnNameFormat;
		QuickGetText(col, -1, &sColumnName);

		sColumnName.Trim();

		sColumnNameFormat.Format("-%s-", sColumnName);
		auto found = sNoCuentaAConveniar.Find(sColumnNameFormat);
					
		if (found != std::string::npos)
		{
			return FALSE;
		}
	}

    UNREFERENCED_PARAMETER(col);
    UNREFERENCED_PARAMETER(row);
    UNREFERENCED_PARAMETER(edit);

	QuickGetText(GetCurrentCol(), -1, &sTxt);
	sTxt.Trim();
    if(sprintf_s(cTxt, "%s", sTxt) < 0){;}
	if (memcmp(cTxt, "SEG. MOTOS", 10) == 0 || memcmp(cTxt, "P. CELULAR", 10) == 0)
	{
		return FALSE;
	}

    bEdicion = true;
    bFlagNegativo = false;

    return TRUE;
}

int GridCapturarAbono::OnCanMove(int oldcol, long oldrow, int newcol, long newrow)
{
    UNREFERENCED_PARAMETER(oldcol);
    UNREFERENCED_PARAMETER(oldrow);
    if (newrow != 21 || newcol < 0 || newcol > iTotalCuentas - 1)
    {
        return FALSE;
    }
    return TRUE;
}

int GridCapturarAbono::OnEditContinue(int oldcol, long oldrow, int* newcol, long* newrow)
{
    if (oldrow == 21)
    {
        *newrow = oldrow;
        *newcol = oldcol + 1;
        return TRUE;
    }
    return FALSE;
}

void  GridCapturarAbono::OnCellChange(int oldcol, int newcol, long oldrow, long newrow)
{
    UNREFERENCED_PARAMETER(newcol);
    UNREFERENCED_PARAMETER(newrow);
    CString sValor, sDato;
    QuickGetText(oldcol, oldrow, &sValor);
    if (sValor == "" && (oldrow == 21))
    {
        QuickGetText(oldcol, 12, &sDato);
        sDato.Trim();
        if (strtol(sDato, NULL, 10) > 0L || lCliente == 1708)
        {
            sValor = "0";
            QuickSetText(oldcol, oldrow, sValor);
            QuickSetAlignment(oldcol, oldrow, UG_ALIGNRIGHT);
            RedrawAll();
        }
    }
}

void GridCapturarAbono::OnCharDown(UINT* vcKey, BOOL processed)
{
    UNREFERENCED_PARAMETER(vcKey);
    UNREFERENCED_PARAMETER(processed);
    CString sDato, sConcepto;
    char cTxt[20] = { 0 };

    if (lCliente >= 0L)
    {
        QuickGetText(GetCurrentCol(), -1, &sConcepto);
        sConcepto.Trim();
        if(sprintf_s(cTxt, "%s", sConcepto) < 0){;}

        QuickGetText(GetCurrentCol(), 12, &sDato);
        sDato.Trim();

        if (strtol(sDato, NULL, 10) > 0L || lCliente == 1708 || memcmp(cTxt, "ROPA", 4) == 0 || memcmp(cTxt, "T.AIRE", 6) == 0 || memcmp(cTxt, "CREDITO Y CASA", 14) == 0)
        {
            if (memcmp(cTxt, "PLAN MOVISTAR", 13) != 0)
            {
                if (iFlagCargo != 0)
                {
                    if (*vcKey == 13 || (*vcKey >= 48 && *vcKey <= 57))
                    {
                        StartEdit(*vcKey);
                    }
                }
                else
                {
                    if (*vcKey == 45)
                    {
                        if (memcmp(cTxt, "CP ROPA", 4) != 0 || memcmp(cTxt, "CP MUEB", 6) != 0 || memcmp(cTxt, "CP PRES", 14) != 0 || memcmp(cTxt, "CP BANC", 14) != 0 || memcmp(cTxt, "CP T.AIRE", 14) != 0 || memcmp(cTxt, "CP COMP ADC", 14) != 0)
                        {
                            StartEdit(*vcKey);
                        }
                    }
                }
            }
        }
    }
}

int GridCapturarAbono::OnEditFinish(int col, long row, CWnd *edit, LPCTSTR string, BOOL cancelFlag)
{
    UNREFERENCED_PARAMETER(cancelFlag);
    int iFlagErrorExe = 0, ValorCausa = 0;
    CString sClave, sCausa, sDato, sSaldaCon, sConcepto, sSinConexion;
    long lSaldaCon = 0L, lSaldo = 0L;
    long lGteHuella = 0, lRespuesta = -1;
    char cExe[50] = { 0 }, cTxt[20] = { 0 }, cNombreProyecto[256] = { 0 },
        cInputParam1[1024] = { 0 }, cInputParam2[1024] = { 0 },
        cOutputParam1[1024] = { 0 }, cOutputParam2[1024] = { 0 };

    SParametros parametros;
    SecureZeroMemory(&parametros, sizeof(SParametros));

    QuickGetText(col, 12, &sDato);
    sDato.Trim();

    QuickGetText(col, -1, &sConcepto);
    sConcepto.Trim();
    if(sprintf_s(cTxt, "%s", sConcepto) < 0){;}

    if (strtol(sDato, NULL, 10) > 0L || lCliente == 1708 || memcmp(cTxt, "ROPA", 4) == 0 || memcmp(cTxt, "T.AIRE", 6) == 0 || memcmp(cTxt, "CREDITO Y CASA", 14) == 0 && memcmp(cTxt, "PLAN MOVISTAR", 13) != 0)
    {
        edit->GetWindowText(sClave);
        if (sClave == "" && row == 21)
        {
            sClave = "0";
            QuickSetText(col, row, sClave);
            RedrawAll();
        }
        else
        {
            if (row == 21)
            {
                iContEntero = 0;

                sDato = sClave;
                sDato.Remove('.');
                sDato.Remove(',');
                lSaldo = strtol(sDato, NULL, 10);
                QuickGetText(col, 18, &sSaldaCon);
                sSaldaCon.Remove('.');
                sSaldaCon.Remove(',');
                lSaldaCon = strtol(sSaldaCon, NULL, 10);
                iContEntero = 0;

                QuickGetText(col, 2, &sSinConexion);
                sSinConexion.Trim();
                if (lCliente > 0)
                {
                    if (memcmp(cTxt, "CREDITO Y CASA", 14) == 0 && sSinConexion == "SIN CONEXION" && lSaldo != 0)
                    {
                        AfxMessageBox("NO SE PUEDE ABONAR SIN CONEXION A CREDITO Y CASA< Enter >");
                        edit->SetWindowText("0");
                        QuickSetText(col, 21, "0");
                        return FALSE;
                    }
                    if (memcmp(cTxt, "CREDITO Y CASA", 14) == 0 && cArea != 'C' && lSaldo != 0)
                    {
                        AfxMessageBox("SOLO SE PUEDE ABONAR A CUENTAS DE CREDITO Y CASA DESDE EL AREA DE CAJAS< Enter >");
                        edit->SetWindowText("0");
                        QuickSetText(col, 21, "0");
                        return FALSE;
                    }
                    if (lSaldo > lSaldaCon && lCliente != 1708 && memcmp(cTxt, "CREDITO Y CASA", 14) != 0)
                    {
                        edit->SetWindowText(sClave);
                        QuickSetText(col, 21, sClave);

                        AfxMessageBox("CONFIRME EL ABONO, ES MAYOR QUE EL SALDA CON, PRESIONE < Enter >");

                        validarHuellaEmpleadoGte01(&odbc, lGteHuella, 1, 5, 0, iTienda, iSistema, iCaja, "CA0030");//gnwSuplirHuellaGerente.cpp
                        if (lGteHuella == -1)
                        {
                            nombreArchivo("GN0055.dll", cExe, DIRECTORIO_GN);
                            parametros.iLink = generarLink();
                            parametros.iTienda = iTienda;
                            parametros.lEmpleado = lEmpleado;
                            parametros.iCajaActual = iCaja;
                            parametros.iMuestraMsg = iMuestraMsg;
                            parametros.iNumSistema = SISTEMA_CAJAS;
                            if(sprintf_s(parametros.sServer, "%s", sServer) < 0){;}

							if(memcpy_s(cInputParam1, sizeof(cInputParam1), &parametros, sizeof(SParametros)) < 0){;}
                            CargarDLL cargarDll(cNombreProyecto, "GN0055", cInputParam1, cInputParam2, cOutputParam1, cOutputParam2);
                            lRespuesta = strtol(cOutputParam1, NULL, 10);

                            if (lRespuesta < 0)
                            {
                                iFlagErrorExe = 1;
                                AfxMessageBox("Error al cargar el programa GN0055.DLL", MB_ICONERROR);
                            }
                            else
                            {
                                lGteHuella = lRespuesta;
                                if (lGteHuella == 2) // No hay conexión
                                    iFlagErrorExe = 1;
                            }
                        }

                        if (lGteHuella < 16 && iFlagErrorExe == 0)
                        {
                            pintarMensajesErrorPasstda(lGteHuella);
                            return FALSE;
                        }
                    }
                }
                string = sClave;
                edit->SetWindowText(sClave);
                QuickSetText(col, 21, sClave);
                RedrawAll();
            }

        }
    }
    RedrawAll();
    bEdicion = false;
    return TRUE;
}

void GridCapturarAbono::obtenerTotalAbono()
{
    long lPago = 0L;
    int i = 0;
    CString sPago, sDato;
    CUGCell m_cell;

    GridDesplegarTotal *const m_grid2 = (GridDesplegarTotal *const)lpGrid;
    m_grid2->lTotalAbonos = 0L;
    for (i = 0; i < iTotalCuentas; i++)
    {
        GetCell(i, 21, &m_cell);
        QuickGetText(i, 21, &sPago);

        lPago = strtol(sPago, NULL, 10);
        m_grid2->lTotalAbonos += lPago;
    }
    sDato.Format("%ld", m_grid2->lTotalAbonos);
    m_grid2->QuickSetText(0, 21, sDato);
    m_grid2->QuickSetAlignment(0, 21, UG_ALIGNRIGHT);
    m_grid2->RedrawAll();
}

BOOL GridCapturarAbono::PreTranslateMessage(MSG* pMsg)
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
