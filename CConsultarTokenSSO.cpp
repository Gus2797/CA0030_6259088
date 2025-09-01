#include "CConsultarTokenSSO.h"
#include "stdafx.h"
#include "CargaDllCSharp.h"
#include  <io.h>


CConsultarTokenSSO::CConsultarTokenSSO(){}	// Constructor estandar
CConsultarTokenSSO::~CConsultarTokenSSO(){} // destructor estandar

CString CConsultarTokenSSO::consultarTokenSSO(short iIdSistema, short iIdServicio, short iOpcion, CString sNombreServicio, char* cIPServidorTiendaNumero, short iTienda, short iCaja)
{
	CString sRespuesta ="";

	CString sRuta = "C:\\SYS\\PROGX\\GN\\GN0290.DLL", sClaseConstructor = "ObtenerTokenServicios.ObtenerToken", sAux="";
	CStringArray sArgsMetodo, sArgsConstructor;

	if(_access(sRuta, 0) == 0)
	{
		sAux.Format("%s",cIPServidorTiendaNumero);
		sArgsMetodo.Add(sAux);
		sAux.Format("%d",iTienda);
		sArgsMetodo.Add(sAux);
		sAux.Format("%d",iIdSistema);
		sArgsMetodo.Add(sAux);
		sAux.Format("%d",iCaja);
		sArgsMetodo.Add(sAux);
		sAux.Format("%d",iIdServicio);
		sArgsMetodo.Add(sAux);
		sAux.Format("%s",sNombreServicio);
		sArgsMetodo.Add(sAux);
		sAux.Format("%d",iOpcion);
		sArgsMetodo.Add(sAux);

		::CoInitialize(NULL);
		CCargaDllCSharp *objPuente = new CCargaDllCSharp();
		objPuente->CargarDllCSharp(sRuta,sClaseConstructor,METODO_STRING,"ObtenerTokenServicio",sArgsConstructor,sArgsMetodo);
		objPuente->getRespuesta(sRespuesta);
		delete objPuente;
		::CoUninitialize();
	}

	return sRespuesta;
}
