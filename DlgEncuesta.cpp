// DlgEncuesta.cpp : implementation file
//

#include "stdafx.h"
#include "sysCapturarAbono.h"
#include "CapturarAbono.h"
#include "DlgEncuesta.h"
#include "DlgCapturarAbono.h"
#include ".\dlgencuesta.h"
#include "CMaximo.hpp"
#include "gnwproto.hpp"
#include <process.h>

// CDlgEncuesta dialog

IMPLEMENT_DYNAMIC(CDlgEncuesta, CDialog2012)
CDlgEncuesta::CDlgEncuesta(CWnd* pParent /*=NULL*/)
    : CDialog2012(CDlgEncuesta::IDD, pParent)
{
    iTienda = iCiudad = 0;
    iControles = iFoco = iCaja = iMuestraMsg = iCiudadCliente = iFlagAceptar = iNumCiudad = 0;
    lEmpleado = lTempZona = lTelefono = lZonaCliente = lColoniaTmp = 0;
    ShiftTab = false;
    SecureZeroMemory(cNombre, sizeof(cNombre));
    SecureZeroMemory(cApellidoMaterno, sizeof(cApellidoMaterno));
    SecureZeroMemory(cApellidoPaterno, sizeof(cApellidoPaterno));
    SecureZeroMemory(cNombreColonia, sizeof(cNombreColonia));
}

CDlgEncuesta::~CDlgEncuesta()
{
	iCaja = 0;
	lEmpleado = 0;
	iMuestraMsg = 0;
	iTienda = 0;
	iCiudadCliente = 0;
}

void CDlgEncuesta::DoDataExchange(CDataExchange* pDX)
{
    CDialog2012::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_NOMBRE2, m_nombre);
    DDX_Control(pDX, IDC_APELLIDOPATERNO2, m_apellidoPaterno);
    DDX_Control(pDX, IDC_APELLIDOMATERNO2, m_apellidoMaterno);
    DDX_Control(pDX, IDC_ZONA, m_zona);
    DDX_Control(pDX, IDC_TELEFONO2, m_telefono);
    DDX_Control(pDX, IDC_ACEPTAR, m_aceptar);
    DDX_Control(pDX, IDC_MENSAJE, m_mensajex);
    DDX_Control(pDX, IDC_COLONIA, m_colonia);
    DDX_Control(pDX, IDC_NOMBRECOLONIA, m_nombreColonia);
}


BEGIN_MESSAGE_MAP(CDlgEncuesta, CDialog2012)
    ON_EN_SETFOCUS(IDC_NOMBRE2, OnEnSetfocusNombre2)
    ON_EN_SETFOCUS(IDC_APELLIDOPATERNO2, OnEnSetfocusApellidopaterno2)
    ON_EN_SETFOCUS(IDC_APELLIDOMATERNO2, OnEnSetfocusApellidomaterno2)
    ON_EN_SETFOCUS(IDC_ZONA, OnEnSetfocusZona)
    ON_EN_SETFOCUS(IDC_TELEFONO2, OnEnSetfocusTelefono2)
    ON_BN_CLICKED(IDC_ACEPTAR, OnBnClickedAceptar)
    ON_EN_SETFOCUS(IDC_COLONIA, OnEnSetfocusColonia)
END_MESSAGE_MAP()


// CDlgEncuesta message handlers

void CDlgEncuesta::OnEnSetfocusNombre2()
{
    // TODO: Add your control notification handler code here
    validarClick(0);
}

void CDlgEncuesta::OnEnSetfocusApellidopaterno2()
{
    // TODO: Add your control notification handler code here
    validarClick(1);
}

void CDlgEncuesta::OnEnSetfocusApellidomaterno2()
{
    // TODO: Add your control notification handler code here
    validarClick(2);
}

void CDlgEncuesta::OnEnSetfocusZona()
{
    // TODO: Add your control notification handler code here
    validarClick(3);
}

void CDlgEncuesta::OnEnSetfocusColonia()
{
    // TODO: Add your control notification handler code here
    validarClick(4);
}

void CDlgEncuesta::OnEnSetfocusTelefono2()
{
    // TODO: Add your control notification handler code here
    validarClick(5);
}


void CDlgEncuesta::OnBnClickedAceptar()
{
    // TODO: Add your control notification handler code here

    OnCancel();

}

