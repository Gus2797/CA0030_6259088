#include "COBTENERDATOSCLIENTE.HPP"
CObtenerDatosCliente::CObtenerDatosCliente(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=12;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_INTEGER;
    nSqlTipo[3] = SQL_INTEGER;
    nSqlTipo[4] = SQL_CHAR;
    nSqlTipo[5] = SQL_CHAR;
    nSqlTipo[6] = SQL_CHAR;
    nSqlTipo[7] = SQL_VARCHAR;
    nSqlTipo[8] = SQL_INTEGER;
    nSqlTipo[9] = SQL_SMALLINT;
    nSqlTipo[10] = SQL_SMALLINT;
    nSqlTipo[11] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_SLONG;
    nCTipo[3] = SQL_C_SLONG;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_CHAR;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_SLONG;
    nCTipo[9] = SQL_C_SSHORT;
    nCTipo[10] = SQL_C_SSHORT;
    nCTipo[11] = SQL_C_SSHORT;
 
    nLongitud[0] = 5;
    nLongitud[1] = 3;
    nLongitud[2] = 5;
    nLongitud[3] = 5;
    nLongitud[4] = 17;
    nLongitud[5] = 17;
    nLongitud[6] = 17;
    nLongitud[7] = 107;
    nLongitud[8] = 5;
    nLongitud[9] = 3;
    nLongitud[10] = 3;
    nLongitud[11] = 3;
    pVar[0] = &cliente;
    pVar[1] =  puntualidad;
    pVar[2] = &casa;
    pVar[3] = &telefono;
    pVar[4] =  nombre;
    pVar[5] =  apellidopaterno;
    pVar[6] =  apellidomaterno;
    pVar[7] = &fechanacimiento;
    pVar[8] = &calle;
    pVar[9] = &ciudad;
    pVar[10] = &colonia;
    pVar[11] = &limitecredito;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CObtenerDatosCliente::~CObtenerDatosCliente()
{
    Commit();
}
    
void CObtenerDatosCliente::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CObtenerDatosCliente::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crCliente");
    return (retorno);
}
BOOL CObtenerDatosCliente::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (cliente, puntualidad, casa, telefono, nombre, apellidopaterno, apellidomaterno, fechanacimiento, calle, ciudad, colonia, limitecredito) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
