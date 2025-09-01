#include "CCONSULTARNOMPUNTFECHACRCLIENTE.HPP"
CConsultarNomPuntFechaCrCliente::CConsultarNomPuntFechaCrCliente(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=9;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_CHAR;
    nSqlTipo[3] = SQL_CHAR;
    nSqlTipo[4] = SQL_CHAR;
    nSqlTipo[5] = SQL_CHAR;
    nSqlTipo[6] = SQL_CHAR;
    nSqlTipo[7] = SQL_VARCHAR;
    nSqlTipo[8] = SQL_CHAR;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_CHAR;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_CHAR;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_CHAR;
 
    nLongitud[0] = 5;
    nLongitud[1] = 17;
    nLongitud[2] = 17;
    nLongitud[3] = 17;
    nLongitud[4] = 3;
    nLongitud[5] = 22;
    nLongitud[6] = 3;
    nLongitud[7] = 107;
    nLongitud[8] = 3;
    pVar[0] = &cliente;
    pVar[1] =  nombre;
    pVar[2] =  apellidopaterno;
    pVar[3] =  apellidomaterno;
    pVar[4] =  sexo;
    pVar[5] =  lugartrabajo;
    pVar[6] =  situacionespecial;
    pVar[7] = &fechanacimiento;
    pVar[8] =  puntualidad;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarNomPuntFechaCrCliente::~CConsultarNomPuntFechaCrCliente()
{
    Commit();
}
    
void CConsultarNomPuntFechaCrCliente::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarNomPuntFechaCrCliente::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crcliente");
    return (retorno);
}
BOOL CConsultarNomPuntFechaCrCliente::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, nombre, apellidopaterno, apellidomaterno, sexo, lugartrabajo, situacionespecial, fechanacimiento, puntualidad) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
