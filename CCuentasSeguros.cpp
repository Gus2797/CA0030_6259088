#include "CCuentasSeguros.h"
#include "gridcapturarabono.hpp"
#include "CConsumoAPICuentasSeguros.h"
#include <iostream>
#include <afx.h>
#include <regex>


CCuentasSeguros::CCuentasSeguros(void)
{
	this->pCuentasSeguros = new CConsumoAPICuentasSeguros();
	//free(pCuentasSeguros); // Memory Leak
	this->iCol = 0;
	this->iCiudad = 0;
	this->iCaja = 0;
	this->iNumeroMeses = 0;
	this->sNombreCliente = "";
	this->sApellidoMaterno = "";
	this->sApellidoPaterno = "";
	this->lCliente = 0L;
	this->lEmpleado = 0L;
	this->lNumeroRecibo = 0L;
	this->lSaldaCon = 0L;
	this->cSexo = '0';
	this->jsonAbonoCelularesC.limpiar();
	this->jsonAbonoCelularesCL.limpiar();
	this->jsonAbonoMotosC.limpiar();
	this->jsonAbonoMotosCL.limpiar();
}

CCuentasSeguros::~CCuentasSeguros(void)
{
	delete this->pCuentasSeguros;
	this->iCol = 0;
	this->iCiudad = 0;
	this->iCaja = 0;
	this->iNumeroMeses = 0;
	this->sNombreCliente = "";
	this->sApellidoMaterno = "";
	this->sApellidoPaterno = "";
	this->lCliente = 0L;
	this->lEmpleado = 0L;
	this->lNumeroRecibo = 0L;
	this->lSaldaCon = 0L;
	this->cSexo = '0';
	this->jsonAbonoCelularesC.limpiar();
	this->jsonAbonoCelularesCL.limpiar();
	this->jsonAbonoMotosC.limpiar();
	this->jsonAbonoMotosCL.limpiar();
}

