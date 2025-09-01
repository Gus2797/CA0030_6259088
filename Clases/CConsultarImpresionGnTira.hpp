// Consulta original solicitada:...
//  SELECT documento FROM gntira LIMIT 1
    
#ifndef CCONSULTARIMPRESIONGNTIRA
#define CCONSULTARIMPRESIONGNTIRA
#include <RecordSet.hpp>
class CConsultarImpresionGnTira : public CRecordSet 
{
public:
    CConsultarImpresionGnTira(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarImpresionGnTira();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];
    
    char                documento[300000];
};
#endif CCONSULTARIMPRESIONGNTIRA
