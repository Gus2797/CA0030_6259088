#ifndef CONSULTARMESANIO
#define CONSULTARMESANIO
#include "stdafx.h"
#include <RecordSet.HPP>
class ConsultarMesAnio : public CRecordSet 
{
public:
    ConsultarMesAnio(C_ODBC *odbc_ext, const char *select=NULL);
    ~ConsultarMesAnio();
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


    long           anio;
    long           mes;

};
#endif CONSULTARMESANIO