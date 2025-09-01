// Consulta original solicitada:...
//  SELECT folio, cliente,nombreasegurado,nombreconyuge,nombre1,apellidopaterno1,apellidomaterno1,porcentaje1,parentesco1,fechanacimiento1,telefono1, nombre2,apellidopaterno2,apellidomaterno2,porcentaje2,parentesco2,fechanacimiento2,telefono2, nombre3,apellidopaterno3,apellidomaterno3,porcentaje3,parentesco3,fechanacimiento3,telefono3, nombre4,apellidopaterno4,apellidomaterno4,porcentaje4,parentesco4,fechanacimiento4,telefono4  FROM fun_consultartdbeneficiarios(145028356,12504,'12','2016-02-16','','1');
    
#ifndef COBTENERDATOSTDBENEFICIARIOSCLUB
#define COBTENERDATOSTDBENEFICIARIOSCLUB
#include "stdafx.h"
#include <RecordSet.hpp>
class CObtenerDatosTdBeneficiariosClub : public CRecordSet 
{
public:
    CObtenerDatosTdBeneficiariosClub(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerDatosTdBeneficiariosClub();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[33];
    int nCTipo[33];
    long nLongitud[33];
    long nLongResp[33];
    void *pVar[33];
    
    long                folio;
    long                cliente;
    char                nombreasegurado[66];
    char                nombreconyuge[66];
    char                nombre1[32];
    char                apellidopaterno1[32];
    char                apellidomaterno1[32];
    short int           porcentaje1;
    short int           parentesco1;
    SqlTimeStamp        fechanacimiento1;
    _int64              telefono1;
    char                nombre2[32];
    char                apellidopaterno2[32];
    char                apellidomaterno2[32];
    short int           porcentaje2;
    short int           parentesco2;
    SqlTimeStamp        fechanacimiento2;
    _int64              telefono2;
    char                nombre3[32];
    char                apellidopaterno3[32];
    char                apellidomaterno3[32];
    short int           porcentaje3;
    short int           parentesco3;
    SqlTimeStamp        fechanacimiento3;
    _int64              telefono3;
    char                nombre4[32];
    char                apellidopaterno4[32];
    char                apellidomaterno4[32];
    short int           porcentaje4;
    short int           parentesco4;
    SqlTimeStamp        fechanacimiento4;
    _int64              telefono4;
};
#endif COBTENERDATOSTDBENEFICIARIOSCLUB
