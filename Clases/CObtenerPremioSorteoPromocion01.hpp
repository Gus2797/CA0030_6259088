#ifndef COBTENERPREMIOSORTEOPROMOCION01
#define COBTENERPREMIOSORTEOPROMOCION01
#include "stdafx.h"
#include <RecordSet.hpp>
class CObtenerPremioSorteoPromocion01 : public CRecordSet 
{
public:
    CObtenerPremioSorteoPromocion01(C_ODBC *odbc_ext,bool bFlagCommit = true, const char *select=NULL);
    ~CObtenerPremioSorteoPromocion01();
    void activarCols();
	void inicializar( bool bFlagCommit ); //Vulnerabilidad Use of Uninitialized Variable
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[7];
    int nCTipo[7];
    long nLongitud[7];
    long nLongResp[7];
    void *pVar[7];
	bool bFlagCommit;
    
    long                boleto;
    char                descripcion[37];
    short int           tipo;
    long                importe;
	short int           campana;
	long                foliocupon;
};
#endif COBTENERPREMIOSORTEOPROMOCION01
