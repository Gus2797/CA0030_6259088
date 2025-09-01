#include "stdafx.h"
#include "CConsumirServicioRest.h"


CConsumirServicioRest::CConsumirServicioRest( CString sUrl, CString sJson, CString sToken )
{
	sRespuesta.Empty();
	this->obtenerRespuesta(sUrl, sJson, sToken);
}


CConsumirServicioRest::~CConsumirServicioRest(void)
{

}

CString CConsumirServicioRest::ObtenerUltimaRespuesta( )
{
    sRespuesta.Trim();
    return sRespuesta;
}

void CConsumirServicioRest::obtenerRespuesta( CString sUrl, CString sJson, CString sToken )
{
    bool bRespuesta = true ;
    _bstr_t bsData ="<empty>";
    char sMensaje[350]= {0};
    CString* sData = NULL;
	int iRetorno = 0;
	bool bRetorno = false;
    
	_bstr_t sConsulta= sUrl;
	_bstr_t sTokenAutentificacion = sToken;
	_bstr_t sJsonArgs = sJson;

    try {		 

        CoInitialize(NULL);        
        RESTREB::IRestREbPtr rest;    
        rest.CreateInstance(__uuidof( RESTREB::REbRest));
        bsData = rest->Post_2(sConsulta, sJsonArgs, sTokenAutentificacion);        
        CoUninitialize();

		sData = new CString(bsData.GetBSTR());
		
		sRespuesta = sData->GetString();
        delete sData;
    }
    catch(...)
    {
		iRetorno = sprintf_s(sMensaje, sizeof(sMensaje), "%s", "ERROR CConsumirServicioRest::obtenerRespuesta: url [%s], json [%s]", sUrl, sJson);
		if( iRetorno >= 0 )
		{
			bRetorno = true;
		}         
    }
}
