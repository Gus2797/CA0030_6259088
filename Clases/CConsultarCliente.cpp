#include "CCONSULTARCLIENTE.HPP"
CConsultarCliente::CConsultarCliente(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=11;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_CHAR;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_SMALLINT;
    nSqlTipo[5] = SQL_CHAR;
    nSqlTipo[6] = SQL_CHAR;
    nSqlTipo[7] = SQL_SMALLINT;
    nSqlTipo[8] = SQL_CHAR;
    nSqlTipo[9] = SQL_VARCHAR;
    nSqlTipo[10] = SQL_SMALLINT;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SSHORT;
    nCTipo[5] = SQL_C_CHAR;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_SSHORT;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_CHAR;
    nCTipo[10] = SQL_C_SSHORT;
 
    nLongitud[0] = 17;
    nLongitud[1] = 17;
    nLongitud[2] = 17;
    nLongitud[3] = 3;
    nLongitud[4] = 3;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    nLongitud[8] = 3;
    nLongitud[9] = 107;
    nLongitud[10] = 3;
    pVar[0] =  nombre;
    pVar[1] =  apellidopaterno;
    pVar[2] =  apellidomaterno;
    pVar[3] = &ciudad;
    pVar[4] = &colonia;
    pVar[5] =  puntualidad;
    pVar[6] =  situacionespecial;
    pVar[7] = &causasitesp;
    pVar[8] =  sexo;
    pVar[9] = &fechanacimiento;
    pVar[10] = &ingresomensual;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarCliente::~CConsultarCliente()
{
    Commit();
}
    
void CConsultarCliente::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarCliente::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("crcliente");
    return (retorno);
}
BOOL CConsultarCliente::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (nombre, apellidopaterno, apellidomaterno, ciudad, colonia, puntualidad, situacionespecial, causasitesp, sexo, fechanacimiento, ingresomensual) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
