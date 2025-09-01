#include "ApiSanaTuDeudaClient.h"
#include <DlgCapturarAbono.cpp>


ApiSanaTuDeudaClient::ApiSanaTuDeudaClient()
{

}

ApiSanaTuDeudaClient::~ApiSanaTuDeudaClient()
{
}

void ApiSanaTuDeudaClient::InicializarVariables()
{
	esClienteZ = false;
	existeCuentaSolex = false;
	url = "";
}

void ApiSanaTuDeudaClient::SetData(ParametrosApiSanaTuDeuda parametros)
{
	this->InicializarVariables();
	this->esClienteZ = parametros.bEsClienteZ;
	this->existeCuentaSolex = parametros.bExisteCuentaSolex;
	this->numeroCliente = parametros.lNumeroCliente;
	this->url = parametros.sUrl;
	this->LoggearData();
}

void ApiSanaTuDeudaClient::LoggearData()
{
	CString logAux = "";
	logAux.Format("esClienteZ [%d] - existeCuentaSolex [%d] - numeroCliente [%ld] - url [%s]",
				   esClienteZ,		 existeCuentaSolex,		  numeroCliente,		url);

	if (sprintf_s(log, sizeof(log), "[ApiSanatuDeudaClient] Data: %s", logAux)) { ; }
	util.GrabarLog(log);
}

/*
void ApiSanaTuDeudaClient::GrabarLog(char* cTexto)
{
	char sArch[80] = { 0 };
	int iTamanio = strlen(cTexto) + 100;
	char* cTextoGrabar = new char[iTamanio];
	memset(cTextoGrabar, 0, iTamanio);
	CTime tFecha = CTime::GetCurrentTime();

	sprintf_s(sArch, "C:\\sys\\mem\\CapturarAbonos%02d%02d.log", tFecha.GetMonth(), tFecha.GetDay());

	sprintf_s(cTextoGrabar, iTamanio, "%04d-%02d-%02d %02d:%02d:%02d %s\n", tFecha.GetYear(), tFecha.GetMonth(), tFecha.GetDay(), tFecha.GetHour(), tFecha.GetMinute(), tFecha.GetSecond(), cTexto);
	C_Archivo arch(sArch, &cTextoGrabar, sizeof(cTextoGrabar));
	arch.posicionar((long)0, BASE_FINAL);
	arch.grabar(cTextoGrabar, (unsigned int)strlen(cTextoGrabar));

	delete[]cTextoGrabar;
}
*/

bool ApiSanaTuDeudaClient::GetApiSanaTuDeuda()
{
	Json::Value response;
	Json::Reader reader;
	int clienteCandidato = 0;
	CString urlApi = "";
	urlApi.Format("%s%ld", url, numeroCliente);

	#pragma region RESTREB
	CString token = "";
	bool bRespuesta = false;
	_bstr_t bsData = "<empty>";
	CString* sData = NULL;
	CString sRespuesta;
	_bstr_t sConsulta = urlApi;

	if (sprintf_s(log, sizeof(log), "Consulta ApiSanaTuDeuda: %s", urlApi) > 0) { ; }
	util.GrabarLog(log);

	try
	{
		CoInitialize(NULL);
		RESTREB::IRestREbPtr rest;
		rest.CreateInstance(__uuidof(RESTREB::REbRest));
		bsData = rest->Get(sConsulta);
		CoUninitialize();

		sData = new CString(bsData.GetBSTR());

		sRespuesta = sData->GetString();
		bRespuesta = true;

		delete sData;
	}
	catch (CExcepcion* error)
	{
		if (error != nullptr)
		{
			util.GrabarLog(error->GetTraza());
		}
		else
		{
			util.GrabarLog("No se recibió el objeto de error");
		}
	}
	catch (...)
	{
		if (sprintf_s(log, sizeof(log), "%s", "ERROR ApiSanaTuDeudaClient::GetApiSanaTuDeuda()")) { ; }
		util.GrabarLog(log);

		bRespuesta = false;
		AfxMessageBox("Error al consumir el servicio, favor de contactar con Mesa de Ayuda.");
	}
	#pragma endregion

	#pragma region [VALIDACION]
	
	if (bRespuesta)
	{
		//AfxMessageBox("PRUEBA - SE SUSTITUYE RESPUESTA POR DATOS DE PRUEBA");
		//sRespuesta.Format("{\"meta\": {\"status\": \"SUCCESS\",\"count\": 1},\"data\": {\"response\": 0}}\"");

		if (sprintf_s(log, sizeof(log), "[ApiSanaTuDeudaClient] Respuesta servicio: %s", sRespuesta)) { ; }
		util.GrabarLog(log);

		std::string sValue = sRespuesta;
		bool parsedSuccess = reader.parse(sValue, response, false);

		if (parsedSuccess)
		{
			util.GrabarLog("Parceado correcto.");

			if (response.size() == NULL)
			{
				util.GrabarLog("Respuesta vacia del servicio.");
				return false;
			}

			clienteCandidato = response["data"]["response"].asInt();

			if (clienteCandidato == CLIENTE_CANDIDATO)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			util.GrabarLog("Parceado incorrecto.");
		}
	}
	else
	{
		util.GrabarLog("bRespuesta = false");
		return false;
	}

	#pragma endregion
}
