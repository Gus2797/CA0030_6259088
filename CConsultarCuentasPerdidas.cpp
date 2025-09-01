#include "stdafx.h"
#include "DlgCapturarAbono.h"

#include "CMaximo.hpp"
#include "CSaldoMesAnterior.hpp"
#include "CSaldo20MesAnterior.hpp"
#include "CSaldoMesAnteriorPrestamo.hpp"
#include "CSaldoMesAnteriorBancoppel.hpp"

static bool obtenerCuentasPerdidas(C_ODBC *xOdbc, C_ODBC *xOdbc_4,long lCliente,CCuentaCliente *pCuentasCliente,int &iNumCtas, int iFlagGenera);
static bool anexoAutomatico(C_ODBC *xOdbc, C_ODBC *xOdbc_4, int iFlagGenera, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas);
static bool obtenerSalarioMinimo(C_ODBC *xOdbc_4, long &lSalarioMinimo, int iAnioActual);
static bool saldo20MesAnterior(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo);
static bool saldoMesAnterior(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo);
static bool saldoMesAnteriorPrestamo(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo);
static bool saldoMesAnteriorDeudaBancoppel(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo);
static bool saldoMesAnteriorTiempoAire(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo);
static bool saldoMesAnteriorRevolvente(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo);

static int obtenerTotalRegistrosMuebles(C_ODBC *xOdbc_4, long lCliente);
static int obtenerTotalRegistrosRopa(C_ODBC *xOdbc_4, long lCliente);
static int obtenerTotalRegistrosPrestamo(C_ODBC *xOdbc_4, long lCliente);
static int obtenerTotalRegistrosDeudaBancoppel(C_ODBC *xOdbc_4, long lCliente);
static int obtenerTotalRegistrosTiempoAire(C_ODBC *xOdbc_4, long lCliente);
static int obtenerTotalRegistrosRevolvente(C_ODBC *xOdbc_4, long lCliente);

//bool CDlgCapturarAbono::obtenerCuentasPerdidasCteZ()
//{
//	bool bConsulta = true;
//	char cIpCredito[20] = {0}, cIpCredito2[20] = {0}, cSql[255] = {0}, cArchivo[80] = {0};
//
//	sprintf(cArchivo,"c:\\sys\\mem\\Ctas.txt");
//									
//	if ( access(cArchivo,0)==0 )
//		unlink(cArchivo);	
//
//	bConsulta = consultarIpServidores( &odbc, cIpCredito, cIpCredito2, SERV_CTASPERDIDAS, cSql );
//
//	if( !bConsulta )
//	{
//		grabarMensajeError( "C", m_grid.iCaja, (LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "CDlgCapturarAbono", "obtenerIpPersonal", cSql,m_grid.lEmpleado,"ERROR EN LA CONSULTA(obteneripcredito)",&odbc,m_grid.iMuestraMsg);
//	}
//	else
//	{
//		if (abrirConexionBD(&odbcCuentasPerdidas, cIpCredito, cIpCredito2, CONECTA_CUENTASPERDIDAS, 0) == true )
//		{
//			//obtiene el total de cuentas de muebles
//			iNumCtas  = obtenerTotalRegistrosMuebles(&odbcCuentasPerdidas,m_grid.lCliente);
//            iNumCtas2 = obtenerTotalRegistrosPrestamo(&odbcCuentasPerdidas,m_grid.lCliente);
//			iNumCtas2 = iNumCtas2 + obtenerTotalRegistrosDeudaBancoppel(&odbcCuentasPerdidas,m_grid.lCliente);
//			iNumCtas2 = iNumCtas2 + obtenerTotalRegistrosTiempoAire(&odbcCuentasPerdidas,m_grid.lCliente);	
//			iNumCtas  = iNumCtas + 1 + iNumCtas2;
//			int iCantidadByte = sizeof(CCuentaCliente)*iNumCtas + 100;
//
//			CCuentaCliente *pCuentasCliente = NULL;
//
//			C_Mem memb( (long)iCantidadByte );
//			memset( memb.buffer,0,(unsigned int)iCantidadByte );               
//
//			pCuentasCliente = ( CCuentaCliente * )memb.buffer;
//
//			//obtener cuentas perdidas si el cliente es puntualidad Z
//			if( !obtenerCuentasPerdidas(&odbc, &odbcCuentasPerdidas, m_grid.lCliente, pCuentasCliente,iNumCtas,1) )
//			{
//				bConsulta = false;						
//				grabarMensajeError( "C", m_grid.iCaja,(LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "CDlgCapturarAbono", "obtenerCuentasPerdidasCteZ", (LPTSTR)(LPCTSTR)odbcCuentasPerdidas.LastErrStr(),m_grid.lEmpleado,"ERROR EN LA CONSULTA(CuentasPerdidas)",&odbc,m_grid.iMuestraMsg);
//			}
//
//			iFlagDespliegaDatosZ = 1;
//			
//			if ( desplegarDatosCliente(memb) == 0)
//			{
//				inicializar();
//				inicializarCaptura();
//			}
//			else
//			{
//				m_cliente.SetReadOnly( true );
//				m_grid.GotoCell(0,21);
//				iContador++;
//			}
//		}
//		else
//		{
//			AfxMessageBox( " Error al abrir conexión Cuentas Perdidas " );
//			bConsulta = false;
//			grabarMensajeError( "C", m_grid.iCaja,(LPTSTR)(LPCTSTR)m_grid.sServer, "CapturarAbono", "CDlgCapturarAbono", "obtenerCuentasPerdidasCteZ", " Error al abrir conexión Cuentas Perdidas ",m_grid.lEmpleado,"ERROR EN LA CONSULTA(CuentasPerdidas)",&odbc,m_grid.iMuestraMsg);
//		}
//	}
//	cerrarConexionBD(&odbcCuentasPerdidas);
//
//	return bConsulta;
//}

