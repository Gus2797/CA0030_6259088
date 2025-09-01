#ifndef COBTENERDETALLEABONOROPA
#define COBTENERDETALLEABONOROPA
#include "stdafx.h"
#include <RecordSet.hpp>
class CObtenerDetalleAbonoRopa : public CRecordSet 
{
public:
    CObtenerDetalleAbonoRopa(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerDetalleAbonoRopa();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[7];
    int nCTipo[7];
    long nLongitud[7];
    long nLongResp[7];
    void *pVar[7];
    
    long			abonoRopa;
    long            abonoTasa0;
    long            abonoInteresRopa;
    long            abonoInteresTasa0;
	long			bonificacionRopa;
	long			bonificacionTasa0;
};
#endif COBTENERDETALLEABONOROPA
