// Consulta original solicitada:...
//  SELECT nombresucursal,domicilio,numempgerentecajas,fecha,clientemaximo,ciudad,nombreciudad,telefono, TRIM(substring(domiciliocompleto FROM 1 for 200)) AS domiciliocompleto,substring(expedicion FROM 1 for 44) AS expedicion FROM gndominio
    
#ifndef CCONSULTARDATOSGNDOMINIO4
#define CCONSULTARDATOSGNDOMINIO4
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarDatosGnDominio4 : public CRecordSet 
{
public:
    CConsultarDatosGnDominio4(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarDatosGnDominio4();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[11];
    int nCTipo[11];
    long nLongitud[11];
    long nLongResp[11];
    void *pVar[11];
    
    char                nombresucursal[22];
    char                domicilio[22];
    long                numempgerentecajas;
    SqlTimeStamp        fecha;
    long                clientemaximo;
    short int           ciudad;
    char                nombreciudad[22];
    char                telefono[12];
    char                domiciliocompleto[202];
    char                expedicion[52];
};
#endif CCONSULTARDATOSGNDOMINIO4
