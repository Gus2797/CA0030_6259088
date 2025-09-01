// Consulta original solicitada:...
//  SELECT * FROM FUN_TDMENSAJEINVITACIONABONO('1', '1','1', '1', '0', '1', '20240106', '20340501', '100','15','30')
    
#ifndef COBTENERMENSAJEABONO
#define COBTENERMENSAJEABONO
#include "stdafx.h"
#include <RecordSet.hpp>
class cObtenerMensajeAbono : public CRecordSet 
{
public:
    cObtenerMensajeAbono(C_ODBC *odbc_ext, const char *select=NULL);
    ~cObtenerMensajeAbono();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[5];
    int nCTipo[5];
    long nLongitud[5];
    long nLongResp[5];
    void *pVar[5];
    
    char                msg1[512];
    char                msg2[512];
    char                msg3[512];
    char                msg4[512];
};
#endif COBTENERMENSAJEABONO
