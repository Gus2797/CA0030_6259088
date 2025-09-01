#ifndef CCONSULTARCLIENTE
#define CCONSULTARCLIENTE
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarCliente : public CRecordSet 
{
public:
    CConsultarCliente(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarCliente();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[12];
    int nCTipo[12];
    long nLongitud[12];
    long nLongResp[12];
    void *pVar[12];
    
    char                nombre[17];
    char                apellidopaterno[17];
    char                apellidomaterno[17];
    short int           ciudad;
    short int           colonia;
    char                puntualidad[3];
    char                situacionespecial[3];
    short int           causasitesp;
    char                sexo[3];
    SqlTimeStamp        fechanacimiento;
    short int           ingresomensual;
};
#endif CCONSULTARCLIENTE
