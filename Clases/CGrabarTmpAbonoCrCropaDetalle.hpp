// Consulta original solicitada:...
//  select num_cliente,imp_saldo,imp_interesadicional,idu_tipodeduccion,fec_ultimomovto,num_sistema,num_caja,num_tienda from tmp_carteraropadetalle
    
#ifndef CGRABARTMPABONOCRCROPADETALLE
#define CGRABARTMPABONOCRCROPADETALLE
#include "stdafx.h"
#include <RecordSet.hpp>
class CGrabarTmpAbonoCrCropaDetalle : public CRecordSet 
{
public:
    CGrabarTmpAbonoCrCropaDetalle(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpAbonoCrCropaDetalle();
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
    
    long                num_cliente;
    long                imp_saldo;
    long                imp_interesadicional;
    long                idu_tipodeduccion;
    SqlTimeStamp        fec_ultimomovto;
    short int           num_sistema;
    short int           num_caja;
    short int           num_tienda;
};
#endif CGRABARTMPABONOCRCROPADETALLE
