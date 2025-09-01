#ifndef CCONSULTARGNVIGENCIAPROMOCION
#define CCONSULTARGNVIGENCIAPROMOCION
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarGnVigenciaPromocion : public CRecordSet 
{
public:
    CConsultarGnVigenciaPromocion(C_ODBC *odbc_ext,bool bFlagCommit = false, const char *select=NULL);
    ~CConsultarGnVigenciaPromocion();
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
	bool bFlagCommit;
    
    short int	campana;
    char		tipocampana[2];
    short int	prioridad;    
};
#endif CCONSULTARGNVIGENCIAPROMOCION
