#include <iostream>
//#include <fstream>
#include "json\src\json.h"
#include "CConsumoAPICuentasSeguros.h"
#include "CargaDllCSharp.h"
#include "json\src\ArduinoJson.h"

using namespace std;

CConsumoAPICuentasSeguros::CConsumoAPICuentasSeguros()
{
	this->lMinimoTotal = 0L;
	this->lVencido = 0L;
	this->lSaldo = 0L;
	this->lImporteTotal = 0L;
	this->iCuentasActivas = 0;
	this->lBaseTotal = 0L;
	pCuentas.clear();
}

CConsumoAPICuentasSeguros::~CConsumoAPICuentasSeguros()
{
	this->lMinimoTotal = 0L;
	this->lVencido = 0L;
	this->lSaldo = 0L;
	this->lImporteTotal = 0L;
	this->iCuentasActivas = 0;
	this->lBaseTotal = 0L;
	if (pCuentas.size() > 0)
	{
		pCuentas.clear();
	}
}

void CConsumoAPICuentasSeguros::consultaCuentaSeguros(char cIpServidorCartera[20], char cFechaTienda[12], long lCliente, CString cIpTienda, int iNumeroTienda)
{
	CString sRuta = "", sClaseConstructor = "", sAux = "", sMetodo = "";
	CStringArray sArgsConstructor, sArgsMetodo;
	//char logMessage[2048] = {0};
	CString logMessage = "";
	CString jsonRespuesta = "";

	util.GrabarLog("CConsumoAPICuentasSeguros::consultaCuentaSeguros(...) -> Inicia consulta de cuentas de seguros.");

	sRuta = "C:\\SYS\\PROGX\\GN\\GN0305.DLL"; //Modulo
	sClaseConstructor = "ConsultaCuentasSeguros.ConsultarCuentasSegurosAPI"; //Clase con el constructor
	sMetodo = "ConsultarApiCuentas"; //Metodo a invocar

	sAux.Format("%s", cIpServidorCartera);
	sArgsMetodo.Add(sAux.Trim());

	sAux.Format("%s", cFechaTienda);
	sArgsMetodo.Add(sAux.Trim());

	sAux.Format("%ld", lCliente);
	sArgsMetodo.Add(sAux.Trim());

	sAux.Format("%s", cIpTienda);
	sArgsMetodo.Add(sAux.Trim());

	sAux.Format("%d", iNumeroTienda);
	sArgsMetodo.Add(sAux.Trim());

	CFileFind finder;
	BOOL bFound = false;

	try {
		bFound = finder.FindFile(sRuta);
		logMessage.Format("CConsumoAPICuentasSeguros::consultaCuentaSeguros(...) -> Resultado busqueda DLL: %d.", bFound);
		util.GrabarLog(logMessage);

		if (bFound == TRUE)
		{
			finder.Close();
			::CoInitialize(NULL);
			CCargaDllCSharp* objPuente = new CCargaDllCSharp();
			objPuente->CargarDllCSharp(sRuta, sClaseConstructor, METODO_STRING, sMetodo, sArgsConstructor, sArgsMetodo);
			objPuente->getRespuesta(jsonRespuesta);
			util.GrabarLog(jsonRespuesta.GetBuffer());
			::CoUninitialize();
			util.GrabarLog("CConsumoAPICuentasSeguros Liberar --> objPuente 82 Cambio Softtek");
			delete objPuente;
			util.GrabarLog("CConsumoAPICuentasSeguros Se Libera --> objPuente 82 Cambio Softtek");


			if (!jsonRespuesta.IsEmpty()) {
				parsearJson(jsonRespuesta);
			}
			else
			{
				AfxMessageBox("Ocurrio un error al consumir el servicio de cuentas seguros: GN0305.DLL (ConsultaCuentasSeguros)");
				util.GrabarLog("CConsumoAPICuentasSeguros::consultaCuentaSeguros(...) -> Error al consumir la API de CuentasSeguros.");

			}

		}
		else
		{
			util.GrabarLog("CConsumoAPICuentasSeguros::consultaCuentaSeguros(...) -> Error al encontrar el modulo GN0305.");
			AfxMessageBox("No se pudo encontrar el modulo: GN0305.DLL (ConsultaCuentasSeguros)");
		}
	}
	catch (...) {
		util.GrabarLog("CConsumoAPICuentasSeguros::consultaCuentaSeguros(...) -> Error en la operacion de cuentas de seguros.");
	}
	util.GrabarLog("Termina el consultaCuentaSeguros");
}

