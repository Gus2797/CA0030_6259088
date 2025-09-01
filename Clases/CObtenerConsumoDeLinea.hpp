// Consulta original solicitada:...
//  SELECT iExcesoCompra, iLimiteDeCredito, iFlagClienteJoven, iPorcentajeCompra, lImporteClienteJoven FROM gnObtenerConsumoDeLinea01( '1', 'A', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', ' ', '1' );
    
#ifndef COBTENERCONSUMODELINEA
#define COBTENERCONSUMODELINEA
#include "stdafx.h"
#include <RecordSet.hpp>
class CObtenerConsumoDeLinea : public CRecordSet 
{
public:
    CObtenerConsumoDeLinea(C_ODBC *odbc_ext, bool bFlagCommit = true, const char *select=NULL);
    ~CObtenerConsumoDeLinea();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[6];
    int nCTipo[6];
    long nLongitud[6];
    long nLongResp[6];
    void *pVar[6];
	bool bFlagCommit;
    
    long                iexcesocompra;
    long                ilimitedecredito;
    short int           iflagclientejoven;
    short int           iporcentajecompra;
    short int           limporteclientejoven;
};
#endif COBTENERCONSUMODELINEA