int CCuentasSeguros::cargarCuentasSeguros(int k, vector<CuentasSegurosWeb>* pCuentasAcitvas)
{
	util.GrabarLog("CCuentasSeguros::cargarCuentasSeguros--inicia cargar cuentas seguro");
	CString sDato;
	char cFecha1[12] = { 0 }, cTexto[80] = { 0 };
	CConsumoAPICuentasSeguros pCuentas = *this->pCuentasSeguros;
	char logCuentSeguro[2048] = { 0 };
	int tamanoVector = pCuentasAcitvas->size();
	int mesesRestantes = 1;
	if (sprintf_s(logCuentSeguro, "CCuentasSeguros::cargarCuentasSeguros -> pCuentas.iCuentasActivas: %i, "
		" this->pCuentasSeguros->iCuentasActivas: %i, tamaño vector: %i",
		pCuentas.iCuentasActivas, this->pCuentasSeguros->iCuentasActivas, tamanoVector) < 0) {
		;
	}
	util.GrabarLog(logCuentSeguro);
	this->lSaldaCon = 0L;

	int fontID = m_grid->AddFont("Lucida Console Bold", 14, 200);

	for (int i = 0; i < tamanoVector; i++) {

		if (k >= 8)
		{
			this->m_grid->AppendCol();
			this->m_grid->SetColWidth(k, 83);
			this->m_grid->m_cell.SetBackColor(RGB(236, 233, 216));
			this->m_grid->SetCell(k, 11, &this->m_grid->m_cell);
			this->m_grid->RedrawCell(k, 11);
			this->m_grid->m_cell.SetBackColor(RGB(236, 233, 216));
			this->m_grid->SetCell(k, 17, &this->m_grid->m_cell);
			this->m_grid->RedrawCell(k, 17);
			this->m_grid->m_cell.SetBackColor(RGB(236, 233, 216));
			this->m_grid->SetCell(k, 20, &this->m_grid->m_cell);
			this->m_grid->RedrawCell(k, 20);
		}

		m_grid->QuickSetFont(k, CABECERO_COLUMNA, fontID);

		this->m_grid->RedrawCol(k);

		CuentasSegurosWeb pCuentaClase = pCuentas.pCuentas.at(i);
		if (sprintf_s(logCuentSeguro, "CCuentasSeguros::cargarCuentasSeguros -> pCuentaClase.iTipoCuenta: %i, pCuentasAcitvas->at(i).iTipoCuenta: %i", pCuentaClase.iTipoCuenta, pCuentasAcitvas->at(i).iTipoCuenta) < 0) { ; }
		util.GrabarLog(logCuentSeguro);
		CuentasSegurosWeb pCuenta = pCuentasAcitvas->at(i);
		if (sprintf_s(logCuentSeguro, "CCuentasSeguros::cargarCuentasSeguros -> pCuenta.iTipoCuenta: %i, pCuentasAcitvas->at(i).iTipoCuenta: %i", pCuenta.iTipoCuenta, pCuentasAcitvas->at(i).iTipoCuenta) < 0) { ; }
		util.GrabarLog(logCuentSeguro);
		if (pCuenta.iTipoCuenta == CUENTA_SEGUROCELULARES) {
			util.GrabarLog(logCuentSeguro);
			this->m_grid->QuickSetText(k, CABECERO_COLUMNA, pCuenta.descripcion.GetBuffer()); // Cabecero de la colunmna

			sDato.Format("%ld", pCuenta.lRecibo);
			this->m_grid->QuickSetText(k, FACTURA, sDato.Trim().GetBuffer()); //Factura
			this->m_grid->QuickSetAlignment(k, FACTURA, UG_ALIGNCENTER);

			miniFecha(cFecha1, pCuenta.tFechaVenta.dia(), pCuenta.tFechaVenta.mes(), pCuenta.tFechaVenta.ano());
			sDato.Format("%s", cFecha1);
			this->m_grid->QuickSetText(k, FECHA_COMPRA, sDato.Trim().GetBuffer()); //FechaCompra
			this->m_grid->QuickSetAlignment(k, FECHA_COMPRA, UG_ALIGNCENTER);

			//fontID = this->m_grid->AddFont("Lucida Console Bold", 14, 600);
			usingx("###,###", cTexto, (double)pCuenta.lImporteVenta);
			sDato.Format("%s", cTexto);
			this->m_grid->QuickSetText(k, IMPORTE, sDato.Trim().GetBuffer()); //Importe
			this->m_grid->QuickSetAlignment(k, IMPORTE, UG_ALIGNCENTER);

			this->m_grid->QuickSetText(k, TIPO_SEGURO, ""); //tiposeguro
			this->m_grid->QuickSetAlignment(k, TIPO_SEGURO, UG_ALIGNCENTER);

			sDato.Format("%d", pCuenta.iPlazo);
			this->m_grid->QuickSetText(k, PLAZO, sDato.Trim().GetBuffer()); //plazo
			this->m_grid->QuickSetAlignment(k, PLAZO, UG_ALIGNCENTER);

			usingx("###,###", cTexto, (double)pCuenta.lSaldo);
			sDato.Format("%s", cTexto);
			this->m_grid->QuickSetText(k, SALDO, sDato.Trim().GetBuffer()); //Saldo
			this->m_grid->QuickSetAlignment(k, SALDO, UG_ALIGNCENTER);

			usingx("###,###", cTexto, (double)pCuenta.lMensualidad);
			sDato.Format("%s", cTexto);
			this->m_grid->QuickSetText(k, BASE, sDato.Trim().GetBuffer()); //Saldo
			this->m_grid->QuickSetAlignment(k, BASE, UG_ALIGNCENTER);

			usingx("###,###", cTexto, (double)pCuenta.lVencido);
			sDato.Format("%s", cTexto);
			this->m_grid->QuickSetText(k, VENCIDO, sDato.Trim().GetBuffer()); // Vencido
			this->m_grid->QuickSetAlignment(k, VENCIDO, UG_ALIGNCENTER);

			usingx("###,###", cTexto, (double)pCuenta.lMinimo);
			//usingx("###,###", cTexto, (double) pCuenta.lMensualidad);
			sDato.Format("%s", cTexto);
			this->m_grid->QuickSetText(k, MINIMO, sDato.Trim().GetBuffer()); //minimo
			this->m_grid->QuickSetAlignment(k, MINIMO, UG_ALIGNCENTER);

			this->m_grid->QuickSetText(k, 21, "0"); //total
			this->m_grid->QuickSetAlignment(k, 21, UG_ALIGNRIGHT);

			sDato.Format("%04d%02d%02d", pCuenta.tFechaVencimiento.ano(), pCuenta.tFechaVencimiento.mes(), pCuenta.tFechaVencimiento.dia());
			this->m_grid->QuickSetText(k, FECHA_VENCIMIENTO, sDato.Trim().GetBuffer()); //fecha de vencimiento
			this->m_grid->QuickSetAlignment(k, FECHA_VENCIMIENTO, UG_ALIGNCENTER);

			sDato.Format("%04d%02d%02d", pCuenta.tFechaActivacion.ano(), pCuenta.tFechaActivacion.mes(), pCuenta.tFechaActivacion.dia());
			this->m_grid->QuickSetText(k, FECHA_ACTIVACION, sDato.Trim().GetBuffer()); //fecha de activacion
			this->m_grid->QuickSetAlignment(k, FECHA_ACTIVACION, UG_ALIGNCENTER);

			sDato.Format("%04d%02d%02d", pCuenta.tFechaCobertura.ano(), pCuenta.tFechaCobertura.mes(), pCuenta.tFechaCobertura.dia());
			this->m_grid->QuickSetText(k, FECHA_COBERTURA, sDato.Trim().GetBuffer()); //fecha de cobertura
			this->m_grid->QuickSetAlignment(k, FECHA_COBERTURA, UG_ALIGNCENTER);

			//sDato.Format("%s", pCuenta.cMotor);
			this->m_grid->QuickSetText(k, MOTOR, pCuenta.motor.GetBuffer()); //motor

			//sDato.Format("%s", pCuenta.cNumeroDeSerie);
			this->m_grid->QuickSetText(k, NUMERO_SERIE, pCuenta.numeroDeSerie.GetBuffer()); //numero de serie

			usingx("###,###", cTexto, (double)pCuenta.lMensualidad);
			sDato.Format("%s", cTexto);
			this->m_grid->QuickSetText(k, MENSUALIDAD, sDato.Trim().GetBuffer()); //mensualidad
			this->m_grid->QuickSetAlignment(k, MENSUALIDAD, UG_ALIGNCENTER);

			//sDato.Format("%s", pCuenta.cPoliza);
			this->m_grid->QuickSetText(k, POLIZACELULARES, pCuenta.poliza.GetBuffer()); //Factura

			//sDato.Format("%s", pCuenta.cPlacas);
			this->m_grid->QuickSetText(k, PLACAS, pCuenta.placas.GetBuffer()); //placas

			mesesRestantes = pCuenta.lVencido / pCuenta.lMensualidad;
			mesesRestantes = (mesesRestantes == 0) ? 1 : mesesRestantes;
			sDato.Format("%i", mesesRestantes);
			this->m_grid->QuickSetText(k, 33, sDato); //Meses capturados
			sDato.Empty();

			this->m_grid->QuickSetText(k, 34, "5"); //tiposeguro
			this->m_grid->QuickSetAlignment(k, 34, UG_ALIGNCENTER);

			usingx("###,###", cTexto, (double)pCuenta.lSaldo);
			sDato.Format("%s", cTexto);
			this->m_grid->QuickSetText(k, SALDA_CON, sDato.Trim().GetBuffer()); //SALDA CON
			this->m_grid->QuickSetAlignment(k, SALDA_CON, UG_ALIGNCENTER);
			sDato.Empty();
			this->lSaldaCon += pCuenta.lSaldo;
			this->m_grid->RedrawAll();
			k++;
		}
		//Agregado de consulta de datos de la cuenta de CPM
		else if (pCuenta.iTipoCuenta == CUENTA_SEGUROMOTO) {
			this->m_grid->QuickSetText(k, CABECERO_COLUMNA, pCuenta.descripcion.GetBuffer()); // Cabecero de la columna

			sDato.Format("%ld", pCuenta.lRecibo);
			this->m_grid->QuickSetText(k, 1, sDato.Trim().GetBuffer()); //Factura
			this->m_grid->QuickSetAlignment(k, 1, UG_ALIGNCENTER);

			miniFecha(cFecha1, pCuenta.tFechaVenta.dia(), pCuenta.tFechaVenta.mes(), pCuenta.tFechaVenta.ano());
			this->m_grid->QuickSetText(k, 2, cFecha1); //FechaCompra
			this->m_grid->QuickSetAlignment(k, 2, UG_ALIGNCENTER);

			//fontID = this->m_grid->AddFont("Lucida Console Bold", 14, 600);
			usingx("###,###", cTexto, (double)pCuenta.lImporteVenta);
			this->m_grid->QuickSetText(k, 3, cTexto); //Importe
			this->m_grid->QuickSetAlignment(k, 3, UG_ALIGNCENTER);

			//sDato.Format("%s", pCuenta.cTipoSeguro);
			this->m_grid->QuickSetText(k, 5, pCuenta.tipoSeguro.GetBuffer()); //tiposeguro
			this->m_grid->QuickSetAlignment(k, 5, UG_ALIGNCENTER);

			sDato.Format("%ld", pCuenta.iPlazo);
			this->m_grid->QuickSetText(k, 9, sDato.Trim().GetBuffer()); //plazo
			this->m_grid->QuickSetAlignment(k, 9, UG_ALIGNCENTER);

			usingx("###,###", cTexto, (double)pCuenta.lSaldo);
			this->m_grid->QuickSetText(k, 12, cTexto); //Saldo
			this->m_grid->QuickSetAlignment(k, 12, UG_ALIGNCENTER);

			usingx("###,###", cTexto, (double)pCuenta.lVencido);
			this->m_grid->QuickSetText(k, 15, cTexto); // Vencido
			this->m_grid->QuickSetAlignment(k, 15, UG_ALIGNCENTER);

			usingx("###,###", cTexto, (double)pCuenta.lMinimo + pCuenta.lVencido);
			this->m_grid->QuickSetText(k, 16, cTexto); //minimo
			this->m_grid->QuickSetAlignment(k, 16, UG_ALIGNCENTER);

			this->m_grid->QuickSetText(k, 21, "0"); //total
			this->m_grid->QuickSetAlignment(k, 21, UG_ALIGNRIGHT);

			sDato.Format("%04d%02d%02d", pCuenta.tFechaVencimiento.ano(), pCuenta.tFechaVencimiento.mes(), pCuenta.tFechaVencimiento.dia());
			this->m_grid->QuickSetText(k, 24, sDato.Trim().GetBuffer()); //fecha de vencimiento
			this->m_grid->QuickSetAlignment(k, 24, UG_ALIGNCENTER);

			sDato.Format("%04d%02d%02d", pCuenta.tFechaActivacion.ano(), pCuenta.tFechaActivacion.mes(), pCuenta.tFechaActivacion.dia());
			this->m_grid->QuickSetText(k, 25, sDato.Trim().GetBuffer()); //fecha de activacion
			this->m_grid->QuickSetAlignment(k, 25, UG_ALIGNCENTER);

			sDato.Format("%04d%02d%02d", pCuenta.tFechaCobertura.ano(), pCuenta.tFechaCobertura.mes(), pCuenta.tFechaCobertura.dia());
			this->m_grid->QuickSetText(k, 26, sDato.Trim().GetBuffer()); //fecha de cobertura
			this->m_grid->QuickSetAlignment(k, 26, UG_ALIGNCENTER);

			//sDato.Format("%s", pCuenta.cMotor);
			this->m_grid->QuickSetText(k, 27, pCuenta.motor.GetBuffer()); //motor

			//sDato.Format("%s", pCuenta.cNumeroDeSerie);
			this->m_grid->QuickSetText(k, 29, pCuenta.numeroDeSerie.GetBuffer()); //numero de serie

			usingx("###,###", cTexto, (double)pCuenta.lMensualidad);
			this->m_grid->QuickSetText(k, 30, cTexto); //mensualidad
			this->m_grid->QuickSetAlignment(k, 30, UG_ALIGNCENTER);

			//sDato.Format("%s", pCuenta.cPoliza);
			this->m_grid->QuickSetText(k, 31, pCuenta.poliza.GetBuffer()); //Factura

			//sDato.Format("%s", pCuenta.cPlacas);
			this->m_grid->QuickSetText(k, 32, pCuenta.placas.GetBuffer()); //placas
			this->lSaldaCon += pCuenta.lSaldo;
			this->m_grid->RedrawAll();
			k++;
		}
	}
	util.GrabarLog("CCuentasSeguros::cargarCuentasSeguros--Finaliza cargar cuentas seguro");

	return k;
}

