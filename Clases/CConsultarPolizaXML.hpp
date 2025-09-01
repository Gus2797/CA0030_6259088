// Consulta original solicitada:...
//  SELECT substring(unnest(cast(xpath('/Movimientos/Movimiento/@NoPoliza', xml::xml) as text)::text[]),3,10) as resultado FROM ctlcrseguroauto c where c.poliza = 1800185345 
    
#ifndef CCONSULTARPOLIZAXML
#define CCONSULTARPOLIZAXML
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarPolizaXML : public CRecordSet 
{
public:
    CConsultarPolizaXML(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarPolizaXML();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];
    
    char                resultado[20001];
};
#endif CCONSULTARPOLIZAXML
