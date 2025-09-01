// Consulta original solicitada:...
//  SELECT des_mensaje FROM cat_mensajes WHERE idu_tipomensaje = 378
    
#ifndef CCONSULTARMENSAJESEGURO
#define CCONSULTARMENSAJESEGURO
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarMensajeSeguro : public CRecordSet 
{
public:
    CConsultarMensajeSeguro(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarMensajeSeguro();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];
    
    char                des_mensaje[1026];
};
#endif CCONSULTARMENSAJESEGURO
