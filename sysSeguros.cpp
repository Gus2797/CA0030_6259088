#include "stdafx.h"
#include "DlgCapturarAbono.h"

#include "CConsultarEdadesClub.hpp"
#include "CConsultarPrecioPlanSalud.hpp"
#include "CMaximo2.hpp"
#include "CGrabarTmpCaCarmovSeguro.hpp"
#include "CConsultarMensajeSeguro.hpp"
#include "CConsultarCalle.hpp"

//3858
bool CDlgCapturarAbono::consultarEdadesPlanSalud(short iTipoSeguro)
{
    bool bRegresa = true;

    if (abrirConexionBD(&odbc_1, cIpServidorCartera, cIpServidorCartera, CONECTA_CARTERA, m_grid.iTienda))
    {
        char cSql[85] = { 0 };

        CConsultarEdadesClub edades(&odbc_1);

        if(sprintf_s(cSql, "SELECT iedadminima, iedadmaxima FROM fun_crobteneredadesseguro('%d')", iTipoSeguro) < 0){;}

        if (edades.Exec(cSql))
        {
            edades.activarCols();
            if (edades.leer())
            {
                iEdadMinimaPlan = edades.edadminima;
                iEdadMaximaPlan = edades.edadmaxima;
            }
        }
        else
        {
            bRegresa = false;
            edades.odbc->GetLastError(edades.GetHstmt());
            grabarMensajeError("C", iCajaDlg, cIpServidorCartera, "CA0030", "CDlgCapturarAbono", "consultarEdadesPlanSalud", cSql, lEmpleadoDlg, "Error al Consultar Edades plan de salud", edades.odbc, iMuestraMsg);
        }
    }
    else
    {
        AfxMessageBox("Error al abrir conexión BD CARTERA");
    }
    cerrarConexionBD(&odbc_1);

    return bRegresa;
}

void CDlgCapturarAbono::consultarPrecioPlanSalud(long &lPrecioPlanSaludM, long &lPrecioPlanSaludD, long &lPrecioPlanSaludA, short iPlan, short iTipoSeguro)
{
    UNREFERENCED_PARAMETER(lPrecioPlanSaludA);
    UNREFERENCED_PARAMETER(lPrecioPlanSaludD);
    char cSql[120] = { 0 };

    grabarLog("consultarPrecioPlanSalud::Consultando precio plan de salud");

    CConsultarPrecioPlanSalud precio(&odbc_1);

    if(sprintf_s(cSql, "SELECT ioplan, ipreciodiario, ipreciomensual, iprecioanual FROM fun_crobtenerpreciosplanesseguro('%d', '%d')", iTipoSeguro, iPlan) < 0){;}

    if (precio.Exec(cSql))
    {
        precio.activarCols();
        if (precio.leer())
        {
            lPrecioPlanSaludM = (long)precio.ipreciomensual;
        }
    }
    else
    {
        bErrorProcesoPS = true;
        precio.odbc->GetLastError(precio.GetHstmt());
        grabarMensajeError("C", iCajaDlg, (LPTSTR)(LPCTSTR)odbc_1.m_strServer, "CA0030", "CDlgCapturarDatosSeguro", "consultarPrecioPlanSalud", cSql, lEmpleadoDlg, "Error al Consultar Precio plan de salud", precio.odbc, iMuestraMsg);
    }
}

