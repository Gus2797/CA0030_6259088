#include "CSesion.h"
#include "json\src\json.h"
#import "C:\sys\progx\libcsharp\RESTREB.TLB"

CSesion::CSesion(CEntorno* entorno,  int idOrigenConfig,  int iduServicioConfig)
{
    this->entorno = entorno;
    this->idOrigenConfig = idOrigenConfig;
    this->iduServicioConfig = iduServicioConfig;    
    this->SetSesion();
}

CSesion::~CSesion(void)
{

}

CString CSesion::GetLastToken()
{
    sToken.Trim();
    return sToken;
}

void CSesion::ValidarYEstablecerRespuesta(CString sData)
{
    Json::Value root;
    Json::Reader reader;  
    CString sDefault = "Error en -> CSesion::ValidarRespuesta()";  
    std::string sInJson = sData;
    bool bParsedSuccess = reader.parse(sInJson, root, false);
    int iREstado = root["StatusCode"].asInt();    
    if(bParsedSuccess)
    {
        if(iREstado==1)
        {            
            sToken = root["Data"].asCString();
        }
        else if(iREstado==-1)
        {
            sDefault = root["Stack"].asCString();            
            throw sDefault;
        }
        else
        {
            sDefault = "El valor Estado en la respuesta no es reconocido";
            throw sDefault;
        }
    }
    else
    {
        sDefault = "Error: No pudo procesarse la respuesta json de RestREb";
        throw sDefault;
    }
}
void CSesion::SetSesion()
{
	int iRetorno = 0;
	bool bRetorno = false;
    bool bRespuesta = true ;
    _bstr_t bsData ="<empty>";
    char sMensaje[350]= {0};
    CString* sData = NULL;
    CTokenSSO* tokenSSO = new CTokenSSO();
    tokenSSO->iTienda = this->entorno->iTienda;
    tokenSSO->iCaja = this->entorno->iCaja;
    tokenSSO->iIduOrigen = this->idOrigenConfig;
    tokenSSO->iIduServicio = this->iduServicioConfig;
    tokenSSO->iSistema = this->entorno->iSistema;
    tokenSSO->sIpTienda = this->entorno->sIpTienda;
    try{

        bsData = tokenSSO->GetJson().AllocSysString();

        CoInitialize(NULL);        
        RESTREB::IMetodosTiendaPtr rest;    
        rest.CreateInstance(__uuidof( RESTREB::TiendaMetodos));       
        bsData = rest->TokenSSO(bsData);        
        CoUninitialize();

        sData = new CString(bsData.GetBSTR());
        
        ValidarYEstablecerRespuesta(sData->GetString());
		delete tokenSSO;  //Vulenrabilidad Memory Leak
		delete sData;  //Vulenrabilidad Memory Leak
    }
    catch(...)
    {		
        iRetorno = sprintf_s(sMensaje, "Se provoco una falla en CSesion->SetSesion()");
		if(iRetorno >=0){
			bRetorno = true;
		}
		else
		{
        	AfxMessageBox("Ha ocurrido un error al consumir TOKEN.");
		}
    }
}