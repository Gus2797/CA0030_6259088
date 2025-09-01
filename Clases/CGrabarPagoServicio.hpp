#ifndef CGRABARPAGOSERVICIO
#define CGRABARPAGOSERVICIO
#include "stdafx.h"
#include <RecordSet.HPP>
class CGrabarPagoServicio : public CRecordSet 
{
public:
    CGrabarPagoServicio(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarPagoServicio();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[10];
    int nCTipo[10];
    long nLongitud[10];
    long nLongResp[10];
    void *pVar[10];
    
    char                ccontratocfe[257];
    char                cimportecfe[257];
    short int           iflagcfe;
    short int           iregistroscfe;
    char                ccontratotelmex[257];
    char                cimportetelmex[257];
    short int           iflagtelmex;
    short int           iregistrostelmex;
    short int           irespuesta;
};
#endif CGRABARPAGOSERVICIO
