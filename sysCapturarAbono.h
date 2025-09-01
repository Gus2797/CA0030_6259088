#pragma once

#include "flags.hpp"
#include "conecta.hpp"
#include "general.hpp"
#include "C_WFormas.hpp"

// Idenfificadores para CrezcaSuHogar
#define SI_ACEPTO      1
#define NO_ACEPTO      2

// Identificadores 
#define CLIENTE_PROMOTOR		39019292
#define CLIENTE_CFE				16452941

#define E00017_CONSULTO_OK_CTE				  0
#define E00017_CLIENTE_NO_EXISTE_EN_MAESTRO	  1
#define E00017_ERROR_CONSULTAR_MAESTRO		 -1
#define E00017_SIN_CONEXION_CARTERA			 -3
#define E00017_ERROR_ENVIAR_DATOS			 -4

#define E00018_ACTUALIZO_OK				      0
#define E00018_ERROR_CONSULTAR_MAESTRO	     -1
#define E00018_ERROR_ACTUALIZAR_MAESTRO		 -2
#define E00018_ERROR_INSERTAR_MAESTRO		 -3
#define E00018_SIN_CONEXION_CARTERA			 -4
#define E00018_ERROR_ENVIAR_DATOS			 -5

//Mensajes
#define TITULO_OPCION_REGISTRAR		1282
#define TITULO_OPCION_ACTUALIZAR	1299
#define OPCION_FINALIZAR_PL			1
#define MSG_BUSQUEDA_SIN_RESULTADOS_PL	1274
//subestatus PL
#define IDU_SUBESTATUS_BAJA			4

struct EstructuraCliente
{
    long lFolio;
    int iDiaNac;
    int iMesNac;
    int iAnioNac;
    int iDiaVenc;
    int iMesVenc;
    int iAnioVenc;
    int iVentaSeguroClub;
    int iCantidadMeses;
    int iFlagCapturaAbonos;
    char cSexo[3];
    char cNombreCompleto[50];
    int iMovimientoImpresion;
};

struct SCandidatoReestructura
{
    long lVencidoTotal;
    long lBaseTotal;
    long lSaldoTotal;
    long lSaldaConTotal;
    char cPuntualidad[3];
    char cSituacionEspecial[3];
    int iCiudad;
    long lInteresAdicional;
    char cSexo[3];
    int iCiudadCliente;
};

struct Parametros2
{

    int 	cliente;
    int		numTda;
    char	folioClub[10];
    int		folioPrestamo;
};

#ifdef MAIN

C_ODBC odbc;           //tienda.####
C_ODBC odbc_1;		   //cartera
C_ODBC odbcSolicitudes;
C_ODBC odbcCuentasPerdidas;
C_WFormas impresionArchivo;
SCandidatoReestructura candidatoReestructura;
#else

extern C_ODBC odbc;
extern C_ODBC odbc_1;
extern C_ODBC odbcSolicitudes;
extern C_ODBC odbcCuentasPerdidas;
extern C_WFormas impresionArchivo;
extern SCandidatoReestructura candidatoReestructura;
#endif

// Abrir Conexion -> if ( abrirConexionBD( &odbcTiendaNumero, cIpTiendaLocal, cIpTiendaLocal, CONECTA_TIENDANUMERO, iTienda ) )
// Cerrar Conexion -> cerrarConexionBD( &odbcTiendaNumero );

// Borrar del proyecto el #include "ctrlglob.hpp" de todos los fuentes y agregar este fuente a su proyecto.
// Borrar la carpeta que incluya las conexiones.
