#ifndef CCONSULTARNOMPUNTFECHACRCLIENTE
#define CCONSULTARNOMPUNTFECHACRCLIENTE
#include "stdafx.h"
#include <RecordSet.HPP>
class CConsultarNomPuntFechaCrCliente : public CRecordSet 
{
public:
    CConsultarNomPuntFechaCrCliente(C_ODBC *odbc_ext, const char *select=NULL);
    ~CConsultarNomPuntFechaCrCliente();
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
    
    long                cliente;
    char                nombre[17];
    char                apellidopaterno[17];
    char                apellidomaterno[17];
    char                sexo[3];
    char                lugartrabajo[22];
    char                situacionespecial[3];
    SqlTimeStamp        fechanacimiento;
    char                puntualidad[3];
};
#endif CCONSULTARNOMPUNTFECHACRCLIENTE
