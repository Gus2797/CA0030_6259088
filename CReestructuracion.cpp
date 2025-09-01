#include "stdafx.h"
#include "sysCapturarAbono.h"
#include "CReestructuracion.h"
#include ".\Creestructuracion.h"
#include <process.h>
#include "CReestructuraDAL.hpp"


CReestructuracion::CReestructuracion(long lcliente, long limp_vencido, long limp_abonobase, char *cpuntualidad, char *csitespecial, int iciudadCliente) {
    lCliente = lcliente;
    imp_AbonoBase = limp_abonobase;
    imp_Vencido = limp_vencido;
    cPuntualidad = cpuntualidad[0];
    csitEspecial = csitespecial[0];
    ciudadCliente = iciudadCliente;
    CalcularMoras();
}
CReestructuracion::CReestructuracion(long lcliente)
{
    lCliente = lcliente;
}

CReestructuracion::~CReestructuracion() {

}

void CReestructuracion::CalcularMoras()
{
    iMoras = 0;
    if (imp_Vencido > 0 && imp_AbonoBase > 0)
    {
        int aux = 0;

        if(((imp_Vencido < 0) ^ (imp_AbonoBase > 0)) && (imp_Vencido%imp_AbonoBase))
        {
            aux = 1;
        }

        iMoras = imp_Vencido / imp_AbonoBase + aux;

    }
}


bool CReestructuracion::VerificarCanditado()
{
    bool bRegresa = false;

    CReestructuraDAL oDAL(&odbc);
    if (oDAL.esProsectoRestructura(iMoras, cPuntualidad, ciudadCliente, csitEspecial))
    {
        bRegresa = true;
        oDAL.activarCols();
        if (oDAL.Leer())
        {
            this->bEsCanditado = (oDAL.esCliente == 1);
        }
    }

    return bRegresa;
}

bool CReestructuracion::GuardaHitReestructura(int iTienda, int iCaja, long lEmpleado, int iAbono, int iOpcFinaliza)
{
    CReestructuraDAL oDAL(&odbc);
    bool bFlag = true;
    bFlag = oDAL.guardaHitReestructura(iTienda, iCaja, lEmpleado, iAbono, iOpcFinaliza);
    return bFlag;
}

bool CReestructuracion::ValidaFormalizoReestructura()
{
    CReestructuraDAL oDAL(&odbc);
    bool bFlag = false;
    if (oDAL.ValidaFormalizoReestructura(lCliente))
    {
        oDAL.activarCols();
        if (oDAL.leer())
        {
            bFlag = (oDAL.iFormalizo == 1);
        }
    }
    return bFlag;
}

short CReestructuracion::ValidaTestigoReestructura(long lCliente)
{
    CReestructuraDAL oDAL(&odbc);
    short iFlag = 0;
    if (oDAL.ValidaTestigoReestructura(lCliente))
    {
        oDAL.activarCols();
        if (oDAL.leer())
        {
            iFlag = (short)oDAL.iClienteTestigo;
        }
    }
    return iFlag;
}

