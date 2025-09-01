// Consulta original solicitada:...
//  select catMod.idu_modulopolizaclub, catMsg.idu_mensajepolizaclub,catMsg.desc_mensaje from cat_modulospolizaclub catMod inner join cat_mensajespolizaclub catMsg on catMod.idu_modulopolizaclub = catMsg.idu_modulopolizaclub WHERE catMod.idu_modulopolizaclub in(1,2,3)
    
#ifndef CCONSULTARDESCRIPCIONCLUB
#define CCONSULTARDESCRIPCIONCLUB
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarDescripcionClub : public CRecordSet 
{
public:
    CConsultarDescripcionClub(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarDescripcionClub();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[4];
    int nCTipo[4];
    long nLongitud[4];
    long nLongResp[4];
    void *pVar[4];
    
    short int           idu_modulopolizaclub;
    long                idu_mensajepolizaclub;
    char                desc_mensaje[2001];
};
#endif CCONSULTARDESCRIPCIONCLUB
