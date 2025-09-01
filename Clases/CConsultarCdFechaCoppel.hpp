#ifndef CCONSULTARCDFECHACOPPEL
#define CCONSULTARCDFECHACOPPEL
#include <RecordSet.HPP>
class CConsultarCdFechaCoppel : public CRecordSet 
{
public:
    CConsultarCdFechaCoppel(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarCdFechaCoppel();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[4];
    int nCTipo[4];
    long nLongitud[4];
    long nLongResp[4];
    void *pVar[4];
    
    short int           tienda;
    char                nombreciudad[22];
    SqlTimeStamp        fecha;
};
#endif CCONSULTARCDFECHACOPPEL
