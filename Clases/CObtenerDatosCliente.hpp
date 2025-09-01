#ifndef COBTENERDATOSCLIENTE
#define COBTENERDATOSCLIENTE

#include <RecordSet.HPP>
class CObtenerDatosCliente : public CRecordSet 
{
public:
    CObtenerDatosCliente(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerDatosCliente();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[13];
    int nCTipo[13];
    long nLongitud[13];
    long nLongResp[13];
    void *pVar[13];
    
    long                cliente;
    char                puntualidad[3];
    long                casa;
    long                telefono;
    char                nombre[17];
    char                apellidopaterno[17];
    char                apellidomaterno[17];
    SqlTimeStamp        fechanacimiento;
    long                calle;
    short int           ciudad;
    short int           colonia;
    short int           limitecredito;
};
#endif COBTENERDATOSCLIENTE
