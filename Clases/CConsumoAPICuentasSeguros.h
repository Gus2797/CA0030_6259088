#pragma once
#include <sqltime.hpp>
#include <iostream>
#include <fstream>

#include "gnwproto.hpp"

#include "CUtil.h"

using namespace std;

struct CuentasSegurosWeb {
	int iTipoCuenta,
		iCiudad,
		iTienda,
		iPlazo;

	long lRecibo,
		lImporteVenta,
		lMensualidad,
		lSaldo,
		lVencido,
		lMinimo;

	CString tipoSeguro;
	CString descripcion;
	CString poliza;
	CString placas;
	CString motor;
	CString numeroDeSerie;

	SqlTimeStamp tFechaVenta,
		tFechaVencimiento,
		tFechaActivacion,
		tFechaCobertura;
};

#define CUENTA_SEGUROMOTO			1
#define CUENTA_SEGUROCELULARES		2

class CConsumoAPICuentasSeguros
{
public:
	CConsumoAPICuentasSeguros();
	~CConsumoAPICuentasSeguros();

public:
	vector<CuentasSegurosWeb> pCuentas;
	int iCuentasActivas;

	long lMinimoTotal, lVencido, lSaldo, lImporteTotal,
		lBaseTotal;

	CUtil util;

	void parsearJson(CString json);
	void limpiarCuentasSeguros();
	void consultaCuentaSeguros(char cIpServidorCartera[20], char cFechaTienda[12], long lCliente, CString cIpTienda, int iNumeroTienda);
	void grabarLog(CString mensaje);

private:
	void inicializarCuenta(CuentasSegurosWeb& cuenta);
	void obtenerFecha(const char* value, SqlTimeStamp& fecha);
	void obtenerValueString(const char* value, CString& variable);

};