static bool obtenerCuentasPerdidas(C_ODBC *xOdbc, C_ODBC *xOdbc_4,long lCliente,CCuentaCliente *pCuentasCliente,int &iNumCtas, int iFlagGenera)
{
	long lTotal=0L,i=0,lFecha=0L, lSalarioMinimo=0;
	int  k=0;
	bool bConsulta = false;		
	bConsulta = anexoAutomatico(xOdbc, xOdbc_4, iFlagGenera, lCliente, pCuentasCliente, iNumCtas);		
	return bConsulta;
}

static bool anexoAutomatico(C_ODBC *xOdbc, C_ODBC *xOdbc_4, int iFlagGenera, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas)
{
	char cSql[255] = {0};

	long lSalarioMinimo = 0;
	int iAnioActual = 0;
	bool bRegresar = false;

	obtenerAnioGnDominio(xOdbc, iAnioActual, cSql );//
	
	if (iFlagGenera == 1)
	{
		if ( obtenerSalarioMinimo(xOdbc_4, lSalarioMinimo, iAnioActual) )
		{
			if ( saldo20MesAnterior(xOdbc_4, lCliente, pCuentasCliente, iNumCtas, lSalarioMinimo) )
			{
				if ( saldoMesAnterior(xOdbc_4, lCliente, pCuentasCliente, iNumCtas, lSalarioMinimo) )
				{
					if (saldoMesAnteriorPrestamo(xOdbc_4, lCliente, pCuentasCliente, iNumCtas, lSalarioMinimo) )
					{
						if ( saldoMesAnteriorDeudaBancoppel(xOdbc_4, lCliente, pCuentasCliente, iNumCtas, lSalarioMinimo) )
						{
							if ( saldoMesAnteriorTiempoAire(xOdbc_4, lCliente, pCuentasCliente, iNumCtas, lSalarioMinimo) )
							{
								if ( saldoMesAnteriorRevolvente(xOdbc_4, lCliente, pCuentasCliente, iNumCtas, lSalarioMinimo) )
								{
									bRegresar = true;
								}
							}
						}
					}
				}
			}
		}
	}
	return bRegresar;
}

static bool obtenerSalarioMinimo(C_ODBC *xOdbc_4, long &lSalarioMinimo, int iAnioActual)
{
	bool bResultado = false;
	CString sSql,sFechaActual;

	sFechaActual.Format("%04d-01-01",iAnioActual);

	sSql.Format("select salariozonac from catsalariosminimos where fechasalario='%s'",sFechaActual);

    CMaximo salarioMinimo(xOdbc_4);

	if( salarioMinimo.Exec(sSql) )
	{
		salarioMinimo.activarCols();
		if (salarioMinimo.Leer())
		{
			lSalarioMinimo = salarioMinimo.Total;
			bResultado = true;
		}
	}
	else
	{
		salarioMinimo.odbc->GetLastError( salarioMinimo.GetHstmt() );
	}

	return bResultado;
}

