// Consulta original solicitada:...
//  SELECT nombresucursal,domicilio,numempgerentecajas,fecha,clientemaximo,ciudad,nombreciudad,telefono,permisogobernacion, salariominimo, TRIM(SUBSTRING(domiciliocompleto FROM 1 FOR 200)) AS domiciliocompleto, SUBSTRING(expedicion FROM 1 for 44) AS expedicion FROM gndominio
    
#ifndef CCONSULTARDATOSGNDOMINIO3
#define CCONSULTARDATOSGNDOMINIO3
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarDatosGnDominio3 : public CRecordSet 
{
public:
    CConsultarDatosGnDominio3(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarDatosGnDominio3();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[15];
    int nCTipo[15];
    long nLongitud[15];
    long nLongResp[15];
    void *pVar[15];
    
    char                nombresucursal[22];
    char                domicilio[22];
    long                numempgerentecajas;
    SqlTimeStamp        fecha;
    long                clientemaximo;
    short int           ciudad;
    char                nombreciudad[22];
    char                telefono[12];
    char                permisogobernacion[37];
    long                salariominimo;
    char                domiciliocompleto[202];
    char                expedicion[52];
	char                foliopoliza[22];
    char                fechavigencia[27];
};
#endif CCONSULTARDATOSGNDOMINIO3
