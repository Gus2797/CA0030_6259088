#include "CContactabilidad.h"
CContactabilidad::CContactabilidad(CEntorno* entorno)
{
    char cLog[500] = { 0 };
    this->bEsActiva = false;
    this->entorno = entorno;
    try
    {
		if(sprintf_s(cLog, "FC0200805103820017 - entra - CContactabilidad - constructor") < 0){;}
        this->util.GrabarLog(cLog);
        this->EstablecerUrls();
        this->SetEsActiva();
    }
    catch (CExcepcion* error)
    {
        if (this->entorno != nullptr)
        {
            this->util.GrabarLog(entorno->GetJson());
        }
        else
        {
            this->util.GrabarLog("No se recibió el objeto de entorno (852c2de46da9)");
        }
        if (error != nullptr)
        {
            this->util.GrabarLog(error->GetTraza());
        }
        else
        {
            this->util.GrabarLog("No se recibió el objeto de error (fac495085ab3)");
        }
    }
    catch (...)
    {
        if (this->entorno != nullptr)
        {
            this->util.GrabarLog(entorno->GetJson());
        }
        else
        {
            this->util.GrabarLog("No se recibió el objeto de entorno(c909daac523f)");
        }
        this->util.GrabarLog("Se provocó un error desconocido en el constructor de contactabilidad");
    }
}

CContactabilidad::~CContactabilidad(void) {}

bool CContactabilidad::GetEsActiva()
{
    return this->bEsActiva;
}

void CContactabilidad::SetEsActiva()
{
    char cLog[500] = { 0 };
    CString sDefault = "void CContactabilidad::SetEsActiva()";
    bool esExitoso = false;
    int iContactaGeneralActiva = 0;
    int iContactaEspecificaActiva = 0;
    int iTiendaLocal = 0;
    bool bEstaFlagSuborigenesOn = false;
    char cMensaje[1024] = { 0 };

	if(sprintf_s(cLog, "FC0200805103820021 - entra - SetEsActiva") < 0){;}
    this->util.GrabarLog(cLog);

    try
    {
        esExitoso = consultarFlag(&odbc, cMensaje, '0', CContactabilidad::iscFlgModoLocal, iTiendaLocal);
        if (esExitoso)
        {
            esExitoso = consultarFlag(&odbc, cMensaje, '0',
                CContactabilidad::iscFlgContacta, iContactaGeneralActiva);
            if (esExitoso)
            {
                if (iContactaGeneralActiva == 1) {
                    bEstaFlagSuborigenesOn = ConsultarContactabilidadEspecifica(this->entorno->iSuborigen);
                    //this->bEsActiva = bEstaFlagSuborigenesOn && iTiendaLocal == 0;
					this->bEsActiva = bEstaFlagSuborigenesOn; //Se realizo modificcacion para activar la CONTACTABILIDAD
                }
            }
            else
            {
                //throw new CExcepcion("Falla en consulta del flag CContactabilidad::iscFlgContacta");
				this->util.GrabarLog("Falla en consulta del flag CContactabilidad::iscFlgContacta");
            }
        }
        else
        {
            //throw new CExcepcion("Falla en consulta de flag CContactabilidad::iscFlgModoLocal");
			this->util.GrabarLog("Falla en consulta de flag CContactabilidad::iscFlgModoLocal");
        }
    }
    catch (CExcepcion *exception)
    {
        //throw new CExcepcion(sDefault, exception);
		this->util.GrabarLog(sDefault);
    }
    catch (...)
    {
        sDefault.Append("|Error: 93411be23fac");
		this->util.GrabarLog(sDefault);
        //throw new CExcepcion(sDefault);
    }

	if(sprintf_s(cLog, "FC0200805103820019 - fin - SetEsActiva - bEsActiva=%s", bEsActiva ? "VERDADERO" : "FALSO") < 0){;}
    this->util.GrabarLog(cLog);
}

void CContactabilidad::EstablecerUrls(void)
{
    char cLog[500] = { 0 };
    CString sDefault = "void CContactabilidad::EstablecerUrls(void)";

	if(sprintf_s(cLog, "FC0200805103820014 - entra - EstablecerUrls") < 0){;}
    this->util.GrabarLog(cLog);

    try
    {
        CString sUrlTelefonos = this->GetUrlWebService(CContactabilidad::iscWebServiceTelefonos);
        this->urlsMetodos.SetTelefonoSolicitar(sUrlTelefonos);
    }
    catch (CExcepcion* ex)
    {
        //throw new CExcepcion(sDefault, ex);
		this->util.GrabarLog(sDefault);
    }
    catch (...)
    {
        sDefault.Append("|Error: 9af96e53665d");
        //throw new CExcepcion(sDefault);
		this->util.GrabarLog(sDefault);
    }
}