static bool saldo20MesAnterior(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo)
{
	CString sSql,sDato,sFecha,sDiaVta,sMesVta,sAnioVta,sFechaUltimoMov,sFechaConvenio;
	char cDia[3]={0},cMes[3]={0},cAnio[5]={0},cFecha[12]={0};
	long lRegistro=0,lSaldo=0,lSaldoTotal=0, iFlagRopa = 0;
	double dSalario = 0, dTemp = 0, dSaldoTotal = 0;
	int iDia,iMes,iAnio;
	bool bResultado = true;

	iNumCtas = 0;

	SecureZeroMemory(cFecha, sizeof(cFecha));
	
	iFlagRopa = obtenerTotalRegistrosRopa(xOdbc_4, lCliente);

	if (iFlagRopa > 0)
	{
		sSql.Format("Select numerocliente, saldoalafecha, interesadicionalmesactual, bonificacionmes1, bonificacionmes2, "
					"bonificacionmes3, bonificacionmes4, bonificacionmes5, fechabonificacionmes1, fechabonificacionmes2, "
					"fechabonificacionmes3, fechabonificacionmes4, fechabonificacionmes5,abonobase, minimoapagar, fechaconvenio, "
					"plazoconvenio, importeconvenio, efectuoconvenio, fechaultimomovimiento, interessobrecompra,fechaultimacompra, "
					"abonosdelmes, tipoconvenio, subtipoconvenio, comprasdelmes, saldoal20mesanterior, interesadicionalmesanterior "
					"from  crctasperdidasropa where numerocliente = %ld",lCliente);

		CSaldo20MesAnterior saldoCtasPerdidasRopa(xOdbc_4);

		if(saldoCtasPerdidasRopa.Exec( sSql ))
		{
			saldoCtasPerdidasRopa.activarCols();				
			while (saldoCtasPerdidasRopa.Leer())
			{
				if (saldoCtasPerdidasRopa.saldoal20mesanterior > 0)
				{
					(pCuentasCliente+iNumCtas)->iTipoDeCuenta = 0;
					sDato.Format("%04d%02d%02d",saldoCtasPerdidasRopa.fechaultimomovimiento.ano(),saldoCtasPerdidasRopa.fechaultimomovimiento.mes(), saldoCtasPerdidasRopa.fechaultimomovimiento.dia());
					if(sprintf_s(cFecha, sizeof(cFecha), "%s",sDato) < 0){;}
					cFecha[10]=0;
					if(memcpy_s(cDia, sizeof(cDia), &cFecha[6],2) < 0){;}
					cDia[2]=0;
					if(memcpy_s(cMes, sizeof(cMes), &cFecha[4],2) < 0){;}
					cMes[2]=0;
					if(memcpy_s(cAnio, sizeof(cAnio), &cFecha[0],4) < 0){;}
					cAnio[4]=0;
					sDiaVta.Format("%s",cDia);
					sMesVta.Format("%s",cMes);
					sAnioVta.Format("%s",cAnio);
					iDia = strtol(sDiaVta, NULL, 10);
					iMes = strtol(sMesVta, NULL, 10);
					iAnio = strtol(sAnioVta, NULL, 10);

				    if ( iDia > 0 && iDia <= 31)
					{
						iDia = saldoCtasPerdidasRopa.fechaultimomovimiento.dia();
					}
					else
					{
						iDia = 20;
					}

					(pCuentasCliente+iNumCtas)->tFechaUltimoMovimiento.ponerFecha(iDia, iMes, iAnio);
					
					(pCuentasCliente+iNumCtas)->lFactura = 999999L;
					(pCuentasCliente+iNumCtas)->cClaveSeguro = 'P';

					dTemp = saldoCtasPerdidasRopa.saldoal20mesanterior;
					dSalario = dTemp/10000;
					dSaldoTotal = (dSalario * lSalarioMinimo) + 0.5;
					sDato.Format("%6.2f",dSaldoTotal);

					lSaldoTotal = strtod(sDato, NULL);

					(pCuentasCliente+iNumCtas)->lSaldo = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lVencido = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lMinimo = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lSaldaCon = lSaldoTotal;
					
					iNumCtas++;
 
				}
				
			}		
		}
		else
		{
			bResultado = false;
			saldoCtasPerdidasRopa.odbc->GetLastError( saldoCtasPerdidasRopa.GetHstmt() );
		}
	}
	return bResultado;
}

