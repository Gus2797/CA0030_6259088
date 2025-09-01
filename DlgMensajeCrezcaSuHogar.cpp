// DlgMensajeCrezcaSuHogar.cpp : implementation file
//

#include "stdafx.h"
#include "CapturarAbono.h"
#include "DlgMensajeCrezcaSuHogar.h"
#include ".\dlgmensajecrezcasuhogar.h"
#include "CMaximo.hpp"
#include "syscapturarabono.h"
#include "CSocketx.hpp"
// CDlgMensajeCrezcaSuHogar dialog

IMPLEMENT_DYNAMIC(CDlgMensajeCrezcaSuHogar, CDialog)
CDlgMensajeCrezcaSuHogar::CDlgMensajeCrezcaSuHogar(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMensajeCrezcaSuHogar::IDD, pParent)
{
	SecureZeroMemory(cNombre,20);
	SecureZeroMemory(cApellidoPaterno,20);
	SecureZeroMemory(cApellidoMaterno,20);
}

CDlgMensajeCrezcaSuHogar::~CDlgMensajeCrezcaSuHogar()
{
	lValorProyectoCH = 0;
	lMensualidadCH = 0;
	lEngancheCH = 0;
	lTotalPagarCH = 0;
	iFinLinea = 0;
	iTipoImpresora = 0;
	lCliente = 0;
	iAnioActual = 0;
	iMesActual = 0;
	iDiaActual = 0;
	iTienda = 0;
	iCajaActual = 0;
	lEmpleado = 0;
	iMuestraMsg = 0;
	iSistema = 0;
}

void CDlgMensajeCrezcaSuHogar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MENSAJECREZCASUHOGAR, m_mensajeCrezcasuHogar);
}


BEGIN_MESSAGE_MAP(CDlgMensajeCrezcaSuHogar, CDialog)
END_MESSAGE_MAP()


// CDlgMensajeCrezcaSuHogar message handlers