int CDlgCapturarAbono::consultarSumaAseguradaPlanSalud(short iPlan, short iTipoSeguro)
{
    char cSql[120] = { 0 };
    int iSumaAseguradaRegresa = 0;

    CMaximo2 sumaAseguradaPlan(&odbc_1);

    if(sprintf_s(cSql, "SELECT idu_plan, imp_sumaasegurada FROM fun_crconsultacatcrplanesseguros('%d');", iTipoSeguro) < 0){;}

    if (sumaAseguradaPlan.Exec(cSql))
    {
        sumaAseguradaPlan.activarCols();
        while (sumaAseguradaPlan.leer())
        {
            if (sumaAseguradaPlan.Total == iPlan)
            {
                iSumaAseguradaRegresa = sumaAseguradaPlan.Total2;
                break;
            }
        }
    }
    else
    {
        bErrorProcesoPS = true;
        sumaAseguradaPlan.odbc->GetLastError(sumaAseguradaPlan.GetHstmt());
        grabarMensajeError("C", iCajaDlg, (LPTSTR)(LPCTSTR)odbc_1.m_strServer, "CA0030", "CDlgCapturarDatosSeguro", "consultarSumaAseguradaPlanSalud", cSql, lEmpleadoDlg, "Error", sumaAseguradaPlan.odbc, iMuestraMsg);
    }

    return iSumaAseguradaRegresa;
}

void CDlgCapturarAbono::consultarMaxAdicionales(short iTipoSeguro)
{
    char cSql[120] = { 0 };

    CMaximo consultarMaxAdic(&odbc);

    if(sprintf_s(cSql, "SELECT num_maxadicionales FROM fun_tdconsultartiposeguros('%d', '1');", iTipoSeguro) < 0){;}

    if (consultarMaxAdic.Exec(cSql))
    {
        consultarMaxAdic.activarCols();
        while (consultarMaxAdic.leer())
        {
            iMaxAdicionales = (short)consultarMaxAdic.Total;
        }
    }
    else
    {
        bErrorProcesoPS = true;
        consultarMaxAdic.odbc->GetLastError(consultarMaxAdic.GetHstmt());
        grabarMensajeError("C", iCajaDlg, (LPTSTR)(LPCTSTR)odbc_1.m_strServer, "CA0030", "CDlgCapturarDatosSeguro", "consultarMaxAdicionales", cSql, lEmpleadoDlg, "Error en fun_tdconsultartiposeguros", consultarMaxAdic.odbc, iMuestraMsg);
    }
}

void CDlgCapturarAbono::borrarTemporalesPlan()
{
    char cSql[150] = { 0 };

    CGrabarTmpCaCarmovSeguro tmpcaCarmovSeguros(&odbc);

    if(sprintf_s(cSql, "DELETE FROM mov_cacarmovtemporal WHERE num_cliente = %ld AND clave='2' AND tienda=%d AND caja=%d;", m_grid.lCliente, m_grid.iTienda, m_grid.iCaja) < 0){;}

    if (!tmpcaCarmovSeguros.Exec(cSql))
    {
        bErrorProcesoPS = true;
        tmpcaCarmovSeguros.odbc->GetLastError(tmpcaCarmovSeguros.GetHstmt());
        grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CA0030", "CDlgCapturarAbono", "borrarTemporalesPlan", cSql, m_grid.lEmpleado, "ERROR", tmpcaCarmovSeguros.odbc, m_grid.iMuestraMsg);
    }

    tmpcaCarmovSeguros.ClearResults();
    tmpcaCarmovSeguros.ClearStatement();

    if(sprintf_s(cSql, "DELETE FROM mov_tdbeneficiariostemporal WHERE num_cliente = %ld AND num_tienda=%d AND num_caja=%d AND idu_seguro='4';", m_grid.lCliente, m_grid.iTienda, m_grid.iCaja) < 0){;}

    if (!tmpcaCarmovSeguros.Exec(cSql))
    {
        bErrorProcesoPS = true;
        tmpcaCarmovSeguros.odbc->GetLastError(tmpcaCarmovSeguros.GetHstmt());
        grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CA0030", "CDlgCapturarAbono", "borrarTemporalesPlan", cSql, m_grid.lEmpleado, "ERROR", tmpcaCarmovSeguros.odbc, m_grid.iMuestraMsg);
    }

}

