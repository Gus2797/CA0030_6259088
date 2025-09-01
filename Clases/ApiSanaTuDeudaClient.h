#pragma once

//#include <C_archiv.hpp>
#include "stdafx.h"
#import "C:\sys\progx\libcsharp\RESTREB.TLB"
#include <ParametrosApiSanaTuDeuda.h>
#include "json\src\json.h"
#include "CUtil.h"


class ApiSanaTuDeudaClient
{
	public:
	ApiSanaTuDeudaClient();
	~ApiSanaTuDeudaClient();
	
	#pragma region [DEFINES]

	#define CLIENTE_CANDIDATO 1

	#pragma endregion

	

	#pragma region [METODOS]
	
	void SetData(ParametrosApiSanaTuDeuda parametros);
	bool GetApiSanaTuDeuda();

	private:
	void InicializarVariables();
	void LoggearData();
	//void GrabarLog(char* cTexto);

	#pragma endregion



	private:
	#pragma region [CAMPOS]

	char log[1024];
	bool existeCuentaSolex;
	bool esClienteZ;
	CString url;
	long numeroCliente;
	CUtil util;

	#pragma endregion

};