static bool saldoMesAnterior(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo)
{
	CString sSql,sDato,sFecha,sDiaVta,sMesVta,sAnioVta,sFechaUltimoMov,sFechaConvenio;
	char cDia[3]={0},cMes[3]={0},cAnio[5]={0},cFecha[12]={0};
	long lRegistro=0,lSaldo=0,lSaldoTotal=0;
	double dSalario = 0, dTemp = 0, dSaldoTotal = 0;
	int iDia,iMes,iAnio, iFlagMuebles = 0;
	bool bResultado = true;

	SecureZeroMemory(cFecha, sizeof(cFecha));

	iFlagMuebles = obtenerTotalRegistrosMuebles(xOdbc_4, lCliente);


	if (iFlagMuebles > 0)
	{
		sSql.Format("Select numerocliente, numerotienda, numerofactura, fechaventa, importeventa, plazoventa, "
					"interessobrecompra, abonomensual, enganche,descripcionarticulo, interesadicional, saldoalafecha, "
					"fechaultimomovimiento, fechaconvenio, importeconvenio, plazoconvenio, efectuoconvenio,abonosdelmes, "
					"numeroarticulos, tipoconvenio, subtipoconvenio, saldomesanterior, interesadicionalmesanterior "
					"from crctasperdidasmuebles where numerocliente = %ld",lCliente);

		CSaldoMesAnterior saldoCtasPerdidasMuebles(xOdbc_4);

		
		if(saldoCtasPerdidasMuebles.Exec( sSql ))
		{
			saldoCtasPerdidasMuebles.activarCols();	
		
			while (saldoCtasPerdidasMuebles.Leer())
			{
				lSaldoTotal = 0;
				dTemp = 0;
				dSalario = 0;
				dSaldoTotal = 0;
				
				if (saldoCtasPerdidasMuebles.saldomesanterior > 0)
				{
					(pCuentasCliente+iNumCtas)->iTipoDeCuenta = 1;
                    (pCuentasCliente+iNumCtas)->cClaveLocal = ' ';
                    (pCuentasCliente+iNumCtas)->cStatus = ' ';
                    (pCuentasCliente+iNumCtas)->iTiendaDondeCompro = saldoCtasPerdidasMuebles.numerotienda/*.tienda_compro_cte*/;
                    (pCuentasCliente+iNumCtas)->lFactura = saldoCtasPerdidasMuebles.numerofactura;
                    (pCuentasCliente+iNumCtas)->lImporteDeVenta /*importe_de_la_compra*/ = saldoCtasPerdidasMuebles.importeventa + saldoCtasPerdidasMuebles.interessobrecompra;
					(pCuentasCliente+iNumCtas)->cClaveSeguro /*flag_seguro_conyugal*/ = 'P';
					sDato.Format("%04d%02d%02d",saldoCtasPerdidasMuebles.fechaventa.ano(),saldoCtasPerdidasMuebles.fechaventa.mes(), saldoCtasPerdidasMuebles.fechaventa.dia());
					if(sprintf_s(cFecha, sizeof(cFecha), "%s",sDato) < 0){;}
					cFecha[10]=0;
					if(memcpy_s(cDia, sizeof(cDia), &cFecha[6],2) < 0){;}
					cDia[2]=0;
					if(memcpy_s(cMes, sizeof(cMes), &cFecha[4],2) < 0){;}
					cMes[2]=0;
					if(memcpy_s(cAnio, sizeof(cAnio), &cFecha[0],4) < 0){;}
					cAnio[4]=0;
					sDiaVta.Format("%s",cDia);
					sMesVta.Format("%s",cMes);
					sAnioVta.Format("%s",cAnio);
					iDia = strtol(sDiaVta, NULL, 10);
					iMes = strtol(sMesVta, NULL, 10);
					iAnio = strtol(sAnioVta, NULL, 10);

					(pCuentasCliente+iNumCtas)->tFechaVenta.ponerFecha(iDia, iMes, iAnio);

					sDato.Format("%04d%02d%02d",saldoCtasPerdidasMuebles.fechaultimomovimiento.ano(),saldoCtasPerdidasMuebles.fechaultimomovimiento.mes(), saldoCtasPerdidasMuebles.fechaultimomovimiento.dia());
					if(sprintf_s(cFecha, sizeof(cFecha), "%s", sDato) < 0{;}
					cFecha[10]=0;
					if(memcpy_s(cDia, sizeof(cDia), &cFecha[6],2) < 0){;}
					cDia[2]=0;
					if(memcpy_s(cMes, sizeof(cMes), &cFecha[4],2) < 0){;}
					cMes[2]=0;
					if(memcpy_s(cAnio, sizeof(cMes), &cFecha[0],4) < 0){;}
					cAnio[4]=0;
					sDiaVta.Format("%s",cDia);
					sMesVta.Format("%s",cMes);
					sAnioVta.Format("%s",cAnio);
					iDia = strtol(sDiaVta, NULL, 10);
					iMes = strtol(sMesVta, NULL, 10);
					iAnio = strtol(sAnioVta, NULL, 10);
                  	(pCuentasCliente+iNumCtas)->tFechaUltimoMovimiento.ponerFecha(iDia, iMes, iAnio);
					                    
					dTemp = saldoCtasPerdidasMuebles.saldomesanterior;
					
					dSalario = dTemp/10000;

					dSaldoTotal = (dSalario * lSalarioMinimo) + 0.5;
					
					sDato.Format("%6.2f",dSaldoTotal);

					lSaldoTotal = strtod(sDato, NULL);

					if(sprintf_s((pCuentasCliente+iNumCtas)->sDescripcion, sizeof(CCuentaCliente), "%s",saldoCtasPerdidasMuebles.descripcionarticulo) < 0){;}
					(pCuentasCliente+iNumCtas)->sDescripcion[10] = 0;
					(pCuentasCliente+iNumCtas)->lSaldo = lSaldoTotal;
                    (pCuentasCliente+iNumCtas)->lVencido = lSaldoTotal;
                    (pCuentasCliente+iNumCtas)->lMinimo = lSaldoTotal;
                    (pCuentasCliente+iNumCtas)->lSaldaCon = lSaldoTotal;
                    (pCuentasCliente+iNumCtas)->lBonificacion = 0L;
                    iNumCtas++;

				}

			}

			
		}
		else
		{
			saldoCtasPerdidasMuebles.odbc->GetLastError( saldoCtasPerdidasMuebles.GetHstmt() );
			bResultado = false;
		}
	}
	return bResultado;
}

static bool saldoMesAnteriorPrestamo(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo)//Andres
{
	CString sSql,sDato,sFecha,sDiaVta,sMesVta,sAnioVta,sFechaUltimoMov,sFechaConvenio;
	char cDia[2]={0},cMes[2]={0},cAnio[5]={0},cFecha[12]={0};
	long lRegistro=0,lSaldo=0,lSaldoTotal=0, iFlagPrestamo = 0;
	double dSalario = 0, dTemp = 0, dSaldoTotal = 0;
	int iDia,iMes,iAnio;
	bool bResultado = true;

	memset(cFecha,' ',sizeof(cFecha));
	
	iFlagPrestamo = obtenerTotalRegistrosPrestamo(xOdbc_4, lCliente);

	if (iFlagPrestamo > 0)
	{		  
           sSql.Format("SELECT  numerocliente,numerofactura,numerotienda,fechaprestamo,importeprestamo,"
					   "interesfinanciamiento,comision,plazo,abonomensual,saldoprestamoanterior,"
					   "saldomesanterior,saldoalafecha,interesadicional,abonosdelmes,prestamosdelmes,"
					   "ajustes,tipoultimomovimiento,fechaultimomovimiento,importeultimomovimiento,fechadelconvenio,"
					   "tipodeconvenio,subtipodeconvenio,plazodelconvenio,importedelconvenio,vecesrealizoconvenio,efectuoconvenio,"
					   "interesadicionalmes,fechacuentasperdidas FROM crctasperdidasprestamos where numerocliente = %ld",lCliente);

		CSaldoMesAnteriorPrestamo saldoCtasPerdidasPrestamo(xOdbc_4);

		if(saldoCtasPerdidasPrestamo.Exec( sSql ))
		{
			saldoCtasPerdidasPrestamo.activarCols();				
			while (saldoCtasPerdidasPrestamo.Leer())
			{
				if (saldoCtasPerdidasPrestamo.saldomesanterior > 0)
				{
					(pCuentasCliente+iNumCtas)->iTipoDeCuenta = 3;
					(pCuentasCliente+iNumCtas)->iTiendaDondeCompro = saldoCtasPerdidasPrestamo.numerotienda;
					sDato.Format("%04d%02d%02d",saldoCtasPerdidasPrestamo.fechaultimomovimiento.ano(),saldoCtasPerdidasPrestamo.fechaultimomovimiento.mes(), saldoCtasPerdidasPrestamo.fechaultimomovimiento.dia());
					if(sprintf_s(cFecha, sizeof(cFecha), "%s",sDato) < 0){;}
					cFecha[10]=0;
					memcpy(cDia,&cFecha[6],2);
					cDia[2]=0;
					memcpy(cMes,&cFecha[4],2);
					cMes[2]=0;
					memcpy(cAnio,&cFecha[0],4);
					cAnio[4]=0;
					sDiaVta.Format("%s",cDia);
					sMesVta.Format("%s",cMes);
					sAnioVta.Format("%s",cAnio);
					iDia = atoi(sDiaVta);
					iMes = atoi(sMesVta);
					iAnio = atoi(sAnioVta);

					sprintf( (pCuentasCliente+iNumCtas)->sDescripcion,"PRESTAMO" );

				    if ( iDia > 0 && iDia <= 31)
					{
						iDia = saldoCtasPerdidasPrestamo.fechaultimomovimiento.dia();
					}
					else
					{
						iDia = 20;
					}

					(pCuentasCliente+iNumCtas)->tFechaUltimoMovimiento.ponerFecha(iDia, iMes, iAnio);					
					(pCuentasCliente+iNumCtas)->lFactura = saldoCtasPerdidasPrestamo.numerofactura;
					(pCuentasCliente+iNumCtas)->cClaveSeguro = 'P';

					dTemp = saldoCtasPerdidasPrestamo.saldomesanterior;
					dSalario = dTemp/10000;
					dSaldoTotal = (dSalario * lSalarioMinimo) + 0.5;
					sDato.Format("%6.2f",dSaldoTotal);

					lSaldoTotal = atof(sDato);

					(pCuentasCliente+iNumCtas)->lSaldo = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lVencido = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lMinimo = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lSaldaCon = lSaldoTotal;
					
					iNumCtas++;
 
				}
				
			}
			
		}
		else
		{
			saldoCtasPerdidasPrestamo.odbc->GetLastError( saldoCtasPerdidasPrestamo.GetHstmt() );
			bResultado = false;
		}
	}
	return bResultado;
}

static bool saldoMesAnteriorDeudaBancoppel(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo)
{
	CString sSql,sDato,sFecha,sDiaVta,sMesVta,sAnioVta,sFechaUltimoMov,sFechaConvenio;
	char cDia[2]={0},cMes[2]={0},cAnio[5]={0},cFecha[12]={0};
	long lRegistro=0,lSaldo=0,lSaldoTotal=0, iFlagPrestamo = 0;
	double dSalario = 0, dTemp = 0, dSaldoTotal = 0;
	int iDia,iMes,iAnio;
	bool bResultado = true;

	memset(cFecha,' ',sizeof(cFecha));
	
	iFlagPrestamo = obtenerTotalRegistrosDeudaBancoppel(xOdbc_4, lCliente);

	if (iFlagPrestamo > 0)
	{		  
           sSql.Format("SELECT  numerocliente,A.numerofactura,numerotienda,fechaprestamo,importeprestamo,"
					   "interesfinanciamiento,comision,plazo,abonomensual,saldoprestamoanterior,"
					   "saldomesanterior,saldoalafecha,interesadicional,abonosdelmes,prestamosdelmes,"
					   "ajustes,tipoultimomovimiento,fechaultimomovimiento,importeultimomovimiento,fechadelconvenio,"
					   "tipodeconvenio,subtipodeconvenio,plazodelconvenio,importedelconvenio,vecesrealizoconvenio,efectuoconvenio,"
					   "interesadicionalmes,fechacuentasperdidas, "
					   "COALESCE(tipoproducto,0) as tipoproducto,COALESCE(vistaentienda,'BANCOPPEL' ) as vistaentienda "
					   "FROM crctasperdidasdeudabancoppel AS A LEFT JOIN crcatalogotipoproductobanco AS B ON A.numerofactura = B.numerofactura "
					   "WHERE numerocliente = %ld",lCliente);

		CSaldoMesAnteriorBancoppel saldoCtasPerdidasBancoppel(xOdbc_4);

		if(saldoCtasPerdidasBancoppel.Exec( sSql ))
		{
			saldoCtasPerdidasBancoppel.activarCols();				
			while (saldoCtasPerdidasBancoppel.Leer())
			{
				if (saldoCtasPerdidasBancoppel.saldomesanterior > 0)
				{
					(pCuentasCliente+iNumCtas)->iTipoDeCuenta = 5;
					(pCuentasCliente+iNumCtas)->iTiendaDondeCompro = saldoCtasPerdidasBancoppel.numerotienda;
					sDato.Format("%04d%02d%02d",saldoCtasPerdidasBancoppel.fechaultimomovimiento.ano(),saldoCtasPerdidasBancoppel.fechaultimomovimiento.mes(), saldoCtasPerdidasBancoppel.fechaultimomovimiento.dia());
					if(sprintf_s(cFecha, sizeof(cFecha), "%s",sDato) < 0){;}
					cFecha[10]=0;
					memcpy(cDia,&cFecha[6],2);
					cDia[2]=0;
					memcpy(cMes,&cFecha[4],2);
					cMes[2]=0;
					memcpy(cAnio,&cFecha[0],4);
					cAnio[4]=0;
					sDiaVta.Format("%s",cDia);
					sMesVta.Format("%s",cMes);
					sAnioVta.Format("%s",cAnio);
					iDia = atoi(sDiaVta);
					iMes = atoi(sMesVta);
					iAnio = atoi(sAnioVta);

					//sprintf( (pCuentasCliente+iNumCtas)->sDescripcion,saldoCtasPerdidasBancoppel.vistaentienda );
					memcpy((pCuentasCliente+iNumCtas)->sDescripcion,saldoCtasPerdidasBancoppel.vistaentienda,11);

				    if ( iDia > 0 && iDia <= 31)
					{
						iDia = saldoCtasPerdidasBancoppel.fechaultimomovimiento.dia();
					}
					else
					{
						iDia = 20;
					}

					(pCuentasCliente+iNumCtas)->tFechaUltimoMovimiento.ponerFecha(iDia, iMes, iAnio);					
					(pCuentasCliente+iNumCtas)->lFactura = saldoCtasPerdidasBancoppel.numerofactura;
					(pCuentasCliente+iNumCtas)->cClaveSeguro = 'P';

					dTemp = saldoCtasPerdidasBancoppel.saldomesanterior;
					dSalario = dTemp/10000;
					dSaldoTotal = (dSalario * lSalarioMinimo) + 0.5;
					sDato.Format("%6.2f",dSaldoTotal);

					lSaldoTotal = atof(sDato);

					(pCuentasCliente+iNumCtas)->lSaldo = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lVencido = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lMinimo = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lSaldaCon = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->iTipoProducto = saldoCtasPerdidasBancoppel.tipoproducto;
					
					iNumCtas++;
 
				}
				
			}
			
		}
		else
		{
			saldoCtasPerdidasBancoppel.odbc->GetLastError( saldoCtasPerdidasBancoppel.GetHstmt() );
			bResultado = false;
		}
	}
	return bResultado;
}

static bool saldoMesAnteriorTiempoAire(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo)
{
	CString sSql,sDato,sFecha,sDiaVta,sMesVta,sAnioVta,sFechaUltimoMov,sFechaConvenio;
	char cDia[2]={0},cMes[2]={0},cAnio[5]={0},cFecha[12]={0};
	long lRegistro=0,lSaldo=0,lSaldoTotal=0, iFlagRopa = 0;
	double dSalario = 0, dTemp = 0, dSaldoTotal = 0;
	int iDia,iMes,iAnio;
	bool bResultado = true;

	memset(cFecha,' ',sizeof(cFecha));
	
	iFlagRopa = obtenerTotalRegistrosTiempoAire(xOdbc_4, lCliente);

	if (iFlagRopa > 0)
	{
		sSql.Format("Select numerocliente, saldoalafecha, interesadicionalmesactual, bonificacionmes1, bonificacionmes2, "
					"bonificacionmes3, bonificacionmes4, bonificacionmes5, fechabonificacionmes1, fechabonificacionmes2, "
					"fechabonificacionmes3, fechabonificacionmes4, fechabonificacionmes5,abonobase, minimoapagar, fechaconvenio, "
					"plazoconvenio, importeconvenio, efectuoconvenio, fechaultimomovimiento, interessobrecompra,fechaultimacompra, "
					"abonosdelmes, tipoconvenio, subtipoconvenio, comprasdelmes, saldoal20mesanterior, interesadicionalmesanterior "
					"from  crctasperdidastaire where numerocliente = %ld",lCliente);

		CSaldo20MesAnterior saldoCtasPerdidasRopa(xOdbc_4);

		if(saldoCtasPerdidasRopa.Exec( sSql ))
		{
			saldoCtasPerdidasRopa.activarCols();				
			while (saldoCtasPerdidasRopa.Leer())
			{
				if (saldoCtasPerdidasRopa.saldoal20mesanterior > 0)
				{
					(pCuentasCliente+iNumCtas)->iTipoDeCuenta = 4;
					sDato.Format("%04d%02d%02d",saldoCtasPerdidasRopa.fechaultimomovimiento.ano(),saldoCtasPerdidasRopa.fechaultimomovimiento.mes(), saldoCtasPerdidasRopa.fechaultimomovimiento.dia());
					if(sprintf_s(cFecha, sizeof(cFecha), "%s",sDato) < 0){;}
					cFecha[10]=0;
					memcpy(cDia,&cFecha[6],2);
					cDia[2]=0;
					memcpy(cMes,&cFecha[4],2);
					cMes[2]=0;
					memcpy(cAnio,&cFecha[0],4);
					cAnio[4]=0;
					sDiaVta.Format("%s",cDia);
					sMesVta.Format("%s",cMes);
					sAnioVta.Format("%s",cAnio);
					iDia = atoi(sDiaVta);
					iMes = atoi(sMesVta);
					iAnio = atoi(sAnioVta);

				    if ( iDia > 0 && iDia <= 31)
					{
						iDia = saldoCtasPerdidasRopa.fechaultimomovimiento.dia();
					}
					else
					{
						iDia = 20;
					}

					(pCuentasCliente+iNumCtas)->tFechaUltimoMovimiento.ponerFecha(iDia, iMes, iAnio);
					
					(pCuentasCliente+iNumCtas)->lFactura = 999999L;
					(pCuentasCliente+iNumCtas)->cClaveSeguro = 'P';

					dTemp = saldoCtasPerdidasRopa.saldoal20mesanterior;
					dSalario = dTemp/10000;
					dSaldoTotal = (dSalario * lSalarioMinimo) + 0.5;
					sDato.Format("%6.2f",dSaldoTotal);

					lSaldoTotal = atof(sDato);

					(pCuentasCliente+iNumCtas)->lSaldo = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lVencido = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lMinimo = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lSaldaCon = lSaldoTotal;
					
					iNumCtas++;
 
				}
				
			}		
		}
		else
		{
			saldoCtasPerdidasRopa.odbc->GetLastError( saldoCtasPerdidasRopa.GetHstmt() );
			bResultado = false;
		}
	}
	return bResultado;
}


static bool saldoMesAnteriorRevolvente(C_ODBC *xOdbc_4, long lCliente, CCuentaCliente *pCuentasCliente, int &iNumCtas, long lSalarioMinimo)
{

	CString sSql,sDato,sFecha,sDiaVta,sMesVta,sAnioVta,sFechaUltimoMov,sFechaConvenio;
	char cDia[2]={0},cMes[2]={0},cAnio[5]={0},cFecha[12]={0};
	long lRegistro=0,lSaldo=0,lSaldoTotal=0, iFlagRevolvente = 0;
	double dSalario = 0, dTemp = 0, dSaldoTotal = 0;
	int iDia,iMes,iAnio;
	bool bResultado = true;

	memset(cFecha,' ',sizeof(cFecha));
	
	iFlagRevolvente = obtenerTotalRegistrosRevolvente(xOdbc_4, lCliente);

	if (iFlagRevolvente > 0)
	{
		sSql.Format("SELECT num_cliente, imp_saldoalafecha, imp_interesadicionalmesactual, imp_bonificacionmes1, "
					"imp_bonificacionmes2, imp_bonificacionmes3, imp_bonificacionmes4, imp_bonificacionmes5, fec_bonificacionmes1, "
					"fec_bonificacionmes2, fec_bonificacionmes3, fec_bonificacionmes4, fec_bonificacionmes5, imp_abonobase, "
					"imp_minimoapagar, fec_convenio, num_plazoconvenio, imp_convenio, num_efectuoconvenio, fec_ultimomovimiento, "
					"imp_interessobrecompra, fec_ultimacompra, imp_abonosdelmes, clv_tipoconvenio, clv_subtipoconvenio, imp_comprasdelmes, "
					"imp_saldoal20mesanterior, imp_interesadicionalmesanterior "
					"FROM crctasperdidasrevolvente WHERE num_cliente = %ld",lCliente);

		CSaldo20MesAnterior saldoCtasPerdidasRevolvente(xOdbc_4);

		if(saldoCtasPerdidasRevolvente.Exec( sSql ))
		{
			saldoCtasPerdidasRevolvente.activarCols();				
			while (saldoCtasPerdidasRevolvente.Leer())
			{
				if (saldoCtasPerdidasRevolvente.saldoal20mesanterior > 0)
				{
					(pCuentasCliente+iNumCtas)->iTipoDeCuenta = 6;
					sDato.Format("%04d%02d%02d",saldoCtasPerdidasRevolvente.fechaultimomovimiento.ano(),saldoCtasPerdidasRevolvente.fechaultimomovimiento.mes(), saldoCtasPerdidasRevolvente.fechaultimomovimiento.dia());
					if(sprintf_s(cFecha, sizeof(cFecha), "%s",sDato) < 0){;}
					cFecha[10]=0;
					memcpy(cDia,&cFecha[6],2);
					cDia[2]=0;
					memcpy(cMes,&cFecha[4],2);
					cMes[2]=0;
					memcpy(cAnio,&cFecha[0],4);
					cAnio[4]=0;
					sDiaVta.Format("%s",cDia);
					sMesVta.Format("%s",cMes);
					sAnioVta.Format("%s",cAnio);
					iDia = atoi(sDiaVta);
					iMes = atoi(sMesVta);
					iAnio = atoi(sAnioVta);

				    if ( iDia > 0 && iDia <= 31)
					{
						iDia = saldoCtasPerdidasRevolvente.fechaultimomovimiento.dia();
					}
					else
					{
						iDia = 20;
					}

					(pCuentasCliente+iNumCtas)->tFechaUltimoMovimiento.ponerFecha(iDia, iMes, iAnio);
					
					(pCuentasCliente+iNumCtas)->lFactura = 999999L;
					(pCuentasCliente+iNumCtas)->cClaveSeguro = 'P';

					dTemp = saldoCtasPerdidasRevolvente.saldoal20mesanterior;
					dSalario = dTemp/10000;
					dSaldoTotal = (dSalario * lSalarioMinimo) + 0.5;
					sDato.Format("%6.2f",dSaldoTotal);

					lSaldoTotal = atof(sDato);

					(pCuentasCliente+iNumCtas)->lSaldo = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lVencido = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lMinimo = lSaldoTotal;
					(pCuentasCliente+iNumCtas)->lSaldaCon = lSaldoTotal;
					
					iNumCtas++;
 
				}
				
			}		
		}
		else
		{
			saldoCtasPerdidasRevolvente.odbc->GetLastError( saldoCtasPerdidasRevolvente.GetHstmt() );
			bResultado = false;
		}
	}
	return bResultado;
}


static int obtenerTotalRegistrosMuebles(C_ODBC *xOdbc_4, long lCliente)
{
	CString sSql;
	int iFlagMuebles = 0;

	sSql.Format("Select count(numerocliente) from  crctasperdidasmuebles where numerocliente = %ld",lCliente);

	CMaximo totalReg(xOdbc_4);

	if (totalReg.Exec(sSql))
	{
		totalReg.activarCols();
		if (totalReg.Leer())
		{
			iFlagMuebles = totalReg.Total;
		}
	}

	return iFlagMuebles;
}

static int obtenerTotalRegistrosRopa(C_ODBC *xOdbc_4, long lCliente)
{
	CString sSql;
	int iFlagRopa = 0;


	sSql.Format("Select count(numerocliente) from  crctasperdidasropa where numerocliente = %ld",lCliente);

	CMaximo totalReg(xOdbc_4);

	if (totalReg.Exec(sSql))
	{
		totalReg.activarCols();
		if (totalReg.Leer())
		{
			iFlagRopa = totalReg.Total;
		}
	}

	return iFlagRopa;
}

static int obtenerTotalRegistrosPrestamo(C_ODBC *xOdbc_4, long lCliente)
{
	CString sSql;
	int iFlagPrestamo = 0;

	sSql.Format("Select count(numerocliente) from  crctasperdidasprestamos where numerocliente = %ld",lCliente);

	CMaximo totalReg(xOdbc_4);

	if (totalReg.Exec(sSql))
	{
		totalReg.activarCols();
		if (totalReg.Leer())
		{
			iFlagPrestamo = totalReg.Total;
		}
	}

	return iFlagPrestamo;
}

static int obtenerTotalRegistrosDeudaBancoppel(C_ODBC *xOdbc_4, long lCliente)
{
	CString sSql;
	int iFlagPrestamo = 0;

	sSql.Format("Select count(numerocliente) from  crctasperdidasdeudabancoppel where numerocliente = %ld",lCliente);

	CMaximo totalReg(xOdbc_4);

	if (totalReg.Exec(sSql))
	{
		totalReg.activarCols();
		if (totalReg.Leer())
		{
			iFlagPrestamo = totalReg.Total;
		}
	}

	return iFlagPrestamo;
}


static int obtenerTotalRegistrosTiempoAire(C_ODBC *xOdbc_4, long lCliente)
{
	CString sSql;
	int iFlagPrestamo = 0;

	sSql.Format("Select count(numerocliente) from  crctasperdidastaire where numerocliente = %ld",lCliente);

	CMaximo totalReg(xOdbc_4);

	if (totalReg.Exec(sSql))
	{
		totalReg.activarCols();
		if (totalReg.Leer())
		{
			iFlagPrestamo = totalReg.Total;
		}
	}

	return iFlagPrestamo;
}
static int obtenerTotalRegistrosRevolvente(C_ODBC *xOdbc_4, long lCliente)
{
	CString sSql;
	int iFlagRevolvente = 0;

	sSql.Format("Select count(num_cliente) from  crctasperdidasrevolvente where num_cliente = %ld",lCliente);

	CMaximo totalReg(xOdbc_4);

	if (totalReg.Exec(sSql))
	{
		totalReg.activarCols();
		if (totalReg.Leer())
		{
			iFlagRevolvente = totalReg.Total;
		}
	}

	return iFlagRevolvente;
}