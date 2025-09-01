// Consulta original solicitada:...
//  select cantidadseguros, fecnacadic FROM tmpcacarmovseguros
    
#ifndef CCONSULTARDATOSSEGUROADICIONAL
#define CCONSULTARDATOSSEGUROADICIONAL
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarDatosSeguroAdicional : public CRecordSet 
{
public:
    CConsultarDatosSeguroAdicional(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarDatosSeguroAdicional();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];
    
    short int           cantidadseguros;
    SqlTimeStamp        fecnacadic;
};
#endif CCONSULTARDATOSSEGUROADICIONAL