BOOL CDlgMensajeCrezcaSuHogar::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString sTexto;

	// TODO:  Add extra initialization here

	char cValorProyectoCH[10]={0},cMensualidadCH[10]={0},cEngancheCH[10]={0},cTotalPagarCH[10]={0};
		bAceptoInvitacion=false;
		usingx("###,###.##",cValorProyectoCH,(double)lValorProyectoCH);
		usingx("###,###.##",cMensualidadCH,(double)lMensualidadCH);
		usingx("###,###.##",cEngancheCH,(double)lEngancheCH);
		usingx("###,###.##",cTotalPagarCH,(double)lTotalPagarCH);

	sTexto.Format("Por ser Cliente cumplido, Coppel en conjunto con Crédito y Casa le "
				"ofrece el crédito Crezca Su Hogar con apoyo del Gobierno Federal " 
				"por la cantidad de $%s con 24 mensualidades de $%s y un pago inicial " 
				"de $%s. Su monto final a pagar es de $%s. Favor de pasar a Clientes Nuevos "
				"a realizar su trámite.",cValorProyectoCH,cMensualidadCH,cEngancheCH,cTotalPagarCH);

	m_mensajeCrezcasuHogar.SetWindowText (sTexto);

	crearMensaje( this,m_barra,m_mensaje );
	ponerMensaje( this,m_barra, m_mensaje, " [ ESC ] No Acepto   [ F1 ] Acepto [ F2 ] No es Titular" );


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgMensajeCrezcaSuHogar::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class	
	
	CString sDato;
	bool ShiftTab = false;
	

	if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
	{	
		switch ( pMsg->wParam )
		{
			case VK_F1:							
				Si_NoAcepto(SI_ACEPTO);
				CDialog::OnCancel();
				break;
			case VK_F2:					
				CDialog::OnCancel();
				break;
			case VK_ESCAPE:
				Si_NoAcepto(NO_ACEPTO);
				CDialog::OnCancel();
				pMsg->wParam=NULL;
				break;					
			default:
				break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
bool CDlgMensajeCrezcaSuHogar::Si_NoAcepto(int iSiNoAcepto)
{
	int iEnviados = 0;	
	char cFechaActual[9]={0};
	bool bResultado=false;
	CSocketx sKhistGrabaInv;
	S00018Recibe skRecibe;
	S00018Envia skEnvia;
	
	sKhistGrabaInv.bloqueante( true );
	sKhistGrabaInv.conectarNormal( cIpServidorCartera, 20506 );

	if ( sKhistGrabaInv.estaConectado() )
	{
		SecureZeroMemory( &skRecibe, sizeof( skRecibe ) );		
		if(sprintf_s(cFechaActual, sizeof(cFechaActual), "%04i%02i%02i",iAnioActual,iMesActual,iDiaActual) < 0){;}		
		if(sprintf_s(skRecibe.cFechaMovimiento, sizeof(skRecibe.cFechaMovimiento), cFechaActual) < 0){;}		
		if(sprintf_s(skRecibe.cIpCartera, sizeof(skRecibe.cIpCartera), cIpServidorCredito) < 0){;}
			if (iSiNoAcepto==SI_ACEPTO)
			{
				skRecibe.cStatus[0] = '7';
			}
			else if (iSiNoAcepto==NO_ACEPTO)
			{
				skRecibe.cStatus[0] = '8';
			}	
			skRecibe.cStatus[1]=0;
	
		skRecibe.iTienda=iTienda;
		skRecibe.iTipoMensaje=18;
		skRecibe.lCliente=lCliente;
		skRecibe.lValorSeguridad=4;

		iEnviados = sKhistGrabaInv.enviarDatos( &skRecibe, sizeof( S00018Recibe ) );
		
		if ( iEnviados == sizeof( S00018Recibe ) )
		{
			if ( sKhistGrabaInv.recibirDatos( &skEnvia, sizeof( S00018Envia ), 30 ) == sizeof( S00018Envia ) )
			{
				if ( skEnvia.iRespuesta == E00018_ACTUALIZO_OK )
				{						
					bResultado=true;

				}
				else if(skEnvia.iRespuesta == E00018_ERROR_CONSULTAR_MAESTRO)
				{
					grabarMensajeError( "C",iCajaActual, (LPTSTR)(LPCTSTR)cServer, "CapturarAbono", "CDlgMensajeCrezcaSuHogar", 
										"GuardarSiNoAceptoInvitacion","E00018_ERROR_CONSULTAR_MAESTRO",lEmpleado, "ERROR EN EL INET", &odbc, iMuestraMsg);
				}
				else if(skEnvia.iRespuesta ==E00018_ERROR_ACTUALIZAR_MAESTRO)
				{
					grabarMensajeError( "C",iCajaActual, (LPTSTR)(LPCTSTR)cServer, "CapturarAbono", "CDlgMensajeCrezcaSuHogar", 
									    "GuardarSiNoAceptoInvitacion","E00018_ERROR_ACTUALIZAR_MAESTRO",lEmpleado, "ERROR EN EL INET", &odbc, iMuestraMsg);
				}
				else if(skEnvia.iRespuesta ==E00018_ERROR_INSERTAR_MAESTRO)
				{
					grabarMensajeError( "C",iCajaActual, (LPTSTR)(LPCTSTR)cServer, "CapturarAbono", "CDlgMensajeCrezcaSuHogar", 
										"GuardarSiNoAceptoInvitacion","E00018_ERROR_INSERTAR_MAESTRO",lEmpleado, "ERROR EN EL INET", &odbc, iMuestraMsg);
				}
				else if(skEnvia.iRespuesta ==E00018_SIN_CONEXION_CARTERA)
				{
					grabarMensajeError( "C",iCajaActual, (LPTSTR)(LPCTSTR)cServer, "CapturarAbono", "CDlgMensajeCrezcaSuHogar", 
										"GuardarSiNoAceptoInvitacion","E00018_SIN_CONEXION_CARTERA",lEmpleado, "ERROR EN EL INET", &odbc, iMuestraMsg);
				}
				else if(skEnvia.iRespuesta ==E00018_ERROR_ENVIAR_DATOS)
				{
					grabarMensajeError( "C",iCajaActual, (LPTSTR)(LPCTSTR)cServer, "CapturarAbono", "CDlgMensajeCrezcaSuHogar", 
										"GuardarSiNoAceptoInvitacion","E00018_ERROR_ENVIAR_DATOS",lEmpleado, "ERROR EN EL INET", &odbc, iMuestraMsg);
				}
			}
			else
			{
				grabarMensajeError( "C",iCajaActual, (LPTSTR)(LPCTSTR)cServer, "CapturarAbono", "CDlgMensajeCrezcaSuHogar", 
							        "GuardarSiNoAceptoInvitacion","ERROR AL RECIBIR LOS DATOS DEL INET",lEmpleado, "ERROR EN EL INET", &odbc, iMuestraMsg);
			}	
		}
	
	}

	imprimirLeyenda();

	return bResultado;
}
	
bool CDlgMensajeCrezcaSuHogar::imprimirLeyenda()
{
	bool bRegresar=true;
	char cRuta[35]={0};

	if(sprintf_s(cRuta, sizeof(cRuta), "C:\\SYS\\MEM\\RECIBOCC.PRN") < 0){;}
	if ( access(cRuta,0)==0 )
	{
		unlink(cRuta);		
	}

	if( iSistema == 3 || iSistema == 7 )
	{
		impresionCajas(cRuta);
	}
	if( iSistema == 1 || iSistema == 2 )
	{
		impresionMueblesRopa(cRuta);
	}
	return bRegresar;
}

bool CDlgMensajeCrezcaSuHogar::impresionCajas(char *cRuta)
{
	bool bRegresar=true;
	char cCadena[MAX_BUFFER_XML]={0},
         cValorProyectoCH[10]={0},cMensualidadCH[10]={0},cEngancheCH[10]={0},cTotalPagarCH[10]={0},
	     cTextoOut[MAX_BUFFER_XML] = {0},cTextoOut1[MAX_BUFFER_XML] = {0},
		 cTextoOut2[MAX_BUFFER_XML] = {0},cTextoOut3[MAX_BUFFER_XML] = {0};

	usingx("###,###.##",cValorProyectoCH,(double)lValorProyectoCH);
	usingx("###,###.##",cMensualidadCH,(double)lMensualidadCH);
	usingx("###,###.##",cEngancheCH,(double)lEngancheCH);
	usingx("###,###.##",cTotalPagarCH,(double)lTotalPagarCH);

	C_FormasPCL hoja( 22,270,cRuta,iFinLinea,iTipoImpresora,1);
	hoja.poner( OCTAVOS,0,0 );
    hoja.poner( COMPACTAR,0,5 );

	SecureZeroMemory(cCadena, sizeof(cCadena));
	quitarBlancoNull(cValorProyectoCH,10);
	quitarBlancoNull(cMensualidadCH,10);
	quitarBlancoNull(cEngancheCH,10);
	quitarBlancoNull(cTotalPagarCH,10);
	quitarBlancoNull(cNombre,20);
	quitarBlancoNull(cApellidoPaterno,20);
	quitarBlancoNull(cApellidoMaterno,20);

	hoja.poner("INVITACION CREZCA SU HOGAR",2,0); 
	if(sprintf_s(cCadena, sizeof(cCadena), "CTE %ld %s %s %s",lCliente,cNombre,cApellidoPaterno,cApellidoMaterno) < 0){;}
	hoja.poner(cCadena,3,0);
	hoja.poner("POR SER CLIENTE CUMPLIDO, COPPEL EN CONJUNTO CON CREDITO Y CASA LE OFRECE EL CREDITO",4,0);
	hoja.poner("CREZCA SU HOGAR CON APOYO DEL GOBIERNO FEDERAL. EL VALOR PROYECTO ES POR LA CANTIDAD",5,0);
	SecureZeroMemory(cCadena, sizeof(cCadena));
	//DE $%s CON 24 MENSUALIDADES DE $%s Y UN PAGO INICIAL DE $%s EL CUAL 
	if(sprintf_s(cCadena, sizeof(cCadena), "%s $%s %s $%s %s $%s %s","DE",cValorProyectoCH,"CON 24 MENSUALIDADES DE",cMensualidadCH,"Y UN PAGO INICIAL DE",cEngancheCH,"EL CUAL") < 0){;}
	hoja.poner(cCadena,6,0);
	SecureZeroMemory(cCadena, sizeof(cCadena));
	if(sprintf_s(cCadena, sizeof(cCadena), "%s $%s. %s","SE DESCONTARA DE SU CREDITO. SU MONTO FINAL A PAGAR ES DE",cTotalPagarCH,"FAVOR DE PASAR A") < 0){;}
	hoja.poner(cCadena,7,0);
	hoja.poner("CLIENTES NUEVOS CON SU IDENTIFICACION OFICIAL.",8,0);

	hoja.poner("-FACIL, EN 15 MIN",10,0);
	hoja.poner("-PUEDE REALIZAR LA MEJORA EN LA CASA QUE HABITE.",11,0);
	hoja.poner("-CONFIRMANDO LA INVERSION EN SU VIVIENDA, PUEDE SOLICITAR OTRO CREDITO.",12,0);

	hoja.poner("LA CANTIDADES MENCIONADAS ESTAN SUJETAS A CAMBIOS SEGUN LOS MOVIMIENTOS POSTERIORES DE SU CUENTA.",14,0);

	hoja.imprimir();
	//copiar_archivo( cRuta,"LPT1" );
	impresionArchivo.imprimirArchivo(cRuta);

	return bRegresar;
}

bool CDlgMensajeCrezcaSuHogar::impresionMueblesRopa(char *cRuta)
{
	bool bRegresar=true;
	char cCadena[130]={0},
		 cValorProyectoCH[10]={0},cMensualidadCH[10]={0},cEngancheCH[10]={0},cTotalPagarCH[10]={0},
		 cTextoOut[MAX_BUFFER_XML] = {0}, cTextoOut1[MAX_BUFFER_XML] = {0};

	usingx("###,###.##",cValorProyectoCH,(double)lValorProyectoCH);
	usingx("###,###.##",cMensualidadCH,(double)lMensualidadCH);
	usingx("###,###.##",cEngancheCH,(double)lEngancheCH);
	usingx("###,###.##",cTotalPagarCH,(double)lTotalPagarCH);

	C_FormasPCL hoja( 33,270,cRuta,iFinLinea,iTipoImpresora,1 );

	SecureZeroMemory(cCadena, sizeof(cCadena));
	quitarBlancoNull(cValorProyectoCH,10);
	quitarBlancoNull(cMensualidadCH,10);
	quitarBlancoNull(cEngancheCH,10);
	quitarBlancoNull(cTotalPagarCH,10);
	quitarBlancoNull(cNombre,20);
	quitarBlancoNull(cApellidoPaterno,20);
	quitarBlancoNull(cApellidoMaterno,20);


	hoja.poner("INVITACION CREZCA SU HOGAR",1,0); 
	if(sprintf_s(cCadena, sizeof(cCadena),"CTE %ld %s %s %s",lCliente,cNombre,cApellidoPaterno,cApellidoMaterno) < 0){;}
	hoja.poner(cCadena,2,0);	
	hoja.poner("POR SER CLIENTE CUMPLIDO, COPPEL EN CONJUNTO CON CREDITO Y CASA",3,0);
	hoja.poner("LE OFRECE EL CREDITO CREZCA SU HOGAR CON APOYO DEL GOBIERNO",4,0);
	SecureZeroMemory(cCadena, sizeof(cCadena));
	if(sprintf_s(cCadena, sizeof(cCadena),"FEDERAL. EL VALOR PROYECTO ES POR LA CANTIDAD DE $%s",cValorProyectoCH) < 0){;}	
	hoja.poner(cCadena,5,0);
	SecureZeroMemory(cCadena, sizeof(cCadena));
	if(sprintf_s(cCadena, sizeof(cCadena),"24 MENSUALIDADES DE $%s Y UN PAGO INICIAL DE $%s",cMensualidadCH,cEngancheCH) < 0){;}		
	hoja.poner(cCadena,6,0);
	hoja.poner("EL CUAL SE DESCONTARA DE SU CREDITO. SU MONTO FINAL A PAGAR",7,0);
	SecureZeroMemory(cCadena, sizeof(cCadena));
	if(sprintf_s(cCadena, sizeof(cCadena),"ES DE $%s. FAVOR DE PASAR A CLIENTES NUEVOS CON SU",cTotalPagarCH) < 0){;}
	hoja.poner(cCadena,8,0);
	hoja.poner("IDENTIFICACION OFICIAL.",9,0);
	hoja.poner("-FACIL, EN 15 MIN.",11,0);
	hoja.poner("-PUEDE REALIZAR LA MEJORA EN LA CASA QUE HABITE.",12,0);
	hoja.poner("-CONFIRMANDO LA INVERSION EN SU VIVIENDA,",13,0);
	hoja.poner("PUEDE SOLICITAR OTRO CREDITO.",14,0);

	hoja.poner("LA CANTIDADES MENCIONADAS ESTAN SUJETAS A CAMBIOS SEGUN",16,0);
	hoja.poner("LOS MOVIMIENTOS POSTERIORES DE SU CUENTA.",17,0);

	hoja.imprimir();
	//copiar_archivo( cRuta,"LPT1" );
	impresionArchivo.imprimirArchivo(cRuta);

	return bRegresar;
}