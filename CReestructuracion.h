#pragma once
#include "afxwin.h"

class CReestructuracion {

public:
    CReestructuracion(long lcliente, long imp_vencido, long imp_abonobase, char *cpuntualidad, char *csitespecial, int ciudadcliente);
    CReestructuracion(long lcliente);
    ~CReestructuracion();


private:
    void CalcularMoras();


public:
    int iMoras,
        ciudadCliente;
    long lCliente,
        imp_Vencido,
        imp_AbonoBase;
    char cPuntualidad,
        csitEspecial;
    bool bEsCanditado;

    bool VerificarCanditado();
    bool GuardaHitReestructura(int iTienda, int iCaja, long lEmpleado, int iAbono, int iOpcFinaliza);
    bool ValidaFormalizoReestructura();
    short ValidaTestigoReestructura(long lCliente);
};