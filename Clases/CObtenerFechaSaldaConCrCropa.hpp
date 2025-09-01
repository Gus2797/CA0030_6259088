#ifndef COBTENERFECHASALDACONCRCROPA
#define COBTENERFECHASALDACONCRCROPA
#include "stdafx.h"
#include <RecordSet.HPP>
class CObtenerFechaSaldaConCrCropa : public CRecordSet 
{
public:
    CObtenerFechaSaldaConCrCropa(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerFechaSaldaConCrCropa();
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
    
    long                cliente;
    SqlTimeStamp        fechaultcompra;
    SqlTimeStamp        fechaultimacomprames1;
    SqlTimeStamp        fechaultimacomprames2;
    SqlTimeStamp        fechaultimacomprames3;
    SqlTimeStamp        fechaultimacomprames4;
    SqlTimeStamp        fechaultimacomprames5;
    long                interessobrecompra;
};
#endif COBTENERFECHASALDACONCRCROPA
