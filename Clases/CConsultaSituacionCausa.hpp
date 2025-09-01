// Consulta original solicitada:...
//  SELECT idsituacion, clvsituacion, numcausasituacion from fun_traerrespuestaregla('2','1','3');  
    
#ifndef CCONSULTASITUACIONCAUSA
#define CCONSULTASITUACIONCAUSA
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultaSituacionCausa : public CRecordSet 
{
public:
    CConsultaSituacionCausa(C_ODBC *odbc_ext, bool bFlagCommit = true, const char *select=NULL);
    ~CConsultaSituacionCausa();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[4];
    int nCTipo[4];
    long nLongitud[4];
    long nLongResp[4];
    void *pVar[4];
	bool bFlagCommit;
    
    long                idsituacion;
    char                clvsituacion;
    char                nada001;                                              
    long                numcausasituacion;
};
#endif CCONSULTASITUACIONCAUSA
