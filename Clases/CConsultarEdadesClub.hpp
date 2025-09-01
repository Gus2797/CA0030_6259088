// Consulta original solicitada:...
//  SELECT edadminima, edadmaxima FROM fun_obteneredadesseguro('1')
    
#ifndef CCONSULTAREDADESCLUB
#define CCONSULTAREDADESCLUB
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarEdadesClub : public CRecordSet 
{
public:
    CConsultarEdadesClub(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarEdadesClub();
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
    
    short int           edadminima;
    short int           edadmaxima;
	short int           edadmaximaabono;
};
#endif CCONSULTAREDADESCLUB
