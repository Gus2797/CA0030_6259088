#pragma once
#include "C_archiv.hpp"
#include "gridcapturarabono.hpp"
#include "JsonAbonoMotosC.h"
#include "JsonAbonoMotosCL.h"
#include "JsonAbonoCelularesC.h"
#include "JsonAbonoCelularesCL.h"
#include "DlgCapturarDatosSeguroMotos.h"
#include "Dlg_CapturaAbonoCelulares.h"
#include "DlgCapturarAbono.h"
#include "CConsumoAPICuentasSeguros.h"
#include <iostream>

#include "CUtil.h"

using namespace std;


#define CUENTA_SEGUROCELULARES		2
#define CUENTA_SEGUROMOTO			1

class CCuentasSeguros
{
public:
	CCuentasSeguros(void);
	~CCuentasSeguros(void);

	GridCapturarAbono* m_grid;
	CConsumoAPICuentasSeguros* pCuentasSeguros;

	int iCol, iCiudad, iCaja, iNumeroMeses;
	CString sNombreCliente, sApellidoPaterno, sApellidoMaterno;
	long lCliente, lEmpleado, lNumeroRecibo, lSaldaCon;
	char cIpServidorCartera[20], cSexo;

	JsonAbonoCelularesC jsonAbonoCelularesC;
	JsonAbonoCelularesCL jsonAbonoCelularesCL;
	JsonAbonoMotosC jsonAbonoMotosC;
	JsonAbonoMotosCL jsonAbonoMotosCL;

	CUtil util;

	//int cargarCuentasSeguros(int k);
	int cargarCuentasSeguros(int k, vector<CuentasSegurosWeb>* pCuentasAcitvas);
	void capturarAbonoSeguroMoto();
	void capturarAbonoSeguroCelulares();
	bool grabarSegurosCacarmov();
	bool grabarSegurosCarmovX();
	bool grabarSeguroMotosCaCarmov();
	bool grabarSeguroMotosCarmovX();
	bool grabarSeguroCelularesCarmovx();
	bool grabarSeguroCelularesCaCarmov();
	//void grabarLog(char *cTexto);
	//void grabarLog(CString mensaje);
};

