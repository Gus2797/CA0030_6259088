#ifndef CCONSULTARCRSEGUROSCLUB
#define CCONSULTARCRSEGUROSCLUB
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarCrSegurosClub : public CRecordSet 
{
public:
    CConsultarCrSegurosClub(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarCrSegurosClub();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[7];
    int nCTipo[7];
    long nLongitud[7];
    long nLongResp[7];
    void *pVar[7];
    
    char                claveseguro[3];
    char                statusseguro[3];
    long                folio;
    char                tipocancelacion[3];
    char                clavenoofrecer[3];
    SqlTimeStamp        fechavencimiento;
};
#endif CCONSULTARCRSEGUROSCLUB
