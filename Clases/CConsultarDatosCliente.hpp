// Consulta original solicitada:...
//  select departamento, clase, grupo, retorno FROM gnconsultargrabarclientepromicion( '9529047', '4', '2011-07-30' )
    
#ifndef CCONSULTARDATOSCLIENTE
#define CCONSULTARDATOSCLIENTE
#include "stdafx.h"
#include <RecordSet.hpp>
class CConsultarDatosCliente : public CRecordSet 
{
public:
    CConsultarDatosCliente(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarDatosCliente();
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
    
    long                departamento;
    long                clase;
    long                grupo;
	long                familia;
    long                retorno;
};
#endif CCONSULTARDATOSCLIENTE
