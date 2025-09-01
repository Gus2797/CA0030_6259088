// Consulta original solicitada:...
//  update mov_mensajes_sms set num_colaborador = 97258377 where fol_seguro = 33705
    
#ifndef CACTUALIZAREMPLEADOMOVSMS
#define CACTUALIZAREMPLEADOMOVSMS
#include "stdafx.h"
#include <RecordSet.hpp>
class CActualizarEmpleadoMovSMS : public CRecordSet 
{
public:
    CActualizarEmpleadoMovSMS(C_ODBC *odbc_ext, const char *select=NULL);
    ~CActualizarEmpleadoMovSMS();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[1];
    int nCTipo[1];
    long nLongitud[1];
    long nLongResp[1];
    void *pVar[1];
    
};
#endif CACTUALIZAREMPLEADOMOVSMS
