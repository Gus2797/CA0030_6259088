// Consulta original solicitada:...
//  SELECT fechaventa,fechaactivacion,fechavencimiento,tipocobertura,placas, numerodeserie, modelo, x.tipovehiculo, tipouso, primaneta, udi, excedente, derechodepoliza, primaantesdeiva, primatotal, primanetaanual, excedenteanual,derechopolizaanual, primaantesdeivaanual, primatotalanual, x.fechaalta, udidespuesdeiva, excedentedespuesdeiva, derechodepolizadespuesdeiva, udianual, udidespuesdeivaanual, excedentedespuesdeivaanual, derechodepolizadespuesdeivaanual,claveamis, danosaterceros, gastosmedicosauto, gastosmedicoscamioneta, asistencialegal, gastosdeasistencialegal,marca,submarca, v.descripcionmarca, w.descripcionlinea FROM (SELECT fechaventa,fechaactivacion,fechavencimiento,a.tipocobertura,placas AS placas, numerodeserie, modelo, a.tipovehiculo, tipouso, primaneta, udi, excedente, derechodepoliza, primaantesdeiva, primatotal, primanetaanual, excedenteanual,derechopolizaanual, primaantesdeivaanual, primatotalanual, fechaalta, udidespuesdeiva, excedentedespuesdeiva, derechodepolizadespuesdeiva, udianual, udidespuesdeivaanual, excedentedespuesdeivaanual, derechodepolizadespuesdeivaanual,claveamis,marca,submarca FROM crsegurosauto AS A inner join crcostosautoseguro as B ON a.tipocobertura = b.tiposeguro AND a.tipovehiculo = b.tipovehiculo  AND a.ciudad = b.ciudad WHERE a.cliente = 102342 AND a.poliza = 6 AND fechaalta <= '20120416' ORDER by fechaalta DESC limit 1) AS X inner  join crtiposeguro as y ON x.tipocobertura = y.tiposeguro INNER JOIN crmarcasvehiculo AS V ON v.clavemarca = x.marca INNER JOIN crlineasvehiculo AS W ON w.clavelinea = x.submarca WHERE y.fechaalta <= '20120416' ORDER by fechaalta DESC limit 1;
    
#ifndef COBTENERDATOSSEGUROAUTO
#define COBTENERDATOSSEGUROAUTO
#include "stdafx.h"
#include <RecordSet.hpp>
class CObtenerDatosSeguroAuto : public CRecordSet 
{
public:
    CObtenerDatosSeguroAuto(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerDatosSeguroAuto();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[39];
    int nCTipo[39];
    long nLongitud[39];
    long nLongResp[39];
    void *pVar[39];
    
    SqlTimeStamp        fechaventa;
    SqlTimeStamp        fechaactivacion;
    SqlTimeStamp        fechavencimiento;
    short int           tipocobertura;
    char                placas[12];
    char                numerodeserie[22];
    short int           modelo;
    short int           tipovehiculo;
    short int           tipouso;
    long                primaneta;
    long                udi;
    long                excedente;
    long                derechodepoliza;
    long                primaantesdeiva;
    long                primatotal;
    long                primanetaanual;
    long                excedenteanual;
    long                derechopolizaanual;
    long                primaantesdeivaanual;
    long                primatotalanual;
    SqlTimeStamp        fechaalta;
    long                udidespuesdeiva;
    long                excedentedespuesdeiva;
    long                derechodepolizadespuesdeiva;
    long                udianual;
    long                udidespuesdeivaanual;
    long                excedentedespuesdeivaanual;
    long                derechodepolizadespuesdeivaanual;
    char                claveamis[8];
    _int64              danosaterceros;
    _int64              gastosmedicosauto;
    _int64              gastosmedicoscamioneta;
    char                asistencialegal[17];
    short int           gastosdeasistencialegal;
    short int           marca;
    short int           submarca;
    char                descripcionmarca[22];
    char                descripcionlinea[32];
};
#endif COBTENERDATOSSEGUROAUTO
