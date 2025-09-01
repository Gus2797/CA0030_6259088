#ifndef CREESTRUCTURADAL
#define CREESTRUCTURADAL
#include <RecordSet.HPP>

class CReestructuraDAL : public CRecordSet
{
public:
    CReestructuraDAL(C_ODBC *odbc_ext);
    ~CReestructuraDAL();
    void activarCols();
    bool esProsectoRestructura(int cMoras, char cPuntualidad, int cCiudad, char cSitEspecial);
    bool guardaHitReestructura(int iTienda, int iCaja, long lEmpleado, int iAbono, int iOpcFinaliza);
    bool ValidaFormalizoReestructura(long lCliente);
    bool ValidaTestigoReestructura(long lCliente);

    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pValor[2];


    int esCliente;
    int iFormalizo;
    int iClienteTestigo;
};
#endif REESTRUCTURADAL