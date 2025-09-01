#ifndef CINSERTARHORAMENSAJE
#define CINSERTARHORAMENSAJE
#include "stdafx.h"
#include <RecordSet.HPP>
class CInsertarHoraMensaje : public CRecordSet 
{
public:
    CInsertarHoraMensaje(C_ODBC *odbc_ext, const char *select=NULL);
    ~CInsertarHoraMensaje();
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
    
    short int           caja;
    short int           hora;
    short int           minuto;
	short int			  tiempomensaje;
};
#endif CINSERTARHORAMENSAJE
