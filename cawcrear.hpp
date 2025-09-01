/*==========================================================================
 * Fecha    :28/02/05 10:35 a.  ( dd-mm-aa )
 * Elabor¢  :Joel Armando Arana Garcia
 * Solicit¢ :Lic. José G. Mendoza
 * Actividad:Crea Tablas Temporales para el proyecto Captura de Abonos.
 * ==================================================================== */

#include <lmaxw.hpp>
#include "ctrlglob.hpp"


//tablas temporales base de datos tienda.0002

bool crearTablaTmpCaCarmovEtp( CGrabarTmpCaCarmovEtp2 &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para grabar al cliente ETP						 
	sConsulta.Format( "CREATE TEMPORARY TABLE tmpclienteetpcacarmov ( clave char(1) DEFAULT ' '::bpchar,tipomovimiento char(1) DEFAULT ' '::bpchar,  clavelocal char(1) DEFAULT ' '::bpchar,cliente int4 DEFAULT 0,tienda int2 DEFAULT 0,ciudad int2 DEFAULT 0,caja int2 DEFAULT 0,fecha date DEFAULT now(),importe int4 DEFAULT 0,recibo int4 DEFAULT 0,clienteetp int4 DEFAULT 0 ) WITHOUT OIDS; " );

	if(memcpy_z( cSqlTxt, strnlen(cSqlTxt, size_t(cSqlTxt)), sConsulta, 255 ) < 0){;}
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpclienteetpcacarmov" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}

bool crearTablaTmpCaEficienciaCajeras( CGrabarTmpCaEficienciaCajeras &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para grabar la eficiencia de cajeras

	sConsulta.Format( " CREATE TEMPORARY TABLE tmpcaeficienciacajeras (  tienda int2 DEFAULT 0,  fechaeficienciacajera date DEFAULT now(),  caja int2 DEFAULT 0,  recibo int4 DEFAULT 0,  cliente int4 DEFAULT 0,  empleado int4 DEFAULT 0,  cuentasconsaldo int4 DEFAULT 0,  cuentasconvencido int4 DEFAULT 0,  cuentasconvencidosinconvenio int4 DEFAULT 0,  cuentasconconvenio int4 DEFAULT 0 ) WITHOUT OIDS; " );

	if(memcpy_s( cSqlTxt, strnlen(cSqlTxt, size_t(cSqlTxt)), sConsulta, 255 ) < 0){;}
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpcaeficienciacajeras" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}
/*
bool crearTablaAbonoTmpCaCarmov( CGrabarAbonoTmpCaCarmov &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para grabar los abonos.

	sConsulta.Format( "CREATE TEMPORARY TABLE tmpabonocacarmov ( clave char(1) DEFAULT ' '::bpchar, cliente int4 DEFAULT 0, tienda int2 DEFAULT 0, ciudad int2 DEFAULT 0,  caja int2 DEFAULT 0,  ejercicio char(1) DEFAULT ' '::bpchar,  factura int4 DEFAULT 0,  fecha date DEFAULT timenow(),  recibo int4 DEFAULT 0,  vencidoinicial int4 DEFAULT 0, minimoinicial int4 DEFAULT 0,  efectuo int4 DEFAULT 0,  tipomovimiento char(1) DEFAULT ' '::bpchar, importe int4 DEFAULT 0,  saldocuenta int4 DEFAULT 0,  saldoinicial int4 DEFAULT 0, saldofinal int4 DEFAULT 0,  base int4 DEFAULT 0,  edad int2 DEFAULT 0,  fechasaldacon date DEFAULT timenow(), importesaldacon int4 DEFAULT 0,  clientelocalizar char(1) DEFAULT ' '::bpchar,  tiposeguro char(1) DEFAULT ' '::bpchar ) WITHOUT OIDS; " );

	memcpy( cSqlTxt, sConsulta, 255 );
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpabonocacarmov" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}
*/
bool crearTablaTmpCaMovimientos( CGrabarTmpCaMovimientos &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para grabar los abonos.

	sConsulta.Format( "CREATE TEMPORARY TABLE tmpcamovimientos(  cliente int4 DEFAULT 0,  fechaconvenio date DEFAULT now(),  plazoconvenio int2 DEFAULT 0,  vencido int4 DEFAULT 0,  saldofinal int4 DEFAULT 0,  fechacompra date DEFAULT now(),  caja int2 DEFAULT 0,  empleado int4 DEFAULT 0 ) WITHOUT OIDS; " );

	if(memcpy_s( cSqlTxt, strnlen(cSqlTxt, size_t(cSqlTxt), sConsulta, 255 ) < 0){;}
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpcamovimientos" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}

/*bool crearTablaTmpAbonoInteresCaCarmov( CGrabarTmpAbonoInteresCaCarmov &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para grabar los abonos a interes en el cacarmov
	sConsulta.Format( " CREATE TEMPORARY TABLE tmpabonointerescacarmov(  clave char(1) DEFAULT ' '::bpchar,  tipomovimiento char(1) DEFAULT ' '::bpchar,  tienda int2 DEFAULT 0,  ciudad int2 DEFAULT 0,  cliente int4 DEFAULT 0,  caja int2 DEFAULT 0,  recibo int4 DEFAULT 0,  factura int4 DEFAULT 0,  importe int4 DEFAULT 0,  saldoinicial int4 DEFAULT 0,  saldofinal int4 DEFAULT 0,  saldocuenta int4 DEFAULT 0,  clientelocalizar char(1) DEFAULT ' '::bpchar,  flagmovtosupervisor char(1) DEFAULT ' '::bpchar,  clavelocal char(1) DEFAULT ' '::bpchar,  vencidoinicial int4 DEFAULT 0,  minimoinicial int4 DEFAULT 0,  anexo char(1) DEFAULT ' '::bpchar,  ejercicio char(1) DEFAULT ' '::bpchar,  fecha date DEFAULT timenow(),  efectuo int4 DEFAULT 0,  tiposeguro char(1) DEFAULT ' '::bpchar,edad int2 DEFAULT 0 ) WITHOUT OIDS; " );

	memcpy( cSqlTxt, sConsulta, 255 );
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpabonointerescacarmov" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}
*/
/*
bool crearTablaTmpConvenioCaCarmov( CGrabarTmpConvenioCaCarmov &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para grabar los convenios en el cacarmov

	sConsulta.Format( " CREATE TEMPORARY TABLE tmpconveniocacarmov (  clave char(1) DEFAULT ' '::bpchar,  tipomovimiento char(1) DEFAULT ' '::bpchar,  cliente int4 DEFAULT 0,  tienda int2 DEFAULT 0,  ciudad int2 DEFAULT 0,  caja int2 DEFAULT 0,  factura int4 DEFAULT 0,  ejercicio char(1) DEFAULT ' '::bpchar,  fecha date DEFAULT timenow(),  recibo int4 DEFAULT 0,  vencidoinicial int4 DEFAULT 0,  minimoinicial int4 DEFAULT 0,  anexo char(1) DEFAULT ' '::bpchar,  efectuo int4 DEFAULT 0,  clavelocal char(1) DEFAULT ' '::bpchar,  saldoinicial int4 DEFAULT 0,  saldofinal int4 DEFAULT 0,  saldocuenta int4 DEFAULT 0,  flagmovtosupervisor char(1) DEFAULT ' '::bpchar,  plazoconvenio int2 DEFAULT 0,  importe int4 DEFAULT 0,  tipoconvenio char(1) DEFAULT ' '::bpchar,subtipoconvenio char(1) DEFAULT ' '::bpchar, clientelocalizar char(1) DEFAULT ' '::bpchar,tiposeguro char(1) DEFAULT ' '::bpchar ) WITHOUT OIDS; " );

	memcpy( cSqlTxt, sConsulta, 255 );
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpconveniocacarmov" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}
*/
/*
bool crearTablaTmpBonificacionCaCarmov( CGrabarTmpBonificacionCaCarmov &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para grabar la bonificacion en el cacarmov


	
	sConsulta.Format( " CREATE TEMPORARY TABLE tmpbonificacioncacarmov(  clave char(1) DEFAULT ' '::bpchar,  tipomovimiento char(1) DEFAULT ' '::bpchar,  importe int4 DEFAULT 0,  clientelocalizar char(1) DEFAULT ' '::bpchar,  cliente int4 DEFAULT 0,  tienda int2 DEFAULT 0,  ciudad int2 DEFAULT 0,  caja int2 DEFAULT 0,  factura int4 DEFAULT 0,  recibo int4 DEFAULT 0,  ejercicio char(1) DEFAULT ' '::bpchar,  fecha date DEFAULT timenow(),  vencidoinicial int4 DEFAULT 0,  minimoinicial int4 DEFAULT 0,  anexo char(1) DEFAULT ' '::bpchar,  efectuo int4 DEFAULT 0,  clavelocal char(1) DEFAULT ' '::bpchar,  flagmovtosupervisor char(1) DEFAULT ' '::bpchar)WITHOUT OIDS; " );

	memcpy( cSqlTxt, sConsulta, 255 );
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpbonificacioncacarmov" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}
*/
/*bool crearTablaTmpBeneficiariosCaCarmov( CGrabarTmpBeneficiariosCaCarmov &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para grabar los beneficiarios en el cacarmov


	
	sConsulta.Format( " CREATE TEMPORARY TABLE tmpbeneficiarioscacarmov(  clave char(1) DEFAULT ' '::bpchar,  tipomovimiento char(1) DEFAULT ' '::bpchar,  cliente int4 DEFAULT 0,  importe int4 DEFAULT 0,  recibo int4 DEFAULT 0,  tienda int2 DEFAULT 0,  ciudad int2 DEFAULT 0,  caja int2 DEFAULT 0,  fecha date DEFAULT timenow(),  folio int4 DEFAULT 0,  efectuo int4 DEFAULT 0,  movtoseguro char(1) DEFAULT ' '::bpchar ) WITHOUT OIDS; " );
	memcpy( cSqlTxt, sConsulta, 255 );
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpbeneficiarioscacarmov" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}
*/
bool crearTablaTmpSeguroCaCarmov( CGrabarTmpSeguroCaCarmov01 &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para grabar los seguros en el cacarmov

	sConsulta.Format( " CREATE TEMPORARY TABLE tmpsegurocacarmov(  clave char(1) DEFAULT ' '::bpchar,  tipomovimiento char(1) DEFAULT ' '::bpchar,  clavelocal char(1) DEFAULT ' '::bpchar,  cliente int4 DEFAULT 0,  tienda int2 DEFAULT 0,  ciudad int2 DEFAULT 0,  tiposeguro char(1) DEFAULT ' '::bpchar,  caja int2 DEFAULT 0,  fechavencimiento date DEFAULT now(),  fechavencimientoanterior date DEFAULT now(),  cantidadsegurosanterior int2 DEFAULT 0,  fecha date DEFAULT now(),  efectuo int4 DEFAULT 0,  mesesvencidos int2 DEFAULT 0,  folio int4 DEFAULT 0,  importe int4 DEFAULT 0,  recibo int4 DEFAULT 0,  cantidadseguros int2 DEFAULT 0,  edad int2 DEFAULT 0,  sexo char(1) DEFAULT ' '::bpchar,  flagseguroconyugal char(1) DEFAULT ' '::bpchar,  bonificacion int4 DEFAULT 0,  clientelocalizar char(1) DEFAULT ' '::bpchar,  movtoseguro char(1) DEFAULT ' '::bpchar,  flagmontoseguro char(1) DEFAULT ' '::bpchar,fechanacimiento date DEFAULT now(),cantidadmeses int2 DEFAULT 0 ) WITHOUT OIDS; " );
	if(memcpy_s( cSqlTxt, strnlen(cSqlTxt, size_t(cSqlTxt)), sConsulta, 255 ) < 0){;}
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpsegurocacarmov" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}

//tablas temporales base de datos cartera	

//seguro
bool crearTablaTmpCrSeguros( CGrabarTmpCrSeguros &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para el seguro


	sConsulta.Format( " CREATE TEMPORARY TABLE tmpcrseguros(  cliente int4 DEFAULT 0,  folio int4 DEFAULT 0,  fechavencimiento date DEFAULT now(),  cvesinbeneficiarios int2 DEFAULT 0,cantidadseguros int2 DEFAULT 0) WITHOUT OIDS; " );
	if(memcpy_s( cSqlTxt, strnlen(cSqlTxt, size_t(cSqlTxt)), sConsulta, 255 ) < 0){;}
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpcrseguros" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}

//prestamo	
bool crearTablaTmpCrPrestamos( CGrabarTmpCrPrestamos &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para el prestamo

	sConsulta.Format( "CREATE TEMPORARY TABLE tmpcrprestamos(  cliente int4 DEFAULT 0,  tienda int2 DEFAULT 0,  factura int4 DEFAULT 0,  interesadicional int4 DEFAULT 0,  saldoactual int4 DEFAULT 0,  importeultimomovimiento int4 DEFAULT 0,  fechaultimomovimiento date DEFAULT now()) WITHOUT OIDS;" );
	if(memcpy_s( cSqlTxt, strnlen(cSqlTxt, size_t(cSqlTxt)), sConsulta, 255 ) < 0){;}
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpcrprestamos" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}
//ropa

bool crearTablaTmpCrCropa( CGrabarTmpCrCropa &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para  la cuenta de ropa


	sConsulta.Format( "CREATE TEMPORARY TABLE tmpcrcropa(  cliente int4 DEFAULT 0,  saldo int4 DEFAULT 0,  minimoapagar int4 DEFAULT 0,  interesadicional int4 DEFAULT 0,  fechaultimomovimiento date DEFAULT now(),flagactualizacion int2 DEFAULT 0 ) WITHOUT OIDS;" );
	if(memcpy_s( cSqlTxt, sizeof(sSqlTxt), sConsulta, 255 ) < 0){;}
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpcrcropa" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}
//muebles
bool crearTablaTmpCrCmuebles( CGrabarTmpCrCmuebles &TablaTemporal, char *cSqlTxt )
{
	CString  sConsulta;
	bool bContinua = true;

	//tabla temporal para  la cuenta de muebles

	sConsulta.Format( "CREATE TEMPORARY TABLE tmpcrcmuebles(  cliente int4 DEFAULT 0,  factura int4 DEFAULT 0,  saldo int4 DEFAULT 0,  interesadicional int4 DEFAULT 0,fechaultimomovimiento date DEFAULT now() ) WITHOUT OIDS;" );
	if(memcpy_s( cSqlTxt, strnlen(cSqlTxt, size_t(cSqlTxt)), sConsulta, 255 ) < 0){;}
	cSqlTxt[ 255 ] = 0;

	if( TablaTemporal.Exec( sConsulta ) )
	{
		TablaTemporal.activarCols();
		TablaTemporal.prepararInsert( "tmpcrcmuebles" );
		TablaTemporal.Commit();
	}
	else
	{
		TablaTemporal.odbc->GetLastError(TablaTemporal.GetHstmt());
		bContinua = false;
	}
	return  bContinua;
}
