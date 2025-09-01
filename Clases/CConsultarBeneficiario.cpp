#include "CCONSULTARBENEFICIARIO.HPP"
CConsultarBeneficiario::CConsultarBeneficiario(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=23;
    odbcRet=TRUE;
    flagInsertar = 0;
    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_CHAR;
    nSqlTipo[2] = SQL_CHAR;
    nSqlTipo[3] = SQL_SMALLINT;
    nSqlTipo[4] = SQL_SMALLINT;
    nSqlTipo[5] = SQL_BIGINT;
    nSqlTipo[6] = SQL_VARCHAR;
    nSqlTipo[7] = SQL_CHAR;
    nSqlTipo[8] = SQL_CHAR;
    nSqlTipo[9] = SQL_CHAR;
    nSqlTipo[10] = SQL_SMALLINT;
    nSqlTipo[11] = SQL_SMALLINT;
    nSqlTipo[12] = SQL_BIGINT;
    nSqlTipo[13] = SQL_VARCHAR;
    nSqlTipo[14] = SQL_CHAR;
    nSqlTipo[15] = SQL_CHAR;
    nSqlTipo[16] = SQL_CHAR;
    nSqlTipo[17] = SQL_SMALLINT;
    nSqlTipo[18] = SQL_SMALLINT;
    nSqlTipo[19] = SQL_BIGINT;
    nSqlTipo[20] = SQL_VARCHAR;
    nSqlTipo[21] = SQL_CHAR;
    nSqlTipo[22] = SQL_INTEGER;
   
    nCTipo[0] = SQL_C_CHAR;
    nCTipo[1] = SQL_C_CHAR;
    nCTipo[2] = SQL_C_CHAR;
    nCTipo[3] = SQL_C_SSHORT;
    nCTipo[4] = SQL_C_SSHORT;
    nCTipo[5] = SQL_C_SBIGINT;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_CHAR;
    nCTipo[9] = SQL_C_CHAR;
    nCTipo[10] = SQL_C_SSHORT;
    nCTipo[11] = SQL_C_SSHORT;
    nCTipo[12] = SQL_C_SBIGINT;
    nCTipo[13] = SQL_C_CHAR;
    nCTipo[14] = SQL_C_CHAR;
    nCTipo[15] = SQL_C_CHAR;
    nCTipo[16] = SQL_C_CHAR;
    nCTipo[17] = SQL_C_SSHORT;
    nCTipo[18] = SQL_C_SSHORT;
    nCTipo[19] = SQL_C_SBIGINT;
    nCTipo[20] = SQL_C_CHAR;
    nCTipo[21] = SQL_C_CHAR;
    nCTipo[22] = SQL_C_SLONG;
 
    nLongitud[0] = 17;
    nLongitud[1] = 17;
    nLongitud[2] = 17;
    nLongitud[3] = 3;
    nLongitud[4] = 3;
    nLongitud[5] = 9;
    nLongitud[6] = 107;
    nLongitud[7] = 17;
    nLongitud[8] = 17;
    nLongitud[9] = 17;
    nLongitud[10] = 3;
    nLongitud[11] = 3;
    nLongitud[12] = 9;
    nLongitud[13] = 107;
    nLongitud[14] = 17;
    nLongitud[15] = 17;
    nLongitud[16] = 17;
    nLongitud[17] = 3;
    nLongitud[18] = 3;
    nLongitud[19] = 9;
    nLongitud[20] = 107;
    nLongitud[21] = 3;
    nLongitud[22] = 5;
    pVar[0] =  nombre1;
    pVar[1] =  apellidopaterno1;
    pVar[2] =  apellidomaterno1;
    pVar[3] = &porcentaje1;
    pVar[4] = &parentesco1;
    pVar[5] = &telefono1;
    pVar[6] = &fechanacimiento1;
    pVar[7] =  nombre2;
    pVar[8] =  apellidopaterno2;
    pVar[9] =  apellidomaterno2;
    pVar[10] = &porcentaje2;
    pVar[11] = &parentesco2;
    pVar[12] = &telefono2;
    pVar[13] = &fechanacimiento2;
    pVar[14] =  nombre3;
    pVar[15] =  apellidopaterno3;
    pVar[16] =  apellidomaterno3;
    pVar[17] = &porcentaje3;
    pVar[18] = &parentesco3;
    pVar[19] = &telefono3;
    pVar[20] = &fechanacimiento3;
    pVar[21] = tiposeguro;
    pVar[22] = &folio;
                                                                  
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
    
    
CConsultarBeneficiario::~CConsultarBeneficiario()
{
   
}
    
void CConsultarBeneficiario::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    flagInsertar=1;
}
 
BOOL CConsultarBeneficiario::prepararInsert()
{
BOOL retorno = FALSE;
    retorno=prepararInsert("tdBeneficiarios");
    return (retorno);
}
BOOL CConsultarBeneficiario::prepararInsert(const char *nombreTabla)
{
BOOL retorno = FALSE;
int i;
CString sqlTxtInsert;
                                                                  
    if (flagInsertar==0) activarCols();
   sqlTxtInsert.Format("INSERT INTO %s (nombre1, apellidopaterno1, apellidomaterno1, porcentaje1, parentesco1, telefono1, fechanacimiento1, nombre2, apellidopaterno2, apellidomaterno2, porcentaje2, parentesco2, telefono2, fechanacimiento2, nombre3, apellidopaterno3, apellidomaterno3, porcentaje3, parentesco3, telefono3, fechanacimiento3, btrim, folio) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",nombreTabla);
    retorno = CRecordSet::PrepararInsert(sqlTxtInsert);
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        ActivarInsert(i, nCTipo[i], nSqlTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
    return (retorno);                                                              
}
