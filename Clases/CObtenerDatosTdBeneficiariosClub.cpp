#include "COBTENERDATOSTDBENEFICIARIOSCLUB.HPP"
CObtenerDatosTdBeneficiariosClub::CObtenerDatosTdBeneficiariosClub(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=32;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_INTEGER;
    nSqlTipo[1] = SQL_INTEGER;
    nSqlTipo[2] = SQL_CHAR;
    nSqlTipo[3] = SQL_CHAR;
    nSqlTipo[4] = SQL_CHAR;
    nSqlTipo[5] = SQL_CHAR;
    nSqlTipo[6] = SQL_CHAR;
    nSqlTipo[7] = SQL_SMALLINT;
    nSqlTipo[8] = SQL_SMALLINT;
    nSqlTipo[9] = SQL_VARCHAR;
    nSqlTipo[10] = SQL_BIGINT;
    nSqlTipo[11] = SQL_CHAR;
    nSqlTipo[12] = SQL_CHAR;
    nSqlTipo[13] = SQL_CHAR;
    nSqlTipo[14] = SQL_SMALLINT;
    nSqlTipo[15] = SQL_SMALLINT;
    nSqlTipo[16] = SQL_VARCHAR;
    nSqlTipo[17] = SQL_BIGINT;
    nSqlTipo[18] = SQL_CHAR;
    nSqlTipo[19] = SQL_CHAR;
    nSqlTipo[20] = SQL_CHAR;
    nSqlTipo[21] = SQL_SMALLINT;
    nSqlTipo[22] = SQL_SMALLINT;
    nSqlTipo[23] = SQL_VARCHAR;
    nSqlTipo[24] = SQL_BIGINT;
    nSqlTipo[25] = SQL_CHAR;
    nSqlTipo[26] = SQL_CHAR;
    nSqlTipo[27] = SQL_CHAR;
    nSqlTipo[28] = SQL_SMALLINT;
    nSqlTipo[29] = SQL_SMALLINT;
    nSqlTipo[30] = SQL_VARCHAR;
    nSqlTipo[31] = SQL_BIGINT;
   
    nCTipo[0] = SQL_C_SLONG;
    nCTipo[1] = SQL_C_SLONG;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_CHAR;
    nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_CHAR;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_SSHORT;
    nCTipo[8] = SQL_C_SSHORT;
    nCTipo[9] = SQL_C_CHAR;
    nCTipo[10] = SQL_C_SBIGINT;
    nCTipo[11] = SQL_C_CHAR;
    nCTipo[12] = SQL_C_CHAR;
    nCTipo[13] = SQL_C_CHAR;
    nCTipo[14] = SQL_C_SSHORT;
    nCTipo[15] = SQL_C_SSHORT;
    nCTipo[16] = SQL_C_CHAR;
    nCTipo[17] = SQL_C_SBIGINT;
    nCTipo[18] = SQL_C_CHAR;
    nCTipo[19] = SQL_C_CHAR;
    nCTipo[20] = SQL_C_CHAR;
    nCTipo[21] = SQL_C_SSHORT;
    nCTipo[22] = SQL_C_SSHORT;
    nCTipo[23] = SQL_C_CHAR;
    nCTipo[24] = SQL_C_SBIGINT;
    nCTipo[25] = SQL_C_CHAR;
    nCTipo[26] = SQL_C_CHAR;
    nCTipo[27] = SQL_C_CHAR;
    nCTipo[28] = SQL_C_SSHORT;
    nCTipo[29] = SQL_C_SSHORT;
    nCTipo[30] = SQL_C_CHAR;
    nCTipo[31] = SQL_C_SBIGINT;
 
    nLongitud[0] = 5;
    nLongitud[1] = 5;
    nLongitud[2] = 66;
    nLongitud[3] = 66;
    nLongitud[4] = 32;
    nLongitud[5] = 32;
    nLongitud[6] = 32;
    nLongitud[7] = 3;
    nLongitud[8] = 3;
    nLongitud[9] = 107;
    nLongitud[10] = 9;
    nLongitud[11] = 32;
    nLongitud[12] = 32;
    nLongitud[13] = 32;
    nLongitud[14] = 3;
    nLongitud[15] = 3;
    nLongitud[16] = 107;
    nLongitud[17] = 9;
    nLongitud[18] = 32;
    nLongitud[19] = 32;
    nLongitud[20] = 32;
    nLongitud[21] = 3;
    nLongitud[22] = 3;
    nLongitud[23] = 107;
    nLongitud[24] = 9;
    nLongitud[25] = 32;
    nLongitud[26] = 32;
    nLongitud[27] = 32;
    nLongitud[28] = 3;
    nLongitud[29] = 3;
    nLongitud[30] = 107;
    nLongitud[31] = 9;
    pVar[0] = &folio;
    pVar[1] = &cliente;
    pVar[2] =  nombreasegurado;
    pVar[3] =  nombreconyuge;
    pVar[4] =  nombre1;
    pVar[5] =  apellidopaterno1;
    pVar[6] =  apellidomaterno1;
    pVar[7] = &porcentaje1;
    pVar[8] = &parentesco1;
    pVar[9] = &fechanacimiento1;
    pVar[10] = &telefono1;
    pVar[11] =  nombre2;
    pVar[12] =  apellidopaterno2;
    pVar[13] =  apellidomaterno2;
    pVar[14] = &porcentaje2;
    pVar[15] = &parentesco2;
    pVar[16] = &fechanacimiento2;
    pVar[17] = &telefono2;
    pVar[18] =  nombre3;
    pVar[19] =  apellidopaterno3;
    pVar[20] =  apellidomaterno3;
    pVar[21] = &porcentaje3;
    pVar[22] = &parentesco3;
    pVar[23] = &fechanacimiento3;
    pVar[24] = &telefono3;
    pVar[25] =  nombre4;
    pVar[26] =  apellidopaterno4;
    pVar[27] =  apellidomaterno4;
    pVar[28] = &porcentaje4;
    pVar[29] = &parentesco4;
    pVar[30] = &fechanacimiento4;
    pVar[31] = &telefono4;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CObtenerDatosTdBeneficiariosClub::~CObtenerDatosTdBeneficiariosClub()
{
    Commit();
}
    
void CObtenerDatosTdBeneficiariosClub::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CObtenerDatosTdBeneficiariosClub::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("TdBeneficiarios");
    return (retorno);
}
BOOL CObtenerDatosTdBeneficiariosClub::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (folio, cliente, nombreasegurado, nombreconyuge, nombre1, apellidopaterno1, apellidomaterno1, porcentaje1, parentesco1, fechanacimiento1, telefono1, nombre2, apellidopaterno2, apellidomaterno2, porcentaje2, parentesco2, fechanacimiento2, telefono2, nombre3, apellidopaterno3, apellidomaterno3, porcentaje3, parentesco3, fechanacimiento3, telefono3, nombre4, apellidopaterno4, apellidomaterno4, porcentaje4, parentesco4, fechanacimiento4, telefono4) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
