#ifndef CCONSULTARSITUACIONCRCLIENTE
#define CCONSULTARSITUACIONCRCLIENTE
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarSituacionCrCliente : public CRecordSet 
{
public:
    CConsultarSituacionCrCliente(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarSituacionCrCliente();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[5];
    int nCTipo[5];
    long nLongitud[5];
    long nLongResp[5];
    void *pVar[5];
    
    long                cliente;
    char                situacionespecial[3];
    short int           causasitesp;
    char                puntualidad[3];
};
#endif CCONSULTARSITUACIONCRCLIENTE