BOOL CDlgEncuesta::OnInitDialog()
{
    CDialog2012::OnInitDialog();
    // TODO:  Add extra initialization here

    m_nombre.SetLimitText(15);
    m_apellidoPaterno.SetLimitText(15);
    m_apellidoMaterno.SetLimitText(15);
    m_zona.SetLimitText(3);
    m_colonia.SetLimitText(4);
    m_telefono.SetLimitText(8);
    lTempZona = 0;
    lTelefono = 0;

    iFoco = 0;
    iControles = 6;
    lColoniaTmp = 0;
    iNumCiudad = 0l;
    iFlagAceptar = 0;

    m_zona.SetWindowText("");
    m_colonia.SetWindowText("");
    m_nombreColonia.SetWindowText("");

    crearMensaje(this, m_barra, m_mensaje);
    ponerMensaje(this, m_barra, m_mensaje, "  [F10] Aceptar ");

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgEncuesta::PreTranslateMessage(MSG* pMsg)
{
    // TODO: Add your specialized code here and/or call the base class
    char cPaso[255] = { 0 }, cZonaTxt[10] = { 0 }, cTexto[40] = { 0 };
    int iCiudadF1 = 0, iDigito = 0;
    long lColoniaF1 = 0;
    bool bConsulta = true;
    CString sTexto;

    ShiftTab = false;
    if (iFoco == 3 || iFoco == 4)
    {
        m_mensajex.SetWindowText(" <F1> CONSULTA DE ZONAS ");
    }
    else
    {
        m_mensajex.SetWindowText("");
    }

    if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
    {
        if (pMsg->wParam == VK_ESCAPE)
        {
            pMsg->wParam = NULL;
        }
        if (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_UP)
        {
            iFoco--;
            if (iFoco < 0)	iFoco = 0;
            asignarFoco();
        }
        if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB || pMsg->wParam == VK_DOWN)//|| pMsg->wParam == VK_RIGHT )
        {
            if (iFoco <= iControles) //numero de controles
            {
                if (validarControl(cPaso))
                {
                    iFoco++;
                    if (iFoco > 5)
                        iFoco = 0;
                    asignarFoco();
                }
                else
                {
                    if (!ShiftTab)
                    {
                        AfxMessageBox(cPaso);
                    }
                }
                return TRUE;
            }
            else
            {
                if (pMsg->wParam != VK_RETURN)
                {
                    iFoco++;
                    if (iFoco > 5)
                        iFoco = 0;
                    asignarFoco();
                }
                else
                {
                    asignarFoco();
                }
                return TRUE;
            }
        }
        else
        {
            if (pMsg->wParam == VK_TAB && GetKeyState(VK_SHIFT) & 0x8000)
            {
                ShiftTab = true;
            }
            else
            {
                switch (pMsg->wParam)
                {
                case VK_F10:
                    if (iFlagAceptar == 1)
                    {
                        OnBnClickedAceptar();
                        pMsg->wParam = NULL;
                    }
                    break;
                case VK_F1:
                    if (iFoco == 3 || iFoco == 4)
                    {
                        char cSqlTxt[255] = { 0 }, cIPServidorCartera[17] = { 0 }, cIPServidorCarteraAlterno[17] = { 0 };
                        bConsulta = consultarIpServidores(&odbc, cIPServidorCartera, cIPServidorCarteraAlterno, SERV_CARTERA, cSqlTxt);
                        if (bConsulta)
                        {
                            int iRegresaDll = 0;
                            char cNombreProyecto[100] = { 0 }, cNombreFuncionDLL[10] = { 0 }, cInputParam1[1024] = { 0 }, cInputParam2[1024] = { 0 }, cOutputParam1[1024] = { 0 }, cOutputParam2[1024] = { 0 };

                            SParametros parametros;
                            SecureZeroMemory(&parametros, sizeof(SParametros));

                            parametros.iLink = generarLink();
                            if(sprintf_s(parametros.sIpCartera1, "%s", cIPServidorCartera) < 0){;}  //IpCartera
                            parametros.iTienda = iTienda;
                            parametros.lEmpleado = lEmpleado;
                            parametros.iCajaActual = iCaja;
                            parametros.iMuestraMsg = iMuestraMsg;

                            m_zona.GetWindowText(sTexto);
                            iNumCiudad = strtol(sTexto, NULL, 10);

                            if (iNumCiudad > 0)
                                parametros.iCiudad = iNumCiudad;
                            else
                                parametros.iCiudad = iCiudadCliente;

                            parametros.iNumSistema = 3;
                            if(sprintf_s(parametros.sIpCartera2, "%s", cIPServidorCarteraAlterno) < 0){;} //IpCartera2

							if(memcpy_s(cInputParam1, sizeof(cInputParam1), &parametros, sizeof(SParametros)) < 0){;}

                            // Ruta del archivo DLL a ejecutar
                            nombreArchivo("GN0002.DLL", cNombreProyecto, DIRECTORIO_GN);

                            // Nombre de la función principal en el DLL
                            if(sprintf_s(cNombreFuncionDLL, "GN0002") < 0){;}

                            CargarDLL cargarDll(cNombreProyecto, cNombreFuncionDLL, cInputParam1, cInputParam2, cOutputParam1, cOutputParam2);
                            iRegresaDll = cargarDll.getResultado();

                            if (iRegresaDll <= 0)
                            {
                                AfxMessageBox("Ocurrio un error al llamado del modulo GN0002.DLL", MB_ICONERROR);
                            }

                            lTempZona = strtol(cOutputParam1, NULL, 10);
                            lZonaCliente = lTempZona;

                            if (lTempZona > 0)
                            {
                                if(sprintf_s(cZonaTxt, "%07ld", lTempZona) < 0){;}
                                iCiudadF1 = valor_campo(&cZonaTxt[0], 3);
                                lColoniaF1 = valor_campo(&cZonaTxt[3], 4);

                                if (buscarCiudad(iCiudadF1) != 1)
                                {
                                    AfxMessageBox(" EL NUMERO DE ZONA NO CORRESPONDE A ESTA CIUDAD ");
                                    m_zona.SetWindowText("");
                                    m_colonia.SetWindowText("");
                                    m_nombreColonia.SetWindowText("");
                                    iFlagAceptar = 0;
                                    iFoco = 3;
                                    asignarFoco();

                                }
                                else
                                {
                                    sTexto.Format("%d", iCiudadF1);
                                    m_zona.SetWindowText(sTexto);

                                    sTexto.Format("%ld", lColoniaF1);
                                    m_colonia.SetWindowText(sTexto);

                                    {
                                        CDlgCapturarAbono dlgCapturarAbono;
                                        dlgCapturarAbono.buscarNombreColonia(iCiudadF1, lColoniaF1, cNombreColonia);
                                    }

                                    sTexto.Format("%s", cNombreColonia);
                                    m_nombreColonia.SetWindowText(sTexto);

                                    iFlagAceptar = 1;
                                    iFoco = 5;
                                    asignarFoco();
                                }
                            }
                            else
                            {
                                if (iFoco == 3)
                                {
                                    AfxMessageBox("Debe Capturar El Número de Ciudad");
                                    m_zona.SetWindowText("");
                                    iFoco = 3;
                                    asignarFoco();
                                }
                                else
                                {
                                    if (iFoco == 4)
                                    {
                                        m_colonia.SetWindowText("");
                                        m_nombreColonia.SetWindowText("");
                                        AfxMessageBox("Debe Capturar El Número de Colonia");
                                        iFoco = 4;
                                        asignarFoco();
                                    }
                                }
                            }
                        }
                        else
                        {
                            grabarMensajeError("C", iCaja, (LPTSTR)(LPCTSTR)odbc.m_strServer, "CapturarAbono", "CDlgEncuesta", "PreTranslateMessage", cSqlTxt, lEmpleado, "ERROR EN LA CONSULTA(dlgencuesta pretranslatemessage)", &odbc, iMuestraMsg);
                        }
                    }
                    break;

                default:
                    if ((iFoco == 0 || iFoco == 1 || iFoco == 2) && pMsg->wParam != VK_TAB && pMsg->wParam != VK_UP && pMsg->wParam != VK_DOWN && pMsg->wParam != VK_LEFT && pMsg->wParam != VK_RIGHT)
                    {
                        sTexto.Format("");
                        sTexto.Format("%d", pMsg->wParam);
						if(memcpy_s(cTexto, sizeof(cTexto), sTexto, sTexto.GetLength()) < 0){;}
                        cTexto[sTexto.GetLength()];
                        iDigito = strtol(cTexto, NULL, 10);
                        if (iDigito < 65 || iDigito>90)
                        {
                            if (iDigito != 32 && iDigito != 35 &&
                                iDigito != 46 && iDigito != 44 &&
                                iDigito != 165 && iDigito != 8 && iDigito != 'Ñ')
                            {
                                AfxMessageBox("Solo Puede Capturar Letras");
                                pMsg->wParam = NULL;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }

    return CDialog2012::PreTranslateMessage(pMsg);
}

bool CDlgEncuesta::validarClick(int nTmpFocus)
{
    int nElementoTmp, i;
    bool regresa = true;
    char cPaso[255] = { 0 };

    if (iFoco < nTmpFocus)
    {
        // validar control anterior
        if (!validarControl(cPaso))
        {
            asignarFoco();
            if (iFoco != iControles)//numero de controles para los que se quieren se vea el mebsaje de error
            {
                if (!ShiftTab)
                {
                    AfxMessageBox(cPaso);
                }
            }
            regresa = false;
        }
        else
        {
            nElementoTmp = iFoco;
            iFoco = nTmpFocus;
            for (i = 0; i <= nTmpFocus; i++)
            {
                iFoco = i;
                //valida hacia abajo los controles
                if (!validarControl(cPaso))
                {
                    break;
                }
            }
            asignarFoco();
        }
    }
    else
    {
        iFoco = nTmpFocus;
    }
    return regresa;
}

void CDlgEncuesta::asignarFoco()
{

    switch (iFoco)
    {
    case 0:
        m_nombre.SetFocus();
        break;
    case 1:
        m_apellidoPaterno.SetFocus();
        break;
    case 2:
        m_apellidoMaterno.SetFocus();
        break;
    case 3:
        lTempZona = 0;
        m_zona.SetFocus();
        break;
    case 4:
        iFlagAceptar = 0;
        m_colonia.SetFocus();
        break;
    case 5:
        m_telefono.SetFocus();
        break;
    case 6:
        m_aceptar.SetFocus();
        break;
    default:
        break;
    }
}

bool CDlgEncuesta::validarControl(char * cCadena)
{
    bool valorRegresa = true;
    CString sTexto;
    char cZona[10] = { 0 };

    switch (iFoco)
    {
    case 0:
        m_nombre.GetWindowText(sTexto);
        sTexto.Trim();
        if (sTexto.IsEmpty())
        {
		 	if(sprintf_s(cCadena, 255, "%s", " DEBE CAPTURAR EL NOMBRE DE LA PERSONA NO TITULAR ") < 0){;}
            m_nombre.SetWindowText("");
            valorRegresa = false;
        }
        else if (sTexto.GetLength() <= 2)
        {
			if(sprintf_s(cCadena, 255, " FAVOR DE INGRESAR AL MENOS TRES CARACTERES AL CAPTURAR EL NOMBRE ") < 0){;}
            m_nombre.SetWindowText("");
            valorRegresa = false;
        }
        else
        {
            if(sprintf_s(cNombre, "%s", sTexto) < 0){;}
        }
        break;
    case 1:
        m_apellidoPaterno.GetWindowText(sTexto);
        sTexto.TrimLeft();
        sTexto.TrimRight();
        if (sTexto.IsEmpty())
        {
			if(sprintf_s(cCadena, 255, "%s", " DEBE CAPTURAR EL APELLIDO PATERNO DE LA PERSONA NO TITULAR ") < 0){;}
            m_apellidoPaterno.SetWindowText("");
            valorRegresa = false;
        }
        else
        {
            if(sprintf_s(cApellidoPaterno, "%s", sTexto) < 0){;}
        }
        break;
    case 2:
        m_apellidoMaterno.GetWindowText(sTexto);
        sTexto.TrimLeft();
        sTexto.TrimRight();
        if (sTexto.IsEmpty())
        {
			if(sprintf_s(cCadena, 255, "%s", " DEBE CAPTURAR EL APELLIDO MATERNO DE LA PERSONA NO TITULAR ") < 0){;}
            m_apellidoMaterno.SetWindowText("");
            valorRegresa = false;
        }
        else
        {
            if(sprintf_s(cApellidoMaterno, "%s", sTexto) < 0){;}
        }
        break;
    case 3:
        m_zona.GetWindowText(sTexto);

        if (strtol(sTexto, NULL, 10) <= 0)
        {
			if(sprintf_s(cCadena, 255, "%s", " CAPTURA INCORRECTA ") < 0){;}
            m_zona.SetWindowText("");
            valorRegresa = false;
        }
        else
        {
            if (lTempZona <= 0L)
            {
                if(sprintf_s(cZona, "%03d", strtol(sTexto, NULL, 10)) < 0){;}
            }
            else
            {
                if(sprintf_s(cZona, "%07ld", lTempZona) < 0){;}
            }
            iNumCiudad = (int)valor_campo(cZona, 3);

            if (buscarCiudad(iNumCiudad) != 1)
            {
				if(sprintf_s(cCadena, 255, "%s", " EL NUMERO DE ZONA NO CORRESPONDE A ESTA CIUDAD ") < 0){;}
                m_zona.SetWindowText("");
                valorRegresa = false;
            }
        }

        break;
    case 4:
        m_colonia.GetWindowText(sTexto);

        if (strtol(sTexto, NULL, 10) <= 0)
        {
			if(sprintf_s(cCadena, 255, "%s", " CAPTURA INCORRECTA ") < 0){;}
            m_colonia.SetWindowText("");
            m_nombreColonia.SetWindowText("");
            valorRegresa = false;
        }
        else
        {
            lColoniaTmp = strtol(sTexto, NULL, 10);

            if (lColoniaTmp > 0)
            {
                CDlgCapturarAbono dlgCapturarAbono;

                if (dlgCapturarAbono.buscarNombreColonia(iNumCiudad, lColoniaTmp, cNombreColonia) == true)
                {
                    sTexto.Format("%d", iNumCiudad);
                    m_zona.SetWindowText(sTexto);

                    sTexto.Format("%s", cNombreColonia);
                    m_nombreColonia.SetWindowText(sTexto);

                    if(sprintf_s(cZona, "%03d%04d", iNumCiudad, lColoniaTmp) < 0){;}
                    lZonaCliente = strtol(cZona, NULL, 10);

                    iFlagAceptar = 1;
                }
                else
                {
					if(sprintf_s(cCadena, 255, "%s", " EL NUMERO DE ZONA NO CORRESPONDE A ESTA CIUDAD ") < 0){;}
                    m_colonia.SetWindowText("");
                    m_nombreColonia.SetWindowText("");
                    valorRegresa = false;
                }
            }
            else
            {
				if(sprintf_s(cCadena, 255, "%s", " CAPTURA INCORRECTA ") < 0){;}
                m_colonia.SetWindowText("");
                m_nombreColonia.SetWindowText("");
                valorRegresa = false;
            }
        }


        break;
    case 5:
        m_telefono.GetWindowText(sTexto);
        if (strtol(sTexto, NULL, 10) > 0L)
        {
            lTelefono = strtol(sTexto, NULL, 10);
        }
        break;
    default:
        break;
    }

    return valorRegresa;
}

bool CDlgEncuesta::validarControles()
{
    bool bValorRegresa = false;
    int i, iFocoAnt;
    bool bandera = true;
    char cPaso[255] = { 0 };

    iFocoAnt = iFoco;

    for (i = 0; i < iControles; i++)
    {
        iFoco = i;
        bandera = validarControl(cPaso);
        if (!bandera)
        {
            AfxMessageBox(cPaso);
            asignarFoco();
            break;
        }
    }

    if (bandera)
    {
        bValorRegresa = true;
    }

    iFoco = iFocoAnt;
    asignarFoco();
    return bValorRegresa;
}

int CDlgEncuesta::buscarCiudad(int iNumCiudad)
{
    char cSql[70] = { 0 };
    int iEncontro = 0;

    CMaximo buscarCorrespondeCd(&odbc);
    if(sprintf_s(cSql, "SELECT ciudad FROM cazonacorrespondeciudad WHERE ciudad = %d", iNumCiudad) < 0){;}
    if (!buscarCorrespondeCd.Exec(cSql))
    {
        //Se obtiene el error
        buscarCorrespondeCd.odbc->GetLastError(buscarCorrespondeCd.GetHstmt());
        grabarMensajeError("C", iCaja, (LPTSTR)(LPCTSTR)odbc.m_strServer, "CapturarAbono", "CDlgEncuesta", "buscarCiudad", cSql, lEmpleado, "ERROR EN LA CONSULTA(buscarciudad dlgencuesta)", buscarCorrespondeCd.odbc, iMuestraMsg);
    }
    else
    {
        buscarCorrespondeCd.activarCols();
        if (buscarCorrespondeCd.leer())
        {
            iEncontro = 1;
        }
    }

    return iEncontro;
}