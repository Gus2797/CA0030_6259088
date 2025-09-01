// Consulta original solicitada:...
//  SELECT iMinutosPregunta,iOpcionStatusAfore,iDiasEncuestaSolicitud,iMesesEncuestaNoCotiza,cDescMes,iEdadCliente,iOpcInvitacionAforeContado,iOpcInvitacionesAforeCliente from fun_obtenerparametrosencuestas()
    
#ifndef CPARAMETROS
#define CPARAMETROS
#include "stdafx.h"
#include <RecordSet.hpp>
class CParametros : public CRecordSet 
{
public:
    CParametros(C_ODBC *odbc_ext, const char *select=NULL);
    ~CParametros();
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
    
    short int           iminutospregunta;
    short int           iopcionstatusafore;
    short int           idiasencuestasolicitud;
    short int           imesesencuestanocotiza;
    char                cdescmes[12];
    short int           iedadcliente;
    short int           iopcinvitacionaforecontado;
    short int           iopcinvitacionesaforecliente;
};
#endif CPARAMETROS