void CConsumoAPICuentasSeguros::parsearJson(CString json) {

	StaticJsonBuffer<32767> jsonBuffer;
	this->lMinimoTotal = 0L;
	this->lSaldo = 0L;
	this->lVencido = 0L;
	this->lImporteTotal = 0L;
	this->pCuentas.clear();
	int tamanioCuentas = 0;

	util.GrabarLog("Si cliente tiene una cuenta");
	JsonObject& root = jsonBuffer.parseObject(json.GetBuffer());
	if (!root.success()) {
		AfxMessageBox("Error al leer cuentas de seguros de cliente.", MB_ICONERROR);
	}
	else {

		util.GrabarLog("Revisando si tiene cuentas activas");
		this->iCuentasActivas = root["cuentasActivas"];
		if (this->iCuentasActivas > 0) {
			JsonArray& cuentas = root["cuentas"];
			util.GrabarLog("Entrando al arreglo de la cuenta");

			if (cuentas.success()) {
				tamanioCuentas = cuentas.size();
				for (int i = 0; i < tamanioCuentas; ++i) {
					CuentasSegurosWeb cuenta;
					inicializarCuenta(cuenta);
					cuenta.iTipoCuenta = cuentas[i]["tipoCuenta"];
					if (cuenta.iTipoCuenta == CUENTA_SEGUROCELULARES)
					{

						cuenta.lRecibo = cuentas[i]["recibo"];
						cuenta.lImporteVenta = cuentas[i]["importeVenta"];
						cuenta.iCiudad = cuentas[i]["ciudad"];
						cuenta.iTienda = cuentas[i]["tienda"];
						cuenta.lMensualidad = cuentas[i]["mensualidad"];
						cuenta.iPlazo = cuentas[i]["plazo"];
						cuenta.lSaldo = cuentas[i]["saldo"];
						cuenta.lVencido = cuentas[i]["vencido"];
						cuenta.lMinimo = cuentas[i]["minimo"];

						this->lMinimoTotal += cuenta.lMinimo;
						this->lVencido += cuenta.lVencido;
						this->lSaldo += cuenta.lSaldo;
						this->lImporteTotal += cuenta.lImporteVenta;
						this->lBaseTotal += cuenta.lMensualidad;

						obtenerValueString(cuentas[i]["tipoSeguro"], cuenta.tipoSeguro);
						obtenerValueString(cuentas[i]["descripcion"], cuenta.descripcion);
						obtenerValueString(cuentas[i]["poliza"], cuenta.poliza);
						obtenerValueString(cuentas[i]["placas"], cuenta.placas);
						obtenerValueString(cuentas[i]["motor"], cuenta.motor);
						obtenerValueString(cuentas[i]["numeroDeSerie"], cuenta.numeroDeSerie);

						obtenerFecha(cuentas[i]["fechaVenta"], cuenta.tFechaVenta);
						obtenerFecha(cuentas[i]["fechaVencimiento"], cuenta.tFechaVencimiento);
						obtenerFecha(cuentas[i]["fechaActivacion"], cuenta.tFechaActivacion);
						obtenerFecha(cuentas[i]["fechaCobertura"], cuenta.tFechaCobertura);

						this->pCuentas.push_back(cuenta);
					}
				}
			}
			else {
				AfxMessageBox("Error al leer cuentas de seguros de cliente.", MB_ICONERROR);
			}
		}
	}
	util.GrabarLog("Saliendo de la Funcion parsearJson");
}

void CConsumoAPICuentasSeguros::grabarLog(CString mensaje) {
	CString sRutaArchivo = "", sMensajeGrabar = "";
	CTime tFecha = CTime::GetCurrentTime();

	sRutaArchivo.Format("C:\\sys\\mem\\CapturarAbonos%02d%02d.log", tFecha.GetMonth(), tFecha.GetDay());
	sMensajeGrabar.Format("%04d-%02d-%02d %02d:%02d:%02d %s", tFecha.GetYear(), tFecha.GetMonth(), tFecha.GetDay(), tFecha.GetHour(), tFecha.GetMinute(), tFecha.GetSecond(), mensaje);

	std::ofstream archivo(sRutaArchivo.GetBuffer(), std::ios::app); // Abre el archivo en modo de escritura al final del archivo
	if (archivo.is_open()) {
		archivo << sMensajeGrabar.GetBuffer() << std::endl; // Escribe el mensaje en el archivo
		archivo.close(); // Cierra el archivo después de escribir
	}
	else {
		std::cerr << "Error al abrir el archivo de log." << std::endl;
	}
}

//
//void CConsumoAPICuentasSeguros::util.GrabarLog(char* cTexto)
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

void CConsumoAPICuentasSeguros::inicializarCuenta(CuentasSegurosWeb& cuenta) {
	cuenta.tipoSeguro = "";
	cuenta.descripcion = "";
	cuenta.poliza = "";
	cuenta.placas = "";
	cuenta.motor = "";
	cuenta.numeroDeSerie = "";

	cuenta.iTipoCuenta = 0;
	cuenta.iCiudad = 0;
	cuenta.iTienda = 0;
	cuenta.iPlazo = 0;

	cuenta.lRecibo = 0L;
	cuenta.lImporteVenta = 0L;
	cuenta.lMensualidad = 0L;
	cuenta.lSaldo = 0L;
	cuenta.lVencido = 0L;
	cuenta.lMinimo = 0L;

	cuenta.tFechaVenta.ponerFecha(1, 1, 1900);
	cuenta.tFechaVencimiento.ponerFecha(1, 1, 1900);
	cuenta.tFechaActivacion.ponerFecha(1, 1, 1900);
	cuenta.tFechaCobertura.ponerFecha(1, 1, 1900);
}

void CConsumoAPICuentasSeguros::obtenerFecha(const char* fechaService, SqlTimeStamp& fecha) {
	CString year = "";
	CString month = "";
	CString day = "";
	CString date = "";
	fecha.ponerFecha(1, 1, 1900);
	obtenerValueString(fechaService, date);
	int nTokenPos = 0;
	nTokenPos = 0;
	year = date.Tokenize(_T("-"), nTokenPos);
	nTokenPos = 4;
	month = date.Tokenize(_T("-"), nTokenPos);
	nTokenPos = 7;
	day = date.Tokenize(_T("-"), nTokenPos);
	fecha.ponerFecha(strtol(day, NULL, 10), strtol(month, NULL, 10), strtol(year, NULL, 10)); //Dangerous Function
}

void CConsumoAPICuentasSeguros::obtenerValueString(const char* value, CString& variable) {
	CString valorString = "";
	variable = "";
	valorString.Format("%s", value);
	variable.Format("%s", valorString.Trim());
}