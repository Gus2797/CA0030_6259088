// Consulta original solicitada:...
//  SELECT cEncabezado, cParrafo1, cParrafo2, cParrafo3, cParrafo4 FROM gnobtenermensajepromociondirecta( '5', '7', '1', 'M', 'S', 'JORGE ANTONIO', 'RAMIREZ', 'MEDINA' )
    
#ifndef COBTENERMENSAJEPROMOCIONDIRECTA
#define COBTENERMENSAJEPROMOCIONDIRECTA
#include "stdafx.h"
#include <RecordSet.hpp>
class CObtenerMensajePromocionDirecta : public CRecordSet 
{
public:
    CObtenerMensajePromocionDirecta(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerMensajePromocionDirecta();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[6];
    int nCTipo[6];
    long nLongitud[6];
    long nLongResp[6];
    void *pVar[6];
    
    char                cencabezado[84];
    char                cparrafo1[257];
    char                cparrafo2[208];
    char                cparrafo3[154];
    char                cparrafo4[38];
};
#endif COBTENERMENSAJEPROMOCIONDIRECTA
