// Consulta original solicitada:...
//  delete from mov_mensajes_sms where fol_seguro = 33738
    
#ifndef CCELIMINARMENSAJESMS
#define CCELIMINARMENSAJESMS
#include "stdafx.h"
#include <RecordSet.hpp>
class CCEliminarMensajeSMS : public CRecordSet 
{
public:
    CCEliminarMensajeSMS(C_ODBC *odbc_ext, const char *select=NULL);
    ~CCEliminarMensajeSMS();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[1];
    int nCTipo[1];
    long nLongitud[1];
    long nLongResp[1];
    void *pVar[1];
    
};
#endif CCELIMINARMENSAJESMS