void CDlgCapturarAbono::compararEdadCliente()
{
    CString sTexto = "";
    char cIntervaloEdad[32] = { 0 };

    bSobrePasaEdadMaxima = false;
    sTexto.Format("select cvalorconfiguracion from FUN_CONSULTARVALORCONFIGURACION01('240');");
    CConsultarMensajeSeguro obtenerConexion(&odbc); // se reutiliza clase que regresa una cadena

    if (!obtenerConexion.Exec(sTexto))
    {
        obtenerConexion.odbc->GetLastError(obtenerConexion.GetHstmt());
        grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "CDlgCapturarAbono", "compararEdadCliente", (LPTSTR)(LPCTSTR)sTexto, m_grid.lEmpleado, "ERROR EN LA CONSULTA(validaFlagPrestamoCteN)", obtenerConexion.odbc, m_grid.iMuestraMsg);
    }
    else
    {
        obtenerConexion.activarCols();
        if (obtenerConexion.Leer())
        {
            if(sprintf_s(cIntervaloEdad, obtenerConexion.des_mensaje) < 0){;}

            sTexto = "";
            sTexto.Format("SELECT CASE WHEN (ianios||' years '||imes||' months '||idias||' days')::INTERVAL > '%s'::INTERVAL THEN 1 ELSE 0 END FROM fun_calculartiempotranscurrido('%04d-%02d-%02d','%04d-%02d-%02d')",
                cIntervaloEdad, iAnioNacimiento, iMesNacimiento, iDiaNacimiento, iAnioActual, iMesActual, iDiaActual);
            CMaximo compararEdadCte(&odbc);

            if (!compararEdadCte.Exec(sTexto))
            {
                bErrorProcesoPS = true;
                compararEdadCte.odbc->GetLastError(compararEdadCte.GetHstmt());
                grabarMensajeError("C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "CDlgCapturarAbono", "compararEdadCliente", (LPTSTR)(LPCTSTR)sTexto, m_grid.lEmpleado, "ERROR EN LA CONSULTA(fun_calculartiempotranscurrido)", compararEdadCte.odbc, m_grid.iMuestraMsg);
            }
            else
            {
                compararEdadCte.activarCols();
                if (compararEdadCte.Leer())
                {
                    if (compararEdadCte.Total == 1)
                    {
                        bSobrePasaEdadMaxima = true;
                    }
                }
            }
        }
    }
}

void CDlgCapturarAbono::consultarNombrePlan(char *cNomPlan, short iPlan, short iTipoSeguro)
{
    char cSql[120] = { 0 };
    CConsultarCalle nombrePlan(&odbc_1); // se reutiliza clase sql con los mismos parametros

    if(sprintf_s(cSql, "SELECT idu_plan, trim(nom_plan) FROM fun_crconsultacatcrplanesseguros('%d');", iTipoSeguro) < 0){;}

    if (nombrePlan.Exec(cSql))
    {
        nombrePlan.activarCols();
        while (nombrePlan.Leer())
        {
            if (nombrePlan.calle == iPlan) // en calle biene el idu_plan
            {
				//if(sprintf_s(cNomPlan, strnlen(cNomPlan, 32), nombrePlan.nombrecalle) < 0){;} // en nombrecalle biene nom_plan
				if(sprintf_s(cNomPlan, 40, nombrePlan.nombrecalle) < 0){;} // solucion a desborde por tamaño de nombre de plan salud
                break;
            }
        }
    }
    else
    {
        bErrorProcesoPS = true;
        nombrePlan.odbc->GetLastError(nombrePlan.GetHstmt());
        grabarMensajeError("C", iCajaDlg, (LPTSTR)(LPCTSTR)odbc_1.m_strServer, "CA0030", "CDlgCapturarDatosSeguro", "consultarNombrePlan", cSql, lEmpleadoDlg, "Error (fun_crconsultacatcrplanesseguros)", nombrePlan.odbc, iMuestraMsg);
    }
}