// Consulta original solicitada:...
//  SELECT lprestamo, iidrechazo FROM fun_crcuentacandidatoprestamoctesn(309529298, '2016-11-11', '214', '14' )
    
#ifndef CCONSULTARCANDIDATOPRESTAMOCN
#define CCONSULTARCANDIDATOPRESTAMOCN
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarCandidatoPrestamoCN : public CRecordSet 
{
public:
    CConsultarCandidatoPrestamoCN(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarCandidatoPrestamoCN();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];
    
    long                lprestamo;
    short int           iidrechazo;
};
#endif CCONSULTARCANDIDATOPRESTAMOCN