CString CContactabilidad::GetUrlWebService(int iTipo)
{
    char cLog[500] = { 0 };
    CString sDefault = "CString CContactabilidad::GetUrlWebService(int iTipo)";
    CString sUrl = "";
    int iRegistros = 0;
    char cQuery[256] = { 0 };

	if(sprintf_s(cLog, "FC0200805103820013 - entra - GetUrlWebService") < 0){;}
    this->util.GrabarLog(cLog);

    try
    {
		if(sprintf_s(cQuery, "select url,tipo,descripcion,keyx from fun_urlswebservice(%d::smallint);", iTipo) < 0){;}
        CUrlWebService urlWebService(&odbc, cQuery);

        while (urlWebService.leer())
        {
            iRegistros++;
        }

        if (iRegistros == 1)
        {
            sUrl.AppendFormat("%s", urlWebService.cUrl);
            sUrl.Trim();
            return sUrl;
        }
        else
        {
            sUrl.AppendFormat("No fue posible determinar la url tipo %d", iTipo);
            //throw new CExcepcion(sUrl);
			this->util.GrabarLog(sUrl);
        }
    }
    catch (CExcepcion* error)
    {
       //throw new CExcepcion(sDefault, error);
		this->util.GrabarLog(sDefault);
    }
    catch (...)
    {
        sDefault.Append("|Error:254e15d3b800");
        //throw new CExcepcion(sDefault);
		this->util.GrabarLog(sDefault);
    }
}

bool CContactabilidad::ConsultarContactabilidadEspecifica(int iSubOrigen)
{
    char cLog[500] = { 0 };
    CString sDefault = "bool CContactabilidad::ConsultarContactabilidadEspecifica(int iSubOrigen)";
    bool bRetorno = false;
    int iContactaEspecificaActiva = 0;
    CString sSql = "";

	if(sprintf_s(cLog, "FC0200805103820009 - entra - ConsultarContactabilidadEspecifica") < 0){;}
    this->util.GrabarLog(cLog);

    CMaximo ctlSuborigen(&odbc, false);
    sSql.Format("SELECT idu_status FROM FUN_CONSULTARCTLSUBORIGENES(%d::smallint);", iSubOrigen);
    try
    {
        if (ctlSuborigen.Exec(sSql))
        {
            bRetorno = true;
            ctlSuborigen.activarCols();
            if (ctlSuborigen.leer())
            {
                iContactaEspecificaActiva = ctlSuborigen.Total;
				 if(sprintf_s(cLog, "Se obtiene de manera correcta el suborigen de abonos: %i ", iContactaEspecificaActiva ) < 0){;}
				 this->util.GrabarLog(cLog);
            }
            else
            {
                iContactaEspecificaActiva = 0;
				if(sprintf_s(cLog, "El valor de suborigen de abonos es: %i ", iContactaEspecificaActiva ) < 0){;}
				this->util.GrabarLog(cLog);
            }
        }
        else
        {
            ctlSuborigen.odbc->GetLastError(ctlSuborigen.GetHstmt());
            sSql.Empty();
            sSql.Append(ctlSuborigen.odbc->m_szErrorMsg);
            //throw new CExcepcion(sSql);
			this->util.GrabarLog(sSql);
        }
        return iContactaEspecificaActiva >= 1;
    }
    catch (CExcepcion* error)
    {
        //throw new CExcepcion(sDefault, error);
		this->util.GrabarLog(sDefault);
    }
    catch (...)
    {
        sDefault.Append("|Error: 6e74b401a027");
        //throw new CExcepcion(sDefault);
		this->util.GrabarLog(sDefault);
    }
}

