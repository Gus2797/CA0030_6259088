// Consulta original solicitada:...
//  SELECT 	TRIM(nombre1) AS nombre1, TRIM(apellidopaterno1) AS apellidopaterno1, TRIM(apellidomaterno1) AS apellidomaterno1, porcentaje1, parentesco1, telefono1, fechanacimiento1,TRIM(nombre2) AS nombre2, TRIM(apellidopaterno2) AS apellidopaterno2, TRIM(apellidomaterno2) AS apellidomaterno2, porcentaje2, parentesco2, telefono2, fechanacimiento2,TRIM(nombre3) As nombre3, TRIM(apellidopaterno3) As apellidopaterno3, TRIM(apellidomaterno3) AS apellidomaterno3, porcentaje3, parentesco3, telefono3, fechanacimiento3,TRIM(tiposeguro), folio FROM  fun_consultartdbeneficiarios(145028356,12504,'12','2016-02-16','','1');
    
#ifndef CCONSULTARBENEFICIARIO
#define CCONSULTARBENEFICIARIO
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarBeneficiario : public CRecordSet 
{
public:
    CConsultarBeneficiario(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarBeneficiario();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[24];
    int nCTipo[24];
    long nLongitud[24];
    long nLongResp[24];
    void *pVar[24];
    
    char                nombre1[17];
    char                apellidopaterno1[17];
    char                apellidomaterno1[17];
    short int           porcentaje1;
    short int           parentesco1;
    _int64              telefono1;
    SqlTimeStamp        fechanacimiento1;
    char                nombre2[17];
    char                apellidopaterno2[17];
    char                apellidomaterno2[17];
    short int           porcentaje2;
    short int           parentesco2;
    _int64              telefono2;
    SqlTimeStamp        fechanacimiento2;
    char                nombre3[17];
    char                apellidopaterno3[17];
    char                apellidomaterno3[17];
    short int           porcentaje3;
    short int           parentesco3;
    _int64              telefono3;
    SqlTimeStamp        fechanacimiento3;
    char                tiposeguro[3];
    long                folio;
};
#endif CCONSULTARBENEFICIARIO