void CCuentasSeguros::capturarAbonoSeguroMoto()
{
	char cFechaNacimientoM[10] = { 0 }, cFechaVencimientoM[10] = { 0 }, cFechaCoberturaM[10] = { 0 }, cMotor[30] = { 0 }, cSerie[30] = { 0 }, cPoliza[30] = { 0 }, cPlacas[30] = { 0 }, cTipoSeguro[15] = { 0 };
	bool bIndividual = false, bConyugal = false;
	CString sTexto;
	long lFolioSeguroi = 0, lFolioSeguroc = 0, lVencido = 0, lMinimo = 0, lMensualidad = 0, lSaldo = 0, lFolioSeguroMotos = 0, lMensualidadPreCalculo = 0, lAbonoAnterior = 0, lImporteTotal = 0;
	int iColX = 0, iAnioVencimiento = 0, iMesesAbono = 0, iPlazo = 0, iCobertura = 0;
	char cFechaVencimiento[10] = { 0 }, cDescripcion[20] = { 0 }, cTipo[12] = { 0 }, cPrecio[5] = { 0 }, cMensajeSeguimiento[50] = { 0 }, cNombreCompleto[50] = { 0 };
	char cStatusSeguro = ' ', cTipoCan = ' ', cClaveNoOfrecer = ' ';
	char cFechaNacMotos[10] = { 0 }, cFechaVenMotos[10] = { 0 }, cFechaCobMotos[10] = { 0 };
	CDlgCapturarDatosSeguroMotos dlgCapturarDatosSeguroMotos;

	lCliente = this->m_grid->lCliente;
	lEmpleado = this->m_grid->lEmpleado;
	iCaja = this->m_grid->iCaja;
	dlgCapturarDatosSeguroMotos.DoModal();

	iNumeroMeses = dlgCapturarDatosSeguroMotos.iNumeroMeses;

	this->m_grid->QuickGetText(iColX, 3, &sTexto);
	sTexto.Trim();
	sTexto.Remove(',');
	lImporteTotal = _ttol(sTexto);

	this->m_grid->QuickGetText(iCol, 15, &sTexto);
	sTexto.Trim();
	sTexto.Remove(',');
	lVencido = _ttol(sTexto);

	this->m_grid->QuickGetText(iCol, 12, &sTexto);
	sTexto.Trim();
	sTexto.Remove(',');
	lSaldo = _ttol(sTexto);

	this->m_grid->QuickGetText(iCol, 21, &sTexto);
	sTexto.Trim();
	sTexto.Remove(',');
	lAbonoAnterior = _ttol(sTexto);

	this->m_grid->QuickGetText(iCol, 1, &sTexto);
	sTexto.Trim();
	sTexto.Remove(',');
	lFolioSeguroMotos = _ttol(sTexto);

	this->m_grid->QuickGetText(iCol, 30, &sTexto);
	sTexto.Trim();
	sTexto.Remove(',');
	lMensualidadPreCalculo = _ttol(sTexto);

	this->m_grid->QuickGetText(iCol, 31, &sTexto);
	sTexto.Trim();
	if (!strcpy_s(cPoliza, sizeof(cPoliza), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Poliza)."); }

	this->m_grid->QuickGetText(iCol, 27, &sTexto);
	sTexto.Trim();
	if (!strcpy_s(cMotor, sizeof(cMotor), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Motor)."); }

	this->m_grid->QuickGetText(iCol, 29, &sTexto);
	sTexto.Trim();
	if (!strcpy_s(cSerie, sizeof(cSerie), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Serie)."); }

	this->m_grid->QuickGetText(iCol, 32, &sTexto);
	sTexto.Trim();
	if (!strcpy_s(cPlacas, sizeof(cPlacas), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Placas)."); }

	this->m_grid->QuickGetText(iCol, 25, &sTexto);
	sTexto.Trim();
	if (!strcpy_s(cFechaNacMotos, sizeof(cFechaNacMotos), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Fecha activacion)."); }

	this->m_grid->QuickGetText(iCol, 24, &sTexto);
	sTexto.Trim();
	if (!strcpy_s(cFechaVenMotos, sizeof(cFechaVenMotos), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Fecha vencimiento)."); }

	this->m_grid->QuickGetText(iCol, 26, &sTexto);
	sTexto.Trim();
	if (!strcpy_s(cFechaCobMotos, sizeof(cFechaCobMotos), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Fecha cobertura)."); }

	this->m_grid->QuickGetText(iCol, 9, &sTexto);
	sTexto.Trim();
	sTexto.Remove(',');
	iCobertura = _ttol(sTexto);

	this->m_grid->QuickGetText(iCol, 5, &sTexto);
	sTexto.Trim();
	if (!strcpy_s(cTipoSeguro, sizeof(cTipoSeguro), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Tipo seguro)."); }

	if (iNumeroMeses > 0) {
		this->m_grid->QuickGetText(iCol, 16, &sTexto);
		sTexto.Trim();
		sTexto.Remove(',');
		lMinimo = _ttol(sTexto);

		this->m_grid->QuickGetText(iCol, 30, &sTexto);
		sTexto.Trim();
		sTexto.Remove(',');
		lMensualidad = _ttol(sTexto);
		lMensualidad = lMinimo + (lMensualidadPreCalculo * (iNumeroMeses - 1));
	}

	if (lMensualidad > lSaldo) {
		AfxMessageBox("No se puede abonar una cantidad superior al saldo pendiente del cliente");
	}
	else {
		sTexto.Format("%ld", lMensualidad);
		this->m_grid->QuickSetText(iCol, 21, sTexto);
	}

	if (sprintf_s(cNombreCompleto, "%s %s %s", sNombreCliente.Trim(), sApellidoPaterno.Trim(), sApellidoMaterno.Trim()) == -1) { AfxMessageBox("Hubo un error al obtener el nombre del cliente."); }

	jsonAbonoMotosC.agregarAbono(this->m_grid->iTienda, iCiudad, this->m_grid->lCliente, this->m_grid->iCaja, lMensualidad, iNumeroMeses, cFechaNacMotos, cSexo, cFechaVenMotos, this->m_grid->lEmpleado, iCobertura, cIpServidorCartera, cNombreCompleto, cPoliza, cFechaCobMotos, cMotor, cSerie, cPlacas, "3", cTipoSeguro, lMensualidadPreCalculo, lImporteTotal);
	jsonAbonoMotosCL.agregarAbono(this->m_grid->lCliente, lMensualidad, iNumeroMeses, this->m_grid->iTienda, lMinimo, this->m_grid->iCaja, this->m_grid->lEmpleado, iCiudad, "3", cPoliza);

	lMensualidad = lMensualidadPreCalculo = iNumeroMeses = 0;
}

void CCuentasSeguros::capturarAbonoSeguroCelulares()
{
	char cMensajeLog[2000] = { 0 },
		cFechaNacimientoM[10] = { 0 },
		cFechaVencimientoM[10] = { 0 },
		cFechaCoberturaM[10] = { 0 },
		cMotor[30] = { 0 },
		cSerie[30] = { 0 },
		cPlacas[30] = { 0 },
		cTipoSeguro[15] = { 0 };
	bool bIndividual = false, bConyugal = false;
	CString sTexto = "";
	CString poliza = "";
	long lFolioSeguroi = 0,
		lFolioSeguroc = 0,
		lVencido = 0,
		lMinimo = 0,
		lMensualidad = 0,
		lSaldo = 0,
		lFolioSeguroMotos = 0,
		lMensualidadPreCalculo = 0,
		lAbonoAnterior = 0,
		lImporteTotal = 0;
	int iColX = 0, iAnioVencimiento = 0, iMesesAbono = 0, iPlazo = 0, iCobertura = 0, MaxMeses = 0, MesesDefault = 0;
	int mensualidadBase = 0;
	char cTexto[10] = { 0 }, cFechaVencimiento[10] = { 0 }, cDescripcion[20] = { 0 }, cTipo[12] = { 0 }, cPrecio[5] = { 0 }, cMensajeSeguimiento[50] = { 0 }, cNombreCompleto[50] = { 0 };
	char cStatusSeguro = ' ', cTipoCan = ' ', cClaveNoOfrecer = ' ';
	char cFechaNacMotos[10] = { 0 }, cFechaVenMotos[10] = { 0 }, cFechaCobMotos[10] = { 0 };
	CString cConsulta = "";
	Dlg_CapturaAbonoCelulares cdlg_CapturaAbonoCelulares;
	iColX = iCol;
	//Obtengo la poliza antes para la consulta de la siguiente funcion
	this->m_grid->QuickGetText(iColX, POLIZACELULARES, &poliza);
	if (poliza.IsEmpty())
	{
		AfxMessageBox("Hubo un error al obtener la informacion del grid (Póliza).");
	}
	else {
		//De aqui saco los meses que se mostrara al abrir el moda (en caso de reabrirlo recuperara el valor de meses capturado anteriormente)
		this->m_grid->QuickGetText(iColX, 33, &sTexto);
		sTexto.Trim();
		MesesDefault = _ttoi(sTexto);

		//Se manda el valor de MesesDefault a iNumeroMeses en cdlg_CapturaAbonoCelulares
		cdlg_CapturaAbonoCelulares.iNumeroMeses = 1;

		//Consulta para obtener el numero de meses maximo que se puede abonar
		cConsulta.Format("select * from fun_consultarmesesrestantes (%d,'%s');", this->m_grid->lCliente, poliza.Trim());
		CMaximo ObenerMesesParaAbonar(&odbc_1);
		if (ObenerMesesParaAbonar.Exec(cConsulta))
		{
			ObenerMesesParaAbonar.activarCols();
			while (ObenerMesesParaAbonar.leer())
			{
				MaxMeses = ObenerMesesParaAbonar.Total;
			}
		}
		else
		{
			ObenerMesesParaAbonar.odbc->GetLastError(ObenerMesesParaAbonar.GetHstmt());
			if (sprintf_s(cMensajeLog, "%s ERROR: Error al ejecutar la funcion fun_consultarmesesrestantes: [%s].", "ERROR EN LA CONSULTA(fun_consultarmesesrestantes)", ObenerMesesParaAbonar.odbc->LastErrStr()) != -1) { ; }
			util.GrabarLog(cMensajeLog);
		}


		//Se manda el valo de MaxMeses a mesesRestantes en cdlg_CapturaAbonoCelulares
		cdlg_CapturaAbonoCelulares.mesesRestantes = MaxMeses;

		////Levantamos el Modal
		//cdlg_CapturaAbonoCelulares.DoModal();

		////Recuperamos el valor de iNumeroMeses del cdlg_CapturaAbonoCelulares
		//iNumeroMeses = cdlg_CapturaAbonoCelulares.iNumeroMeses;

		////Sacamos los valores del grid y lo asignamos a variables
		//if(sprintf_s(cTexto, "%d", iNumeroMeses)){;}
		//this->m_grid->QuickSetText(iColX,33,cTexto);

		this->m_grid->QuickGetText(iColX, IMPORTE, &sTexto);
		sTexto.Trim();
		sTexto.Remove(',');
		lImporteTotal = _ttol(sTexto);

		this->m_grid->QuickGetText(iColX, VENCIDO, &sTexto);
		sTexto.Trim();
		sTexto.Remove(',');
		lVencido = _ttol(sTexto);

		this->m_grid->QuickGetText(iColX, SALDO, &sTexto);
		sTexto.Trim();
		sTexto.Remove(',');
		lSaldo = _ttol(sTexto);

		this->m_grid->QuickGetText(iColX, SU_PAGO_MINIMO, &sTexto);
		sTexto.Trim();
		sTexto.Remove(',');
		lAbonoAnterior = _ttol(sTexto);

		this->m_grid->QuickGetText(iColX, FACTURA, &sTexto);
		sTexto.Trim();
		sTexto.Remove(',');
		lFolioSeguroMotos = _ttol(sTexto);

		this->m_grid->QuickGetText(iColX, MENSUALIDAD, &sTexto);
		sTexto.Trim();
		sTexto.Remove(',');
		lMensualidadPreCalculo = _ttol(sTexto);

		sTexto.Empty();
		this->m_grid->QuickGetText(iColX, BASE, &sTexto);
		sTexto.Remove(',');
		mensualidadBase = _ttol(sTexto);

		this->m_grid->QuickGetText(iColX, MOTOR, &sTexto);
		sTexto.Trim();
		if (!strcpy_s(cMotor, sizeof(cMotor), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Motor)."); }

		this->m_grid->QuickGetText(iColX, 29, &sTexto);
		sTexto.Trim();
		if (!strcpy_s(cSerie, sizeof(cSerie), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Serie)."); }

		this->m_grid->QuickGetText(iColX, 32, &sTexto);
		sTexto.Trim();
		if (!strcpy_s(cPlacas, sizeof(cPlacas), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Placas)."); }

		this->m_grid->QuickGetText(iColX, 25, &sTexto);
		sTexto.Trim();
		if (!strcpy_s(cFechaNacMotos, sizeof(cFechaNacMotos), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Fecha activacion)."); }

		this->m_grid->QuickGetText(iColX, 24, &sTexto);
		sTexto.Trim();
		if (!strcpy_s(cFechaVenMotos, sizeof(cFechaVenMotos), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Fecha vencimiento)."); }

		this->m_grid->QuickGetText(iColX, 26, &sTexto);
		sTexto.Trim();
		if (!strcpy_s(cFechaCobMotos, sizeof(cFechaCobMotos), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Fecha cobertura)."); }

		this->m_grid->QuickGetText(iColX, PLAZO, &sTexto);
		sTexto.Trim();
		sTexto.Remove(',');
		iCobertura = _ttol(sTexto);

		this->m_grid->QuickGetText(iColX, 5, &sTexto);
		sTexto.Trim();
		if (!strcpy_s(cTipoSeguro, sizeof(cTipoSeguro), sTexto) == 0) { AfxMessageBox("Hubo un error al obtener la informacion del grid (Tipo seguro)."); }

		cdlg_CapturaAbonoCelulares.mensualidad = mensualidadBase;

		//Validacion para saber el monto, pago normal o pago con vencido 
		if (cdlg_CapturaAbonoCelulares.DoModal() == IDOK) {
			iNumeroMeses = cdlg_CapturaAbonoCelulares.iNumeroMeses;
			if (iNumeroMeses > 0) {
				this->m_grid->QuickGetText(iColX, MINIMO, &sTexto);
				sTexto.Trim();
				sTexto.Remove(',');
				lMinimo = _ttol(sTexto);
				lMensualidad = cdlg_CapturaAbonoCelulares.importeCelular;
			}

			if (lMensualidad > lSaldo) {
				AfxMessageBox("No se puede abonar una cantidad superior al saldo pendiente del cliente", MB_ICONINFORMATION);
				iNumeroMeses = 0;
				lMensualidad = 0;
				//Con esto restablecemos el numero de meses por default por si hubo algun error al capturar los meses
				//this->m_grid->QuickSetText(iColX,33,"1");
			}
			else {
				if (sprintf_s(cNombreCompleto, "%s %s %s", sNombreCliente.Trim(), sApellidoPaterno.Trim(), sApellidoMaterno.Trim()) == -1) { AfxMessageBox("Hubo un error al obtener el nombre del cliente."); }
				//Generamos el Json para su respectivo guardado
				jsonAbonoCelularesC.agregarAbono(this->m_grid->iTienda, iCiudad, this->m_grid->lCliente, this->m_grid->iCaja, lMensualidad, iNumeroMeses, cFechaNacMotos, cSexo, cFechaVenMotos, this->m_grid->lEmpleado, iCobertura, cIpServidorCartera, cNombreCompleto, poliza.GetBuffer(), cFechaCobMotos, cMotor, cSerie, cPlacas, "3", cTipoSeguro, lMensualidadPreCalculo, lImporteTotal);
				jsonAbonoCelularesCL.agregarAbono(this->m_grid->lCliente, lMensualidad, iNumeroMeses, this->m_grid->iTienda, lMinimo, this->m_grid->iCaja, this->m_grid->lEmpleado, iCiudad, "3", poliza.GetBuffer());
			}

		}
		else {
			iNumeroMeses = 0;
			lMensualidad = 0L;
		}

		if (iNumeroMeses == 0)
		{
			jsonAbonoCelularesC.eliminarAbono(poliza);
			jsonAbonoCelularesCL.eliminarAbono(poliza);
		}

		sTexto.Format("%d", iNumeroMeses);
		this->m_grid->QuickSetText(iColX, 33, sTexto.GetBuffer());

		sTexto.Format("%ld", lMensualidad);
		this->m_grid->QuickSetText(iColX, SU_PAGO_MINIMO, sTexto);
		this->m_grid->QuickSetAlignment(iColX, SU_PAGO_MINIMO, UG_ALIGNRIGHT);

		lMensualidad = lMensualidadPreCalculo = iNumeroMeses = 0;
	}
}


bool CCuentasSeguros::grabarSegurosCacarmov() {

	bool flagSeguros = true;
	if (!jsonAbonoCelularesC.vacio()) {
		if (!grabarSeguroCelularesCaCarmov()) {
			flagSeguros = false;
		}
	}
	else {
		util.GrabarLog("jsonAbonoCelularesC vacio, no aplica abono");
	}

	if (!jsonAbonoMotosC.vacio()) {
		if (!grabarSeguroMotosCaCarmov()) {
			flagSeguros = false;
		}
	}
	else {
		util.GrabarLog("jsonAbonoMotosC vacio, no aplica abono");
	}
	return flagSeguros;
}

bool CCuentasSeguros::grabarSegurosCarmovX() {
	bool flagSeguros = true;
	if (!jsonAbonoCelularesCL.vacio()) {
		if (!grabarSeguroCelularesCarmovx()) {
			flagSeguros = false;
		}
	}
	else {
		util.GrabarLog("jsonAbonoCelularesCL vacio, no aplica abono");
	}

	if (!jsonAbonoMotosCL.vacio()) {
		if (!grabarSeguroMotosCarmovX()) {
			flagSeguros = false;
		}
	}
	else {
		util.GrabarLog("jsonAbonoMotosCL vacio, no aplica abono");
	}
	return flagSeguros;
}

bool CCuentasSeguros::grabarSeguroMotosCaCarmov()
{
	char cMensajeLog[2000] = { 0 };
	bool bResultado = false;
	char cSql[1100] = { 0 }, cJson[1000] = { 0 };
	long folioMotos = lNumeroRecibo;

	if (!strcpy_s(cJson, sizeof(cJson), jsonAbonoMotosC.getJson().c_str()) == 0) { AfxMessageBox("Hubo un error al obtener los datos del abono de motos"); }

	if (sprintf_s(cSql, "SELECT FUN_CAGRABARABONOSEGUROMOTO( %s, %ld )", cJson, folioMotos) == -1) { AfxMessageBox("Hubo un error al generar el abono de motos."); }

	if (!jsonAbonoMotosC.vacio()) {
		CMaximo flagCoppel(&odbc, false);
		if (flagCoppel.Exec(cSql))
		{
			flagCoppel.activarCols();
			if (flagCoppel.Leer())
			{
				bResultado = true;
				jsonAbonoMotosC.limpiar();
			}
		}
		else
		{
			flagCoppel.odbc->GetLastError(flagCoppel.GetHstmt());
			if (sprintf_s(cMensajeLog, "%s ERROR: Error al ejecutar la funcion FUN_CAGRABARABONOSEGUROMOTO: [%s].", "ERROR EN LA CONSULTA(grabarSeguroMotosCaCarmov)", flagCoppel.odbc->LastErrStr()) == -1) { AfxMessageBox("Hubo un error al guardar el abono de motos en tienda."); }
			util.GrabarLog(cMensajeLog);
			bResultado = false;
		}
	}
	else
	{
		bResultado = true;
	}
	return  bResultado;
}

bool CCuentasSeguros::grabarSeguroMotosCarmovX()
{
	char cMensajeLog[2000] = { 0 };
	bool bResultado = false;
	char cSql[1000] = { 0 }, cJson[1000] = { 0 };
	long folioMotos = lNumeroRecibo;

	if (!strcpy_s(cJson, sizeof(cJson), jsonAbonoMotosCL.getJson().c_str()) == 0) { AfxMessageBox("Hubo un error al obtener los datos del abono de motos"); }

	if (sprintf_s(cSql, "SELECT fun_crgrabarabonoseguromoto( %s, %ld )", cJson, folioMotos)) { ; }

	if (!jsonAbonoMotosCL.vacio()) {
		CMaximo flagCoppel(&odbc_1, false);
		if (flagCoppel.Exec(cSql))
		{
			flagCoppel.activarCols();
			if (flagCoppel.Leer())
			{
				bResultado = true;
				jsonAbonoMotosCL.limpiar();
			}
		}
		else
		{
			flagCoppel.odbc->GetLastError(flagCoppel.GetHstmt());
			if (sprintf_s(cMensajeLog, "%s ERROR: Error al ejecutar la funcion grabarSeguroMotosCarmovX: [%s].", "ERROR EN LA CONSULTA(grabarSeguroMotosCarmovX)", flagCoppel.odbc->LastErrStr()) == -1) { AfxMessageBox("Hubo un error al guardar el abono de motos en cartera."); }
			util.GrabarLog(cMensajeLog);
			bResultado = false;
		}
	}
	else { bResultado = true; }
	return  bResultado;
}

bool CCuentasSeguros::grabarSeguroCelularesCarmovx()
{
	char cMensajeLog[2000] = { 0 }, cLog[1024] = { 0 };
	bool bResultado = false;
	CString sql = "";
	CString json = "";
	long folioCelulares = lNumeroRecibo;

	json.Format("%s", jsonAbonoCelularesCL.getJson());
	sql.Format("SELECT fun_crgrabarabonosegurocelulares( %s, %ld )", json, folioCelulares);
	//util.GrabarLog(cSql);
	if (!jsonAbonoCelularesCL.vacio()) {
		if (sprintf_s(cLog, "CCuentasSeguros::grabarSeguroCelularesCarmovx: " + sql) < 0) { ; }
		util.GrabarLog(cLog);
		CMaximo flagCoppel(&odbc_1, false);
		if (flagCoppel.Exec(sql.GetBuffer()))
		{
			flagCoppel.activarCols();
			if (flagCoppel.Leer())
			{
				bResultado = true;
				jsonAbonoCelularesCL.limpiar();
			}
		}
		else
		{
			//Se obtiene el error
			flagCoppel.odbc->GetLastError(flagCoppel.GetHstmt());
			if (sprintf_s(cMensajeLog, "%s ERROR: Error al ejecutar la funcion fun_crgrabarabonosegurocelulares: [%s].", "ERROR EN LA CONSULTA(grabarSeguroCelularesCarmovx)",
				flagCoppel.odbc->LastErrStr()) == -1) {
				AfxMessageBox("Hubo un error al guardar el abono de celulares en cartera.");
			}
			util.GrabarLog(cMensajeLog);
			bResultado = false;
		}
	}
	else { bResultado = true; }
	return  bResultado;
}

bool CCuentasSeguros::grabarSeguroCelularesCaCarmov()
{
	char cMensajeLog[2000] = { 0 }, cLog[1024] = { 0 };
	bool bResultado = false;
	CString sql = "";
	CString json = "";
	long folioCelulares = lNumeroRecibo;

	json.Format("%s", jsonAbonoCelularesC.getJson());
	sql.Format("SELECT FUN_CAGRABARABONOSEGUROCELULARES( %s, %ld )", json, folioCelulares);

	if (!jsonAbonoCelularesC.vacio()) {
		if (sprintf_s(cLog, "CCuentasSeguros::grabarSeguroCelularesCaCarmov: " + sql) < 0) { ; }
		util.GrabarLog(cLog);
		CMaximo flagCoppel(&odbc, false);
		if (flagCoppel.Exec(sql.GetBuffer()))
		{
			flagCoppel.activarCols();
			if (flagCoppel.Leer())
			{
				bResultado = true;
				jsonAbonoCelularesC.limpiar();
			}
		}
		else
		{
			flagCoppel.odbc->GetLastError(flagCoppel.GetHstmt());
			if (sprintf_s(cMensajeLog, "%s ERROR: Error al ejecutar la funcion FUN_CAGRABARABONOSEGUROCELULARES: [%s].", "ERROR EN LA CONSULTA(grabarSeguroCelularesCaCarmov)",
				flagCoppel.odbc->LastErrStr()) == -1) {
				AfxMessageBox("Hubo un error al guardar el abono de celulares en tienda.");
			}
			util.GrabarLog(cMensajeLog);
			bResultado = false;
		}
	}
	else
	{
		bResultado = true;
	}
	return  bResultado;
}

//void CCuentasSeguros::grabarLog(char* cTexto)
//{
//	char sArch[80]={0};
//	char cTextoGrabar[2048]={0};
//	CTime tFecha = CTime::GetCurrentTime();
//
//	if(sprintf_s(sArch, "C:\\sys\\mem\\CapturarAbonos%02d%02d.log", tFecha.GetMonth(), tFecha.GetDay() ) < 0){;}
//	
//	if(sprintf_s( cTextoGrabar, "%04d-%02d-%02d %02d:%02d:%02d %s\n", tFecha.GetYear(), tFecha.GetMonth(), tFecha.GetDay(), tFecha.GetHour(), tFecha.GetMinute(), tFecha.GetSecond(), cTexto) < 0){;}
//	C_Archivo arch( sArch, &cTextoGrabar, sizeof( cTextoGrabar ) );
//	arch.posicionar( (long)0, BASE_FINAL);
//	arch.grabar( cTextoGrabar, (unsigned int) strnlen(cTextoGrabar, sizeof(cTextoGrabar)) );
//
//}