bool CContactabilidad::GetEsSolicitable()
{
    char cLog[500] = { 0 };
    CString sDefault = "void CContactabilidad::GetEsSolicitable()";
    int iResult = 0;
    CUT_HTTPClient clienteHttp;
    LPCSTR sLinea = "";
    long lLineas = 0;
    int i = 0;
    int iDatos = 0;
    CString sBody = "";
    char *cJson = nullptr;
    CString sHttpResp = "";
    int iSolicitable = 0;
    CString sLog = "";
    bool bRetorno = false;

	if(sprintf_s(cLog, "FC0200805103820007 - entra - GetEsSolicitable") < 0){;}
    this->util.GrabarLog(cLog);

    CString sUrlFull = this->urlsMetodos.GetTelefonoSolicitar(this->entorno->iSuborigen, this->entorno->lCliente, 0);
    try
    {
        clienteHttp.AddSendHeaderTag("Content-Type: application/json; charset=utf-8");
        iResult = clienteHttp.GET(sUrlFull.GetBuffer(sUrlFull.GetLength()));
        if (iResult == UTE_SUCCESS)
        {
            lLineas = clienteHttp.GetBodyLineCount();
            for (; i < lLineas; i++)
            {
                sLinea = clienteHttp.GetBodyLine(i);
                if (sLinea != NULL)
                {
                    sBody.AppendFormat("%s\r\n", sLinea);
                }
            }
            cJson = new char[sBody.GetLength() + 30];
			if(sprintf_s(cJson, sBody.GetLength() + 30, "{\"Datos\":%s}", sBody) < 0){;}
            JsonObject &root = jsonBuffer.parseObject(cJson);

            if (root.success())
            {
                JsonArray& listaDatos = root["Datos"];
                iDatos = listaDatos.size();
                for (i = 0; i < iDatos; i++)
                {
                    iSolicitable = listaDatos[i]["solicitar"];
                    if (iSolicitable >= 1)
                    {
                        sLog.AppendFormat("El cliente %ld tiene teléfonos por solicitar (25ac67708ab0) - solicitable",
                            this->entorno->lCliente);
                        this->util.GrabarLog(sLog);
                        bRetorno = true;
                        i = iDatos;
                    }
                }
                if (iSolicitable < 1)
                {
                    sLog.AppendFormat("El cliente %ld sin teléfonos por solicitar (1ef1bc5ef40d) - no solicitable",
                        this->entorno->lCliente);
                    this->util.GrabarLog(sLog);
                }
            }
            else
            {
                sDefault.AppendFormat("Valor no serializable (294745dfff75) | Respuesta: %s", sBody);
                //throw new CExcepcion("Valor no serializable (294745dfff75)");
				this->util.GrabarLog(sDefault);
            }
        }
        else
        {
            sHttpResp.AppendFormat("| HTTP-Status: %ld", CUT_ERR::GetErrorString(iResult));
            //throw new CExcepcion(sHttpResp);
			this->util.GrabarLog(sHttpResp);
        }
    }
    catch (CExcepcion* error)
    {
        sDefault.AppendFormat("| Url: %s | Error: %s", sUrlFull, error->GetTraza());
        this->util.GrabarLog(sDefault);
    }
    catch (...)
    {
        sDefault.Append("|Error: 8e028e26a260");
        this->util.GrabarLog(sDefault);
    }
    if (cJson != nullptr)
    {
        delete[]cJson;
    }
    return bRetorno;
}

void CContactabilidad::EjecutarAppCapturaValidacion()
{
    char cLog[500] = { 0 };
    int iFlag = 0;
    char cRespuesta1[1024] = { 0 };
    char cRespuesta2[1024] = { 0 };
    char cParametrosUWP[1024] = { 0 };
    char cParametrosCore[1024] = { 0 };
    CString sDllFlag = "";
    CString sDefault = "void CContactabilidad::EjecutarAppCapturaValidacion()";

	if(sprintf_s(cLog, "FC0200805103820011 - entra - EjecutarAppCapturaValidacion") < 0){;}
    this->util.GrabarLog(cLog);

    SParametros sParametrosUWP;
    try
    {
        SecureZeroMemory(&sParametrosUWP, sizeof(SParametros));
		if(sprintf_s(sParametrosUWP.cNombre, "capvaltelefonos") < 0){;}
        sParametrosUWP.iTienda = this->entorno->iTienda;
        sParametrosUWP.iCajaActual = this->entorno->iCaja;
		if(sprintf_s(sParametrosUWP.sArea, "C") < 0){;}
		if(sprintf_s(sParametrosUWP.sServer, "%s", this->entorno->sIpTienda) < 0){;}
        sParametrosUWP.iTipo = 0;
		if(sprintf_s(sParametrosUWP.sModo, "odbcoff") < 0){;}

		if(memcpy_s(cParametrosUWP, sizeof(cParametrosUWP), &sParametrosUWP, sizeof(SParametros)) < 0){;}
        if(sprintf_s(cParametrosCore,
            "tipoprocedimiento=capturavalidacion&idsuborigen=%d&estiloapp=2&numeroempleado=%ld&numerocliente=%ld&modo=commit",
			this->entorno->iSuborigen, this->entorno->lEmpleado, this->entorno->lCliente) < 0){;}
        this->util.GrabarLog("cargarDll->OPENUWP->tipo = 0");
        CargarDLL cargarDll("C:\\sys\\progx\\libcsharp\\OPENUWP.DLL", "OPENUWP",
            cParametrosUWP, cParametrosCore, cRespuesta1, cRespuesta2);
		 
        iFlag = cargarDll.getResultado();
        sDllFlag.AppendFormat("cargarDll()->iFlag %d, Respuesta de la UWP->%s, Respuesta del powershell+start->%s",
            iFlag, cRespuesta1, cRespuesta2);
        this->util.GrabarLog(sDllFlag);
        this->util.SendAltTab();
        this->util.GrabarLog("Finaliza envío de alt+tab");
    }
    catch (...)
    {
        sDefault.Append("|Error: 445b383c3579");
        this->util.GrabarLog(sDefault);
    }
}