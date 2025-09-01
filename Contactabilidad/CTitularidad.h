#pragma once
#include "general.hpp"
class CTitularidad
{
public:
    long lKey;
    short iBiometrizadoCliente; // resultado del cliente
    short iBiometrizadoGerente; // resultado del gerente
    short iTipoCuestion;     // pregunta titular, adicional o ninguno
    short iAutenticacion;    // sms o ivr  
    int iNumAdicional;
    bool bEsControlada;
    CTitularidad(void)
    {
        CTime tFecha = CTime::GetCurrentTime();
        char cKey[30] = { 0 };
		if(sprintf_s(cKey, "%d%d%d%d", tFecha.GetDay(), tFecha.GetHour(), tFecha.GetMinute(), tFecha.GetSecond()) < 0){;}
        InicializarValores();
        lKey = strtol(cKey, NULL, 10);
		
		//Correccion por vulnerabilidad Use of Uninitialized Variable
		this->iAutenticacion = 0;
		this->iTipoCuestion = 0;
		this->iBiometrizadoCliente = 0;
		this->iNumAdicional = 0;
		this->iBiometrizadoGerente = 0;


    }
    ~CTitularidad(void) {}
    void InicializarValores()
    {
        this->lKey = 0;
        this->iBiometrizadoCliente = 0;
        this->iBiometrizadoGerente = 0;
        this->iTipoCuestion = 0;
        this->iAutenticacion = 0;
        this->iNumAdicional = 0;
        this->bEsControlada = false;
    }
    void GetJSON(char *cOutJson)
    {
        if(sprintf_s(cOutJson, 512, "{\"lKey\":%ld, \"iAutenticacion\":%d, \"iTipoCuestion\":%d, \"iBiometrizadoCliente\":%d,"
            " \"iNumAdicional\":%d, \"iBiometrizadoGerente\":%d}",
			lKey, iAutenticacion, iTipoCuestion, iBiometrizadoCliente, iNumAdicional, iBiometrizadoGerente) < 0){;}
    }
    bool SetJSON(char *cInJson)
    {
        bool bRetorno = false;
        StaticJsonBuffer<32767> jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(cInJson);
        if (root.success())
        {
            this->lKey = root["lKey"];
            this->iBiometrizadoCliente = root["iBiometrizadoCliente"];
            this->iBiometrizadoGerente = root["iBiometrizadoGerente"];
            this->iTipoCuestion = root["iTipoCuestion"];
            this->iAutenticacion = root["iAutenticacion"];
            this->iNumAdicional = root["iNumAdicional"];
            this->bEsControlada = this->lKey > 0;
            bRetorno = true;
        }
        return bRetorno;
    }
};

