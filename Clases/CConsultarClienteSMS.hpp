// Consulta original solicitada:...
//  Select cast( count (1) as smallint) as sumatoria  from mov_mensajes_sms where idu_cliente =  141821035 and ((fec_mensaje_envio_sms::date - '2019-05-27') < 90);
    
#ifndef CCONSULTARCLIENTESMS
#define CCONSULTARCLIENTESMS
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarClienteSMS : public CRecordSet 
{
public:
    CConsultarClienteSMS(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarClienteSMS();
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
    
    short int           sumatoria;
    char                nada001;                                              
};
#endif CCONSULTARCLIENTESMS
