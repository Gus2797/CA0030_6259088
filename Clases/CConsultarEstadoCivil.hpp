#ifndef CCONSULTARESTADOCIVIL
#define CCONSULTARESTADOCIVIL
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarEstadoCivil : public CRecordSet 
{
public:
    CConsultarEstadoCivil(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarEstadoCivil();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];
    
    long                cliente;
    char                estadocivil[3];
};
#endif CCONSULTARESTADOCIVIL
