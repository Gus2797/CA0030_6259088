#ifndef CCONSULTARCRSEGUROSCLUBADICIONAL
#define CCONSULTARCRSEGUROSCLUBADICIONAL
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarCrSegurosClubAdicional : public CRecordSet 
{
public:
    CConsultarCrSegurosClubAdicional(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarCrSegurosClubAdicional();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[9];
    int nCTipo[9];
    long nLongitud[9];
    long nLongResp[9];
    void *pVar[9];
    
    long                folio;
    short int           cantidadseguros;
    char                nombreadicional[17];
    char                apellidopaternoadic[17];
    char                apellidomaternoadic[17];
    SqlTimeStamp        fecnacadic;	
	short int           parentescoadic;
	SqlTimeStamp        fechavencimiento;	
};
#endif CCONSULTARCRSEGUROSCLUBADICIONAL